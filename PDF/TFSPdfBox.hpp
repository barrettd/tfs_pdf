// ---------------------------------------------------------------------------------
//  TFSPdfBox.cpp
//
//  Created by Barrett Davis on 3/22/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#ifndef TFSPdfBox_hpp
#define TFSPdfBox_hpp

namespace tfs {

class TFSPdfBox {
public:
    long x;
    long y;
    long width;
    long height;
    double lineWidth;
    double shading;     // [0.0 to 1.0] with 0.0 = black, 1.0 = white
    bool hasShading;
public:
    TFSPdfBox( double lineWidth, long x, long y, long width, long height, double shading = 0.0, bool hasShading = false );
    
    bool ok( void ) const;
};


}   // namespace tfs


#endif /* TFSPdfBox_hpp */
