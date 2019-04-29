/************************************************************/
/*    NAME: Sravya K                                              */
/*    ORGN: MIT                                             */
/*    FILE: visual.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "visual.h"
#include <string>


using namespace std;


//---------------------------------------------------------
// Constructor

visual::visual()
{
initialize = 0;
}

//---------------------------------------------------------
// Destructor

visual::~visual()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool visual::OnNewMail(MOOSMSG_LIST &NewMail)
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

bool visual::OnConnectToServer()
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


double visual::distanceCalculate(double x1, double y1, double x2, double y2)
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

bool visual::Iterate()
{

// Just to view qroute and Ga1 and Ga2
if (initialize == 0)
{
  string s = "";
  /*
  // GA2
  string s = "radial:: x=150, y=-80, radius=20, pts=8, snap=1, label= GA2";
  Notify("VIEW_POLYGON",s);

  // GA1
  s = "radial:: x=20, y=-80, radius=20, pts=8, snap=1,  label= GA1";
  Notify("VIEW_POLYGON",s);

  // Qroute

  s= "pts={-105,-49:245,-49},  label= QROUTE";
  Notify("VIEW_SEGLIST",s);

  s= "pts={-113,-99:218,-100}";
  Notify("VIEW_SEGLIST",s);
  */

  // Grids
  double top_left[2] = {-141,76};
  double top_right[2] = {270,76};
  double bottom_left[2] = {-141,-225};
  double bottom_right[2] = {270,-225};
  double horizontal_dist = distanceCalculate(top_left[0],
                                          top_left[1],
                                          bottom_left[0],
                                          bottom_left[1]);

  double vertical_dist = distanceCalculate(top_left[0],
                                          top_left[1],
                                          top_right[0],
                                          top_right[1]);

  int grid = 20 ;
  int count = 0;
  for (int i=0; i < (horizontal_dist/grid); i++)
  {
    s= "pts={" + to_string(top_left[0]) + "," + to_string(top_left[1] - i*grid)
               + ":" + to_string(top_right[0]) + ","
               + to_string(top_right[1] - i*grid) + "},  label=" + to_string(i);

    Notify("VIEW_SEGLIST",s);
    count = count + 1;
  }

  for (int i=0; i < (vertical_dist/grid); i++)
  {
    s= "pts={" + to_string(top_left[0] + i*grid) + "," + to_string(top_left[1] )
               + ":" + to_string(bottom_left[0] + i*grid) + ","
               + to_string(bottom_left[1] ) + "},  label=" + to_string(i + count);

    Notify("VIEW_SEGLIST",s);
  }

initialize = 1;
}



  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool visual::OnStartUp()
{
  list<string> sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(m_MissionReader.GetConfiguration(GetAppName(), sParams)) {
    list<string>::iterator p;
    for(p=sParams.begin(); p!=sParams.end(); p++) {
      string original_line = *p;
      string param = stripBlankEnds(toupper(biteString(*p, '=')));
      string value = stripBlankEnds(*p);

      if(param == "FOO") {
        //handled
      }
      else if(param == "BAR") {
        //handled
      }
    }
  }
  RegisterVariables();
  return(true);
}

//---------------------------------------------------------
// Procedure: RegisterVariables

void visual::RegisterVariables()
{
  // Register("FOOBAR", 0);
}
