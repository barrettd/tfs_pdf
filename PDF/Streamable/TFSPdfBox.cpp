// ---------------------------------------------------------------------------------
//  TFSPdfBox.cpp
//
//  Created by Barrett Davis on 3/22/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#include "TFSPdfBox.hpp"
#include "TFSPdfStream.hpp"

namespace tfs {

TFSPdfBox::TFSPdfBox( const TFSPdfBox &other ):
TFSPdfStreamable( other ),
m_width(  other.m_width ),
m_height( other.m_height ) {
}

TFSPdfBox::TFSPdfBox( TFSPainting painting, double lineWidth, double shading, double x, double y, double width, double height ):
TFSPdfStreamable( TFSPdfStreamableType::BOX, painting, lineWidth, shading, x, y ),
m_width(  width ),
m_height( height ) {
}

TFSPdfBox::~TFSPdfBox( void ) {
}

bool TFSPdfBox::ok( void ) const {
    return TFSPdfStreamable::ok() && m_width > 0.0 && m_height > 0.0;
}

void TFSPdfBox::stream( TFSPdfStream &stream ) const {
    if( !ok()) {
        return;
    }
    stream.setLineWidth( m_lineWidth );
    stream << m_x << m_y << m_width << m_height << "re\n";     // x,y w,h Rectangle
    stream.fillOrStroke( m_painting, m_shading );
    return;
}


}   // namespace tfs
