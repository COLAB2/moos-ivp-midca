/************************************************************/
/*    NAME: Sravya Kondrakunta                                              */
/*    ORGN: MIT                                             */
/*    FILE: mine_layer.h                                          */
/*    DATE:                                                 */
/************************************************************/

#ifndef mine_layer_HEADER
#define mine_layer_HEADER

#include "MOOS/libMOOS/MOOSLib.h"
#include <stack>

// --- Point structure
struct Point {
  double x;
  double y;
  int label;
};


class mine_layer : public CMOOSApp
{
 public:
   mine_layer();
   ~mine_layer();

 protected: // Standard MOOSApp functions to overload
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();
   std::stack<Point> Line_pattern(double ga1_init_x,
                                         double slope,
                                         double intercept,
                                         double line_increment,
                                         double overflow_flag,
                                         int total_mines);

  bool Send_info_mines(double x, double y, int label);

 protected:
   double speed;
   std::stack<Point> lay_mines;
   int shift;
   std::string mission;
   void RegisterVariables();

 private: // Configuration variables

 private: // State variables
};

#endif
