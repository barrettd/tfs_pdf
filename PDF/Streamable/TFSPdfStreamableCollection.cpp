// ---------------------------------------------------------------------------------
//  TFSPdfStreamableCollection.cpp
//
//  Created by Barrett Davis on 3/28/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#include "TFSPdfStreamableCollection.hpp"

namespace tfs {


TFSPdfStreamableCollection::TFSPdfStreamableCollection( const TFSPdfStreamableCollection &other ):
m_objects() {
    for( const std::unique_ptr<TFSPdfStreamable> &obj : m_objects ) {   // Deep copy
        if( obj && obj->ok()) {
            switch( obj->getType()) {
                case TFSPdfStreamableType::BOX:      cloneBox(     obj );    break;
                case TFSPdfStreamableType::CIRCLE:   cloneCircle(  obj );    break;
                case TFSPdfStreamableType::LINE:     cloneLine(    obj );    break;
                case TFSPdfStreamableType::POLYGON:  clonePolygon( obj );    break;
                case TFSPdfStreamableType::TEXT:     cloneText(    obj );    break;
            }
        }
    }
}

TFSPdfStreamableCollection::TFSPdfStreamableCollection( void ):
m_objects() {
}

void TFSPdfStreamableCollection::cloneBox( const std::unique_ptr<TFSPdfStreamable> &obj ) {
    TFSPdfBox *box = dynamic_cast<TFSPdfBox*>(obj.get());
    if( box != nullptr ) {
        m_objects.push_back( std::make_unique<TFSPdfBox>( *box ));
    }
}
void TFSPdfStreamableCollection::cloneCircle( const std::unique_ptr<TFSPdfStreamable> &obj ) {
    TFSPdfCircle *circle = dynamic_cast<TFSPdfCircle*>(obj.get());
    if( circle != nullptr ) {
        m_objects.push_back( std::make_unique<TFSPdfCircle>( *circle ));
    }
}
void TFSPdfStreamableCollection::cloneLine( const std::unique_ptr<TFSPdfStreamable> &obj ) {
    TFSPdfLine *line = dynamic_cast<TFSPdfLine*>(obj.get());
    if( line != nullptr ) {
        m_objects.push_back( std::make_unique<TFSPdfLine>( *line ));
    }
}
void TFSPdfStreamableCollection::clonePolygon( const std::unique_ptr<TFSPdfStreamable> &obj ) {
    TFSPdfPolygon *polygon = dynamic_cast<TFSPdfPolygon*>(obj.get());
    if( polygon != nullptr ) {
        m_objects.push_back( std::make_unique<TFSPdfPolygon>( *polygon ));
    }
}
void TFSPdfStreamableCollection::cloneText( const std::unique_ptr<TFSPdfStreamable> &obj ) {
    TFSPdfText *text = dynamic_cast<TFSPdfText*>(obj.get());
    if( text != nullptr ) {
        m_objects.push_back( std::make_unique<TFSPdfText>( *text ));
    }
}

bool TFSPdfStreamableCollection::empty( void ) const {
    return m_objects.empty();
}

std::size_t TFSPdfStreamableCollection::size( void ) const {
    return m_objects.size();
}

std::vector<std::unique_ptr<TFSPdfStreamable>>::const_iterator TFSPdfStreamableCollection::begin( void ) const {
    return m_objects.begin();
}

std::vector<std::unique_ptr<TFSPdfStreamable>>::const_iterator TFSPdfStreamableCollection::end(   void ) const {
    return m_objects.end();
}

void TFSPdfStreamableCollection::stream( TFSPdfStream &stream ) const {
    for( const std::unique_ptr<TFSPdfStreamable> &obj : m_objects ) {
        if( obj && obj->ok()) {
            obj->stream( stream );
        }
    }
}

bool TFSPdfStreamableCollection::setPolyline( double lineWidth, const std::vector<std::pair<double,double>> &verticies ) {
    std::unique_ptr<TFSPdfLine> line = std::make_unique<TFSPdfLine>( lineWidth, verticies  );
    if( !line->ok()) {
        return false;
    }
    m_objects.push_back( std::move( line ));
    return true;
}

bool TFSPdfStreamableCollection::setPolygon( TFSPdfStreamable::TFSPainting painting, double lineWidth, double shading, const std::vector<std::pair<double,double>> &verticies ) {
    std::unique_ptr<TFSPdfPolygon> polygon = std::make_unique<TFSPdfPolygon>( painting, lineWidth, shading, verticies );
    if( !polygon->ok()) {
        return false;
    }
    m_objects.push_back( std::move( polygon ));
    return true;

}

bool TFSPdfStreamableCollection::setCircle( TFSPdfStreamable::TFSPainting painting, double lineWidth, double shading, double x, double y, double radius ) {
    std::unique_ptr<TFSPdfCircle> circle = std::make_unique<TFSPdfCircle>( painting, lineWidth, shading, x, y, radius );
    if( !circle->ok()) {
        return false;
    }
    m_objects.push_back( std::move( circle ));
    return true;
}

bool TFSPdfStreamableCollection::setBox( TFSPdfStreamable::TFSPainting painting, double lineWidth, double shading, double x, double y, double width, double height ) {
    std::unique_ptr<TFSPdfBox> box = std::make_unique<TFSPdfBox>( painting, lineWidth, shading, x, y, width, height );
    if( !box->ok()) {
        return false;
    }
    m_objects.push_back( std::move( box ));
    return true;
}

bool TFSPdfStreamableCollection::setText( TFSPdfFont font, std::size_t fontSize, double x, double y, const std::string &text ) {
    std::unique_ptr<TFSPdfText> textObject = std::make_unique<TFSPdfText>( font, fontSize, x, y, text );
    if( !textObject->ok()) {
        return false;
    }
    m_objects.push_back( std::move( textObject ));
    return true;
}


}   // namespace tfs
