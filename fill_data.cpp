/**************************************************
 * 2019-01
 *      - Purpose is to take data in data stuctures and 
 *        place it into the data file for storage in the proper
 *        format
 **************************************************/

#ifndef fill_data
#define fill_data

#include <iostream>
#include <iomanip> 
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream> 
#include <vector>
#include <ctime> 

#include "data_elements.hpp"


using namespace std;

void store_data( ofstream fDataFile, vector<oRounds>* pvData, vector<oCourse>* pvCourse, int* piNumRounds, int* piNumCourses );


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
void store_data( ofstream &fDataFile, vector<oRounds>* pvData, vector<oCourse>* pvCourse, int* piNumRounds, int* piNumCourses )
{

    time_t      current_date; 
    time(&current_date);

    int         i, j, k;

    int         iNumHoles = 0;
    int         iNumShots = 0; 
    
    
    /* 
     * Add comments to top of file to indicate information 
     */

    //Title
    fDataFile << "#GOLF STATISICS DATA FILE: DO NOT MODIFY\n";

    //Current date
    fDataFile << "#\tCreated on: " << ctime(&current_date);  //End line printed from function ctime

    //Input other formal information 
    fDataFile << "#\tCreated by: Ryan Stolys" << endl;


    //Spacing 
    fDataFile << "#\n#\n#\n";


    /*
     * Add Round data to file 
     */
 
    //Title of section 
    fDataFile << "#\t\t\tROUND DATA\n#" << endl;

    /* For each round in data  */
    for(i = 0; i < *piNumRounds; i++) {

        /* Add Round header and course name  */ 
        fDataFile << ROUND_INFO << COMMA << pvData->at(i).sDate << COMMA;
        
        /* Add date, Number of holes played */
        fDataFile << pvData->at(i).sDate << COMMA << pvData->at(i).iNumHoles << COMMA; 

        //Record number of holes of round
        iNumHoles = pvData->at(i).iNumHoles;

        /* Add tournament round and round number  */ 
        fDataFile << pvData->at(i).bTournament << COMMA << pvData->at(i).iRndNum;

        /* End line */ 
        fDataFile << endl;


        /* For each Hole in round  */
        for(j = 0; j < iNumHoles; j++) {

            /* Add Hole header and number  */ 
            fDataFile << HOLE_INFO << COMMA << pvData->at(i).spHole[j].iNumber << COMMA; 

            /* Add Hole length and par of hole */ 
            fDataFile << pvData->at(i).spHole[j].iLength << COMMA << pvData->at(i).spHole[j].iPar << COMMA;

            /* Save the number of shots on the hole  */ 
            iNumShots = pvData->at(i).spHole[j].vShot.size();


            /* For each shot on hole  */ 
            for(k = 0; k < iNumShots; k++) {

                /* Add shot header and shot number */ 
                fDataFile << SHOT_INFO << COMMA << pvData->at(i).spHole[j].vShot[k].iShotNum << COMMA;

                /* Add type and distance to hole  */ 
                fDataFile << pvData->at(i).spHole[j].vShot[k].sType << COMMA << pvData->at(i).spHole[j].vShot[k].iDistance << COMMA;

                /* Add lie type */ 
                fDataFile << pvData->at(i).spHole[j].vShot[k].sLie << COMMA << pvData->at(i).spHole[j].vShot[k].sMiss << COMMA;

                /* Add fairway and green booleans  */ 
                fDataFile << pvData->at(i).spHole[j].vShot[k].bFairway << COMMA << pvData->at(i).spHole[j].vShot[k].bGreen << COMMA;

                /* Add holed boolean  */ 
                fDataFile << pvData->at(i).spHole[j].vShot[k].bHoled;


                /* End line */ 
                fDataFile << endl;

            }
        }
    }


    
    //Spacing 
    fDataFile << "#\n#\n#\n";


    ///
    /// Add Course data to file 
    ///

    //Title of section 
    fDataFile << "#\t\t\tCOURSE DATA\n#" << endl;


    /* For each round in data  */
    for(i = 0; i < *piNumCourses; i++) {

        /* Add header for course and course name */
        fDataFile << COURSE_INFO << COMMA << pvCourse->at(i).sName << COMMA;

        /* Add Course Length and Par  */ 
        fDataFile << pvCourse->at(i).iLength << COMMA << pvCourse->at(i).iPar << COMMA;

        /* Add Rating and Slope of course  */ 
        fDataFile << fixed << setprecision(1) << pvCourse->at(i).fRating << COMMA << pvCourse->at(i).iSlope << COMMA;

        /* Add hole data  */ 
        for(j = 0; j < 18; j++) {

            /* Add Hole number and length */ 
            fDataFile << pvCourse->at(i).spInfo[j].iNumber << SPACE << pvCourse->at(i).spInfo[j].iLength << SPACE;

            /* Add hole par and add comma */
            fDataFile << pvCourse->at(i).spInfo[j].iPar << COMMA;
        }

        /* End line */ 
        fDataFile << endl;
    }



    //End of file 
    fDataFile << "#\n#END OF FILE";
    return;
}



#endif  /* fill_data  */