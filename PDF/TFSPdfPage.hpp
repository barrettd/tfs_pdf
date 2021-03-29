// ---------------------------------------------------------------------------------
//  TFSPdfPage.hpp
//
//  Created by Barrett Davis on 3/22/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#ifndef TFSPdfPage_hpp
#define TFSPdfPage_hpp

#include "TFSPdfStreamableCollection.hpp"
#include "TFSPdfTextCollection.hpp"


namespace tfs {

class TFSPdfPage {
public:
    std::vector<TFSPdfFont> observedFonts;   // Page level observed fonts.
private:
    TFSPdfStreamableCollection  m_objects;
    TFSPdfTextCollection        m_texts;
    TFSPdfFont                  m_currentFont;
    std::size_t                 m_pageNumber;
    std::size_t                 m_objectIndex;
    std::size_t                 m_streamIndex;

private:
    void recordFont( TFSPdfFont font );

public:
    TFSPdfPage( const TFSPdfPage &other );
    TFSPdfPage( TFSPdfFont currentFont, std::size_t pageNumber );
 
    TFSPdfFont setFont( TFSPdfFont font );
    
    bool empty( void ) const;
    bool ok( void ) const;
    
    const TFSPdfStreamableCollection& getObjects( void ) const;
    const TFSPdfTextCollection&       getTexts( void ) const;
    
    void        setPageNumber( std::size_t number );
    std::size_t getPageNumber( void ) const;
    
    void        setObjectIndex( std::size_t index );
    std::size_t getObjectIndex( void ) const;
    void        setStreamIndex( std::size_t index );
    std::size_t getStreamIndex( void ) const;

    bool setPolyline( double lineWidth, const std::vector<std::pair<double,double>> &verticies );
    bool setPolygon( TFSPdfStreamable::TFSPainting painting, double lineWidth, double shading, const std::vector<std::pair<double,double>> &verticies );
    bool setCircle(  TFSPdfStreamable::TFSPainting painting, double lineWidth, double shading, double x, double y, double radius );
    bool setBox(     TFSPdfStreamable::TFSPainting painting, double lineWidth, double shading, double x, double y, double width, double height );
    bool setText( std::size_t fontSize, double x, double y, const std::string &text );

};

}   // namespace tfs

#endif /* TFSPdfPage_hpp */
