// ---------------------------------------------------------------------------------
//  TFSPdfFontMap.hpp
//
//  Created by Barrett Davis on 3/24/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#include<sstream>
#include "TFSPdfFontMap.hpp"

namespace tfs {

// ---------------------------------------------------------------------------------
// TFSPdfFontMapNode
// ---------------------------------------------------------------------------------
TFSPdfFontMapNode::TFSPdfFontMapNode( const int index, const std::string &name,  const std::size_t objectIndex  ):
shortName(),
fullname( name ),
objectIndex( objectIndex ) {           // Filled in later.
    std::ostringstream os;
    os << "F" << index;
    shortName = os.str();
}



// ---------------------------------------------------------------------------------
// TFSPdfFontMap
// ---------------------------------------------------------------------------------
TFSPdfFontMap::TFSPdfFontMap( void ):
m_map() {
}

TFSPdfFontMapNode* TFSPdfFontMap::addNode( const TFSPdfFont font, const int fontIndex, const std::size_t objectIndex ) {
    const std::string &fontName = getFontName( font );
    std::unique_ptr<TFSPdfFontMapNode> node = std::make_unique<TFSPdfFontMapNode>( fontIndex, fontName, objectIndex );
    TFSPdfFontMapNode *ptr = node.get();
    m_map[font] = std::move( node );
    return ptr;
}

const TFSPdfFontMapNode* TFSPdfFontMap::getNode( const TFSPdfFont font ) {
    std::unique_ptr<TFSPdfFontMapNode> &node = m_map[font];
    return node.get();
}



}   // namespace tfs
