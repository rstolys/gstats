#ifndef  fill_data
#define  fill_data

#include <iostream>
#include <fstream> 
#include <vector>

#include "data_elements.hpp"

using namespace std;

/////////////////////////////////////////////////////////////////////////
/// Save data into database file
///
/// @param[in]      fDataFile       File for storing data
/// @param[in/out]  pvData          Vector of Round Data
/// @param[in/out]  pvCourses       Vector of Courses Data
/// @param[in]      piNumRound      counter for number of rounds in database
/// @param[in]      piNumCourses    Counter for number of courses in database
///
//////////////////////////////////////////////////////////////////////////
void store_data( ofstream &fDataFile, vector<oRounds>* pvData, vector<oCourse>* pvCourse, int* piNumRounds, int* piNumCourses );


#endif