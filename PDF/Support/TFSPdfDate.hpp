// ---------------------------------------------------------------------------------
//  TFSPdfDate.hpp
//
//  Created by Barrett Davis on 3/24/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#ifndef TFSPdfDate_hpp
#define TFSPdfDate_hpp

namespace tfs {


class TFSPdfDate {
public:
    int year;           // [2021 to 2100]
    int month;          // [1 to 12]
    int day;            // [1 to 31] nb not all months have 31 days, obviously
    int hour;           // [0 to 23]
    int minute;         // [0 to 59]
    int second;         // [0 to 59]
public:
    TFSPdfDate( void ); // Set to all zero.
    TFSPdfDate( int year, int month, int day, int hour = 0, int minute = 0, int second = 0 );
    
    bool set( int year, int month, int day, int hour = 0, int minute = 0, int second = 0 );
    
    bool ok( void ) const;
    
    explicit operator bool( void ) const;
};

}   // namepace tfs

#endif /* TFSPdfDate_hpp */
