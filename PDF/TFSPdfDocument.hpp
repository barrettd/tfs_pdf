// ---------------------------------------------------------------------------------
//  TFSPdfDocument.hpp
//
//  Created by Barrett Davis on 3/22/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
// Dimensions are in points ( 72 per inch )
// e.g. 8.5 x 11 = 612 x 792;  A4 = 595 x 842;
// Document coordinates: x min is left, x max is right. y min is bottom, y max is top.
// Shapes and lines are drawn in the order that they were set into the document.
// Text is drawn after (on top of) the shapes and lines.
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
    // 72 Points per inch. e.g. (8.5 x 11) = (612 x 792);  A4 = (595 x 842);
    TFSPdfDocument( long width = 612, long height = 792, TFSPdfFont font = TFSPdfFont::DEFAULT );
    virtual ~TFSPdfDocument( void );

    bool ok( void ) const;          // Among other things, an empty document is not ok...
    bool empty( void ) const;
    
    long width( void ) const;
    long height( void ) const;
    
    bool   setLineWidth( double width );
    double getLineWidth( void ) const;
    
    bool setCreationDate( int year, int month, int day, int hour = 0, int minute = 0, int second = 0 );     // Optional, 24 hour
    
    bool newPage( void );
    std::size_t pageCount( void ) const;
    std::size_t currentPageNumber( void ) const;    // Starts at 1.
    
    void append( const TFSPdfDocument &other );
    TFSPdfDocument &operator <<( const TFSPdfDocument &other );
    
    TFSPdfFont  setFont( TFSPdfFont font );         // Returns previous font.
    TFSPdfFont  setFont( TFSPdfFontFamily fontFamily, bool bold = false, bool italic = false );
    std::size_t setFontSize( std::size_t size );

    bool setLine( double x1, double y1, double x2, double y2 );
    bool setPolyline( const std::vector<std::pair<double,double>> &verticies );
    
    // Note: shading [0.0 to 1.0] with 0.0 = black, 1.0 = white
    
    bool setPolygon( const std::vector<std::pair<double,double>> &verticies );                          // Stroked (framed)
    bool setPolygon( const std::vector<std::pair<double,double>> &verticies, double shading );          // Filled with shading
    bool setFramedPolygon( const std::vector<std::pair<double,double>> &verticies, double shading );    // Filled and stroked (framed)

    // Circle center (x,y) and radius
    bool setCircle( double x, double y, double radius );                                    // Stroked (framed)
    bool setCircle( double x, double y, double radius, double shading );                    // Filled with grey shading
    bool setFramedCircle( double x, double y, double radius, double shading );              // Filled and stroked (framed)

    bool setBox( double x, double y, double width, double height );                         // Stroked (framed)
    bool setBox( double x, double y, double width, double height, double shading );         // Filled with grey shading
    bool setFramedBox( double x, double y, double width, double height, double shading );   // Filled and stroked (framed)
    
    bool setText( double x, double y, const std::string &text );
    bool setText( double x, double y, const char *text );
};


}   // namespace tfs

#endif /* TFSPdfDocument_hpp */
