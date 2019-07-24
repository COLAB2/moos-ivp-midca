/************************************************************/
/*    NAME:                                               */
/*    ORGN: MIT                                             */
/*    FILE: pause_vessels.h                                          */
/*    DATE:                                                 */
/************************************************************/

#ifndef pause_vessels_HEADER
#define pause_vessels_HEADER

#include "MOOS/libMOOS/MOOSLib.h"

class pause_vessels : public CMOOSApp
{
 public:
   pause_vessels();
   ~pause_vessels();

 protected: // Standard MOOSApp functions to overload
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected:
   clock_t  start;
   double pause_time;
   std::string  group_name;
   bool paused;
   void RegisterVariables();

 private: // Configuration variables

 private: // State variables
};

#endif
