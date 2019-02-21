#ifndef new_course
#define new_course


#include <iostream>
#include <fstream> 
#include <vector>

#include "data_elements.hpp"

using namespace std;


///////////////////////////////////////////////////////////
/// Collect information for new course
///
/// @param[in]  pvCourses       Vector to courses in database
/// @param[in]  piNumCourses    Number of courses currently in database
///
///////////////////////////////////////////////////////////
int add_course( vector<oCourse>* pvCourse, int* piNumCourses);

#endif  /* new_course */