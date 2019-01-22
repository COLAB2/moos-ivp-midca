/************************************************************/
/*    NAME: Sravya                                              */
/*    ORGN: WSU                                           */
/*    FILE: midca.cpp                                        */
/*    DATE:                                                 */
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


    else if(key == "UHZ_DETECTION_REPORT"){
      report  = msg.GetString();
      s_send (publisher_mine, "MINE:" + report);

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



    if (m_current_x != -1 && m_current_y != -1 && m_current_s != -1 && m_current_h != -1)
	{
	s_send (publisher, "X:" + std::to_string(m_current_x) + "," + "Y:" + std::to_string(m_current_y) + "," + "SPEED:" + std::to_string(m_current_s) + "," + "HEADING:" + std::to_string(m_current_h));
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


// check to see if there is a message from midca
if  ( !contents.empty() && contents.compare("M") != 0)
{

// their scope is defined at pMarineViewer in alder.moos and alder.bhv files
// for the behaviour
Notify("mission","true");

// send the new points to MOOSDB
Notify("NEW_POINTS", contents);


}
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool midca::OnStartUp()
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
  publisher.bind("tcp://127.0.0.1:5563");
  publisher_mine.bind("tcp://127.0.0.1:5564");
  subscriber.connect("tcp://127.0.0.1:5560");
  subscriber.setsockopt( ZMQ_SUBSCRIBE, "M" , 1);
  int timeout = 1;
  int count = 2;
  subscriber.setsockopt (ZMQ_RCVTIMEO, &timeout, sizeof (int));
  subscriber.setsockopt (ZMQ_CONFLATE, &timeout, sizeof (int));
  publisher.setsockopt (ZMQ_SNDHWM, &count, sizeof (int));
  publisher_mine.setsockopt (ZMQ_SNDHWM, &count, sizeof (int));

  RegisterVariables();
  return(true);
}

//---------------------------------------------------------
// Procedure: RegisterVariables

void midca::RegisterVariables()
{
  Register("NAV_X", 0);
  Register("NAV_Y", 0);
  Register("NAV_SPEED", 0);
  Register("NAV_HEADING", 0);
  Register("UHZ_DETECTION_REPORT", 0);
}
