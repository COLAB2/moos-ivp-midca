/************************************************************/
/*    NAME: Sravya K                                              */
/*    ORGN: MIT                                             */
/*    FILE: loc.h                                          */
/*    DATE:                                                 */
/************************************************************/

#ifndef loc_HEADER
#define loc_HEADER

#include "MOOS/libMOOS/MOOSLib.h"
#include "MOOS/libMOOSGeodesy/MOOSGeodesy.h"

class loc : public CMOOSApp
{
 public:
   loc();
   ~loc();

 protected: // Standard MOOSApp functions to overload
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();
   double distanceCalculate(double x1, double y1, double x2, double y2);

 protected:
   CMOOSGeodesy m_geodesy;
   void RegisterVariables();
   // condition variable to first load Qroute
   int initialize;
   double lat_origin;
   double long_origin;

 private: // Configuration variables

 private: // State variables
};

#endif
