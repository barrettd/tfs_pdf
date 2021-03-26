// ---------------------------------------------------------------------------------
//  TFSPdfFont.hpp
//
//  Created by Barrett Davis on 3/22/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#ifndef TFSPdfFont_hpp
#define TFSPdfFont_hpp

namespace tfs {

enum class TFSPdfFontFamily {
    Times = 0,
    Courier,
    Helvetica,
    Symbol,
    ZapfDingbats,
};

enum class TFSPdfFont {
    Times_Roman = 0,
    Times_Bold,
    Times_Italic,
    Times_Bold_Italic,
    Courier,
    Courier_Bold,
    Courier_Oblique,
    Courier_Bold_Oblique,
    Helvetica,
    Helvetica_Bold,
    Helvetica_Oblique,
    Helvetica_Bold_Oblique,
    Symbol,
    ZapfDingbats,
    DEFAULT = Helvetica         // My personal favorite ...
};

TFSPdfFont getFont( TFSPdfFontFamily fontFamily, bool bold, bool italic );

const char *getFontName( TFSPdfFont font );

}   // namespace tfs

#endif /* TFSPdfFont_hpp */
