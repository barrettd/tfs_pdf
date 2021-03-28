// ---------------------------------------------------------------------------------
//  TFSPdfWriter.cpp
//
//  Created by Barrett Davis on 3/20/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#include "TFSPdfStream.hpp"
#include "TFSPdfWriter.hpp"

namespace tfs {

static const char VERSION[] = { "1.10" };

TFSPdfWriter::TFSPdfWriter( const std::string &path ):
m_fontMap(),
m_stream( path ),
m_objPositions( 1, 0 ),     // Store 0 as the first position.
m_rootIndex( 0 ),
m_pageCatalogIndex( 0 ),
m_infoIndex( 0 ),
m_xrefPosition( 0 ) {
}

TFSPdfWriter::operator bool( void ) const {
    if( !m_stream ) {
        return false;
    }
    return true;
}

bool TFSPdfWriter::writeHeader( void ) {
    if( !m_stream ) {
        return false;
    }
    m_stream << "%PDF-1.4\n";   // Header; specifies that this file uses PDF version 1.4
    m_stream << "%¥±ëáœñø\n";   // Comment containing at least 4 high bit bytes.
    return true;
}

std::size_t TFSPdfWriter::getNextObjectIndex( void ) {
    const std::streamoff position = m_stream.tellp();
    const std::size_t index = m_objPositions.size();
    m_objPositions.push_back( position );
    return index;
}

std::size_t TFSPdfWriter::startObject( void ) {
    std::size_t index = getNextObjectIndex();     // Object index
    m_stream << index << " 0 obj ";
    return index;
}

void TFSPdfWriter::endObject( void ) {
    m_stream << "endobj\n\n";
}

bool TFSPdfWriter::writeFonts( const TFSPdfDocument &document ) {
    if( !m_stream ) {
        return false;
    }
    const std::vector<TFSPdfFont>&fonts = document.getObservedFonts();
    int fontNumber = 1;
    for( TFSPdfFont font : fonts ) {
        const std::size_t index = startObject();
        TFSPdfFontMapNode *fontNode = m_fontMap.addNode( font, fontNumber++, index );
        m_stream << "<< /Type /Font /Subtype /Type1 /Name /" << fontNode->shortName << " /BaseFont /" << fontNode->fullname << " >>\n";
        endObject();
    }
    return true;
}

bool TFSPdfWriter::writeRootDictionary( void ) {
    if( !m_stream ) {
        return false;
    }
    m_rootIndex = startObject();                        // Object 1 index
    const std::size_t nextIndex = m_rootIndex + 1;      // Next index
    m_stream << "<< /Type /Catalog ";                   // Begin a Catalog dictionary
    m_stream << "/Pages " << nextIndex << " 0 R >>\n";  // The root Pages object: Object 2, Generation 0
    endObject();                                        // End object
    return true;
}

bool TFSPdfWriter::writePagesDictionary( const TFSPdfDocument &document ) {     // AKA Page Catalog
    if( !m_stream ) {
        return false;
    }
    const std::size_t pageCount = document.pageCount();
    m_pageCatalogIndex = startObject();                 // Object 2 index
    m_stream << "<< /Type /Pages\n";                    // Begin a Pages dictionary
    m_stream << "/Kids [";                              // An array of the individual pages in the document
    bool first = true;
    for( const std::unique_ptr<TFSPdfPage> &page : document ) {
        const std::size_t objectIndex = getNextObjectIndex();   // The positions will be overwritten later.
        const std::size_t streamIndex = getNextObjectIndex();
        page->setObjectIndex( objectIndex );
        page->setStreamIndex( streamIndex );
        if( first ) {
            first = false;
        } else {
            m_stream << " ";
        }
        m_stream << objectIndex << " 0 R";
    }
    m_stream << "]\n";                                  // End of array

    m_stream << "/Count " << pageCount << "\n";         // The array contains N pages
    m_stream << ">>\n";                                 // End dictionary
    endObject();                                        // End object
    return true;
}

void TFSPdfWriter::emitFontDictionary( const std::unique_ptr<TFSPdfPage> &page ) {
    m_stream << "<< /Font << ";
    for( TFSPdfFont font : page->observedFonts ) {
        const TFSPdfFontMapNode *node = m_fontMap.getNode( font );
        m_stream << "/" << node->shortName << " " << node->objectIndex << " 0 R ";    // /F1 9 0 R
    }
    m_stream << ">> >>";
}

bool TFSPdfWriter::writePageDictionary( const TFSPdfDocument &document, const std::unique_ptr<TFSPdfPage> &page ) {
    if( !m_stream ) {
        return false;
    }
    const long width  = document.width();               // Assume all pages are the same dimension.
    const long height = document.height();

    const std::size_t objectIndex = page->getObjectIndex();
    const std::size_t streamIndex = page->getStreamIndex();

    m_objPositions[objectIndex] = m_stream.tellp();     // Go back and fill in current position.
    m_stream << objectIndex << " 0 obj\n";              // Object 3, Generation 0
    m_stream << "<< /Type /Page\n";                     // Begin a Page dictionary
    m_stream << "/Parent " << m_pageCatalogIndex << " 0 R\n";
    m_stream << "/Resources ";                          // The resources for this page…
    emitFontDictionary( page );
    m_stream << "\n";
    m_stream << "/Contents " << streamIndex << " 0 R\n";// The contents of the page: Object 4, Generation 0
    m_stream << "/MediaBox [0 0 ";                      // Global page size, lower-left to
    m_stream << width << " " << height << "]\n";        // upper-right, measured in points
    m_stream << ">>\n";                                 // End dictionary
    endObject();                                        // End object
    return true;
}

bool TFSPdfWriter::writePageContents( const std::unique_ptr<TFSPdfPage> &page ) {
    if( !m_stream ) {
        return false;
    }
    const std::size_t streamIndex = page->getStreamIndex();
    m_objPositions[streamIndex] = m_stream.tellp();     // Go back and fill in current position.
    m_stream << streamIndex << " 0 obj\n";              // Object 3, Generation 0

    TFSPdfStream stream;
    for( const std::unique_ptr<TFSPdfStreamable> &object : *page ) {
        stream << *object;
    }
    const std::vector<std::unique_ptr<TFSPdfText>> &texts = page->getTexts();
    for( const std::unique_ptr<TFSPdfText> &text : texts ) {
        text->stream( stream, m_fontMap );
    }
    const std::string payload     = stream.str();
    const std::size_t payloadSize = payload.size();

    m_stream << "<< /Length " << payloadSize << " >>\n";// A stream, payloadSize bytes in length
    m_stream << "stream\n";                             // Begin stream
    
    m_stream << payload;
    
    m_stream << "endstream\n";                          // End stream
    endObject();                                        // End object
    return true;
}

static void write2Digits( std::ostream &stream, int value ) {
    stream << std::setfill( '0' ) << std::setw( 2 ) << value;
}

bool TFSPdfWriter::writeInfoDictionary( const TFSPdfDocument &document ) {
    if( !m_stream ) {
        return false;
    }
    const TFSPdfDate &date = document.getCreationDate();
    
    m_infoIndex = startObject();
    m_stream << "<< /Creator (TFSPdfWriter, Version " << VERSION << ")\n";
    m_stream << "/Producer (Tree Frog Software, http://www.thefrog.com)\n";
    if( date ) {
        m_stream << "/CreationDate (D:" << date.year;   // e.g. (D:20210301072826)  TODO: Timezone?
        write2Digits( m_stream, date.month  );
        write2Digits( m_stream, date.day    );
        write2Digits( m_stream, date.hour   );
        write2Digits( m_stream, date.minute );
        write2Digits( m_stream, date.second );
        m_stream << ")\n";
        m_stream << std::setfill( ' ' ) << std::setw( 0 );  // Reset
    }
    m_stream << ">>\n";
    endObject();                                            // End object
    return true;
}

bool TFSPdfWriter::writeCrossReference( void ) {
    if( !m_stream ) {
        return false;
    }
    const std::size_t count = m_objPositions.size();
    m_xrefPosition = m_stream.tellp();          // Remember the xref position
    m_stream << "xref\n";                       // The xref section
    m_stream << "0 " << count << "\n";          // A contiguous group of N objects, starting with Object 0
    m_stream << "0000000000 65535 f \n";        // Object 0: is object number 0, generation 65535, free, space+linefeed
    for( long ii = 1; ii < count; ii++ ) {      // Remember, the first postion stored is zero.
        m_stream << std::setfill( '0' ) << std::setw( 10 ) << m_objPositions[ii] << " 00000 n \n";    // Object N: at byte offset Y, generation 0, in use, space+linefeed
    }
    m_stream << std::setfill( ' ' ) << std::setw( 0 );  // Reset
    return true;
}

bool TFSPdfWriter::writeTrailer( void ) {
    if( !m_stream ) {
        return false;
    }
    const std::size_t count = m_objPositions.size();
    m_stream << "trailer\n";                            // The trailer section
    m_stream << "<< /Root " << m_rootIndex << " 0 R\n";  // The document root is Object, Generation 0 (the Catalog dictionary)
    m_stream << "/Size " << count << "\n";              // The document contains N indirect objects
    m_stream << "/Info " << m_infoIndex << " 0 R\n>>\n";
    m_stream << "startxref\n";                          // xref location
    m_stream << m_xrefPosition << "\n";                 // byte offset start of xref
    return true;
}

bool TFSPdfWriter::writeEnd( void ) {
    if( !m_stream ) {
        return false;
    }
    m_stream << "%%EOF";      // End of File
    return true;
}
    
TFSPdfWriter& TFSPdfWriter::operator <<( const TFSPdfDocument &document ) {
    if( !m_stream || !document.ok()) {
        return *this;
    }
    writeHeader();
    writeFonts( document );
    writeRootDictionary();
    writePagesDictionary( document );
    for( const std::unique_ptr<TFSPdfPage> &page : document ) {
        writePageDictionary( document, page );
        writePageContents( page );
    }
    writeInfoDictionary( document );
    writeCrossReference();
    writeTrailer();
    writeEnd();
    m_stream.close();
    return *this;
}

}   // namespace tfs

