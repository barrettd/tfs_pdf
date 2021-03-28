// ---------------------------------------------------------------------------------
//  TFSPdfCircle.cpp
//
//  Created by Barrett Davis on 3/26/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#include "TFSPdfCircle.hpp"

namespace tfs {

TFSPdfCircle::TFSPdfCircle( double strokeWidth, double x, double y, double radius, double shadingValue, bool hasShading ):
TFSPdfStreamable( x, y, strokeWidth, shadingValue, hasShading ),
m_radius( radius ) {
}

TFSPdfCircle::~TFSPdfCircle( void ) {
}

bool TFSPdfCircle::ok( void ) const {
    return TFSPdfStreamable::ok() && m_radius > 0.0;
}

void TFSPdfCircle::stream( TFSPdfStream &stream ) const {
    // https://stackoverflow.com/questions/1734745/how-to-create-circle-with-bézier-curves
    // Calculate end points and control points for the 4 Bézier curves
    // Remember that the X coordinates increase to the left and Y coordinates increase upwards.
    if( !ok()) {
        return;
    }
    const double r = m_radius;
    // End points:
    std::pair<double,double> top(    m_x,     m_y + r );    // 12 o' clock
    std::pair<double,double> right(  m_x + r, m_y     );    //  3 0' clock
    std::pair<double,double> bottom( m_x,     m_y - r );    //  6 o' clock
    std::pair<double,double> left(   m_x - r, m_y     );    //  9 o' clock

    stream.setLineWidth( m_lineWidth );
    // Construct 4 Béziers, clockwise from the top, each with 2 endpoints and 2 control points.
    constexpr double c = 0.552284749831;   // (4/3)*tan(pi/8) = 4*(sqrt(2)-1)/3 = 0.552284749831;
    const double cr = c * r;
    stream <<     top.first       <<    top.second << "m ";  // Move to the start position.
    stream <<    (top.first + cr) <<    top.second;           // Control point
    stream <<   right.first       << (right.second + cr);     // Control point
    stream <<   right.first       <<  right.second << "c ";  // End position.
    
    stream <<  right.first        << (right.second - cr);     // Control point
    stream << (bottom.first + cr) << bottom.second;           // Control point
    stream <<  bottom.first       << bottom.second << "c ";  // End position.
    
    stream << (bottom.first - cr) << bottom.second;           // Control point.
    stream <<    left.first       <<  (left.second - cr);     // Control point.
    stream <<    left.first       <<   left.second << "c ";  // End position.
    
    stream <<    left.first       <<  (left.second + cr);     // Control point.
    stream <<    (top.first - cr) <<    top.second;           // Control point.
    stream <<     top.first       <<    top.second << "c ";  // End position.
    stream.fillOrStroke( m_hasShading, m_shading );
    return;
}



}   // namespace tfs
