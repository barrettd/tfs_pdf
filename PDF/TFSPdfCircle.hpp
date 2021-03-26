// ---------------------------------------------------------------------------------
//  TFSPdfCircle.hpp
//
//  Created by Barrett Davis on 3/26/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#ifndef TFSPdfCircle_hpp
#define TFSPdfCircle_hpp

namespace tfs {

class TFSPdfCircle {
public:
    double x;
    double y;
    double radius;
    double lineWidth;
    double shading;     // [0.0 to 1.0] with 0.0 = black, 1.0 = white
    bool   hasShading;
public:
    TFSPdfCircle( double lineWidth, double x, double y, double radius, double shading = 0.0, bool hasShading = false );
    
    bool ok( void ) const;
};


}   // namespace tfs


#endif /* TFSPdfCircle_hpp */
