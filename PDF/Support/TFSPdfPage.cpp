// ---------------------------------------------------------------------------------
//  TFSPdfPage.cpp
//
//  Created by Barrett Davis on 3/22/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#include <algorithm>
#include "TFSPdfPage.hpp"

namespace tfs {

TFSPdfPage::TFSPdfPage( const TFSPdfPage &other ):
observedFonts( other.observedFonts ),
m_objects(     other.m_objects ),
m_texts(       other.m_texts   ),
m_currentFont( other.m_currentFont ),
m_pageNumber(  other.m_pageNumber  ),
m_objectIndex( other.m_objectIndex ),
m_streamIndex( other.m_streamIndex ) {
}

TFSPdfPage::TFSPdfPage( TFSPdfFont currentFont, std::size_t pageNumber ):
observedFonts(),
m_objects(),
m_texts(),
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
    return m_objects.empty() && m_texts.empty();
}

bool TFSPdfPage::ok( void ) const {
    return !empty();
}

const TFSPdfStreamableCollection& TFSPdfPage::getObjects( void ) const {
    return m_objects;
}

const TFSPdfTextCollection& TFSPdfPage::getTexts( void ) const {
    return m_texts;
}

void TFSPdfPage::setPageNumber( std::size_t number ) {
    m_pageNumber = number;
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

bool TFSPdfPage::setPolyline( double lineWidth, const std::vector<std::pair<double,double>> &verticies ) {
    return m_objects.setPolyline( lineWidth, verticies );
}

bool TFSPdfPage::setPolygon( TFSPdfStreamable::TFSPainting painting, double lineWidth, double shading, const std::vector<std::pair<double,double>> &verticies ) {
    return m_objects.setPolygon( painting, lineWidth, shading, verticies );
}

bool TFSPdfPage::setCircle( TFSPdfStreamable::TFSPainting painting, double lineWidth, double shading, double x, double y, double radius ) {
    return m_objects.setCircle( painting, lineWidth, shading, x, y, radius );
}

bool TFSPdfPage::setBox( TFSPdfStreamable::TFSPainting painting, double lineWidth, double shading, double x, double y, double width, double height ) {
    return m_objects.setBox( painting, lineWidth, shading, x, y, width, height );
}

bool TFSPdfPage::setText( std::size_t fontSize, double x, double y, const std::string &text ) {
    return m_texts.setText( m_currentFont, fontSize, x, y, text );
}


}   // namespace tfs
