// ---------------------------------------------------------------------------------
//  TFSPdfText.cpp
//
//  Created by Barrett Davis on 3/22/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#include "TFSPdfText.hpp"

namespace tfs {

TFSPdfFont font;
long x;
long y;
std::string text;


TFSPdfText::TFSPdfText( TFSPdfFont font, std::size_t fontSize, long x,  long y, const std::string &text ):
font( font ),
fontSize( fontSize ),
x( x ),
y( y ),
text( text ) {
}

bool TFSPdfText::empty( void ) const {
    return text.empty();
}

std::size_t TFSPdfText::size( void ) const {
    return text.size();
}

}   // namespace tfs
