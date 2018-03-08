/************************************************************/
/*    NAME: Sravya                                              */
/*    ORGN: Wright State                                       */
/*    FILE: midca.h                                          */
/*    DATE:                                                 */
/************************************************************/

#ifndef midca_HEADER
#define midca_HEADER

#include "MOOS/libMOOS/MOOSLib.h"
#include <string>

using namespace std;

class midca : public CMOOSApp
{
 public:
   midca();
   ~midca();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected:
   bool   m_first_reading;
   // navigation points from moos db
   double m_current_x; 
   double m_current_y;
   // variables to distinguish new points
   double m_previous_x;
   double m_previous_y;
   // spped from moos DB
   double m_current_s;
   // condition variable to first load Qroute
   int initialize;
   // This variable is a condition variable sent to MoosDB for behavior 
   string mission;
   // points read from MIDCA
   string points;


 protected:
   void RegisterVariables();

 private: // Configuration variables

 private: // State variables
};

#endif 
