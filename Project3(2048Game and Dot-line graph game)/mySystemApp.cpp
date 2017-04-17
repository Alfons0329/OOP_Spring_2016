//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//
#include "mySystemApp.h"

using namespace std;

void MY_SYSTEM_APP::showStudentInfo( ) const
{
	cout << "*******************************" << endl;
	cout << "Student ID:0416324\t" << endl;
	cout << "Student Name:An-Fong Hwu\t" << endl;
	cout << "Student Email:alfons.cs04@g2.nctu.edu.tw\t" << endl;
	cout << "*******************************" << endl;
}

void MY_SYSTEM_APP::showMenu( ) const
{
    cout << "Welcome to our mini-world!" << endl;
    cout << "Menu----------------------" << endl;
    cout << "Key usage:" << endl;
    cout << "F1: Graph System" << endl;
    cout << "F2: 2048" << endl;
    cout << endl;
    cout << "r: reset" << endl;

    cout << "--------------------------" << endl;

}

MY_SYSTEM_APP::MY_SYSTEM_APP( )
{
    mCurSystem = 0;
}

void MY_SYSTEM_APP::initApp( )
{
	mFlgShow_Grid = false;
    showMenu( );
    //
    mGraphSystem = new GRAPH_SYSTEM;
    mMy2048 = new MY_2048;
    //
    mCurSystem = mMy2048;

    ////////////////////////////////////////////
    ((MY_2048*)mMy2048)->setPosition( 30.0, 0);

    mPrev_2048 = new MY_2048;
    mPrev_2048->setPosition( 0.0, 0);
    mPrev_2048->setFocus( false );
    //
    specialFunc(GLUT_KEY_F1, 0, 0);
}

void MY_SYSTEM_APP::update( )
{
    mCurSystem->update( );
}




