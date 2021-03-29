// ---------------------------------------------------------------------------------
//  TFSPdfStreamable.cpp
//
//  Created by Barrett Davis on 3/26/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#include "TFSPdfStream.hpp"
#include "TFSPdfLine.hpp"

namespace tfs {


TFSPdfStreamable::TFSPdfStreamable( const TFSPdfStreamable &other ):
m_type(       other.m_type ),
m_painting(   other.m_painting ),
m_lineWidth(  other.m_lineWidth ),
m_shading(    other.m_shading   ),
m_x(          other.m_x ),
m_y(          other.m_y ) {
}

TFSPdfStreamable::TFSPdfStreamable( TFSPdfStreamableType objType, TFSPainting painting, double lineWidth, double shading, double x, double y ):
m_type(      objType  ),
m_painting(  painting ),
m_lineWidth( lineWidth ),
m_shading(   shading   ),
m_x(         x ),
m_y(         y ) {
}

TFSPdfStreamable::~TFSPdfStreamable( void ) {
}
    
TFSPdfStreamableType TFSPdfStreamable::getType( void ) const {
    return m_type;
}

bool TFSPdfStreamable::ok( void ) const {
    return m_x >= 0.0 && m_y >= 0.0 &&
           m_lineWidth >= TFSPdfLine::LINE_WIDTH_MIN && m_lineWidth <= TFSPdfLine::LINE_WIDTH_MAX &&
           m_shading >= 0.0 && m_shading <= 1.0;
}

TFSPdfStream& operator<<( TFSPdfStream &stream, const TFSPdfStreamable &streamable ) {
    streamable.stream( stream );
    return stream;
}


}   // namespace tfs
