// ---------------------------------------------------------------------------------
//  TestPDF.cpp
//
//  Created by Barrett Davis on 3/21/21.
//  Copyright (c) 2021 Tree Frog Software, All Rights Reserved.
// ---------------------------------------------------------------------------------
#include <iostream>
#include "TestPDF.hpp"
#include "TFSPdfWriter.hpp"


namespace tfs {

static bool testPDFDate( void ) {
    TFSPdfDate date( 2021, 3, 24, 10, 12, 13 );         // Good date
    if( !date.ok()) {
        return false;
    }
    if( date.set( 2020, 3, 24, 10, 12, 13 )) {          // Bad date, year < 2021
        return false;
    }
    if( date.set( 2104, 4, 31, 10, 12, 13 )) {          // Bad date, year > 2100 (but is is a leap year)
        return false;
    }
    if( date.set( 2021, 0, 31, 10, 12, 13 )) {          // Bad date, month < 1
        return false;
    }
    if( date.set( 2021, 13, 31, 10, 12 )) {             // Bad date, month > 12
        return false;
    }
    if( date.set( 2022, 1, 31, 15, 45, 60 )) {          // Bad date, second > 59
        return false;
    }
    if( date.set( 2022, 1, 31, 15, 60, 0 )) {           // Bad date, minute > 59
        return false;
    }
    if( date.set( 2022, 1, 31, 24, 0, 0 )) {            // Bad date, hour > 23
        return false;
    }
    if( date.set( 2022, 1, -1, 0, 0, 0 )) {             // Bad date, day < 1
        return false;
    }
    if( date.set( 2022, 0, 1, 0, 0, 0 )) {              // Bad date, month < 1
        return false;
    }
    if( !date.set( 2022, 1, 31, 15, 45 )) {             // Good date, January has 31
        return false;
    }
    if( !date.set( 2022, 2, 28, 0, 45 )) {              // Good date, Feburary 2022 has 28 days
        return false;
    }
    if( date.set( 2022, 2, 29, 15, 45 )) {              // Bad date, Feburary 2022 has 28 days
        return false;
    }
    if( !date.set( 2024, 2, 29, 23, 59 )) {             // Good date, Feburary leap year
        return false;
    }
    if( !date.set( 2024, 2, 29 )) {                     // Good date, Feburary leap year
        return false;
    }
    if( !date.set( 2024, 2, 29, 23, 59, 59 )) {         // Good date, Feburary leap year
        return false;
    }
    if( !date.set( 2028, 2, 29, 23, 59, 59 )) {         // Good date, Feburary leap year
        return false;
    }
    if( !date.set( 2032, 2, 29, 23, 59, 59 )) {         // Good date, Feburary leap year
        return false;
    }
    if( date.set( 2033, 2, 29, 23, 59, 59 )) {          // Bad date, Feburary not leap year
        return false;
    }
    if( !date.set( 2096, 2, 29, 23, 59, 59 )) {         // Good date, Feburary leap year
        return false;
    }
    if( date.set( 2100, 2, 29, 23, 59, 59 )) {          // Bad date, Feburary not leap year
        return false;
    }
    if( !date.set( 2022, 3, 31, 15, 45 )) {             // Good date, March has 31
        return false;
    }
    if( date.set( 2021, 4, 31, 10, 12 )) {              // Bad date, April has 30 days
        return false;
    }
    if( !date.set( 2022, 5, 31, 15, 45 )) {             // Good date, May has 31
        return false;
    }
    if( date.set( 2021, 6, 31, 10, 12 )) {              // Bad date, June has 30 days
        return false;
    }
    if( !date.set( 2022, 7, 31, 15, 45 )) {             // Good date, July has 31
        return false;
    }
    if( !date.set( 2022, 8, 31, 15, 45 )) {             // Good date, August has 31
        return false;
    }
    if( !date.set( 2021, 9, 30, 10, 12 )) {             // Good date, September has 30 days
        return false;
    }
    if( date.set( 2021, 9, 31, 10, 12 )) {              // Bad date, September has 30 days
        return false;
    }
    if( !date.set( 2022, 10, 31, 15, 45 )) {            // Good date, October has 31
        return false;
    }
    if( date.set( 2021, 11, 31, 10, 12 )) {             // Bad date, November has 30 days
        return false;
    }
    if( !date.set( 2022, 12, 31, 23, 59, 59 )) {        // Good date, December has 31 days
        return false;
    }
    return true;
}

bool testPDF( const std::string &outDirectory ) {
    if( outDirectory.empty()) {
        return false;
    }
    bool result = testPDFDate();
    if( !result ) {
        std::cerr << "testPDFDate() failed\n";
    }
    
    // page width = 612, page height = 792  (8.5 x 11)
    // x min is left,   x max is right.
    // y min is bottom, y max is top.
    long x =  31;
    long y = 700;
    
    TFSPdfDocument document;
    
    document.setCreationDate( 2021, 03, 25 );
    
    document.setLine( 100.0, 100.0, 300.0, 300.0 );
    document.setLineWidth( 20.0 );
    document.setLine( 100.0, 100.0, 100.0, 300.0 );

    document.setLineWidth( 2.0 );
    document.setBox( 200, 200, 300, 50 );
    document.setBox( 200, 260, 300, 25, 0.90 );         // Fill a box with grey
    document.setBox( 200, 260, 300, 25 );               // Frame the box with black
    
    document.setCircle( 450.0, 600.0, 20.0 );               // Little circle, above a larger one.
    document.setFramedCircle( 450.0, 500.0, 100.0, 0.95 );  // Shaded and framed

    document.setFont( TFSPdfFont::Helvetica );
    document.setFontSize( 12 );
    document.setText( x, y, "Hello there, this should be in Helvetica, 12 point" );
    y -= 20;
    document.setText( x, y, "Text line two" );
    y -= 20;
    document.setText( x, y, "Text line three" );

    y -= 20;
    document.setFont( TFSPdfFont::Courier );
    document.setText( x, y, "This should be in Courier, 12 point" );

    y -= 20;
    document.setFontSize( 18 );
    document.setText( x, y, "This should be in Courier, 18 point" );

    y -= 20;
    document.setFontSize( 6 );
    document.setText( x, y, "This should be in Courier, 6 point" );

    const std::string path{ outDirectory + "test.pdf" };        // TODO: Have Path append
    TFSPdfWriter pdfWriter( path );
    if( !pdfWriter ) {
        std::cerr << "Unable to open " << path << " for write\n";
        return false;
    }
    pdfWriter << document;

    return result;
}

}   // namespace tfs

