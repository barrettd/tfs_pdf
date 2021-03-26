// ---------------------------------------------------------------------------------
//  TFSPdfWriter.hpp
//
//  Created by Barrett Davis on 3/20/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
// Dimensions are in points.  72 points to an inch.
// ---------------------------------------------------------------------------------
#ifndef TFSPdfWriter_hpp
#define TFSPdfWriter_hpp

#include <fstream>
#include "TFSPdfDocument.hpp"
#include "TFSPdfFontMap.hpp"

namespace tfs {

class TFSPdfWriter {
private:
    TFSPdfFontMap     m_fontMap;
    std::ofstream     m_stream;
    std::vector<std::streamoff> m_objPositions;
    std::size_t       m_rootIndex;
    std::size_t       m_pageCatalogIndex;
    std::size_t       m_infoIndex;
    std::streamoff    m_xrefPosition;
    double            m_lineWidth;
    
private:
    std::size_t getNextObjectIndex( void );
    std::size_t startObject( void );
    void        endObject( void );
    
private:
    bool writeHeader( void );
    bool writeFonts( const TFSPdfDocument &document );
    bool writeRootDictionary( void );
    bool writePagesDictionary( const TFSPdfDocument &document );
    void emitFontDictionary( const std::unique_ptr<TFSPdfPage> &page );
    bool writePageDictionary( const TFSPdfDocument &document, const std::unique_ptr<TFSPdfPage> &page );
    
    void streamLineWidth( std::ostream &stream, double width );

    void streamLine(      std::ostream &stream, const std::unique_ptr<TFSPdfLine> &line );
    void streamPageLines( std::ostream &stream, const std::unique_ptr<TFSPdfPage> &page );

    void streamCircle(      std::ostream &stream, const std::unique_ptr<TFSPdfCircle> &circle );
    void streamPageCircles( std::ostream &stream, const std::unique_ptr<TFSPdfPage>   &page );

    void streamBox(       std::ostream &stream, const std::unique_ptr<TFSPdfBox>  &box );
    void streamPageBoxes( std::ostream &stream, const std::unique_ptr<TFSPdfPage> &page );

    void streamPageText(  std::ostream &stream, const std::unique_ptr<TFSPdfPage> &page );

    bool writePageContents(const std::unique_ptr<TFSPdfPage> &page );
    bool writeInfoDictionary( const TFSPdfDocument &document );
    bool writeCrossReference( void );
    bool writeTrailer( void );
    bool writeEnd( void );
    
public:
    TFSPdfWriter( const std::string &path );
    
    explicit operator bool( void ) const;
           
    TFSPdfWriter &operator <<( const TFSPdfDocument &document );
};

}   // namespace tfs

#endif /* TFSPdfWriter_hpp */
