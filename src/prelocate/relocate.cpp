/************************************************************/
/*    NAME: Sravya                                              */
/*    ORGN: MIT                                             */
/*    FILE: relocate.cpp                                        */
/*    DATE:                                                 */

/* This file is to make the ships work by imitating the functionality of pNodeReporter (look at moos documentation)
   Moreover, it checks whether a ship hits the mine or not, if it does then the ship will be transported to a location outside  the experiment area"
   Furthermore, it sets the delay to which the ships start moving */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "relocate.h"
#include <sstream>
#include <iostream>
#include <math.h>
#include <fstream>
#include <fstream>
#include <unistd.h>
#include <cstdio>
#include <string>




using namespace std;


//---------------------------------------------------------
// Constructor

relocate::relocate()
{
  newreport = "" ;
  // navigation points from moos db
  m_current_x = 0.0;
  m_current_y = 0.0;
  // spped from moos DB
  m_current_s = 0.0;
  //heading from moos DB
  m_current_h = 90.0;
  // depth from moos DB
  m_current_d = 0.0;
  //latitude from moos DB
  m_current_lat = 0;
  //Longitude from moos DB
  m_current_long = 0;
  // ivp State
  ivp_state = "";
  // ivp ALLSTOP
  ivp_allstop = "";
  // for database time
  m_current_time = 0;
  // INDEX
  index = 1;
  // length of the ship
  length = 5;
  // name
  name = "";
  // check if the ship is wrecked or not
  wreck = 0;
}

//---------------------------------------------------------
// Destructor

relocate::~relocate()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool relocate::OnNewMail(MOOSMSG_LIST &NewMail)
{
  MOOSMSG_LIST::iterator p;

  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key   = msg.GetKey();
    name = msg.GetCommunity();
    if(key == "DB_TIME"){
      m_current_time = msg.GetDouble();
    }
    else if(key == "NAV_X"){

      m_current_x = msg.GetDouble();
    }
    else if(key == "NAV_Y"){

      m_current_y = msg.GetDouble();
    }
    else if(key == "NAV_LAT"){

      m_current_lat = msg.GetDouble();
    }
    else if(key == "NAV_LONG"){

      m_current_long = msg.GetDouble();
    }
    else if(key == "IVPHELM_STATE"){

      ivp_state = msg.GetString();
    }
    else if(key == "IVPHELM_ALLSTOP"){

      ivp_allstop = msg.GetString();
    }
    else if(key == "NAV_HEADING"){

      m_current_h = msg.GetDouble();
    }
    else if(key == "NAV_DEPTH"){

      m_current_d = msg.GetDouble();
    }
    else if(key == "UHZ_DETECTION_REPORT"){
      wreck = 1;

      // get the mine label and notify to the hazardsensor
      std::string s = msg.GetString();
      std::string delimiter = "=";
      size_t pos = 0;
      std::string token;
      while ((pos = s.find(delimiter)) != std::string::npos) {
      token = s.substr(0, pos);
      s.erase(0, pos + delimiter.length());
      }
      Notify("RemoveHazard", s);
      }


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

bool relocate::OnConnectToServer()
{
   // register for variables here
   // possibly look at the mission file?
   // m_MissionReader.GetConfigurationParam("Name", <string>);
   // m_Comms.Register("VARNAME", 0);

   RegisterVariables();
   return(true);
}

// Procedure: Iterate()
//            happens AppTick times per second

bool relocate::Iterate()
{

//Notify("DB_CLIENTS","uXMS_166,pHostInfo,pShare,prelocate,uProcessWatch,pHelmIvP,pMarinePID,uSimMarine,");
//  Notify("NODE_REPORT_LOCAL","NAME=ship,X=206.77,Y=-66.34,SPD=0,HDG=84.8,DEP=0,LAT=43.82473273,
//                            LON=-70.32781596,TYPE=SHIP,MODE=DRIVE,ALLSTOP=NothingToDo,
//                            INDEX=4771,YAW=0.0908344,TIME=12311502446.75,LENGTH=8");



// lock variable is to send the location of the ship to pMArineviewer through node NODE_REPORT
// If it is zero, then transport the ship to a different location outside the experiment
// if it is one, continously send the current location of the ship (same functionality as pNodeReporter)
// appending name
if (wreck == 1)
{
  newreport = newreport + "Name=" + name + ",";
  newreport = newreport + "X=-1700,";
  newreport = newreport + "Y=-1500,";
  newreport = newreport + "SPD=0," ;
  newreport = newreport + "HDG=0,";
  newreport = newreport + "DEP=0," ;
  newreport = newreport + "LAT=0,";
  newreport = newreport + "LONG=0," ;
  newreport = newreport + "TYPE=SHIP,";
  newreport = newreport + "MODE=PARK,";
  newreport = newreport + "ALLSTOP=Wreck,";
  newreport = newreport + "INDEX=" + to_string(index) + ",";
  newreport = newreport + "TIME=" + to_string(m_current_time) + ",";
  newreport = newreport + "LENGTH=1";
  Notify("NODE_REPORT_LOCAL", newreport);
}
else
{
  newreport = newreport + "Name=" + name + ",";
  newreport = newreport + "X=" + to_string(m_current_x) + ",";
  newreport = newreport + "Y=" + to_string(m_current_y) + ",";
  newreport = newreport + "SPD=" + to_string(m_current_s) + ",";
  newreport = newreport + "HDG=" + to_string(m_current_h) + ",";
  newreport = newreport + "DEP=" + to_string(m_current_d) + ",";
  newreport = newreport + "LAT=" + to_string(m_current_lat) + ",";
  newreport = newreport + "LONG=" + to_string(m_current_long) + ",";
  newreport = newreport + "TYPE=SHIP,";
  newreport = newreport + "MODE=" + ivp_state + ",";
  newreport = newreport + "ALLSTOP=" + ivp_allstop + ",";
  newreport = newreport + "INDEX=" + to_string(index) + ",";
  newreport = newreport + "TIME=" + to_string(m_current_time) + ",";
  newreport = newreport + "LENGTH=" + to_string(length) + ",";
  Notify("NODE_REPORT_LOCAL", newreport);
}

index= index + 1;
newreport = "" ;
// after a certain delay make the ships traverse through the Qroute

return(true);
}



//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool relocate::OnStartUp()
{
  list<string> sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(m_MissionReader.GetConfiguration(GetAppName(), sParams)) {
    list<string>::iterator p;
    for(p=sParams.begin(); p!=sParams.end(); p++) {
      string original_line = *p;
      string param = stripBlankEnds(toupper(biteString(*p, '=')));
      string value = stripBlankEnds(*p);
    }
  }

RegisterVariables();
  return(true);
}

//---------------------------------------------------------
// Procedure: RegisterVariables

void relocate::RegisterVariables()
{
  Register("DB_TIME", 0);
  Register("NAV_X", 0);
  Register("NAV_Y", 0);
  Register("NAV_SPEED", 0);
  Register("NAV_HEADING", 0);
  Register("NAV_LAT", 0);
  Register("NAV_LONG", 0);
  Register("IVPHELM_STATE", 0);
  Register("UHZ_DETECTION_REPORT", 0);
}
