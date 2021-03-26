// ---------------------------------------------------------------------------------
//  TFSPdfPage.cpp
//
//  Created by Barrett Davis on 3/22/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#include <algorithm>
#include "TFSPdfPage.hpp"

namespace tfs {


TFSPdfPage::TFSPdfPage( TFSPdfFont currentFont, std::size_t pageNumber ):
observedFonts(),
lines(),
circles(),
boxes(),
texts(),
m_currentFont( currentFont ),
m_pageNumber( pageNumber ),
m_objectIndex( 0 ),
m_streamIndex( 0 ) {
    recordFont( currentFont );
}

void TFSPdfPage::recordFont( TFSPdfFont font ) {
    // Keep a list of the fonts used in this page.
    std::vector<TFSPdfFont>::const_iterator it = std::find( observedFonts.begin(), observedFonts.end(), font );
    if( it == observedFonts.end()) {
        observedFonts.push_back( font );
    }
    return;
}

TFSPdfFont TFSPdfPage::setFont( TFSPdfFont font ) {
    TFSPdfFont previousFont = m_currentFont;
    m_currentFont = font;
    recordFont( font );
    return previousFont;
}

bool TFSPdfPage::empty( void ) const {
    return texts.empty() && lines.empty() && circles.empty() && boxes.empty();
}

std::size_t TFSPdfPage::getPageNumber( void ) const {
    return m_pageNumber;
}

void TFSPdfPage::setObjectIndex( std::size_t index ) {
    m_objectIndex = index;
}
std::size_t TFSPdfPage::getObjectIndex( void ) const {
    return m_objectIndex;
}

void TFSPdfPage::setStreamIndex( std::size_t index ) {
    m_streamIndex = index;
}
std::size_t TFSPdfPage::getStreamIndex( void ) const {
    return m_streamIndex;
}

bool TFSPdfPage::setLine( double lineWidth, double x1, double y1, double x2, double y2 ) {
    lines.push_back( std::make_unique<TFSPdfLine>( lineWidth, x1, y1, x2, y2 ));
    return true;
}

bool TFSPdfPage::setPolyline( double lineWidth, const std::vector<std::pair<double,double>> &verticies ) {
    lines.push_back( std::make_unique<TFSPdfLine>( lineWidth, verticies ));
    return true;
}

bool TFSPdfPage::setCircle( double lineWidth, double x, double y, double radius ) {
    circles.push_back( std::make_unique<TFSPdfCircle>( lineWidth, x, y, radius ));
    return true;
}

bool TFSPdfPage::setCircle( double lineWidth, double x, double y, double radius, double shading ) {
    circles.push_back( std::make_unique<TFSPdfCircle>( lineWidth, x, y, radius, shading, true ));
    return true;
}

bool TFSPdfPage::setBox( double lineWidth, long x,  long y,  long width, long height ) {
    boxes.push_back( std::make_unique<TFSPdfBox>( lineWidth, x, y, width, height ));
    return true;
}

bool TFSPdfPage::setBox( double lineWidth, long x,  long y,  long width, long height, double shading ) {
    boxes.push_back( std::make_unique<TFSPdfBox>( lineWidth, x, y, width, height, shading, true ));
    return true;
}

bool TFSPdfPage::setText( std::size_t fontSize, long x,  long y, const std::string &text ) {
    texts.push_back( std::make_unique<TFSPdfText>( m_currentFont, fontSize, x, y, text ));
    return true;
}


}   // namespace tfs
