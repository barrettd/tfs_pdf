// ---------------------------------------------------------------------------------
//  TFSPdfLine.cpp
//
//  Created by Barrett Davis on 3/22/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#include "TFSPdfLine.hpp"

namespace tfs {

TFSPdfLine::TFSPdfLine( double width, double x1, double y1, double x2, double y2 ):
verticies(),
lineWidth( width ) {
    setLine( x1, y1, x2, y2 );
}

TFSPdfLine::TFSPdfLine( double width, const std::vector<std::pair<double,double>> &verts ):
verticies( verts ),
lineWidth( width ) {
}

bool TFSPdfLine::empty( void ) const {
    return verticies.empty();
}

bool TFSPdfLine::setLineWidth( double width ) {
    if( width < LINE_WIDTH_MIN || width > LINE_WIDTH_MAX ) {
        return false;
    }
    lineWidth = width;
    return true;
}

bool TFSPdfLine::setLine( double x1, double y1, double x2, double y2 ) {
    std::pair<double,double> aa( x1, y1 );
    std::pair<double,double> bb( x2, y2 );
    verticies.push_back( aa );
    verticies.push_back( bb );
    return true;
}

bool TFSPdfLine::setPolyline( const std::vector<std::pair<double,double>> &verts ) {
    verticies = verts;
    return !verticies.empty();
}



}   // namespace tfs
