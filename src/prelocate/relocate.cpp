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
#include <time.h>
#include <fstream>
#include <unistd.h>
#include "zhelpers.hpp"
#include <cstdio>
#include <ctime>



using namespace std;
zmq::context_t context(1);
zmq::socket_t subscriber (context, ZMQ_SUB);
zmq::socket_t subscriber_add_mine (context, ZMQ_SUB);
zmq::socket_t publisher_mine(context, ZMQ_PUB);

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

  index_x = 0;
  index_y = 0;
  index_label=0;
  lock = 0;

  start = -1.0;
  stop_lock = 0;

  // distance
  threshold_distance = 3;
  // group delays
  delay_group1 = 1.3;
  delay_group2 = 1.7;
  //filename = "/home/sampath/moos-ivp/moos-ivp-midca/missions/new/hazards.txt";
  filename = "../../missions/gatars/hazards6.txt" ;
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
    else
    {
      return(true);
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

//---------------------------------------------------------
double distanceCalculate(double x1, double y1, double x2, double y2)
{
	double x = x1 - x2; //calculating number to square in next step
	double y = y1 - y2;
	double dist;

	dist = pow(x, 2) + pow(y, 2);       //calculating Euclidean distance
	dist = sqrt(dist);

	return dist;
}


// supporting function to add mines to respective arrays
bool relocate::hazard_feed(string line)
{
  std::string line_label;
  std::string line_y;
  line = line.replace(0,9,"");
  for (int i =0 ; i < line.length() ; i++)
   {

       if (line[i] == ',')
       {
           line_y = line;
           line_y = line_y.replace(0,i+1,"");
           line = line.replace(i,line.length(),"");
           line = line.replace(0,2,"");
           double temp = std::stod( line);
           x[index_x] = temp;
           cout << temp << "  ";
           index_x = index_x + 1;
           //x[index_x] = std::stoi( line) ;
           //index_x = index_x + 1;
           break;
   }


  }

  for (int i =0 ; i < line_y.length() ; i++)
   {
       if (line_y[i] == ',')
       {
           line_label = line_y;
           line_label = line_label.replace(0,i+1,"");
           line_y = line_y.replace(i,line_y.length(),"");
           line_y = line_y.replace(0,2,"");

           double temp = std::stod( line_y);
           y[index_y] = temp;
           cout << temp << "  ";
           index_y = index_y + 1;
            break;
   }
  }
  for (int i =0 ; i < line_label.length() ; i++)
   {
       if (line_label[i] == ',')
       {
           line_label = line_label.replace(i,line_label.length(),"");
           line_label = line_label.replace(0,7,"");
           int temp = std::stoi(line_label);
           cout << temp << " \n";
           label[index_label] = temp;
           index_label = index_label + 1;
            break;
   }
  }

  return (true);
}



// Procedure: Iterate()
//            happens AppTick times per second

bool relocate::Iterate()
{


// Calculate the time and start the ships after certain delay
double duration;
duration = double( clock() - start ) / (double) CLOCKS_PER_SEC;


if (duration > delay_group1 && start != -1.0)
  // this is to make the ships of the group1 to move
  Notify("GROUP1","true");

if (duration > delay_group2 && start != -1.0)
    // this is to make the ships of the group1 to move
    Notify("GROUP2","true");


  //Notify("DB_CLIENTS","uXMS_166,pHostInfo,pShare,prelocate,uProcessWatch,pHelmIvP,pMarinePID,uSimMarine,");
//  Notify("NODE_REPORT_LOCAL","NAME=ship,X=206.77,Y=-66.34,SPD=0,HDG=84.8,DEP=0,LAT=43.82473273,
//                            LON=-70.32781596,TYPE=SHIP,MODE=DRIVE,ALLSTOP=NothingToDo,
//                            INDEX=4771,YAW=0.0908344,TIME=12311502446.75,LENGTH=8");



// lock variable is to send the location of the ship to pMArineviewer through node NODE_REPORT
// If it is zero, then transport the ship to a different location outside the experiment
// if it is one, continously send the current location of the ship (same functionality as pNodeReporter)
// appending name
if (lock == 0)
{

  // check if there is a mine removed
  std::string contents = s_recv (subscriber);
  if  ( !contents.empty() && contents.compare("M") != 0)
  {
    int label_mine = std::stoi (contents);
  for (int i =0 ; i < index_label ; i++)
  {
    if (label[i] == label_mine)
      {
        x[i] = 1000;
        y[i] = 1000;
      }
  }
  }

  contents = s_recv (subscriber_add_mine);
  if  ( !contents.empty() && contents.compare("M") != 0)
  {
    hazard_feed(contents);

  }



newreport = newreport + "Name=" + name + ",";
for (int i =0 ; i < index_x ; i++)
{
    double distance =  distanceCalculate(x[i],y[i],m_current_x,m_current_y)  ;
    if ( distance < threshold_distance)
      {
        s_sendmore(publisher_mine,"M");
        s_send(publisher_mine,to_string(label[i]));


        newreport = newreport + "X=-700,";
        newreport = newreport + "Y=-500,";
        newreport = newreport + "SPD=0," ;
        newreport = newreport + "HDG=0,";
        newreport = newreport + "DEP=0," ;
        newreport = newreport + "LAT=0,";
        newreport = newreport + "LONG=0," ;
        newreport = newreport + "TYPE=SHIP,";
        newreport = newreport + "MODE=PARK,";
        newreport = newreport + "ALLSTOP=NothingToDo,";
        newreport = newreport + "INDEX=" + to_string(index) + ",";
        newreport = newreport + "TIME=" + to_string(m_current_time) + ",";
        newreport = newreport + "LENGTH=1";
        Notify("NODE_REPORT_LOCAL", newreport);
        lock = 1;

        // write to a file
        std::ofstream outfile;
        outfile.open("scores.csv", std::ios_base::app);
        outfile << name + ",-1" << "\n" ;
        outfile.close();

        break;

      }

}
}
if (lock == 1)
{
  return(true);
}
else
{
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

      if(param == "FOO") {
        //handled
      }
      else if(param == "BAR") {
        //handled
      }
    }
  }


  std::string line;
  std::ifstream infile(filename);
  while (std::getline(infile, line))
  {

    hazard_feed(line);


  }
infile.close();
// write to a file
std::ofstream outfile;
outfile.open("scores.csv", std::ios_base::app);
outfile << name + ",1" << "\n" ;
outfile.close();
publisher_mine.connect("tcp://127.0.0.1:5565");
subscriber.connect("tcp://127.0.0.1:5570");
subscriber_add_mine.connect("tcp://127.0.0.1:5522");
subscriber.setsockopt( ZMQ_SUBSCRIBE, "M" , 1);
subscriber_add_mine.setsockopt( ZMQ_SUBSCRIBE, "M" , 1);
 int timeout = 1;
 int count = 2;
subscriber.setsockopt (ZMQ_RCVTIMEO, &timeout, sizeof (int));
subscriber.setsockopt (ZMQ_CONFLATE, &timeout, sizeof (int));
subscriber_add_mine.setsockopt (ZMQ_RCVTIMEO, &timeout, sizeof (int));
subscriber_add_mine.setsockopt (ZMQ_CONFLATE, &timeout, sizeof (int));
publisher_mine.setsockopt (ZMQ_SNDHWM, &count, sizeof (int));
start = clock();
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
}
