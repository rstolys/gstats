#ifndef new_round
#define new_round

#include <iostream>
#include <iomanip> 
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream> 
#include <vector>
#include <ctime> 

#include "data_elements.hpp"
#include "new_round.hpp"

using namespace std;

int show_round_menu();

int round_menu(); 
int basic_info();
int basic_stats();
int advanced_stats(); 

//I am testing the git push pull function


///////////////////////////////////////////////////////////
/// Collect information for new round
///
/// @param[in/out]  pvData       Vector to courses in database
/// @param[in/out]  piNumRound   Number of courses currently in database
///
///////////////////////////////////////////////////////////
int add_round( vector<oRounds>* pvData, vector<oCourse> *pvCourses,int *piNumRounds, int *piNumCourses )
{
    int         iSelection;
    
    
    string      sNewRound;


    switch ( round_menu() )
    {

        case 1:
            /* Basic Info */
            break;

        case 2:
            /* Basic Stats */
            break; 

        case 3:
            /* Advanced Stats */
            break; 
        
        case 4: 
            break;

    }
        

    //Ask if they want to enter another round 
    cout << "\n\nDo you want to enter another round?";
    cout << "Enter Y or N: "; 
    cin >> sNewRound; 

    if( "Y" == sNewRound ) {

        //Indicate call of function again
        return 1;
    }
    else if ( "N" == sNewRound ) {
 
        //Indicate end of entry
        return 0;
    }
    else {

        //Invalid choice 
        cout << "Invalid Choice... \tAssuming Selection: 'N'" << endl;

        //Indicate end of entry
        return 0;
    }
}

///////////////////////////////////////////////////////////
/// Menu Structure for New Rounds
///
/// @param[out]  iSelection     Menu Selection of user 
///
///////////////////////////////////////////////////////////
int round_menu() {

    int         iSelection;

    bool        bSuccess = false; 


    //Give menu of information to enter 
        // 1. Basic Info
        // 2. Basic Stats
        // 3. Advanced Stats
    
    while (!bSuccess) {

        //Show menu, if selection is invalid 
        if ( -1 == ( iSelection = show_round_menu() ) ) {

            clear_screen();

            /* Invalid Response  */
            cout << "Invalid selection" << endl; 
            continue;
        }
        else if ( 0 > iSelection  || 4 < iSelection ) {

            clear_screen();

            /* Invalid Response  */
            cout << "Invalid selection" << endl; 
            continue;
        }
        else {

            //Selection accepted
            bSuccess = true;
        }
    }

    return iSelection; 
}


///////////////////////////////////////////////////////////
/// New Round Menu Display
///
/// @param[out]  iSelection     Menu Selection of user 
///
///////////////////////////////////////////////////////////
int show_round_menu()
{
    int iSelection; 

    cout << endl << endl; 

    /* Print options  */ 
    cout << "\t1.\tBasic Info" << endl; 
    cout << "\t2.\tBasic Stats" << endl;
    cout << "\t3.\tAdvanced Stats" << endl;
    cout << "\t4.\tExit Program" << endl;

    cout << endl << "\tEnter Selection (1-4): ";
    if( !(cin >> iSelection) ) {

        cin.clear(); 
        cin.ignore();

        return -1;  //Invalid selection
    }
    else {
         return iSelection;
    }
}

///////////////////////////////////////////////////////////
/// Collects Basic Information from user
///
/// @param[out]  iSelection     Menu Selection of user 
///
///////////////////////////////////////////////////////////
int basic_info(){

    
    //Ask for course name 
        //Check if course is in database (linear search)
            //if yes: load data for course 
            //if no: prompt them to add the course (call add_course();)

    // Ask for date played
        //allow for entry of today (simpler)
            //get date to enter


    //Get total number of holes played 
        //Must be integer

    //Allow for selection of tournament round

    return 1;
}

///////////////////////////////////////////////////////////
/// Collects Basic Statistics from user
///
/// @param[out]  iSelection     Menu Selection of user 
///
///////////////////////////////////////////////////////////
int basic_stats();

///////////////////////////////////////////////////////////
/// Collects Advanced Statistics from user
///
/// @param[out]  iSelection     Menu Selection of user 
///
///////////////////////////////////////////////////////////
int advanced_stats(); 


#endif /* new_round */