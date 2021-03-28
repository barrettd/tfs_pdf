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
    return m_objects.empty();
}

std::vector<std::unique_ptr<TFSPdfStreamable>>::const_iterator TFSPdfPage::begin( void ) const {
    return m_objects.begin();
}
std::vector<std::unique_ptr<TFSPdfStreamable>>::const_iterator TFSPdfPage::end( void ) const {
    return m_objects.end();
}

const std::vector<std::unique_ptr<TFSPdfText>>& TFSPdfPage::getTexts( void ) const {
    return m_texts;
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
    std::unique_ptr<TFSPdfLine> line = std::make_unique<TFSPdfLine>( lineWidth, x1, y1, x2, y2 );
    if( !line->ok()) {
        return false;
    }
    m_objects.push_back( std::move( line ));
    return true;
}

bool TFSPdfPage::setPolyline( double lineWidth, const std::vector<std::pair<double,double>> &verticies ) {
    std::unique_ptr<TFSPdfLine> line = std::make_unique<TFSPdfLine>( lineWidth, verticies  );
    if( !line->ok()) {
        return false;
    }
    m_objects.push_back( std::move( line ));
    return true;
}

bool TFSPdfPage::setPolygon( double lineWidth, const std::vector<std::pair<double,double>> &verticies ) {
    std::unique_ptr<TFSPdfPolygon> polygon = std::make_unique<TFSPdfPolygon>( lineWidth, verticies );
    if( !polygon->ok()) {
        return false;
    }
    m_objects.push_back( std::move( polygon ));
    return true;
}

bool TFSPdfPage::setPolygon( double lineWidth, const std::vector<std::pair<double,double>> &verticies, double shading ) {
    std::unique_ptr<TFSPdfPolygon> polygon = std::make_unique<TFSPdfPolygon>( lineWidth, verticies, shading );
    if( !polygon->ok()) {
        return false;
    }
    m_objects.push_back( std::move( polygon ));
    return true;
}

bool TFSPdfPage::setCircle( double lineWidth, double x, double y, double radius ) {
    std::unique_ptr<TFSPdfCircle> circle = std::make_unique<TFSPdfCircle>( lineWidth, x, y, radius );
    if( !circle->ok()) {
        return false;
    }
    m_objects.push_back( std::move( circle ));
    return true;
}

bool TFSPdfPage::setCircle( double lineWidth, double x, double y, double radius, double shading ) {
    std::unique_ptr<TFSPdfCircle> circle = std::make_unique<TFSPdfCircle>( lineWidth, x, y, radius, shading, true );
    if( !circle->ok()) {
        return false;
    }
    m_objects.push_back( std::move( circle ));
    return true;
}

bool TFSPdfPage::setBox( double lineWidth, double x,  double y, double width, double height ) {
    std::unique_ptr<TFSPdfBox> box = std::make_unique<TFSPdfBox>( lineWidth, x, y, width, height );
    if( !box->ok()) {
        return false;
    }
    m_objects.push_back( std::move( box ));
    return true;
}

bool TFSPdfPage::setBox( double lineWidth, double x,  double y, double width, double height, double shading ) {
    std::unique_ptr<TFSPdfBox> box = std::make_unique<TFSPdfBox>( lineWidth, x, y, width, height, shading, true );
    if( !box->ok()) {
        return false;
    }
    m_objects.push_back( std::move( box ));
    return true;
}

bool TFSPdfPage::setText( std::size_t fontSize, double x, double y, const std::string &text ) {
    std::unique_ptr<TFSPdfText> textObject = std::make_unique<TFSPdfText>( m_currentFont, fontSize, x, y, text );
    if( !textObject->ok()) {
        return false;
    }
    m_texts.push_back( std::move( textObject ));
    return true;
}


}   // namespace tfs
