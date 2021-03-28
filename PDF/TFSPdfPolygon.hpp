// ---------------------------------------------------------------------------------
//  TFSPdfPolygon.hpp
//
//  Created by Barrett Davis on 3/26/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#ifndef TFSPdfPolygon_hpp
#define TFSPdfPolygon_hpp

#include "TFSPdfLine.hpp"

namespace tfs {

class TFSPdfPolygon : public TFSPdfLine {
public:
    TFSPdfPolygon( double lineWidth, double x1, double y1, double x2, double y2, double shading = 0.0, bool hasShading = false );
    TFSPdfPolygon( double lineWidth, const std::vector<std::pair<double,double>> &verticies, double shading = 0.0, bool hasShading = false );
    virtual ~TFSPdfPolygon( void );
    
    virtual void stream( TFSPdfStream &stream ) const override;

};  // class TFSPdfPolygon


}   // namespace tfs


#endif /* TFSPdfPolygon_hpp */
