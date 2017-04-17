//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//
#include <sstream>
#include "mySystemApp.h"

using namespace std;

void MY_SYSTEM_APP::askForInput( )
{
}

void MY_SYSTEM_APP::reset( )
{
}

void MY_SYSTEM_APP::clickAt(float x, float y )
{
    if ( mCurSystem ) {
        mCurSystem->clickAt( x, y );
    }
}

bool MY_SYSTEM_APP::specialFunc(int key, int x, int y)
{
    //cout << "special key:" << key << endl;

    bool flgHandled = false;

    switch( key ) {
    case GLUT_KEY_F1:
        flgHandled = true;
        mCurSystem = mGraphSystem;
         mCamera->setZoom(53.0);
        mCamera->set( vec3(-22.8, -23.4, 0.0) );
    break;
    case GLUT_KEY_F2:
        flgHandled = true;
        mCurSystem = mMy2048;
        mCamera->setZoom(69.0);
        mCamera->set( vec3(-23.8, -11.4, 0.0) );
    break;
    };

     if ( flgHandled == false && mCurSystem == mMy2048 ) {
         mPrev_2048->copy( mCurSystem );
        mCurSystem->handleSpecialKeyPressedEvent( key );
     return true;
     }


    return true;
}

bool MY_SYSTEM_APP::handleKeyEvent( unsigned char key )
{
    bool flgHandled = false;
    cout << "key:" << (int) key << endl;

    if ( key == 'm' || key == 'M' ) {
        showMenu( );
        return true;
    }
    if ( key == 's' || key == 'S') {
        showStudentInfo();
        return true;
    }

    if ( key == 'i' || key == 'I') {
        mCurSystem->askForInput( );
        return true;
    }

    if ( mCurSystem ) 
	{
		if (mCurSystem==mMy2048)
			mPrev_2048->copy( mCurSystem );
        mCurSystem->handleKeyPressedEvent( key );
        return true;
    }

    return flgHandled;
}

bool MY_SYSTEM_APP::mouseMotionFunc( int mx, int my )
{
    static vector3 color( 1.0, 0.0, 0.0 );


    float x, y, z;
    mCamera->getCoordinates( x, y, z, (float) mx, (float) my );

    mMouseX_2DSpace = x;
    mMouseY_2DSpace = z;

    if ( mMouseButton == GLUT_LEFT_BUTTON ) {
        //cout << "mouseMotionFunc GLUT_LEFT_BUTTON" << endl;


        float rf = (rand()%1000)/1000.0f*0.5f;
        color += vector3(0.1f, 0.07f, 0.11f*rf);
        //clickAt( (int) x, (int) z, color );
        clickAt( x, z );

    } else {
        //if ( mPickedObj == 0 ) {
        return FREE_CANVAS_2D::mouseMotionFunc( mx, my );
        //}
    }

    //cout << "here 5" << endl;

    //float x, y, z;
    //mCamera->getCoordinates( x, y, z, mx, my );
    //cout << "Set Position XZ:" << x << "\t" << z << endl;
    return true;
}

bool MY_SYSTEM_APP::mouseFunc( int button, int state, int mx, int my )
{
    //cout << "button:" << button << endl;
    //if ( mPickedObj == 0 || button == GLUT_MIDDLE_BUTTON ) {
    //if ( button == 3 || button == 4 ) {

    float x, y, z;
    mCamera->getCoordinates( x, y, z, (float) mx, (float) my );

    vector3 color( 1.0, 0.0, 0.0 );
    mMouseButton = button;
    mMouseX = mx;
    mMouseY = mCanvasHeight - my;

    //cout << "mMouseX:" << mMouseX << endl;

    //cout << "mMouseY:" << mMouseY << endl;

    if ( button == GLUT_LEFT_BUTTON ) 
    {
        if ( state == GLUT_DOWN ) {
            clickAt( x, z );
        }   
    } else {
        return FREE_CANVAS_2D::mouseFunc( button, state, mx, my );
    }
    return true;
}


bool MY_SYSTEM_APP::passiveMouseFunc( int mx, int my )
{
    float x, y, z;
    mCamera->getCoordinates( x, y, z, (float) mx, (float) my );

    mMouseX_2DSpace = x;
    mMouseY_2DSpace = z;
    if ( mCurSystem ) {
        mCurSystem->handlePassiveMouseEvent( x, z );
    }
    return true;
}