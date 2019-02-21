#ifndef new_round
#define new_round


#include <iostream>
#include <fstream> 
#include <vector>

#include "data_elements.hpp"

using namespace std;


///////////////////////////////////////////////////////////
/// Collect information for new round
///
/// @param[in/out]  pvData       Vector to courses in database
/// @param[in/out]  piNumRound   Number of courses currently in database
///
///////////////////////////////////////////////////////////
int add_round( vector<oRounds>* pvData, vector<oCourse> *pvCourses,int *piNumRounds, int *piNumCourses );

///////////////////////////////////////////////////////////
/// New Round Menu Display
///
/// @param[out]  iSelection     Menu Selection of user 
///
///////////////////////////////////////////////////////////
int show_round_menu();

#endif  /* new_round */