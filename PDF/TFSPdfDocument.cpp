// ---------------------------------------------------------------------------------
//  TFSPdfDocument.hpp
//
//  Created by Barrett Davis on 3/22/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#include "TFSPdfDocument.hpp"

namespace tfs {

static constexpr double    LINE_WIDTH_DEFAULT = 1.0;
static constexpr long                MIN_WIDTH = 72;
static constexpr long               MIN_HEIGHT = 72;
static constexpr std::size_t DEFAULT_FONT_SIZE = 12;

TFSPdfDocument::TFSPdfDocument( long width, long height ):
m_pages(),
m_observedFonts(),
m_currentPage( nullptr ),
m_currentFont( TFSPdfFont::DEFAULT ),
m_fontSize( DEFAULT_FONT_SIZE ),
m_width(  width ),
m_height( height ),
m_lineWidth( LINE_WIDTH_DEFAULT ),
m_creationDate() {
    setFont( TFSPdfFont::DEFAULT );
    newPage();          // Start out with one blank page.
}

bool TFSPdfDocument::ok( void ) const {
    if( empty()) {
        return false;
    }
    if( m_width < MIN_WIDTH || m_height < MIN_HEIGHT ) {
        return false;
    }
    return true;
}

bool TFSPdfDocument::empty( void ) const {
    if( m_pages.size() > 1 ) {
        return false;
    }
    return m_currentPage->empty();
}

long TFSPdfDocument::width( void ) const {
    return m_width;
}

long TFSPdfDocument::height( void ) const {
    return m_height;
}

bool TFSPdfDocument::setLineWidth( double width ) {
    if( width < TFSPdfLine::LINE_WIDTH_MIN || width > TFSPdfLine::LINE_WIDTH_MAX ) {
        return false;
    }
    m_lineWidth = width;
    return true;
}

double TFSPdfDocument::getLineWidth( void ) const {
    return m_lineWidth;
}

bool TFSPdfDocument::setCreationDate( int year, int month, int day, int hour, int minute, int second ) {
    return m_creationDate.set( year, month, day, hour, minute, second );
}

const TFSPdfDate& TFSPdfDocument::getCreationDate( void ) const {
    return m_creationDate;
}

void TFSPdfDocument::recordFont( TFSPdfFont font ) {
    // Keep a list of the fonts used in this page.
    std::vector<TFSPdfFont>::const_iterator it = std::find( m_observedFonts.begin(), m_observedFonts.end(), font );
    if( it == m_observedFonts.end()) {
        m_observedFonts.push_back( font );
    }
    return;
}

TFSPdfFont TFSPdfDocument::setFont( TFSPdfFont font ) {
    recordFont( font );
    TFSPdfFont previousFont = m_currentFont;
    m_currentFont = font;
    if( m_currentPage != nullptr ) {
        return m_currentPage->setFont( font );
    }
    return previousFont;
}

TFSPdfFont TFSPdfDocument::setFont( TFSPdfFontFamily fontFamily, bool bold, bool italic ) {
    return setFont( getFont( fontFamily, bold, italic ));
}
  
std::size_t TFSPdfDocument::setFontSize( std::size_t size ) {
    const std::size_t previousSize = m_fontSize;
    m_fontSize = size;
    return previousSize;
}

bool TFSPdfDocument::newPage( void ) {
    std::unique_ptr<TFSPdfPage> page = std::make_unique<TFSPdfPage>( m_currentFont, m_pages.size() + 1 );  // Page numbering starts at one.
    m_currentPage = page.get();
    m_pages.push_back( std::move( page ));
    return true;
}

std::size_t TFSPdfDocument::pageCount( void ) const {
    return m_pages.size();
}

std::vector<std::unique_ptr<TFSPdfPage>>::const_iterator TFSPdfDocument::begin( void ) const {
    return m_pages.begin();
}

std::vector<std::unique_ptr<TFSPdfPage>>::const_iterator TFSPdfDocument::end( void ) const {
    return m_pages.end();
}

const std::vector<TFSPdfFont>& TFSPdfDocument::getObservedFonts( void ) const {
    return m_observedFonts;
}

bool TFSPdfDocument::setLine( double x1, double y1, double x2, double y2 ) {
    return m_currentPage->setLine( m_lineWidth, x1, y1, x2, y2 );
}

bool TFSPdfDocument::setPolyline( const std::vector<std::pair<double,double>> &verticies ) {
    return m_currentPage->setPolyline( m_lineWidth, verticies );
}

bool TFSPdfDocument::setCircle( double x, double y, double radius ) {    // Center (x,y) and radius
    return m_currentPage->setCircle( m_lineWidth, x, y, radius );
}

bool TFSPdfDocument::setCircle( double x, double y, double radius, double shading ) {
    return m_currentPage->setCircle( m_lineWidth, x, y, radius, shading );
}

bool TFSPdfDocument::setBox( long x, long y,  long width, long height ) {
    return m_currentPage->setBox( m_lineWidth, x, y, width, height );
}

bool TFSPdfDocument::setBox( long x, long y,  long width, long height, double shading ) {
    return m_currentPage->setBox( m_lineWidth, x, y, width, height, shading );
}

bool TFSPdfDocument::setText( long x, long y, const std::string &text ) {
    if( text.empty()) {
        return false;
    }
    return m_currentPage->setText( m_fontSize, x, y, text );
}

bool TFSPdfDocument::setText( long x,  long y, const char *text ) {
    if( text == nullptr || *text == 0 ) {
        return false;
    }
    std::string str{ text };
    return setText( x, y, str );
}

    
}   // namespace tfs
