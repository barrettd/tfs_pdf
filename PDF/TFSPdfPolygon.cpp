// ---------------------------------------------------------------------------------
//  TFSPdfPolygon.cpp
//
//  Created by Barrett Davis on 3/26/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#include "TFSPdfPolygon.hpp"


namespace tfs {


TFSPdfPolygon::TFSPdfPolygon( double lineWidth, double x1, double y1, double x2, double y2, double shading, bool hasShading ):
TFSPdfLine( lineWidth, x1, y1, x2, y2 ) {
    m_shading    = shading;
    m_hasShading = hasShading;
}

TFSPdfPolygon::TFSPdfPolygon( double lineWidth, const std::vector<std::pair<double,double>> &verticies, double shading, bool hasShading ):
TFSPdfLine( lineWidth, verticies ) {
    m_shading    = shading;
    m_hasShading = hasShading;
}

TFSPdfPolygon::~TFSPdfPolygon( void ) {
}

void TFSPdfPolygon::stream( TFSPdfStream &stream ) const {
    if( !ok()) {
        return;
    }
    stream.setLineWidth( m_lineWidth );
    bool first = true;
    for( const std::pair<double,double> &pair : m_verticies ) {
        stream << pair.first << pair.second;
        if( first ) {
            stream << "m ";    // Move to x,y
            first = false;
        } else {
            stream << "l ";    // Line to x,y
        }
    }
    stream << "h ";            // Close the current subpath by appending a straight line segment from the current point to the starting point of the subpath.
    stream.fillOrStroke( m_hasShading, m_shading );
    return;
}


}   // namespace tfs
