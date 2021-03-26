// ---------------------------------------------------------------------------------
//  TFSPdfPage.hpp
//
//  Created by Barrett Davis on 3/22/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#ifndef TFSPdfPage_hpp
#define TFSPdfPage_hpp

#include <memory>
#include <vector>
#include "TFSPdfBox.hpp"
#include "TFSPdfCircle.hpp"
#include "TFSPdfLine.hpp"
#include "TFSPdfText.hpp"


namespace tfs {

class TFSPdfPage {
public:
    std::vector<TFSPdfFont>              observedFonts;   // Page level observed fonts.
    std::vector<std::unique_ptr<TFSPdfLine>>     lines;
    std::vector<std::unique_ptr<TFSPdfCircle>> circles;
    std::vector<std::unique_ptr<TFSPdfBox>>      boxes;
    std::vector<std::unique_ptr<TFSPdfText>>     texts;
private:
    TFSPdfFont                               m_currentFont;
    std::size_t                              m_pageNumber;
    std::size_t                              m_objectIndex;
    std::size_t                              m_streamIndex;

private:
    void recordFont( TFSPdfFont font );

public:
    TFSPdfPage( TFSPdfFont currentFont, std::size_t pageNumber );
    
    TFSPdfFont setFont( TFSPdfFont font );
    
    bool empty( void ) const;
    
    std::size_t getPageNumber( void ) const;
    
    void        setObjectIndex( std::size_t index );
    std::size_t getObjectIndex( void ) const;
    void        setStreamIndex( std::size_t index );
    std::size_t getStreamIndex( void ) const;

    bool setLine( double lineWidth, double x1, double y1, double x2, double y2 );
    bool setPolyline( double lineWidth, const std::vector<std::pair<double,double>> &verticies );

    bool setCircle( double lineWidth, double x, double y, double radius );
    bool setCircle( double lineWidth, double x, double y, double radius, double shading );

    bool setBox( double lineWidth, long x,  long y,  long width, long height );
    bool setBox( double lineWidth, long x,  long y,  long width, long height, double shading );    // shading [0.0 to 1.0] with 0.0 = black, 1.0 = white

    bool setText( std::size_t fontSize, long x,  long y, const std::string &text );

};

}   // namespace tfs

#endif /* TFSPdfPage_hpp */
