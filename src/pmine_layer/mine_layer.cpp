/************************************************************/
/*    NAME: Sravya Kondrakunta                                              */
/*    ORGN: MIT                                             */
/*    FILE: mine_layer.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "mine_layer.h"
#include "zhelpers.hpp"
#include <cstdio>
#include <ctime>
#include <unistd.h>
#include <string>
#include <time.h>
#include <cmath>
#include <stack>


using namespace std;
zmq::context_t context(1);
zmq::socket_t publisher(context, ZMQ_PUB);
zmq::socket_t publisher_mine(context, ZMQ_PUB);


//---------------------------------------------------------
// Constructor

mine_layer::mine_layer()
{
  speed = 0.0;
  mission = "true" ;
  shift = 0;
}

//---------------------------------------------------------
// Destructor

mine_layer::~mine_layer()
{

}

//---------------------------------------------------------
// Procedure: OnNewMail

bool mine_layer::OnNewMail(MOOSMSG_LIST &NewMail)
{
  MOOSMSG_LIST::iterator p;

  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key   = msg.GetKey();
  if(key == "NAV_SPEED"){
      speed  = msg.GetDouble();

    }
    if(key == "emission"){
        mission  = msg.GetString();

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

bool mine_layer::OnConnectToServer()
{
   // register for variables here
   // possibly look at the mission file?
   // m_MissionReader.GetConfigurationParam("Name", <string>);
   // m_Comms.Register("VARNAME", 0);

   RegisterVariables();
   return(true);
}
//------------------
// Procedure : Send_info_mines
bool mine_layer::Send_info_mines(double x, double y, int label)
{

  string content = "x=" +std::to_string(x )+ ",y=" +std::to_string(y)+ ",label= "+std::to_string(label)+", type=hazard";
  s_sendmore(publisher,"M");
  s_send(publisher,content);

  string content_add = "hazard = x=" +std::to_string(x )+ ",y=" +std::to_string(y)+ ",label= "+std::to_string(label)+", type=hazard";
  s_sendmore(publisher_mine,"M");
  s_send(publisher_mine,content_add);

  return 0;
}
//-----------------------------------------------------------
// Procedure : Line_pattern
stack<Point> mine_layer::Line_pattern(double ga1_init_x,
                                      double slope,
                                      double intercept,
                                      double line_increment,
                                      double overflow_flag,
                                      int total_mines)
{

    int count = 25;
    int mine_count = 0;
    double increment = 0;
    Point point;
    stack<Point> points;
    while (mine_count != total_mines)
    {
    /*
    if ((ga1_init_x + increment) >= ga1_final_x )
        {
        increment =  (line_increment/ overflow_flag)  ;
        overflow_flag = overflow_flag * 2;
        }
    */
    //else if ( (ga1_init_x + increment) <= ga1_init_x )
    //  increment =  increment + 5 ;
   //else
   //{
     double y = slope * ( ga1_init_x + increment ) + intercept;

    // add it to stack
    point.x = (ga1_init_x + increment );
    point.y = y;
    point.label = count;
    points.push(point);

     /*
     // for statistical learning data
     std::ofstream outfile;
     outfile.open("mines_ga1.csv", std::ios_base::app);
     outfile << std::to_string(count) + "," + std::to_string(ga1_init_x + increment) + "," + std::to_string(y) << "\n" ;
     outfile.close();


    string content_add = "hazard = x=" +std::to_string(point.x )+ ",y=" +std::to_string(y)+ ",label= "+std::to_string(count)+",type=hazard";
     std::ofstream outfile;
     outfile.open("mines_line.txt", std::ios_base::app);
     outfile  << content_add <<"\n" ;
     outfile.close();
*/

     count ++;
     mine_count ++ ;

     increment += line_increment;
    //}

}
return points;
}


//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool mine_layer::Iterate()
{


  if (lay_mines.empty())
    return (true);

  else if (speed == 0 && !lay_mines.empty())
    {

      if (shift == 1)
      {
        if (mission == "false")
        {
          Point p = lay_mines.top() ;
          Send_info_mines(p.x, p.y, p.label);
          lay_mines.pop();
          shift = 0;
        }
      }
      else
      {
      Notify("emission", "true");
      Point p = lay_mines.top() ;
      string content = "point = " +std::to_string(p.x)+ "," +std::to_string(p.y)  ;
      Notify("UPDATE_POINTS", content);
      shift = 1;
    }
    }
  else
  {
    return 0;
  }


  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool mine_layer::OnStartUp()
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
  publisher.connect("tcp://127.0.0.1:5505");
  publisher_mine.bind("tcp://127.0.0.1:5522");
  int timeout = 1;
  int count = 2;
  publisher.setsockopt (ZMQ_SNDHWM, &count, sizeof (int));
  publisher_mine.setsockopt (ZMQ_SNDHWM, &count, sizeof (int));

/*
  double ga1_init_x,
  double slope,
  double intercept,
  double line_increment,
  double overflow_flag,
  int total_mines

*/
  lay_mines = Line_pattern(52, -0.7, -10, 15, 2, 7);
  //lay_mines = Line_pattern(-15, -0.7, -90, 10, 2, 11);
  //lay_mines = Line_pattern(120, -0.7, 75, 10, 2, 11);

  RegisterVariables();
  return(true);
}

//---------------------------------------------------------
// Procedure: RegisterVariables

void mine_layer::RegisterVariables()
{
   Register("NAV_SPEED", 0);
   Register("emission", 0);
}
