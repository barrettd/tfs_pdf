// ---------------------------------------------------------------------------------
//  TFSPdfText.cpp
//
//  Created by Barrett Davis on 3/22/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#include "TFSPdfText.hpp"
#include "TFSPdfStream.hpp"

namespace tfs {

TFSPdfText::TFSPdfText( const TFSPdfText &other ):
TFSPdfStreamable( other ),
m_font(     other.m_font     ),
m_fontSize( other.m_fontSize ),
m_text(     other.m_text     ) {
}

TFSPdfText::TFSPdfText( TFSPdfFont font, std::size_t fontSize, double x, double y, const std::string &text ):
TFSPdfStreamable( TFSPdfStreamableType::TEXT, TFSPainting::STROKED, DEFAULT_LINE_WIDTH, DEFAULT_SHADING, x, y ),
m_font(     font     ),
m_fontSize( fontSize ),
m_text(     text     ) {
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
    return TFSPdfStreamable::ok() && m_fontSize > 0 && !m_text.empty();
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

void TFSPdfText::stream( TFSPdfStream &stream, const TFSPdfFontMap &fontMap ) const {
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
