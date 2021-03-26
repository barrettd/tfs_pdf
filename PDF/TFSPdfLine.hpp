// ---------------------------------------------------------------------------------
//  TFSPdfLine.pp
//
//  Created by Barrett Davis on 3/22/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#ifndef TFSPdfLine_hpp
#define TFSPdfLine_hpp

#include <utility>
#include <vector>

namespace tfs {

class TFSPdfLine {
public:
    static constexpr double LINE_WIDTH_MIN     = 1.0;
    static constexpr double LINE_WIDTH_MAX   = 700.0;

public:
    std::vector<std::pair<double,double>> verticies;
    double lineWidth;
public:
    TFSPdfLine( double lineWidth, double x1, double y1, double x2, double y2 );
    TFSPdfLine( double lineWidth, const std::vector<std::pair<double,double>> &verticies );

    bool empty( void ) const;

    bool setLineWidth( double width );
    bool setLine( double x1, double y1, double x2, double y2 );
    bool setPolyline( const std::vector<std::pair<double,double>> &verticies );
};


}   // namespace tfs

#endif /* TFSPdfLine_hpp */
