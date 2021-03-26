// ---------------------------------------------------------------------------------
//  TFSPdfDocument.hpp
//
//  Created by Barrett Davis on 3/22/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
// Dimensions are in points ( 72 per inch )
// e.g. 8.5 x 11 = 612 x 792;  A4 = 595 x 842;
// Document coordinates: x min is left, x max is right. y min is bottom, y max is top.
// Items are drawn in order: boxes, circles, lines then text.
// ---------------------------------------------------------------------------------
#ifndef TFSPdfDocument_hpp
#define TFSPdfDocument_hpp

#include "TFSPdfPage.hpp"
#include "TFSPdfDate.hpp"

namespace tfs {


class TFSPdfDocument {
    friend class TFSPdfWriter;     // Forward declaration
private:
    std::vector<std::unique_ptr<TFSPdfPage>> m_pages;
    std::vector<TFSPdfFont>                  m_observedFonts;   // Document level observed fonts.  There is a similar one for each page.
    TFSPdfPage *m_currentPage;
    TFSPdfFont  m_currentFont;
    std::size_t m_fontSize;
    long        m_width;            // Assume that all pages in the document have the same dimension.
    long        m_height;
    double      m_lineWidth;
    TFSPdfDate  m_creationDate;

private:    // Methods for class TFSPdfWriter:
    const TFSPdfDate &getCreationDate( void ) const;

    std::vector<std::unique_ptr<TFSPdfPage>>::const_iterator begin( void ) const;
    std::vector<std::unique_ptr<TFSPdfPage>>::const_iterator end( void ) const;
    
    const std::vector<TFSPdfFont>& getObservedFonts( void ) const;

private:
    void recordFont( TFSPdfFont font );

public:
    TFSPdfDocument( long width = 612, long height = 792 );           // Points 72 per inch. e.g. 8.5 x 11 = 612 x 792;  A4 = 595 x 842;

    bool ok( void ) const;          // Among other things, an empty document is not ok...
    bool empty( void ) const;
    
    long width( void ) const;
    long height( void ) const;
    
    bool   setLineWidth( double width );
    double getLineWidth( void ) const;
    
    bool setCreationDate( int year, int month, int day, int hour = 0, int minute = 0, int second = 0 );     // Optional
    
    bool newPage( void );
    std::size_t pageCount( void ) const;
    
    TFSPdfFont  setFont( TFSPdfFont font );     // Returns previous font.
    TFSPdfFont  setFont( TFSPdfFontFamily fontFamily, bool bold = false, bool italic = false );
    std::size_t setFontSize( std::size_t size );

    bool setLine( double x1, double y1, double x2, double y2 );
    bool setPolyline( const std::vector<std::pair<double,double>> &verticies );
    
    bool setCircle( double x, double y, double radius );                    // Center (x,y) and radius
    bool setCircle( double x, double y, double radius, double shading );    // Center (x,y) and radius, shading [0.0 to 1.0] with 0.0 == black

    bool setBox( long x,  long y,  long width, long height );
    bool setBox( long x,  long y,  long width, long height, double shading );    // shading [0.0 to 1.0] with 0.0 = black, 1.0 = white

    bool setText(  long x,  long y, const std::string &text );
    bool setText(  long x,  long y, const char *text );
};


}   // namespace tfs

#endif /* TFSPdfDocument_hpp */
