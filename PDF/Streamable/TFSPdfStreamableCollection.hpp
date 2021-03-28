// ---------------------------------------------------------------------------------
//  TFSPdfStreamableCollection.hpp
//
//  Created by Barrett Davis on 3/28/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#ifndef TFSPdfStreamableCollection_hpp
#define TFSPdfStreamableCollection_hpp

#include <memory>
#include <vector>
#include "TFSPdfBox.hpp"
#include "TFSPdfCircle.hpp"
#include "TFSPdfLine.hpp"
#include "TFSPdfPolygon.hpp"
#include "TFSPdfText.hpp"

namespace tfs {

class TFSPdfStreamableCollection {
private:
    std::vector<std::unique_ptr<TFSPdfStreamable>> m_objects;
    
private:
    void cloneBox(     const std::unique_ptr<TFSPdfStreamable> &obj );
    void cloneCircle(  const std::unique_ptr<TFSPdfStreamable> &obj );
    void cloneLine(    const std::unique_ptr<TFSPdfStreamable> &obj );
    void clonePolygon( const std::unique_ptr<TFSPdfStreamable> &obj );
    void cloneText(    const std::unique_ptr<TFSPdfStreamable> &obj );

public:
    TFSPdfStreamableCollection( const TFSPdfStreamableCollection &other );
    TFSPdfStreamableCollection( void );
    
    bool empty( void ) const;
    std::size_t size( void ) const;
    
    std::vector<std::unique_ptr<TFSPdfStreamable>>::const_iterator begin( void ) const;
    std::vector<std::unique_ptr<TFSPdfStreamable>>::const_iterator end(   void ) const;
    
    void stream( TFSPdfStream &stream ) const;

    bool setLine(     double lineWidth, double x1, double y1, double x2, double y2 );
    bool setPolyline( double lineWidth, const std::vector<std::pair<double,double>> &verticies );

    bool setPolygon( double lineWidth, const std::vector<std::pair<double,double>> &verticies );
    bool setPolygon( double lineWidth, const std::vector<std::pair<double,double>> &verticies, double shading );

    bool setCircle( double lineWidth, double x, double y, double radius );
    bool setCircle( double lineWidth, double x, double y, double radius, double shading );

    bool setBox( double lineWidth, double x,  double y,  double width, double height );
    bool setBox( double lineWidth, double x,  double y,  double width, double height, double shading );    // shading [0.0 to 1.0] with 0.0 = black, 1.0 = white

    bool setText( TFSPdfFont font, std::size_t fontSize, double x, double y, const std::string &text );
};


}   // namespace tfs


#endif /* TFSPdfStreamableCollection_hpp */
