// ---------------------------------------------------------------------------------
//  TFSPdfText.cpp
//
//  Created by Barrett Davis on 3/22/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#include "TFSPdfText.hpp"

namespace tfs {


TFSPdfText::TFSPdfText( TFSPdfFont font, std::size_t fontSize, double x, double y, const std::string &text ):
TFSPdfStreamable( x, y ),
m_font( font ),
m_fontSize( fontSize ),
m_text( text ) {
}

TFSPdfText::~TFSPdfText( void ) {
}

bool TFSPdfText::empty( void ) const {
    return m_text.empty();
}

std::size_t TFSPdfText::size( void ) const {
    return m_text.size();
}

bool TFSPdfText::ok( void ) const {
    return TFSPdfStreamable::ok() && !m_text.empty();
}

static void escapeText( std::string &dst, const std::string &src ) {
    // Sequence | Meaning
    // ---------------------------------------------
    // \n       | LINE FEED (0Ah) (LF)
    // \r       | CARRIAGE RETURN (0Dh) (CR)
    // \t       | HORIZONTAL TAB (09h) (HT)
    // \b       | BACKSPACE (08h) (BS)
    // \f       | FORM FEED (FF)
    // \(       | LEFT PARENTHESIS (28h)
    // \)       | RIGHT PARENTHESIS (29h)
    // \\       | REVERSE SOLIDUS (5Ch) (Backslash)
    // \ddd     | Character code ddd (octal)
    for( const char ch : src ) {
        if( ch == '(' ) {
            dst.append( "\\(" );
        } else if( ch == ')' ) {
            dst.append( "\\)" );
        } else if( ch == '\\' ) {
            dst.append( "\\\\" );
        } else {
            dst.push_back( ch );
        }
    }
    return;
}

void TFSPdfText::stream( TFSPdfStream &stream ) const {
}

void TFSPdfText::stream( TFSPdfStream &stream, const TFSPdfFontMap &fontMap ) {
    if( !ok()) {
        return;
    }
    std::string escaped;
    escapeText( escaped, m_text );
    const TFSPdfFontMapNode *node = fontMap.getNode( m_font );
    stream << "BT ";                                                // Begin Text object
    stream << "/" << node->shortName << " " << m_fontSize << "Tf "; // Use F1 font at 18 point size
    stream << m_x << m_y << "Td ";                                  // Position the text at x,y
    stream << "(" << escaped << ") Tj ";                            // Show text
    stream << "ET\n";                                               // End Text
    return;
}


}   // namespace tfs
