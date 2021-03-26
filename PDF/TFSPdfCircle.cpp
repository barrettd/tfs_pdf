// ---------------------------------------------------------------------------------
//  TFSPdfCircle.cpp
//
//  Created by Barrett Davis on 3/26/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#include "TFSPdfCircle.hpp"

namespace tfs {

TFSPdfCircle::TFSPdfCircle( double strokeWidth, double x, double y, double radius, double shadingValue, bool hasShading ):
x( x ),
y( y ),
radius( radius ),
lineWidth( strokeWidth ),
shading( shadingValue ),
hasShading( hasShading ) {
}

bool TFSPdfCircle::ok( void ) const {
    return x >= 0.0 && y >= 0.0 && radius > 0.0 && lineWidth > 0.0 && shading >= 0.0 && shading <= 1.0;
}


}   // namespace tfs
