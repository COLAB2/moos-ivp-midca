/************************************************************/
/*    NAME: Sravya K                                              */
/*    ORGN: MIT                                             */
/*    FILE: visual.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "visual.h"
#include "zhelpers.hpp"

using namespace std;

zmq::context_t context(1);
zmq::socket_t subscriber (context, ZMQ_SUB);
zmq::socket_t publisher(context, ZMQ_PUB);
zmq::socket_t publisher_mine(context, ZMQ_PUB);

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



std::string contents = s_recv (subscriber);


// check to see if there is a message from midca/ships
if  ( !contents.empty() && contents.compare("M") != 0)
{
// make the mine disappear
// contents has the label for the mine
string report = "x=0,y=0,width=0, label=" + contents;

Notify("VIEW_MARKER",report);

// inform ships that there is no mine
s_sendmore(publisher, "M");
s_send(publisher,contents);

// inform midca that the hazard is removed
s_send(publisher_mine, "mine"+contents);

}

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
  // this is to make the mine disappear
  subscriber.bind("tcp://127.0.0.1:5565");
  // this is to inform the disappeared mine to ships
  publisher.bind("tcp://127.0.0.1:5570");
  // to inform midca that hazard is removed
  publisher_mine.bind("tcp://127.0.0.1:5580");

  subscriber.setsockopt( ZMQ_SUBSCRIBE, "M" , 1);
  int timeout = 1;
  int count = 2;
  subscriber.setsockopt (ZMQ_RCVTIMEO, &timeout, sizeof (int));
  subscriber.setsockopt (ZMQ_CONFLATE, &timeout, sizeof (int));
  publisher_mine.setsockopt (ZMQ_SNDHWM, &count, sizeof (int));
  RegisterVariables();
  return(true);
}

//---------------------------------------------------------
// Procedure: RegisterVariables

void visual::RegisterVariables()
{
  // Register("FOOBAR", 0);
}
