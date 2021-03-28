// ---------------------------------------------------------------------------------
//  TFSPdfStream.cpp
//
//  Created by Barrett Davis on 3/26/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
// Convention:
//  1. All numbers are followed by whitespace.
//  2. All commands are followed by newline
// ---------------------------------------------------------------------------------
#include <iomanip>
#include "TFSPdfStream.hpp"


TFSPdfStream::TFSPdfStream( void ):
m_stream(),
m_lineWidth( 0.0 ) {
}

TFSPdfStream::~TFSPdfStream( void ) {
}

std::string TFSPdfStream::str( void ) {
    return m_stream.str();
}

void TFSPdfStream::setLineWidth( double width ) {
    if( m_lineWidth != width ) {
        m_stream << width << " w\n";
        m_lineWidth = width;
    }
}

void TFSPdfStream::saveGraphicsState( void ) {      // Push graphics state.
    m_stream << "q\n";
}
void TFSPdfStream::restoreGraphicsState( void ) {   // Pop graphics state
    m_stream << "Q\n";
}

void TFSPdfStream::fillOrStroke( bool hasShading, double shadeValue ) {
    if( hasShading ) {
        saveGraphicsState();
        m_stream << shadeValue << " g f\n";    // Set greyscale color, then fill.
        restoreGraphicsState();
    } else {
        m_stream << "s\n";    // Stroke
    }
    return;
}


TFSPdfStream& TFSPdfStream::operator<<( char value ) {
    m_stream << value << " ";
    return *this;
}
TFSPdfStream& TFSPdfStream::operator<<( int value ) {
    m_stream << value << " ";
    return *this;
}
TFSPdfStream& TFSPdfStream::operator<<( long value ) {
    m_stream << value << " ";
    return *this;
}
TFSPdfStream& TFSPdfStream::operator<<( float value ) {
    m_stream << value << " ";
    return *this;
}
TFSPdfStream& TFSPdfStream::operator<<( double value )  {
    m_stream << value << " ";
    return *this;
}
TFSPdfStream& TFSPdfStream::operator<<( std::size_t value )  {
    m_stream << value << " ";
    return *this;
}
TFSPdfStream& TFSPdfStream::operator<<( std::streamoff value )  {
    m_stream << value << " ";
    return *this;
}

TFSPdfStream& TFSPdfStream::operator<<( const char *value ) {
    if( value != nullptr && *value != 0 ) {
        m_stream << value;
    }
    return *this;
}
TFSPdfStream& TFSPdfStream::operator<<( const std::string &value ) {
    if( !value.empty()) {
        m_stream << value;
    }
    return *this;
}


