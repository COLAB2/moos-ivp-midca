/************************************************************/
/*    NAME: Sravya K                                              */
/*    ORGN: MIT                                             */
/*    FILE: visualGenios.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "visualGenios.h"
#include <string>


using namespace std;


//---------------------------------------------------------
// Constructor

visualGenios::visualGenios()
{
initialize = 0;
}

//---------------------------------------------------------
// Destructor

visualGenios::~visualGenios()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool visualGenios::OnNewMail(MOOSMSG_LIST &NewMail)
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

bool visualGenios::OnConnectToServer()
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


double visualGenios::distanceCalculate(double x1, double y1, double x2, double y2)
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

bool visualGenios::Iterate()
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
  // This variable is the top left points on the grid
  double top_left[2] = {0,0};
  double top_right[2] = {8854,0};
  double bottom_left[2] = {0,-6455};
  double bottom_right[2] = {8854,-6455};



  double horizontal_dist = distanceCalculate(top_left[0],
                                          top_left[1],
                                          bottom_left[0],
                                          bottom_left[1]);

  double vertical_dist = distanceCalculate(top_left[0],
                                          top_left[1],
                                          top_right[0],
                                          top_right[1]);

  // grid size
  int grid_x = 1600 ;

  //grid size
  int grid_y = 1600;

  // count is for labeling the grid
  int count = 0;

  // lines drawn vertical
  for (int i=0; i < (horizontal_dist/grid_x); i++)
  {
    s= "pts={" + to_string(top_left[0]) + "," + to_string(top_left[1] - i*grid_x)
               + ":" + to_string(top_right[0]) + ","
               + to_string(top_right[1] - i*grid_x) + "},  label=" + to_string(i);

    Notify("VIEW_SEGLIST",s);
    count = count + 1;
  }

  // Lines drawn horizontal
  for (int i=0; i < (vertical_dist/grid_y); i++)
  {
    s= "pts={" + to_string(top_left[0] + i*grid_y) + "," + to_string(top_left[1] )
               + ":" + to_string(bottom_left[0] + i*grid_y) + ","
               + to_string(bottom_left[1] ) + "},  label=" + to_string(i + count);

    Notify("VIEW_SEGLIST",s);
  }


  // Route
 s= "pts={0,-4000:8854,-4000},  edge_color=red, label= QROUTE";
 Notify("VIEW_SEGLIST",s);

  // GA2
  //s = "radial:: x=139, y=-130, radius=30, pts=8, snap=1, label= GA2";
  //Notify("VIEW_POLYGON",s);

  // GA1
  //s = "radial:: x=-23, y=-130, radius=30, pts=8, snap=1,  label= GA1";
  //Notify("VIEW_POLYGON",s);




}



  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool visualGenios::OnStartUp()
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

void visualGenios::RegisterVariables()
{
  // Register("FOOBAR", 0);
}
