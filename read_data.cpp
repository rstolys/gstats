/**************************************************
 * 2019-01 
 *      Inital devlopment of algorthim completed
 *
 **************************************************/

#ifndef read_data
#define read_data

#include <iostream>
#include <iomanip>  
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream> 
#include <vector>
#include <ctime>

#include "data_elements.hpp"
#include "read_data.hpp"


using namespace std;

void vParseHoles( char *szElement, vector<oCourse> *pvCourses, int iHoleNum, int iNumCourses );
void copy_file( string sFileName, string sFileName_copy );


/////////////////////////////////////////////////////////////////////////
/// Read Data file into program Data Structures
///
/// @param[in]      ifDataFile       File for storing data
/// @param[in/out]  pvData          Vector of Round Data
/// @param[in/out]  pvCourses       Vector of Courses Data
/// @param[in]      piNumRound      counter for number of rounds in database
/// @param[in]      piNumCourses    Counter for number of courses in database
///
//////////////////////////////////////////////////////////////////////////
void vParseGolf( string sFileName, string sFileName_copy, vector<oRounds>* pvData, vector<oCourse>* pvCourses, int* piNumRounds, int* piNumCourses ) {

    char        *szElement;
    string      sLine;
    char        *szLine;
    bool        bEnd = false;
    int         iNumLines = 0;
    int         iHoleNum = 0; 
    int         i; 

    ifstream    ifDataFile;
    ofstream    ofStatsLog;

    //Define enumerators and initalize to first element 
    shotElement_t       eShotElement = SHOT_NUMBER;
    holeElement_t       eHoleElement = HOLE_NUM;
    roundElement_t      eRoundElement = NAME;
    courseElement_t     eCourseElement = COURSE_NAME;

    //Open file to log progress 
    ofStatsLog.open("StatsLog.txt", fstream::app );

    //Can write to file as progress is made through parsing 

    //Create Backup File
    copy_file( sFileName, sFileName_copy );
    
    
    //Attempt to open input file
    ifDataFile.open(sFileName);


    if (!(ifDataFile.good())) {

        cerr << "ERROR: Opening input file\n\tCannot read data\n";
        cerr << "\tIt is reccomended to exit the program and retry\n";

        return;
    }
    
    ofStatsLog << "File Open\n";

    //While there is another line 
    while (!bEnd && getline(ifDataFile, sLine)) { 
        
        iNumLines++; 

        if(ifDataFile.eof()) {

            //End of file reached 
            bEnd = true;
            continue;
        }

        //allocate memory for c-string to split to tokens
        szLine = new char[ sLine.length() + 1 ];

        //Copy sLine into szLine
        strcpy( szLine, sLine.c_str() );

        //Copy first element into szElement
        szElement = strtok( szLine, COMMA );

        ofStatsLog << "First Element # " << szElement << "-end" << endl;


        if ( !strcmp(SHOT_INFO, szElement) ) {

            int iShotNum = 0; 

            //Loop for each token in line, the order is known
            while ( NULL != (szElement = strtok( NULL, "," )) ) {
                

                switch ( eShotElement ) {

                    case SHOT_NUMBER:                

                        //Save shot number
                        iShotNum = atoi ( szElement );

                        //Initalize and save shot number
                        pvData->at( *piNumRounds - 1).spHole[ iHoleNum ].vShot.push_back( iShotNum );

                        //Move to next element 
                        eShotElement = SHOT_TYPE;

                        break;

                    case SHOT_TYPE:

                        //Save shot type 
                        pvData->at( *piNumRounds - 1).spHole[ iHoleNum ].vShot[iShotNum].sType = szElement; 

                        //Move to next element 
                        eShotElement = DISTANCE;

                        break;
                        
                    case DISTANCE:

                        //Save Distance of shot 
                        pvData->at( *piNumRounds - 1).spHole[ iHoleNum ].vShot[ iShotNum ].iDistance = atoi( szElement ); 
                        
                        //Move to next element 
                        eShotElement = LIE;

                        break;
                     
                    case LIE:


                        //Save Lie type 
                        pvData->at( *piNumRounds - 1).spHole[ iHoleNum ].vShot[ iShotNum ].sLie = szElement; 

                        //Move to next element 
                        eShotElement = MISS_DIR;

                        break;
                     
                    case MISS_DIR:

                        //Save shot type 
                        pvData->at( *piNumRounds - 1).spHole[ iHoleNum ].vShot[ iShotNum ].sMiss = szElement; 

                        //Move to next element 
                        eShotElement = FWY_HIT;
                        
                        break;
                     
                    case FWY_HIT:

                        //Determine if fairway was hit or if it was possible 
                        if ( 1 == atoi( szElement ) ) {
                            pvData->at( *piNumRounds - 1).spHole[ iHoleNum ].vShot[ iShotNum ].bFairway = true;  
                        }
                        else {
                            pvData->at( *piNumRounds - 1).spHole[ iHoleNum ].vShot[ iShotNum ].bFairway = false; 
                        }

                        //Move to next element 
                        eShotElement = GREEN_HIT;

                        break;
                    
                    case GREEN_HIT:

                        //Determine if fairway was hit or missed 
                        /* Even if it is not possible still save as false  */ 
                        if ( 1 == atoi( szElement ) ) {
                            pvData->at( *piNumRounds - 1).spHole[ iHoleNum ].vShot[ iShotNum ].bGreen = true; 
                        }
                        else {
                            pvData->at( *piNumRounds - 1).spHole[ iHoleNum ].vShot[ iShotNum ].bGreen = false; 
                        }

                        //Move to next element 
                        eShotElement = HOLED;

                        break;

                    case HOLED:

                         //Determine if fairway was hit or if it was possible 
                        if ( 1 == atoi( szElement ) ) {
                            pvData->at( *piNumRounds - 1).spHole[ iHoleNum ].vShot[ iShotNum ].bHoled = true; 
                        }
                        else {
                            pvData->at( *piNumRounds - 1).spHole[ iHoleNum ].vShot[ iShotNum ].bHoled = false; 
                        }

                        //Reset incrementer
                        eShotElement = SHOT_NUMBER;

                        break;
                    break;

                }
            } 
        }
        else if ( !strcmp(HOLE_INFO, szElement) ) {
            
            //Loop for each token in line, the order is known
            while ( NULL != (szElement = strtok( NULL, "," )) ) {
                
                //For each element, save variable
                //Save data into correct location 
                switch ( eHoleElement ) {
                    case HOLE_NUM:
                        
                        //cast integer for hole number, save hole number
                        iHoleNum = atoi( szElement );
                        pvData->at( *piNumRounds - 1).spHole[ iHoleNum ].iNumber = iHoleNum;

                        //Move to next element 
                        eHoleElement = HOLE_LEN;

                        break;

                    case HOLE_LEN:


                        //Save hole length 
                        pvData->at( *piNumRounds - 1).spHole[ iHoleNum ].iLength = atoi( szElement );

                        //Move to next element 
                        eHoleElement = HOLE_PAR;

                        break;

                    case HOLE_PAR:

                        //Save hole par 
                        pvData->at( *piNumRounds - 1).spHole[ iHoleNum ].iPar = atoi( szElement );

                        //Reset incrementer
                        eHoleElement = HOLE_NUM;

                        break;    

                }
            }
        }
        else if ( !strcmp(ROUND_INFO, szElement) ) {

            //Add new round to list of rounds
            pvData->push_back(oRounds());

            //Update number of total rounds 
            (*piNumRounds)++;

            //Loop for each token in line, the order is known
            while ( NULL != (szElement = strtok( NULL, "," )) ) {
                
                //For each element, save variable
                //Save data into correct location 
                switch ( eRoundElement ) {

                    case NAME:

                        //Save name of course 
                        pvData->at( *piNumRounds - 1).sCourse = szElement; 
            
                        //Move to next element 
                        eRoundElement = DATE;

                        break;

                    case DATE:

                        //Save date of round
                        pvData->at( *piNumRounds - 1).sDate = szElement; 

                        //Move to next element
                        eRoundElement = NUM_HOLES;

                        break;

                    case NUM_HOLES:

                        //cast character to interger and save
                        pvData->at( *piNumRounds - 1).iNumHoles = atoi( szElement );
                    
                        //Move to next element
                        eRoundElement = TOURNAMENT;

                        break;

                    case TOURNAMENT:

                        

                        //If round is a tournament round
                        if ( 1 == atoi( szElement ) ) 
                        {
                        
                            pvData->at( *piNumRounds - 1).bTournament = true; 
                        }
                        else
                        {

                            pvData->at( *piNumRounds - 1).bTournament = false; 
                        }

                        //Move to next element
                        eRoundElement = ROUND_NUM;

                        break;

                    case ROUND_NUM: 

                        //Save round number index 
                        pvData->at( *piNumRounds - 1).iRndNum = *piNumRounds; 
                        
                        //Reset Incrementor
                        eRoundElement = NAME;

                        break;

                }
            }
        }
        else if ( !strcmp(COURSE_INFO, szElement) ) {

            //Start at 0 for array index
            int     iHoleNum = 0;

            //Add course to database
            pvCourses->push_back(oCourse());

            //Update the number of courses
            (*piNumCourses)++; 

            ofStatsLog << "Added Course # " << *piNumCourses << endl;
            ofStatsLog << "vector len: " << pvCourses->size() << endl;


            //Loop for each token in line, the order is known
            while ( NULL != (szElement = strtok( NULL, "," )) ) {

                ofStatsLog << "element: " << szElement << endl;
                
                switch ( eCourseElement ) {

                    case COURSE_NAME:

                        //Save name of course
                        pvCourses->at( *piNumCourses - 1 ).sName = szElement;

                        //Move to next element
                        eCourseElement = COURSE_LENGTH;

                        break;

                    case COURSE_LENGTH:

                        //Save Length of course
                        pvCourses->at( *piNumCourses - 1).iLength = atoi( szElement );

                        //Move to next element
                        eCourseElement = PAR;

                        break;

                    case PAR:
                        
                        //Save Par of course
                        pvCourses->at( *piNumCourses - 1).iPar = atoi( szElement );

                        //Move to next element
                        eCourseElement = RATING;

                        break;

                    case RATING:

                        //Save Course Rating
                        pvCourses->at( *piNumCourses - 1).fRating = atof( szElement );

                        //Move to next element
                        eCourseElement = SLOPE;

                        break;

                    case SLOPE:

                        //Save Slope of course
                        pvCourses->at( *piNumCourses - 1).iSlope = atoi( szElement );

                        //Move to next element
                        eCourseElement = HOLES;

                        break;

                    case HOLES: 

                        //Save three hole elements into data structure 
                        vParseHoles( szElement, pvCourses, iHoleNum, *piNumCourses );

                        //if all holes have been parsed
                        if(16 < iHoleNum) {

                            //Reset Incrementor
                            eCourseElement = COURSE_NAME;
                        }
                        else {

                            //Increment to next hole
                            iHoleNum++; 
                        }

                        break;

                }
            }
        }
        else {
            
            //If line is blank
            if ( '\n' == szElement[0] ) {
                // ignore
                continue;
            }
            //If the line is a comment
            else if( '#' == szLine[0] || "" ) {
                //ignore
                continue;
            }
            //Line is invalid
            else {
                cerr << "INVALID MESSAGE ON LINE: " << iNumLines << endl; 
                exit ( -1 );
            }
            
        }

    }

    //close file
    ifDataFile.close();

    return;
}


/////////////////////////////////////////////////////////////////////////
/// Read Hole data for courses vector
///
/// @param[in]      szElement       char array of data
/// @param[in/out]  pvCourses       Vector of Courses Data
/// @param[in]      iHoleNum        Hole being parsed
/// @param[in]      iNumCourses     Number of courses in database
///
//////////////////////////////////////////////////////////////////////////
void vParseHoles( char *szElement, vector<oCourse> *pvCourses, int iHoleNum, int iNumCourses ) {

    holeElement_t   eHoleElement = HOLE_NUM;

    stringstream    szHoleElement;

    //Create String stream for reading 
    szHoleElement << szElement;

    //Save hole number 
    szHoleElement >> pvCourses->at(iNumCourses - 1).spInfo[ iHoleNum ].iNumber;

    //Save hole length 
    szHoleElement >> pvCourses->at( iNumCourses - 1 ).spInfo[ iHoleNum ].iLength;

    //Save hole length 
    szHoleElement >> pvCourses->at( iNumCourses - 1 ).spInfo[ iHoleNum ].iPar;

    return;
}

///////////////////////////////////////////////////////////
/// Copy input file to save contents in event of error
///
/// @param[in]  ifDataFile  input Data file
/// @param[in]  sFileName   name of copy file
///
///////////////////////////////////////////////////////////
void copy_file( string sFileName, string sFileName_copy ) {

    string      line; 

    ifstream    ifDataFile;
    ofstream    ofCopyFile; 

    ifDataFile.open(sFileName);

    if (!(ifDataFile.good())) {

        cerr << "ERROR: Could not create backup file\n";
        cerr << "\tIt is reccomended to exit the program and retry\n";

        return;
    }

    ofCopyFile.open(sFileName_copy);

    while (getline(ifDataFile, line)) {

        ofCopyFile << line << endl;
    }

    ifDataFile.close();
    ofCopyFile.close();

    return;
}

#endif   /* read_data  */