// ---------------------------------------------------------------------------------
//  TFSPdfText.hpp
//
//  Created by Barrett Davis on 3/22/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#ifndef TFSPdfText_hpp
#define TFSPdfText_hpp

#include "TFSPdfFontMap.hpp"
#include "TFSPdfStreamable.hpp"

namespace tfs {

class TFSPdfText : public TFSPdfStreamable {
protected:
    TFSPdfFont  m_font;
    std::size_t m_fontSize;
    std::string m_text;
    
public:
    TFSPdfText( const TFSPdfText &other );
    TFSPdfText( TFSPdfFont font, std::size_t fontSize, double x,  double y, const std::string &text );
    virtual ~TFSPdfText( void );
    
    bool empty( void ) const;
    std::size_t size( void ) const;
    
    virtual bool ok( void ) const override;

    virtual void stream( TFSPdfStream &stream ) const override;     // NOP
    void stream( TFSPdfStream &stream, const TFSPdfFontMap &fontMap ) const;
};

}   // namespace tfs

#endif /* TFSPdfText_hpp */
