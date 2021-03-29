// ---------------------------------------------------------------------------------
//  TFSPdfStreamable.hpp
//
//  Created by Barrett Davis on 3/26/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#ifndef TFSPdfStreamable_hpp
#define TFSPdfStreamable_hpp

#include "TFSPdfStreamableType.hpp"

namespace tfs {

class TFSPdfStream;             // Forward declaration.

class TFSPdfStreamable {        // Base class for streamable objects.
public:
    enum class TFSPainting {
        STROKED,
        FILLED,
        STROKED_AND_FILLED
    };
    
protected:
    TFSPdfStreamableType m_type;
    TFSPainting          m_painting;
    double               m_lineWidth;
    double               m_shading;
    double               m_x;
    double               m_y;

public:
    TFSPdfStreamable( const TFSPdfStreamable &other );
    TFSPdfStreamable( TFSPdfStreamableType objType, TFSPainting painting, double lineWidth, double shading, double x = 0.0, double y = 0.0 );
    virtual ~TFSPdfStreamable( void );
    
    TFSPdfStreamableType getType( void ) const;
    
    virtual bool ok( void ) const;

    virtual void stream( TFSPdfStream &stream ) const = 0;
    
};  // TFSPdfStreamable

constexpr TFSPdfStreamable::TFSPainting DEFAULT_PAINTING   = TFSPdfStreamable::TFSPainting::STROKED;
constexpr double                        DEFAULT_LINE_WIDTH = 1.0;
constexpr double                        DEFAULT_SHADING    = 0.0;

TFSPdfStream& operator<<( TFSPdfStream &stream, const TFSPdfStreamable &streamable );


}   // namespace tfs



#endif /* TFSPdfStreamable_hpp */
