// ---------------------------------------------------------------------------------
//  TFSPdfBox.cpp
//
//  Created by Barrett Davis on 3/22/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#include "TFSPdfBox.hpp"

namespace tfs {

TFSPdfBox::TFSPdfBox( double strokeWidth, long x, long y, long width, long height, double shadingValue, bool hasShading ):
x( x ),
y( y ),
width( width ),
height( height ),
lineWidth( strokeWidth ),
shading( shadingValue ),
hasShading( hasShading ){
}

bool TFSPdfBox::ok( void ) const {
    return x >= 0.0 && y >= 0.0 && width > 0.0 && height > 0.0 && lineWidth > 0.0 && shading >= 0.0 && shading <= 1.0;
}


}   // namespace tfs
