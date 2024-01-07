// for compile and build: g++ -o BasicExample BasicExample.cpp ../../src/TinyGPS++.cpp
#include <iostream>
#include "../../src/TinyGPS++.h"

using namespace std;
/* 
   This sample sketch should be the first you try out when you are testing a TinyGPSPlus
   (TinyGPSPlus) installation.  In normal use, you feed TinyGPSPlus objects characters from
   a serial NMEA GPS device, but this example uses static strings for simplicity.
*/

// A sample NMEA stream.
const char *gpsStream =
  "$GPRMC,045103.000,A,3014.1984,N,09749.2872,W,0.67,161.46,030913,,,A*7C\r\n"
  "$GPGGA,045104.000,3014.1985,N,09749.2873,W,1,09,1.2,211.6,M,-22.5,M,,0000*62\r\n"
  "$GPRMC,045200.000,A,3014.3820,N,09748.9514,W,36.88,65.02,030913,,,A*77\r\n"
  "$GPGGA,045201.000,3014.3864,N,09748.9411,W,1,10,1.2,200.8,M,-22.5,M,,0000*6C\r\n"
  "$GPRMC,045251.000,A,3014.4275,N,09749.0626,W,0.51,217.94,030913,,,A*7D\r\n"
  "$GPGGA,045252.000,3014.4273,N,09749.0628,W,1,09,1.3,206.9,M,-22.5,M,,0000*6F\r\n";

// The TinyGPSPlus object
TinyGPSPlus gps;

void setup();
void displayInfo();

int main(void)
{
  setup();

  return 0;
}

void setup()
{

  cout<< (("BasicExample.ino"))<< endl;
  cout<< (("Basic demonstration of TinyGPSPlus (no device needed)"));
  cout<< (("Testing TinyGPSPlus library v. ")); cout<< (TinyGPSPlus::libraryVersion())<< endl;
  cout<< (("by Mohammad Nikanjam"))<< endl;
  cout<< "\n";

  while (*gpsStream)
    if (gps.encode(*gpsStream++))
      displayInfo();

  cout<< "\n";
  cout<< (("Done."))<< endl;
}

void displayInfo()
{
  cout<< (("Location: ")); 
  if (gps.location.isValid())
  {
    cout<< gps.location.lat();
    cout<< (",");
    cout<< gps.location.lng();
  }
  else
  {
    cout<< (("INVALID"));
  }

  cout<< (("  Date/Time: "));
  if (gps.date.isValid())
  {
    cout<< (gps.date.month());
    cout<< ("/");
    cout<< (gps.date.day());
    cout<< ("/");
    cout<< (gps.date.year());
  }
  else
  {
    cout<< (("INVALID"));
  }

  cout<< ((" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) cout<< (("0"));
    cout<< (gps.time.hour());
    cout<< ((":"));
    if (gps.time.minute() < 10) cout<< (("0"));
    cout<< (gps.time.minute());
    cout<< ((":"));
    if (gps.time.second() < 10) cout<< (("0"));
    cout<< (gps.time.second());
    cout<< (("."));
    if (gps.time.centisecond() < 10) cout<< (("0"));
    cout<< (gps.time.centisecond());
  }
  else
  {
    cout<< (("INVALID"));
  }

  cout<< "\n";
}
