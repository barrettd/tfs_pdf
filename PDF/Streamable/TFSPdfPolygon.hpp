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
    TFSPdfPolygon( TFSPdfStreamableType objType, TFSPainting painting, double lineWidth, double x1, double y1, double x2, double y2 );
    TFSPdfPolygon( TFSPdfStreamableType objType, TFSPainting painting, double lineWidth, const std::vector<std::pair<double,double>> &verticies );
    TFSPdfPolygon( double lineWidth, double x1, double y1, double x2, double y2, double shading = 0.0, TFSPainting painting = TFSPainting::STROKED );
    TFSPdfPolygon( double lineWidth, const std::vector<std::pair<double,double>> &verticies, double shading = 0.0, TFSPainting painting = TFSPainting::STROKED );
    virtual ~TFSPdfPolygon( void );
    
    virtual void stream( TFSPdfStream &stream ) const override;

};  // class TFSPdfPolygon


}   // namespace tfs


#endif /* TFSPdfPolygon_hpp */
