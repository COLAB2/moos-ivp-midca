/************************************************************/
/*    NAME: Sravya K                                              */
/*    ORGN: MIT                                             */
/*    FILE: loc.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "loc.h"
#include <string>
#include <cmath>
using namespace std;


//---------------------------------------------------------
// Constructor

loc::loc()
{
initialize = 0;
lat_origin = 0;
long_origin = 0;
}

//---------------------------------------------------------
// Destructor

loc::~loc()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool loc::OnNewMail(MOOSMSG_LIST &NewMail)
{
  MOOSMSG_LIST::iterator p;

  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;

#if 0 // Keep these around just for template
    string key   = msg.GetKey();
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string sval  = msg.GetString();
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif
   }

   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool loc::OnConnectToServer()
{
   // register for variables here
   // possibly look at the mission file?
   // m_MissionReader.GetConfigurationParam("Name", <string>);
   // m_Comms.Register("VARNAME", 0);

   RegisterVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: distanceCalculate()
//            happens AppTick times per second


double loc::distanceCalculate(double x1, double y1, double x2, double y2)
{
	double x = x1 - x2; //calculating number to square in next step
	double y = y1 - y2;
	double dist;

	dist = pow(x, 2) + pow(y, 2);       //calculating Euclidean distance
	dist = sqrt(dist);

	return dist;
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool loc::Iterate()
{
double nav_x = 0;
double nav_y = 5;
double nav_lat, nav_long;
m_geodesy.LocalGrid2LatLong(nav_x, nav_y, nav_lat, nav_long);

std::stringstream stream;
stream << std::setprecision(11) << nav_lat;
std::string lat = stream.str();

std::stringstream stream1;
stream1 << std::setprecision(11) << nav_long;
std::string longitude = stream1.str();


cout << "latitude :"<< lat << "  longitdue : "<< longitude << "\n";

  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool loc::OnStartUp()
{
  list<string> sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(m_MissionReader.GetConfiguration(GetAppName(), sParams)) {
    list<string>::iterator p;
    for(p=sParams.begin(); p!=sParams.end(); p++) {
      string original_line = *p;
      string param = stripBlankEnds(toupper(biteString(*p, '=')));
      string value = stripBlankEnds(*p);

      if(param == "LAT") {
        lat_origin = stod(value);
        //handled
      }
      else if(param == "LONG") {
        //handled
        long_origin = stod(value);
      }
    }
  }

  // initialize m_geodesy
if(!m_geodesy.Initialise(lat_origin, long_origin))
  cout << "Geodesy init failed.";


  RegisterVariables();
  return(true);
}

//---------------------------------------------------------
// Procedure: RegisterVariables

void loc::RegisterVariables()
{
  // Register("FOOBAR", 0);
}
