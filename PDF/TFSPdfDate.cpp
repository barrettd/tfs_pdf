// ---------------------------------------------------------------------------------
//  TFSPdfDate.cpp
//
//  Created by Barrett Davis on 3/24/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#include "TFSPdfDate.hpp"

namespace tfs {

static constexpr int MIN_YEAR { 2021 };
static constexpr int MAX_YEAR { 2100 };

static bool isLeapYear( const int year ) {
    if( year % 4 != 0 ) {
        return false;
    }
    if( year % 100 != 0 ) {
        return true;
    }
    if( year % 400 == 0 ) {
        return true;
    }
    return false;
}

TFSPdfDate::TFSPdfDate( void ) :
year(   0 ),
month(  0 ),
day(    0 ),
hour(   0 ),
minute( 0 ),
second( 0 ) {
}


TFSPdfDate::TFSPdfDate( int newYear, int newMonth, int newDay, int newHour, int newMinute, int newSecond ):
year(   newYear ),
month(  newMonth ),
day(    newDay ),
hour(   newHour ),
minute( newMinute ),
second( newSecond ) {
}

bool TFSPdfDate::set( int newYear, int newMonth, int newDay, int newHour, int newMinute, int newSecond ) {
    year   = newYear;
    month  = newMonth;
    day    = newDay;
    hour   = newHour;
    minute = newMinute;
    second = newSecond;
    return ok();
}


bool TFSPdfDate::ok( void ) const {     // Check that the components of the date are within bounds.
    if( year < MIN_YEAR || year > MAX_YEAR ||
        month  < 1 || month  > 12 ||
        day    < 1 || day    > 31 ||
        hour   < 0 || hour   > 23 ||
        minute < 0 || minute > 59 ||
        second < 0 || second > 59 ) {
        return false;
    }
    if( day < 29 ) {
        return true;
    }
    if( month == 2 ) {              // Special case for Feburary with 28 or 29 days.
        int max_feb = 28;           // Normal year
        if( isLeapYear( year )) {
            max_feb = 29;           // Leap year
        }
        if( day > max_feb ) {
            return false;
        }
        return true;
    }
    if( day > 30 && ( month == 4 || month == 6 || month == 9 || month == 11 )) {    // Months with 30 days
        return false;   // April, June, September, November
    }
    return true;
}

TFSPdfDate::operator bool( void ) const {
    return ok();
}


}   // namespace tfs
