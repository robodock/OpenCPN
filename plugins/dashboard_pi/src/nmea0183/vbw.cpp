/***************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  NMEA0183 Support Classes
 * Author:   Samuel R. Blackburn, David S. Register
 *
 ***************************************************************************
 *   Copyright (C) 2010 by Samuel R. Blackburn, David S Register           *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.         *
 ***************************************************************************
 *
 *   S Blackburn's original source license:                                *
 *         "You can use it any way you like."                              *
 *   More recent (2010) license statement:                                 *
 *         "It is BSD license, do with it what you will"                   *
 */

#include "nmea0183.h"

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** VBW support added by eddie@robodock.net
**
** You can use it any way you like.
*/

//IMPLEMENT_DYNAMIC( VBW, RESPONSE )

VBW::VBW()
{
   Mnemonic = _T("VBW");
   Empty();
}

VBW::~VBW()
{
   Mnemonic.Empty();
   Empty();
}

void VBW::Empty( void )
{
//   ASSERT_VALID( this );

   LongitudinalWaterSpeed       = 0.0;
   TransverseWaterSpeed         = 0.0;
   LongitudinalGroundSpeed      = 0.0;
   TransverseGroundSpeed        = 0.0;
}

bool VBW::Parse( const SENTENCE& sentence )
{
//   ASSERT_VALID( this );

   /*
   ** VBW - Dual Water/Ground speed
   **
   **        1   2   3 4   5   6 7  
   **        |   |   | |   |   | |  
   ** $--VBW,x.x,x.x,A,x.x,x.x,A*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Longitudinal Water Speed, "-"means astern
   **  2) Transverse Water Speed, "-"means port
   **  3) Status, A=Data Valid
   **  4) Longitudinal Ground Speed, "-"means astern
   **  5) Transverse Ground Speed, "-"means port
   **  6) Status, A=Data Valid
   **  7) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 7 ) == TRUE )
   {
      SetErrorMessage( _T("Invalid Checksum") );
      return( FALSE );
   } 

   LongitudinalWaterSpeed  = sentence.Double( 1 );
   TransverseWaterSpeed    = sentence.Double( 2 );
   LongitudinalGroundSpeed = sentence.Double( 4 );
   TransverseGroundSpeed   = sentence.Double( 5 );

   return( TRUE );
}

bool VBW::Write( SENTENCE& sentence )
{
//   ASSERT_VALID( this );

   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += LongitudinalWaterSpeed;
   sentence += TransverseWaterSpeed;
   sentence += _T("A");
   sentence += LongitudinalGroundSpeed;
   sentence += TransverseGroundSpeed;
   sentence += _T("A");

   sentence.Finish();

   return( TRUE );
}

const VBW& VBW::operator = ( const VBW& source )
{
//   ASSERT_VALID( this );

   LongitudinalWaterSpeed  = source.LongitudinalWaterSpeed;
   TransverseWaterSpeed    = source.TransverseWaterSpeed;
   LongitudinalGroundSpeed = source.LongitudinalGroundSpeed;
   TransverseGroundSpeed   = source.TransverseGroundSpeed;

   return( *this );
}
