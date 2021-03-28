// ---------------------------------------------------------------------------------
//  TFSPdfLine.cpp
//
//  Created by Barrett Davis on 3/22/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#include "TFSPdfLine.hpp"

namespace tfs {

TFSPdfLine::TFSPdfLine( double lineWidth, double x1, double y1, double x2, double y2 ):
TFSPdfStreamable( 0.0, 0.0, lineWidth ),
m_verticies() {
    std::pair<double,double> aa( x1, y1 );
    std::pair<double,double> bb( x2, y2 );
    m_verticies.push_back( aa );
    m_verticies.push_back( bb );
}

TFSPdfLine::TFSPdfLine( double lineWidth, const std::vector<std::pair<double,double>> &verts ):
TFSPdfStreamable( 0.0, 0.0, lineWidth ),
m_verticies( verts ) {
}

TFSPdfLine::~TFSPdfLine( void ) {
}

bool TFSPdfLine::empty( void ) const {
    return m_verticies.empty();
}

bool TFSPdfLine::ok( void ) const {
    return m_lineWidth > 0.0 && !m_verticies.empty();
}

void TFSPdfLine::stream( TFSPdfStream &stream ) const {
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
    stream << "s\n";            // Stroke
    return;
}


}   // namespace tfs
