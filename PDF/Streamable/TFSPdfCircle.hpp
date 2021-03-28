// ---------------------------------------------------------------------------------
//  TFSPdfCircle.hpp
//
//  Created by Barrett Davis on 3/26/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#ifndef TFSPdfCircle_hpp
#define TFSPdfCircle_hpp

#include "TFSPdfStreamable.hpp"

namespace tfs {

class TFSPdfCircle : public TFSPdfStreamable {
protected:
    double m_radius;
public:
    TFSPdfCircle( const TFSPdfCircle &other );
    TFSPdfCircle( double lineWidth, double x, double y, double radius, double shading = 0.0, TFSPainting painting = TFSPainting::STROKED );
    virtual ~TFSPdfCircle( void );
    
    virtual bool ok( void ) const override;    
    virtual void stream( TFSPdfStream &stream ) const override;
};


}   // namespace tfs


#endif /* TFSPdfCircle_hpp */
