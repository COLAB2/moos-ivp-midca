/************************************************************/
/*    NAME: Sravya K                                              */
/*    ORGN: MIT                                             */
/*    FILE: visual.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "visual.h"

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
// Procedure: Iterate()
//            happens AppTick times per second

bool visual::Iterate()
{

// Just to view qroute and Ga1 and Ga2
if (initialize == 0)
{



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
