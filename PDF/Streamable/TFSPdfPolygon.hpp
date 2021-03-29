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
    TFSPdfPolygon( const TFSPdfPolygon &other );
    TFSPdfPolygon( TFSPdfStreamableType objType, TFSPainting painting, double lineWidth, double shading, const std::vector<std::pair<double,double>> &verticies );
    TFSPdfPolygon( TFSPainting painting, double lineWidth, double shading, const std::vector<std::pair<double,double>> &verticies );
    virtual ~TFSPdfPolygon( void );
    
    virtual void stream( TFSPdfStream &stream ) const override;

};  // class TFSPdfPolygon


}   // namespace tfs


#endif /* TFSPdfPolygon_hpp */
