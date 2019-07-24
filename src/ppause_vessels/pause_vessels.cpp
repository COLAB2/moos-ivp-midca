/************************************************************/
/*    NAME:                                               */
/*    ORGN: MIT                                             */
/*    FILE: pause_vessels.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "pause_vessels.h"
#include <string>     // std::string, std::stod
#include <time.h>

using namespace std;

//---------------------------------------------------------
// Constructor

pause_vessels::pause_vessels()
{
  paused = false;
}

//---------------------------------------------------------
// Destructor

pause_vessels::~pause_vessels()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool pause_vessels::OnNewMail(MOOSMSG_LIST &NewMail)
{
  MOOSMSG_LIST::iterator p;

  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;

#if 0 // Keep these around just for te
mplate
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

bool pause_vessels::OnConnectToServer()
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

bool pause_vessels::Iterate()
{
  // Calculate the time and start the ships after certain delay
  double duration;
  duration = (double( clock() - start ) / CLOCKS_PER_SEC) * 1000 ;

  if ((duration > pause_time))
  {
      if (paused)
      {
        Notify(group_name,"speed = 0.5");
        paused = false;
      }
      else {
        Notify(group_name,"speed = 0.0");
        paused = true;
      }

      start = clock();
  }
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool pause_vessels::OnStartUp()
{
  list<string> sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(m_MissionReader.GetConfiguration(GetAppName(), sParams)) {
    list<string>::iterator p;
    for(p=sParams.begin(); p!=sParams.end(); p++) {
      string original_line = *p;
      string param = stripBlankEnds(toupper(biteString(*p, '=')));
      string value = *p;
      if(param == "PAUSETIME")
      {
        pause_time =  std::stod(value);

      }
      else if(param == "GROUPNAME")
      {
        group_name = value;
      }
      else
      {
          value = value;
      }


    }
  }

  start = clock();
  RegisterVariables();
  return(true);
}

//---------------------------------------------------------
// Procedure: RegisterVariables

void pause_vessels::RegisterVariables()
{
  // Register("FOOBAR", 0);
}
