#include <iostream> 
#include <fstream> 
//#include <filesystem>

#include "data_elements.hpp"

#include "read_data.hpp"
#include "fill_data.hpp"
#include "new_course.hpp"
#include "new_round.hpp"

using namespace std;

int show_menu();
void clear_screen();

void copy_file( ifstream & ifDataFile, string sFileName );

///////////////////////////////////////////////////////////
///
/// Main Menu structure of the program, 
/// All actions of program are centered around this file
///
/// @param[in]  argc    number of inputs to program
/// @param[in]  argv    array of char arrays to inputs to program
///
///////////////////////////////////////////////////////////
int main(int argc, char** argv) {

    int                 iSelection;

    int                 iReturn;

    bool                bExitFlag = false;

    vector<oRounds>     vRounds; 
    int                 iNumRounds = 0;

    string              line;

    vector<oCourse>     vCourses;
    int                 iNumCourses = 0;

    ofstream            ofDataFile;

    ofstream            ofStatsLog;
    
    //Create file for logging
    ofStatsLog.open("StatsLog.txt");    ofStatsLog.close();

    string              sFileName = "DO_NOT_OPEN.dat";
    string              sFileName_copy = "DO_NOT_OPEN_backup.dat";

    


    //get data from file
    vParseGolf( sFileName, sFileName_copy, &vRounds, &vCourses, &iNumRounds, &iNumCourses );

    //Copy file for safe keeping 
    //fs::copy(sFileName, sFileName_copy);


    //Attempt to open output file 
    ofDataFile.open(sFileName);

    if (!ofDataFile.good()) {

        cerr << "ERROR: Opening output file\n\tCannot save data\n";
        cerr << "\tIt is reccomended to exit the program and retry\n";
    }



    // Loop until program ends
    while(1) {

        /* Show menu */
        iSelection = show_menu(); 

        if( -1 == iSelection ) {

            clear_screen();

            cout << endl << "Please enter Numbers only" << endl;
            continue;
        }
        else if ( 4 < iSelection || 0 > iSelection ) {

            clear_screen();

            /* Invalid Response  */
            cout << "Invalid selection" << endl; 
            continue;
        }

        //Depending on selection
        switch(iSelection) {

            case ANALYZE:
                /* Analyze Stats */

                break;
            case ADD_ROUND:
                /* Add Round */
               

                break;
            case ADD_COURSE:

                iReturn = add_course( &vCourses, &iNumCourses );

                //while new course entry is requested
                while (1 == iReturn) {

                    iReturn = add_course( &vCourses, &iNumCourses );
                }

                break;

            case EXIT:
                /* Exit Program */

                cout << iNumRounds << endl;

                store_data( ofDataFile, &vRounds, &vCourses, &iNumRounds, &iNumCourses);

                //copy_file(sFileName, sFileName_copy);

                //Release allocated memory
                bExitFlag = true;
                break;
        }

        if(!bExitFlag) {

            //Go to start of menu
            clear_screen();

            continue;

        }
        else {

            //store data in file
            //Exit program
            break;
        }
    }


    return 0;
}

///////////////////////////////////////////////////////////
/// Main Menu Display
///
/// @param[out]  iSelection     Menu Selection of user 
///
///////////////////////////////////////////////////////////
int show_menu()
{
    int iSelection; 

    cout << endl << endl; 

    /* Print options  */ 
    cout << "\t1.\tAnalyze" << endl; 
    cout << "\t2.\tAdd Round" << endl;
    cout << "\t3.\tAdd Course" << endl;
    cout << "\t4.\tExit Program" << endl;

    cout << endl << "\tEnter Selection (1-4): ";
    if( !(cin >> iSelection) ) {

        return -1;  //Invalid selection
    }
    else {
         return iSelection;
    }
}


///////////////////////////////////////////////////////////
/// Clears Screen
///
/// No @param
///
///////////////////////////////////////////////////////////
void clear_screen()
{
    /* Clear the screen */
    for(int i = 0; i < 10; i++) {
        cout << endl;
    }

    /* Reset cin */
    cin.clear(); 
    cin.ignore();

    return; 
}
