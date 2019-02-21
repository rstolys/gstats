#ifndef read_data
#define read_data

#include <iostream>
#include <fstream> 
#include <vector>

#include "data_elements.hpp"

using namespace std;


/////////////////////////////////////////////////////////////////////////
/// Read Data file into program Data Structures
///
/// @param[in]      fDataFile       File storing data
/// @param[in/out]  pvData          Vector of Round Data
/// @param[in/out]  pvCourses       Vector of Courses Data
/// @param[in]      piNumRound      counter for number of rounds in database
/// @param[in]      piNumCourses    Counter for number of courses in database
///
//////////////////////////////////////////////////////////////////////////
void vParseGolf( string sFileName, string sFileName_copy, vector<oRounds>* pvData, vector<oCourse>* pvCourses, int* piNumRounds, int* piNumCourses );
/////////////////////////////////////////////////////////////////////////
/// Read Hole data for courses vector
///
/// @param[in]      szElement       char array of data
/// @param[in/out]  pvCourses       Vector of Courses Data
/// @param[in]      iHoleNum        Hole being parsed
/// @param[in]      iNumCourses     Number of courses in database
///
//////////////////////////////////////////////////////////////////////////
void vParseHoles( char *szElement, vector<oCourse>* pvCourses, int iHoleNum, int iNumCourses);

///////////////////////////////////////////////////////////
/// Copy input file to save contents in event of error
///
/// @param[in]  ifDataFile  input Data file
/// @param[in]  sFileName   name of copy file
///
///////////////////////////////////////////////////////////
void copy_file( string sFileName, string sFileName_copy );


#endif /* read_data */