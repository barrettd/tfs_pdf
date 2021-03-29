// ---------------------------------------------------------------------------------
//  TFSPdfColor.cpp
//
//  Created by Barrett Davis on 3/28/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#include "TFSPdfColor.hpp"

namespace tfs {

TFSPdfColor::TFSPdfColor( const TFSPdfColor &other ):
m_isColor( other.m_isColor ),
m_red(     other.m_red ),
m_green(   other.m_green ),
m_blue(    other.m_blue ),
m_grey(    other.m_grey ) {
}

TFSPdfColor::TFSPdfColor( double red, double green, double blue ):
m_isColor( true ),
m_red(   red ),
m_green( green ),
m_blue(  blue ),
m_grey( 0.0 ) {
}

TFSPdfColor::TFSPdfColor( double grey ):
m_isColor( false ),
m_red(   0.0 ),
m_green( 0.0 ),
m_blue(  0.0 ),
m_grey( grey ) {
}

bool TFSPdfColor::ok( void ) const {
    return m_red >= 0.0 && m_red <= 1.0 && m_green >= 0.0 && m_green <= 1.0 && m_blue >= 0.0 && m_blue <= 1.0 && m_grey >= 0.0 && m_grey <= 1.0;
}

void TFSPdfColor::stream( TFSPdfStream &stream ) const {
    // TODO: work here.
}

}   // namespace tfs

