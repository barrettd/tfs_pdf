// ---------------------------------------------------------------------------------
//  TFSPdfStreamable.cpp
//
//  Created by Barrett Davis on 3/26/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#include "TFSPdfStreamable.hpp"

namespace tfs {


TFSPdfStreamable::TFSPdfStreamable( double x, double y, double lineWidth, double shading, bool hasShading ):
m_x( x ),
m_y( y ),
m_lineWidth( lineWidth ),
m_shading( shading ),
m_hasShading( hasShading ) {
}

TFSPdfStreamable::~TFSPdfStreamable( void ) {
}
    
bool TFSPdfStreamable::ok( void ) const {
    return m_x >= 0.0 && m_y >= 0.0  && m_lineWidth > 0.0 && m_shading >= 0.0 && m_shading <= 1.0;
}

TFSPdfStream& operator<<( TFSPdfStream &stream, const TFSPdfStreamable &streamable ) {
    streamable.stream( stream );
    return stream;
}


}   // namespace tfs
