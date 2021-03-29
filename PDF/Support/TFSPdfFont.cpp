// ---------------------------------------------------------------------------------
//  TFSPdfFont.hpp
//
//  Created by Barrett Davis on 3/22/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#include "TFSPdfFont.hpp"

namespace tfs {

// Font names:
static const char TIMES_ROMAN[]             = { "Times-Roman" };
static const char TIMES_BOLD[]              = { "Times-Bold" };
static const char TIMES_ITALIC[]            = { "Times-Italic" };
static const char TIMES_BOLD_ITALIC[]       = { "Times-Bold-Italic" };

static const char COURIER[]                 = { "Courier" };
static const char COURIER_BOLD[]            = { "Courier-Bold" };
static const char COURIER_OBLIQUE[]         = { "Courier-Oblique" };
static const char COURIER_BOLD_OBLIQUE[]    = { "Courier-Bold-Oblique" };

static const char HELVETICA[]               = { "Helvetica" };
static const char HELVETICA_BOLD[]          = { "Helvetica-Bold" };
static const char HELVETICA_OBLIQUE[]       = { "Helvetica-Oblique" };
static const char HELVETICA_BOLD_OBLIQUE[]  = { "Helvetica-Bold-Oblique" };

static const char SYMBOL[]                  = { "Symbol" };
static const char ZAPFDINGBATS[]            = { "ZapfDingbats" };


TFSPdfFont getFont( TFSPdfFontFamily fontFamily, bool bold, bool italic ) {
    TFSPdfFont font = TFSPdfFont::DEFAULT;
    switch ( fontFamily ) {
        case TFSPdfFontFamily::Times:
            if( bold ) {
                if( italic ) {  font = TFSPdfFont::Times_Bold_Italic;
                } else {        font = TFSPdfFont::Times_Bold;
                }
            } else {
                if( italic ) {  font = TFSPdfFont::Times_Italic;
                } else {        font = TFSPdfFont::Times_Roman;
                }
            }
            break;
        case TFSPdfFontFamily::Courier:
            if( bold ) {
                if( italic ) {  font = TFSPdfFont::Courier_Bold_Oblique;
                } else {        font = TFSPdfFont::Courier_Bold;
                }
            } else {
                if( italic ) {  font = TFSPdfFont::Courier_Oblique;
                } else {        font = TFSPdfFont::Courier;
                }
            }
            break;
        case TFSPdfFontFamily::Helvetica:
            if( bold ) {
                if( italic ) {  font = TFSPdfFont::Helvetica_Bold_Oblique;
                } else {        font = TFSPdfFont::Helvetica_Bold;
                }
            } else {
                if( italic ) {  font = TFSPdfFont::Helvetica_Oblique;
                } else {        font = TFSPdfFont::Helvetica;
                }
            }
            break;
        case TFSPdfFontFamily::Symbol:
            font = TFSPdfFont::Symbol;
            break;
        case TFSPdfFontFamily::ZapfDingbats:
            font = TFSPdfFont::ZapfDingbats;
            break;
    }
    return font;
}

const char *getFontName( TFSPdfFont font ) {
    switch ( font ) {
        case TFSPdfFont::Times_Roman:               return TIMES_ROMAN;
        case TFSPdfFont::Times_Bold:                return TIMES_BOLD;
        case TFSPdfFont::Times_Italic:              return TIMES_ITALIC;
        case TFSPdfFont::Times_Bold_Italic:         return TIMES_BOLD_ITALIC;
        case TFSPdfFont::Courier:                   return COURIER;
        case TFSPdfFont::Courier_Bold:              return COURIER_BOLD;
        case TFSPdfFont::Courier_Oblique:           return COURIER_OBLIQUE;
        case TFSPdfFont::Courier_Bold_Oblique:      return COURIER_BOLD_OBLIQUE;
        case TFSPdfFont::Helvetica:                 return HELVETICA;
        case TFSPdfFont::Helvetica_Bold:            return HELVETICA_BOLD;
        case TFSPdfFont::Helvetica_Oblique:         return HELVETICA_OBLIQUE;
        case TFSPdfFont::Helvetica_Bold_Oblique:    return HELVETICA_BOLD_OBLIQUE;
        case TFSPdfFont::Symbol:                    return SYMBOL;
        case TFSPdfFont::ZapfDingbats:              return ZAPFDINGBATS;
    }
    return HELVETICA;
}

}   // namespace tfs
