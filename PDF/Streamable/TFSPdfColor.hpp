// ---------------------------------------------------------------------------------
//  TFSPdfColor.hpp
//
//  Created by Barrett Davis on 3/28/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#ifndef TFSPdfColor_hpp
#define TFSPdfColor_hpp

#include "TFSPdfStream.hpp"

namespace tfs {

class TFSPdfColor {
protected:
    bool   m_isColor;   // True for RGB, false for Grey
    double m_red;       // [0.0 to 1.0]
    double m_green;     // [0.0 to 1.0]
    double m_blue;      // [0.0 to 1.0]
    double m_grey;      // [0.0 to 1.0]
                        // Alpha one day?
public:
    TFSPdfColor( const TFSPdfColor &other );
    TFSPdfColor( double red, double green, double blue );
    TFSPdfColor( double grey );
    
    bool ok( void ) const;
    void stream( TFSPdfStream &stream ) const;

};


}   // namespace tfs

#endif /* TFSPdfColor_hpp */
