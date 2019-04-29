/************************************************************/
/*    NAME: Sravya K                                              */
/*    ORGN: MIT                                             */
/*    FILE: visual.h                                          */
/*    DATE:                                                 */
/************************************************************/

#ifndef visual_HEADER
#define visual_HEADER

#include "MOOS/libMOOS/MOOSLib.h"

class visual : public CMOOSApp
{
 public:
   visual();
   ~visual();

 protected: // Standard MOOSApp functions to overload
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();
   double distanceCalculate(double x1, double y1, double x2, double y2);

 protected:
   void RegisterVariables();
   // condition variable to first load Qroute
   int initialize;

 private: // Configuration variables

 private: // State variables
};

#endif
