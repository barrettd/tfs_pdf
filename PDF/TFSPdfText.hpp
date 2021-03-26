// ---------------------------------------------------------------------------------
//  TFSPdfText.hpp
//
//  Created by Barrett Davis on 3/22/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#ifndef TFSPdfText_hpp
#define TFSPdfText_hpp

#include <string>
#include "TFSPdfFont.hpp"

namespace tfs {

class TFSPdfText {
public:
    TFSPdfFont  font;
    std::size_t fontSize;
    long x;
    long y;
    std::string text;
    
public:
    TFSPdfText( TFSPdfFont font, std::size_t fontSize, long x,  long y, const std::string &text );
    
    bool empty( void ) const;
    std::size_t size( void ) const;
};

}   // namespace tfs

#endif /* TFSPdfText_hpp */
