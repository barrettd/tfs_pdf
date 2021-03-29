// ---------------------------------------------------------------------------------
//  TFSPdfPolygon.cpp
//
//  Created by Barrett Davis on 3/26/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#include "TFSPdfPolygon.hpp"
#include "TFSPdfStream.hpp"


namespace tfs {

TFSPdfPolygon::TFSPdfPolygon( const TFSPdfPolygon &other ):
TFSPdfLine( other ) {
}

TFSPdfPolygon::TFSPdfPolygon( TFSPdfStreamableType objType, TFSPainting painting, double lineWidth, double shading, const std::vector<std::pair<double,double>> &verticies ):
TFSPdfLine( objType, painting, lineWidth, shading, verticies ) {
}

TFSPdfPolygon::TFSPdfPolygon( TFSPainting painting, double lineWidth, double shading, const std::vector<std::pair<double,double>> &verticies ):
TFSPdfLine( TFSPdfStreamableType::POLYGON, painting, lineWidth, shading, verticies ) {
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
    stream.fillOrStroke( m_painting, m_shading );
    return;
}


}   // namespace tfs
