#ifndef new_course
#define new_course

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

bool get_name( string *sCourse, int *iRemove );
bool get_rating (float *fRating, int *iRemove );
bool get_slope ( int *iSlope, int *iReturn );
int  get_holes(int *piPar, int *piLength);
void display_course( vector<oCourse> vCourse, int iNumCourses );
bool edit_holes(int *piPar, int *piLength, int *piHole);

///////////////////////////////////////////////////////////
/// Collect information for new course
///
/// @param[in]  pvCourses       Vector to courses in database
/// @param[in]  piNumCourses    Number of courses currently in database
///
///////////////////////////////////////////////////////////
int add_course( vector<oCourse>* pvCourse, int* piNumCourses)
{

    int         iRemove = 0; 

    bool        bCourseName = false;
    string     sCourse;

    bool        bRating = false;
    float       fRating = 0.0; 
   
    bool        bSlope = false;
    int         iSlope = 0;

    //Course Data
    int         iPar = 0; 
    int         iLength = 0; 
    int         piPar[18];
    int         piLength[18];

    int         iLengthTotal = 0;
    int         iParTotal = 0;

    bool        bEdits = false;
    string      sEdits; 
    int         iEditSelect; 

    int         iHoleEdit;
    int         iParEdit;
    int         iLengthEdit;
    bool        bMoreHoleEdits = true;

    string      sNewCourse;


    //Prompt user that this is add course section

     cout << "You selected to enter a new course\n"; 

     cout << "NOTE:\n\tCoures must be 18 holes in length\n\tTo exit at any point: Enter '-1'\n\n";

    //Add new course to vector 
    pvCourse->push_back(oCourse());

    //Increment counter
    (*piNumCourses)++;

    //Get name of course to enter
    while (!bCourseName) {

        //Get name of course
        bCourseName = get_name( &sCourse, &iRemove );

        if( 1 == iRemove ) {

            ///Remove course from vector
            pvCourse->erase(pvCourse->begin() + (*piNumCourses - 1) );

            return 0;
        }
    }

    //Save new course name
    pvCourse->at( *piNumCourses - 1).sName = sCourse;


    //Get the Rating of course 
    while (!bRating) {

        bRating = get_rating( &fRating, &iRemove );

        if( 1 == iRemove ) {

            ///Remove course from vector
            pvCourse->erase(pvCourse->begin() + (*piNumCourses - 1) );

            return 0;
        }
    }

    //Save Rating 
    pvCourse->at( *piNumCourses - 1).fRating = fRating;
    
    //Get the Slope of course 
    while (!bSlope) {

        //Get slope
        bSlope = get_slope( &iSlope, &iRemove );

        if( iRemove ) {

            ///Remove course from vector
            pvCourse->erase(pvCourse->begin() + (*piNumCourses - 1) );

            return 0;
        }
    }


    //Log Rating and slope in data structure 
    pvCourse->at( *piNumCourses - 1).fRating = fRating;
    pvCourse->at( *piNumCourses - 1).iSlope = iSlope;


    //Get Hole length and par of course

    //if exit command was selected 
    if ( -1 == get_holes(piPar, piLength) ) {

        //Remove course from vector
        pvCourse->erase(pvCourse->begin() + (*piNumCourses - 1) );

        return 0;
    }
    //else successful hole collection


   

    //Log Course Data and  
    for (int i = 0; i < 18; i++) {

        //Save Par and Length into data structure
        pvCourse->at( *piNumCourses - 1).spInfo[i].iPar = piPar[i];
        pvCourse->at( *piNumCourses - 1).spInfo[i].iLength = piLength[i];
        pvCourse->at( *piNumCourses - 1).spInfo[i].iNumber = i + 1;

        //Calculate the total length and par
        iParTotal += piPar[i];
        iLengthTotal += piLength[i];
    }


    //Save total length and par in data structure 
    pvCourse->at( *piNumCourses - 1).iPar = iParTotal;
    pvCourse->at( *piNumCourses - 1).iLength = iLengthTotal;


    //Display Course Information 
    display_course( *pvCourse, *piNumCourses );


    //Allow for edit of information

    //Ask if edits are required 
    cout << "\nDo you need to change any of the information? (Y or N): "; 
    cin >> sEdits;

    //Ensure selection is valid
    if( "Y" == sEdits || "y" == sEdits ) {

        //Indicate call of function again
        bEdits = true;
    }
    else if ( "N" == sEdits || "n" == sEdits ) {
 
        //No edits needed
        bEdits = false;
    }
    else {

        //Invalid choice 
        cout << "Invalid Choice... \tAssuming Selection: 'N'" << endl;

        //No edits needed
        bEdits = false;
    }

    // Loop until all errors are fixed
    while (bEdits) {

        //Print menu 
        cout << "\nWhat changes do you want to make? \n\tMake selection: \n"; 
        cout << "\t1. Course Name\n"; 
        cout << "\t2. Rating\n"; 
        cout << "\t3. Slope\n"; 
        cout << "\t4. Hole Info\n";
        cout << "\t5. No Edits Needed\n";
        cout << "\tSelection: ";
        //If entry is invalid  
        if ( !(cin >> iEditSelect) ) {

            //Clear screen 
            clear_screen();

            //Invalid entry for rating
            cout << "Please enter numbers only \n\n TRY AGAIN\n\n";

            //Reset entry
            continue;
        }  
        else if ( 5 < iEditSelect || 0 > iEditSelect ) {

            //Clear screen 
            clear_screen();

            //Invalid entry for rating
            cout << "Please select one of the options \n\n TRY AGAIN\n\n";

        }


        //else enter switch statement 
        switch (iEditSelect) {

            case 1: 

                /* Edit Course Name */
                bCourseName = false; 

                while (!bCourseName) {

                    //Get name of course
                    bCourseName = get_name( &sCourse, &iRemove );

                    if( 1 == iRemove ) {

                        ///Remove course from vector
                        pvCourse->erase(pvCourse->begin() + (*piNumCourses - 1) );

                        return 0;
                    }
                }

                //Update Course Name
                pvCourse->at( *piNumCourses - 1).sName = sCourse;

                break;

            case 2:

                /* Edit Rating */
                bRating = false; 

                while (!bRating) {

                    //Get Rating
                    bRating = get_rating (&fRating, &iRemove );

                    if( 1 == iRemove ) {

                        ///Remove course from vector
                        pvCourse->erase(pvCourse->begin() + (*piNumCourses - 1) );

                        return 0;
                    }
                }

                //Update Rating
                pvCourse->at( *piNumCourses - 1).fRating = fRating;
                

                break;

            case 3:

                /* Edit Slope */
                bSlope = false; 

                while (!bSlope) {

                    //Get slope
                    bSlope = get_slope ( &iSlope, &iRemove );

                    if( iRemove ) {

                        ///Remove course from vector
                        pvCourse->erase(pvCourse->begin() + (*piNumCourses - 1) );

                        return 0;
                    }
                }

                //Update Slope
                pvCourse->at( *piNumCourses - 1).iSlope = iSlope;
            
                break;

            case 4:

                /* Edit Hole Info */

                while(bMoreHoleEdits) {

                    bMoreHoleEdits = edit_holes( &iParEdit, &iLengthEdit, &iHoleEdit);

                    //save info 
                    pvCourse->at( *piNumCourses - 1).spInfo[iHoleEdit].iPar = iParEdit;
                    pvCourse->at( *piNumCourses - 1).spInfo[iHoleEdit].iLength = iLengthEdit;
                }

                break;

            case 5: 

                //No more edits needed
                bEdits = false;
                break;
        }
    }




    //Ask if they want to enter another course 
    cout << "\n\nDo you want to enter another course?\n";
    cout << "\tEnter Y or N: "; 
    cin >> sNewCourse; 

    if( "Y" == sNewCourse || "y" == sNewCourse ) {

        //Indicate call of function again
        return 1;
    }
    else if ( "N" == sNewCourse || "n" == sNewCourse ) {
 
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


bool get_name( string *sCourse, int *iRemove ) {

    //Ask for 3 letter course name 
        cout << "Enter the 3 letter acronym to represent the course: ";
        cin >> *sCourse;

        //If the acronym is too long or too short
        if ( 3 != (*sCourse).length()) {

            clear_screen();

            //prompt user to try again
            cout << "Course Acronym was not 3 letters \nPlease Try Again"; 

            return false;
        }
        else {

            //Check for exit command 
            if( "-1" == *sCourse )
            {

                //Remove course from vector
                *iRemove = 1; 

                return false;
            }
            
            //Proceed for next step in process
            return true;
        }
}


bool get_rating (float *fRating, int *iRemove ) {

    //Ask for Rating
    cout << "Enter the Rating of the course: ";
    if( !(cin >> *fRating)) {

        //Clear screen 
        clear_screen();

        //Invalid entry for rating
        cout << "Please enter numbers only \n\n TRY AGAIN\n\n";

        //Reset entry
        return false;
    }
    else {

        //Check for exit command 
        if( -1.0 == *fRating )
        {

            ///Remove course from vector
            *iRemove = 1;

            return 0;
        }

        //Proceed to next step
        return true;
    }

}


bool get_slope ( int *iSlope, int *iRemove ) {

    //Ask for Slope
    cout << "Enter the Slope of the course: ";
    if( !(cin >> *iSlope)) {

        //Clear screen 
        clear_screen();

        //Invalid entry for rating
        cout << "Please enter integers only \n\n TRY AGAIN\n\n";

        //Reset entry
        return false;
    }
    else {

        //Check for exit command 
        if( -1 == *iSlope )
        {

            //Remove course from vector
            *iRemove = 1;

            return false;
        }

        //Proceed to next step
        return true;
    }
}


int get_holes(int *piPar, int *piLength) {
    int     iPar; 
    int     iLength;

    //Give user instructions on filling in data 
    cout << "Enter the Par and Length of each hole in the following form:\n";
    cout << "\tMistakes can be fixed at the end...\n\n";
    cout << "\tHole #: <Par> <Length(yds)>\n\n";

    for (int i = 0 ; i < 18; ) {

        cout << "\tHole " << i + 1 << ": ";
        if(!(cin >> iPar) || (iPar < 3 && iPar >= 0)) {

            //Invalid Par entry
            cout << "Invalid Par Entry for Hole #" << i + 1 << "\tTRY HOLE AGAIN\n\n";
            
            //Try hole again
            continue;
        } 

        //Check for exit command 
        if( 0 > iPar ) {

            return -1;
        }

        if(!(cin >> iLength) || iLength == 0) {

            //Invalid Length entry
            cout << "Invalid Length Entry for Hole #" << i + 1 << "\tTRY HOLE AGAIN\n\n";

            //Try Hole Again
            continue;
        }

        //Check for exit command 
        if( 0 > iLength ) {

            return -1;
        }

        //Hole data was valid save in array 
        piPar[i] = iPar; 
        piLength[i] = iLength; 

        //Increment to next hole 
        i++;  
    }

    //Return no errors
    return 0;
}


void display_course( vector<oCourse> vCourse, int iNumCourses ) {

    //Display Final Course Data
    cout << "\n\n\tCourse Name: " << vCourse[iNumCourses - 1].sName << endl;
    cout << "\tLength: " << vCourse[iNumCourses - 1].iLength << endl;
    cout << "\tPar: " << vCourse[iNumCourses - 1].iPar << endl;
    cout << "\tRating: " << vCourse[iNumCourses - 1].fRating << endl;
    cout << "\tSlope: " << vCourse[iNumCourses - 1].iSlope << endl;

    //Hole Data 
    cout << "Hole Data:\n";

    //For each hole
    for (int i = 0; i < 9; i++)
    {

        //Display Front 9 Hole
        cout << i + 1 << ".  " << vCourse[iNumCourses - 1].spInfo[i].iPar << " ";
        cout << vCourse[iNumCourses - 1].spInfo[i].iLength;

        cout << "\t\t";

        //Display Back 9 Hole
        cout << i + 10 << ". " << vCourse[iNumCourses - 1].spInfo[i + 9].iPar << " ";
        cout << vCourse[iNumCourses - 1].spInfo[i + 9].iLength;

        //End line 
        cout << endl;
    }

}


bool edit_holes(int *piPar, int *piLength, int *piHole) {

    int     edit_hole;  
    int     iPar;
    int     iLength;

    string  sMoreEdits;


    cout << "Select Hole to edit: ";
    if( !(cin >> edit_hole) || 0 > edit_hole || 18 < edit_hole ) {

        //Invalid Par entry
        cout << "Invalid Entry for Hole #\tTRY AGAIN\n\n";
        
        //Try hole again
        return true;
    }

    cout << "\tHole #: <Par> <Length(yds)>\n";

    cout << "\tHole " << edit_hole << ": ";
    if(!(cin >> iPar) || iPar < 3) {

        //Invalid Par entry
        cout << "Invalid Par Entry for Hole #" << edit_hole << "\tTRY HOLE AGAIN\n\n";
        
        //Try hole again
        return true;
    } 


    if(!(cin >> iLength) || iLength < 0) {

        //Invalid Length entry
        cout << "Invalid Length Entry for Hole #" << edit_hole << "\tTRY HOLE AGAIN\n\n";

        //Try Hole Again
        return true;
    }

    //Save given edits
    *piHole = edit_hole;
    *piPar = iPar; 
    *piLength = iLength;

    cout << "Continue to edit holes? (Y or N): ";
    cin >> sMoreEdits; 

    if( "Y" == sMoreEdits || "y" == sMoreEdits ) {

        //Indicate call of function again
        return true;
    }
    else if ( "N" == sMoreEdits || "n" == sMoreEdits ) {
 
        //Indicate end of entry
        return false;
    }
    else {

        //Invalid choice 
        cout << "Invalid Choice... \tAssuming Selection: 'N'" << endl;

        //Indicate end of entry
        return false;
    } 


}


#endif /* new_course */