// ---------------------------------------------------------------------------------
//  TFSPdfStream.hpp
//
//  Created by Barrett Davis on 3/26/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#ifndef TFSPdfStream_hpp
#define TFSPdfStream_hpp

#include <sstream>

#include "TFSPdfStreamable.hpp"

namespace tfs {


class TFSPdfStream {
protected:
    std::stringstream m_stream;
    double            m_lineWidth;
    
public:
    TFSPdfStream( void );
    virtual ~TFSPdfStream( void );
    
    std::string str( void );
    
    void saveGraphicsState( void );     // Push graphics state.
    void restoreGraphicsState( void );  // Pop graphics state

    void setLineWidth( double width );
    
    void fillOrStroke( TFSPdfStreamable::TFSPainting painting, double shadeValue );
    
    TFSPdfStream& operator<<( char value );
    TFSPdfStream& operator<<( int  value );
    TFSPdfStream& operator<<( long value );

    TFSPdfStream& operator<<( float  value );
    TFSPdfStream& operator<<( double value );

    TFSPdfStream& operator<<( std::size_t    value );
    TFSPdfStream& operator<<( std::streamoff value );
    
    TFSPdfStream& operator<<( const char *value );
    TFSPdfStream& operator<<( const std::string &value );
    
};  // class TFSPdfStream

}   // namespace tfs

#endif /* TFSPdfStream_hpp */
