/************************************************************/
/*    NAME: Sravya Kondrakunta                                              */
/*    ORGN: MIT                                             */
/*    FILE: mine_distributor.h                                          */
/*    DATE:                                                 */
/************************************************************/

#ifndef mine_distributor_HEADER
#define mine_distributor_HEADER

#include "MOOS/libMOOS/MOOSLib.h"

class mine_distributor : public CMOOSApp
{
 public:
   mine_distributor();
   ~mine_distributor();

 protected: // Standard MOOSApp functions to overload
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected:
   int lock;
   int count;
   int total_mines;
   int mine_count;
   clock_t start;
   std::string pattern;
   double delay;
   double delay_ga1;
   double delay_qroute;
   double delay_ga2;
   double radius;
   double circle_increment;
   double increment;
   double ga1_center_x;
   double ga1_center_y;
   double qroute_center_x;
   double qroute_center_y;
   double ga2_center_x;
   double ga2_center_y;
   double ga1_init_x;
   double ga2_init_x;
   double ga1_final_x;
   double ga2_final_x;
   double qroute_area_init_x;
   double qroute_area_final_x;

   bool Line_pattern(double duration);
   bool Circle_pattern(double duration);
   void RegisterVariables();

 private: // Configuration variables

 private: // State variables
};

#endif
