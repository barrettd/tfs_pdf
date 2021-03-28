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
#include "TFSPdfStreamable.hpp"

namespace tfs {

class TFSPdfLine : public TFSPdfStreamable {
public:
    static constexpr double LINE_WIDTH_MIN     = 0.1;   // Arbitrary max / min values
    static constexpr double LINE_WIDTH_MAX   = 700.0;

protected:
    std::vector<std::pair<double,double>> m_verticies;
public:
    TFSPdfLine( const TFSPdfLine &other );
    TFSPdfLine( TFSPdfStreamableType objType, TFSPainting painting, double lineWidth, double x1, double y1, double x2, double y2 );
    TFSPdfLine( TFSPdfStreamableType objType, TFSPainting painting, double lineWidth, const std::vector<std::pair<double,double>> &verticies );
    TFSPdfLine( double lineWidth, double x1, double y1, double x2, double y2 );
    TFSPdfLine( double lineWidth, const std::vector<std::pair<double,double>> &verticies );
    virtual ~TFSPdfLine( void );

    bool empty( void ) const;

    virtual bool ok( void ) const override;    

    virtual void stream( TFSPdfStream &stream ) const override;
};


}   // namespace tfs

#endif /* TFSPdfLine_hpp */
