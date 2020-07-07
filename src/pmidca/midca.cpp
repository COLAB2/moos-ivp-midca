/************************************************************/
/*    NAME: Sravya                                              */
/*    ORGN: WSU                                           */
/*    FILE: midca.cpp                                        */
/*    Functionality:    It does three specific things
                        1. Communicates vehicle location (x,y), speed and heading
                        2. Communicates Detected mines
                        3. Subscribes way_points from midca */


/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "midca.h"
#include <string>
#include "zhelpers.hpp"
#include <unistd.h>

using namespace std;

zmq::context_t context(1);
zmq::socket_t publisher(context, ZMQ_PUB);
zmq::socket_t publisher_mine(context, ZMQ_PUB);
zmq::socket_t subscriber (context, ZMQ_SUB);
//---------------------------------------------------------
// Constructor

midca::midca()
{
   m_first_reading = true;
   m_current_x = 0;
   m_current_y = 0;
   m_previous_x = 0;
   m_previous_y = 0;
   points = "ptx=0 # pty =0";
   mission = "false";
   report = "" ;
   previous_report = "";
   status = "";
   ship_status = "";
   send_mine_flag = 0;

}

//---------------------------------------------------------
// Destructor

midca::~midca()
{

}

//---------------------------------------------------------
// Procedure: OnNewMail

bool midca::OnNewMail(MOOSMSG_LIST &NewMail)
{

  // Get the X,Y and speed coordinates from MOOSDB and publish for MIDCA
  MOOSMSG_LIST::iterator p;

  m_current_x = -1;
  m_current_y = -1;
  m_current_s = -1;
  m_current_h = -1;
  report = "false";



  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key   = msg.GetKey();

    if(key == "NAV_X"){
      m_current_x  = msg.GetDouble();
    }
    else if(key == "NAV_Y"){
      m_current_y  = msg.GetDouble();

    }
    else if(key == "NAV_SPEED"){
      m_current_s  = msg.GetDouble();

    }
    else if(key == "NAV_HEADING"){
        m_current_h  = msg.GetDouble();

    }
    else if(key == "IVPHELM_ALLSTOP"){
        status  = msg.GetString();
        }
    else if(key == "SHIP_STATUS"){
            ship_status  = msg.GetString();
            }

    else if(key == "UHZ_DETECTION_REPORT"){
      report  = msg.GetString();
      if (send_mine_flag)
        s_send (publisher_mine, "MINE:" + report);
      }

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




    if (m_current_x != -1 && m_current_y != -1)
	{
  if (ship_status != "")
  {

    // send vehicles current location speed and heading of format  "X:90,Y:180,SPEED:1.5,HEADING:180,STATUS:clear"
    s_send (publisher, "X:" + std::to_string(m_current_x) + "," + "Y:" + std::to_string(m_current_y) + "," + "SPEED:" + std::to_string(m_current_s) + "," + "HEADING:" + std::to_string(m_current_h) + "," + "STATUS:" + ship_status);
  }
  else
    s_send (publisher, "X:" + std::to_string(m_current_x) + "," + "Y:" + std::to_string(m_current_y) + "," + "SPEED:" + std::to_string(m_current_s) + "," + "HEADING:" + std::to_string(m_current_h) + "," + "STATUS:" + status);

    }
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool midca::OnConnectToServer()
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

bool midca::Iterate()
{

//  Read envelope with address
std::string address = s_recv (subscriber);
//  Read message contents
std::string contents = s_recv (subscriber);


// check to see if there is a message from midca for the vehicle behavior
if  (address.compare("Vehicle") == 0 && !contents.empty() && contents.compare("Vehicle") != 0)
{
// their scope is defined at pMarineViewer in alder.moos and alder.bhv files
// for the behaviour
Notify("mission","true");

// send the new points to MOOSDB
Notify("NEW_POINTS", contents);

}

// check to see if there is a message from midca for Removing a Mine
else if  ( address.compare("RemoveHazard") == 0 && !contents.empty() && contents.compare("RemoveHazard") != 0)
{
// add a variable RemoveMine so that the uFldHazardSensor can remove the mine reading the RemoveMine variable
// this is also added in the configuration parameters of the uFldNodeBroker
Notify("RemoveHazard", contents);
}

// check to see if there is a message from midca for adding a Mine
else if  (address.compare("AddHazard") == 0 && !contents.empty() && contents.compare("AddHazard") != 0)
{

// add a variable RemoveMine so that the uFldHazardSensor can remove the mine reading the RemoveMine variable
// this is also added in the configuration parameters of the uFldNodeBroker
Notify("AddHazard", contents);

}


  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool midca::OnStartUp()
{

  string publish_ip = "tcp://";
  string subscribe_ip = "tcp://";
  string publish_mine_ip = "tcp://";

  list<string> sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(m_MissionReader.GetConfiguration(GetAppName(), sParams)) {
    list<string>::iterator p;
    for(p=sParams.begin(); p!=sParams.end(); p++) {
      string original_line = *p;
      string param = stripBlankEnds(toupper(biteString(*p, '=')));
      string value = *p;
        if(param == "PUBLISH_IP") {
            publish_ip = publish_ip + value;
        }
        else if(param == "PUBLISH_MINE_IP") {
            publish_mine_ip = publish_mine_ip + value;
            send_mine_flag = 1;
        }
        else if(param == "SUBSCRIBE_IP") {
            subscribe_ip = subscribe_ip + value;
        }
        else
        {
            value = value;
        }


    }
  }
  publisher.bind(publish_ip);
  subscriber.bind(subscribe_ip);
  subscriber.setsockopt( ZMQ_SUBSCRIBE, "Vehicle" , 1);
  subscriber.setsockopt( ZMQ_SUBSCRIBE, "RemoveHazard" , 1);
  subscriber.setsockopt( ZMQ_SUBSCRIBE, "AddHazard" , 1);
  int timeout = 1;
  int count = 2;
  int count_mine = 0;
  subscriber.setsockopt (ZMQ_RCVTIMEO, &timeout, sizeof (int));
  publisher.setsockopt (ZMQ_SNDHWM, &count, sizeof (int));

  if (send_mine_flag)
  {
  publisher_mine.bind(publish_mine_ip);
  publisher_mine.setsockopt (ZMQ_SNDHWM, &count_mine, sizeof (int));
  }
  RegisterVariables();
  return(true);
}

//---------------------------------------------------------
// Procedure: RegisterVariables

void midca::RegisterVariables()
{
  Register("IVPHELM_ALLSTOP", 0);
  Register("NAV_X", 0);
  Register("NAV_Y", 0);
  Register("NAV_SPEED", 0);
  Register("NAV_HEADING", 0);
  Register("UHZ_DETECTION_REPORT", 0);
  Register("SHIP_STATUS", 0);

}
