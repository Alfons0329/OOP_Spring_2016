//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//

#ifndef __MY_2048_SYSTEM_H_
#define __MY_2048_SYSTEM_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>
#include "base_class.h"
#include "graph_basics.h"

using std::vector;

#define MAX_2048_NX 10
#define MAX_2048_NZ 10

class MY_2048 : public BASE_SYSTEM {
protected:
	void draw_GridCell(int ix, int iz) const;
	void draw_GridCells() const;
	void draw_Board() const;
	void draw_Event() const;

	void reset();
	void generateNumber();
	void moveDown();
	void moveUp();
	void moveLeft();
	void moveRight();
	//
	void generateNumbers_All_2to4();
	void generateNumbers_All_2to8();
	void generateNumbers_All();
	//
	// Implement your own stuff
	//
	bool ismoved = false;
public:
	MY_2048();
	void draw() const;
	void askForInput();
	void handleKeyPressedEvent(unsigned char key);
	void handleSpecialKeyPressedEvent(unsigned char key);
	void setPosition(int x, int z);
	void copy(const BASE_SYSTEM *m);
	void tmp_to_done()
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				mBoard[i][j] = mTmpBoard[i][j];
	}
	void done_to_tmp()
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				mTmpBoard[i][j] = mBoard[i][j];
	}
	void setFocus(bool flg);
protected:
	bool mFlgFocus;
	int mPositionX, mPositionZ;
	int mNX, mNZ;
	//int mNumFreeCells;
	int mBoard[MAX_2048_NZ][MAX_2048_NX];
	int mTmpBoard[MAX_2048_NZ][MAX_2048_NX];
	//
	unsigned char mEvent;
	bool start_status = false;
	bool generated_indicator = false;
	//
	// Implement your own stuff
	//
};

#endif