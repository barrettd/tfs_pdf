// ---------------------------------------------------------------------------------
//  TFSPdfBox.cpp
//
//  Created by Barrett Davis on 3/22/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#ifndef TFSPdfBox_hpp
#define TFSPdfBox_hpp

#include "TFSPdfStreamable.hpp"

namespace tfs {

class TFSPdfBox : public TFSPdfStreamable {
protected:
    long   m_width;
    long   m_height;
public:
    TFSPdfBox( const TFSPdfBox &other );
    TFSPdfBox( TFSPainting painting, double lineWidth, double shading, double x, double y, double width, double height );
    virtual ~TFSPdfBox( void );
    
    virtual bool ok( void ) const override;    
    virtual void stream( TFSPdfStream &stream ) const override;
    
};




}   // namespace tfs


#endif /* TFSPdfBox_hpp */
