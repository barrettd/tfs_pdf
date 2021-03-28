// ---------------------------------------------------------------------------------
//  TFSPdfTextCollection.hpp
//
//  Created by Barrett Davis on 3/28/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#ifndef TFSPdfTextCollection_hpp
#define TFSPdfTextCollection_hpp

#include <memory>
#include <vector>
#include "TFSPdfText.hpp"

namespace tfs {

class TFSPdfTextCollection {
private:
    std::vector<std::unique_ptr<TFSPdfText>> m_texts;

public:
    TFSPdfTextCollection( const TFSPdfTextCollection &other );
    TFSPdfTextCollection( void );
    
    bool empty( void ) const;
    std::size_t size( void ) const;
    
    std::vector<std::unique_ptr<TFSPdfText>>::const_iterator begin( void ) const;
    std::vector<std::unique_ptr<TFSPdfText>>::const_iterator end(   void ) const;
    
    void stream( TFSPdfStream &stream, const TFSPdfFontMap &fontMap ) const;

    bool setText( TFSPdfFont font, std::size_t fontSize, double x, double y, const std::string &text );
};


}   // namespace tfs


#endif /* TFSPdfTextCollection_hpp */
