// ---------------------------------------------------------------------------------
//  TFSPdfTextCollection.cpp
//
//  Created by Barrett Davis on 3/28/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#include "TFSPdfTextCollection.hpp"

namespace tfs {


TFSPdfTextCollection::TFSPdfTextCollection( const TFSPdfTextCollection &other ):
m_texts() {
    for( const std::unique_ptr<TFSPdfText> &text : other.m_texts ) {
        if( text->ok()) {
            m_texts.push_back( std::make_unique<TFSPdfText>( *text ));
        }
    }
}

TFSPdfTextCollection::TFSPdfTextCollection( void ):
m_texts() {
}

bool TFSPdfTextCollection::empty( void ) const {
    return m_texts.empty();
}

std::size_t TFSPdfTextCollection::size( void ) const {
    return m_texts.size();
}

std::vector<std::unique_ptr<TFSPdfText>>::const_iterator TFSPdfTextCollection::begin( void ) const {
    return m_texts.begin();
}
std::vector<std::unique_ptr<TFSPdfText>>::const_iterator TFSPdfTextCollection::end( void ) const {
    return m_texts.end();
}

void TFSPdfTextCollection::stream( TFSPdfStream &stream, const TFSPdfFontMap &fontMap ) const {
    for( const std::unique_ptr<TFSPdfText> &text : m_texts ) {
        if( text->ok()) {
            text->stream( stream, fontMap );
        }
    }
}

bool TFSPdfTextCollection::setText( TFSPdfFont font, std::size_t fontSize, double x, double y, const std::string &text ) {
    std::unique_ptr<TFSPdfText> textObject = std::make_unique<TFSPdfText>( font, fontSize, x, y, text );
    if( !textObject->ok()) {
        return false;
    }
    m_texts.push_back( std::move( textObject ));
    return true;
}

}   // namespace tfs
