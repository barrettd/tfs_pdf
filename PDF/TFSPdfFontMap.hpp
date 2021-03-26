// ---------------------------------------------------------------------------------
//  TFSPdfFontMap.hpp
//
//  Created by Barrett Davis on 3/24/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#ifndef TFSPdfFontMap_hpp
#define TFSPdfFontMap_hpp

#include <map>
#include <memory>
#include <string>
#include "TFSPdfFont.hpp"

namespace tfs {

class TFSPdfFontMapNode {
public:
    std::string shortName;          // e.g. "F1"
    std::string fullname;           // e.g. "Helvetica"
    std::size_t objectIndex;        // index to << /Type /Font
    
public:
    TFSPdfFontMapNode( const int fontIndex, const std::string &name,  const std::size_t objectIndex );
    
};  // class TFSPdfFontMapNode



class TFSPdfFontMap {
private:
    std::map<TFSPdfFont, std::unique_ptr<TFSPdfFontMapNode>> m_map;
    
public:
    TFSPdfFontMap( void );
    
    TFSPdfFontMapNode* addNode( const TFSPdfFont font, const int fontIndex, const std::size_t objectIndex );
    const TFSPdfFontMapNode* getNode( const TFSPdfFont font );
    
    
};  // class TFSPdfFontMap

}   // namespace tfs



#endif /* TFSPdfFontMap_hpp */
