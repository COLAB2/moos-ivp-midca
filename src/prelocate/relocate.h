/************************************************************/
/*    NAME: Sravya                                              */
/*    ORGN: MIT                                             */
/*    FILE: relocate.h                                          */
/*    DATE:                                                 */
/************************************************************/

#ifndef relocate_HEADER
#define relocate_HEADER

#include "MOOS/libMOOS/MOOSLib.h"

class relocate : public CMOOSApp
{
 public:
   relocate();
   ~relocate();

 protected: // Standard MOOSApp functions to overload
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected:
   std::string newreport;
   bool   m_first_reading;
   // navigation points from moos db
   double m_current_x;
   double m_current_y;
   // spped from moos DB
   double m_current_s;
   //heading from moos DB
   double m_current_h;
   // depth from moos DB
   double m_current_d;
   //latitude from moos DB
   double m_current_lat;
   //Longitude from moos DB
   double m_current_long;
   // ivp State
   std::string ivp_state;
   // ivp ALLSTOP
   std::string ivp_allstop;
   // for database time
   double m_current_time;
   // INDEX
   int index;
   // name
   std::string name;
   // wreck
   int wreck;
   // length of the ship
   int length;
 protected:
   void RegisterVariables();


 private: // Configuration variables

 private: // State variables
};

#endif
