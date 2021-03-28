// ---------------------------------------------------------------------------------
//  TFSPdfStreamable.hpp
//
//  Created by Barrett Davis on 3/26/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#ifndef TFSPdfStreamable_hpp
#define TFSPdfStreamable_hpp

#include "TFSPdfStream.hpp"

namespace tfs {

class TFSPdfStreamable {        // Base class for streamable objects.
protected:
    double m_x;
    double m_y;
    double m_lineWidth;
    double m_shading;           // [0.0 to 1.0] with 0.0 = black, 1.0 = white
    bool   m_hasShading;

public:
    TFSPdfStreamable( double x = 0.0, double y = 0.0, double lineWidth = 1.0, double shading = 0.0, bool hasShading = false );
    virtual ~TFSPdfStreamable( void );
    
    virtual bool ok( void ) const;

    virtual void stream( TFSPdfStream &stream ) const = 0;
    
};  // TFSPdfStreamable


TFSPdfStream& operator<<( TFSPdfStream &stream, const TFSPdfStreamable &streamable );


}   // namespace tfs



#endif /* TFSPdfStreamable_hpp */
