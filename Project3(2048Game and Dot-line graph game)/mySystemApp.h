//********************************************
// Student Name			:
// Student ID			:
// Student Email Address:
//********************************************
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//
#ifndef __MY_SYSTEM_APP_APP_H_
#define __MY_SYSTEM_APP_APP_H_
/////////////////////////////////////////////
#include "../headers.h"
#include <string>
#include "../openGLbasic/opengl_stuff.h"
#include "../freeCanvas2D/freeCanvas2D.h"
#include "../textureManager/texture.h"
/////////////////////////////////////////////
#include "mySystem_GraphSystem.h"
#include "mySystem_2048.h"

using namespace ns_opengl;
class MY_SYSTEM_APP : public FREE_CANVAS_2D
{
protected:
	bool mFlgShow_Grid;
	int mMouseButton;
    int mMouseX, mMouseY;
    float mMouseX_2DSpace, mMouseY_2DSpace;
    //
	void drawOrigin( ) const;
    void draw_System_Content( ) const;
    //

	void draw_MonteCarlo_Simulation( ) const;
	void draw_GalaxySystem( ) const;
	void draw_SimplePainter( ) const;
	void draw_SortingVisualization( ) const;
    void draw_SimpleFileEditor( ) const;
    void askForInput( );
    void reset( );
	//
	void showStudentInfo( ) const;
    void showMenu( ) const;
    //
    void updateMonteCarloTitle( );
public:
	MY_SYSTEM_APP( );
	virtual void update( );
	virtual void draw( ) const;
	virtual void initApp( );
	//
    void clickAt(float x, float y );
	bool specialFunc(int key, int x, int y);
	bool handleKeyEvent( unsigned char key );
	bool passiveMouseFunc( int mx, int my );
	bool mouseMotionFunc( int x, int y );
	bool mouseFunc( int button, int state, int x, int y );
	//////////////////////////////////////////////////
    
protected:
    MY_2048 *mPrev_2048;
    BASE_SYSTEM *mCurSystem;
    //
    GRAPH_SYSTEM *mGraphSystem;
    MY_2048 *mMy2048;
};

#endif