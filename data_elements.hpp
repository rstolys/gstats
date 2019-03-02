#ifndef data_elements
#define data_elements

#include <string>
#include <vector>

using namespace std;

// Defintions  

// Data Steam types
#define COURSE_INFO                 "$CSE"
#define ROUND_INFO                  "$RND"
#define HOLE_INFO                   "$HOL"
#define SHOT_INFO                   "$SHT"

// Shot types
#define S_DRIVE                     "DRV"
#define S_APPROACH                  "APP" 
#define S_CHIP                      "CHP" 
#define S_SAND                      "SND" 
#define S_PUTT                      "PUT" 

// Lie types
#define L_TEE                       "TEE"
#define L_FAIRWAY                   "FWY"
#define L_ROUGH                     "RGH"
#define L_SAND                      "SND"
#define L_GREEN                     "GRN"

// Miss directions
#define M_LEFT                      "LFT"
#define M_RIGHT                     "RGH"

// No entry
#define NO_ENTRY                    '-'

//Define characters
#define COMMA                       ","
#define SPACE                       " "

#define LINE_LEN                    1024
#define ELEMENT_LEN                 25

//Main Menu Entry Types
#define ANALYZE                     1
#define ADD_ROUND                   2
#define ADD_COURSE                  3
#define EXIT                        4




class oRounds;
class oHoles; 
class oShots;
class oCourse; 
class oHoleData; 


class oShots 
{
    public: 
        oShots(int iShotNum) {
            this->iShotNum = iShotNum; 
        }

        int             iShotNum;
        string          sType;
        int             iDistance;        
        string          sLie; 
        string          sMiss;           
        bool            bFairway;       
        bool            bGreen;       
        bool            bHoled; 
};

class oHoles 
{
    public:
        oHoles() {}

        vector<oShots> vShot;
        int                 iNumber; 
        int                 iLength; 
        int                 iPar; 
};

class oRounds 
{
    public:
        //No initalizer to all for added element without values
        oRounds() {}

        string          sCourse; 
        string          sDate;
        int             iNumHoles; 
        bool            bTournament;
        int             iRndNum;
        oHoles          spHole[18];

        ~oRounds() {}
};



class oHoleData 
{
    public:
        oHoleData() {};

        int iNumber; 
        int iLength; 
        int iPar; 
};

class oCourse 
{
    public:
        oCourse() {}
  
        string          sName; 
        int             iLength;
        int             iPar; 
        float           fRating;
        int             iSlope; 
        oHoleData       spInfo[18]; 

        ~oCourse() {}
};


typedef enum 
{
    SHOT_NUMBER, SHOT_TYPE, 
    DISTANCE, LIE, MISS_DIR, 
    FWY_HIT, GREEN_HIT, HOLED
} shotElement_t;

typedef enum 
{
    HOLE_NUM, 
    HOLE_LEN, 
    HOLE_PAR
} holeElement_t;

typedef enum 
{
    NAME, DATE, NUM_HOLES,
    TOURNAMENT, ROUND_NUM
} roundElement_t;

typedef enum
{
    COURSE_NAME, COURSE_LENGTH, 
    PAR, RATING, SLOPE, HOLES 
} courseElement_t;

///////////////////////////////////////////////////////////
/// Main Menu Display
///
/// @param[out]  iSelection     Menu Selection of user 
///
///////////////////////////////////////////////////////////
int show_menu();

///////////////////////////////////////////////////////////
/// Clears Screen
///
/// No @param
///
///////////////////////////////////////////////////////////
void clear_screen();

///////////////////////////////////////////////////////////
/// Copy input file to save contents in event of error
///
/// @param[in]  ifDataFile  input Data file
/// @param[in]  sFileName   name of copy file
///
///////////////////////////////////////////////////////////
void copy_file( string sFileName, string sFileName_copy );

#endif