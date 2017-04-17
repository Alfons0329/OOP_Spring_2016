#include "mySystem_2048.h"
#include <iostream>

using namespace std;

MY_2048::MY_2048()
{
	mNX = 4;
	mNZ = 4;
	reset();

	mPositionX = 0;
	mPositionZ = 0;
	mFlgFocus = true;
}

void MY_2048::setFocus(bool flg)
{
	mFlgFocus = flg;
}

void MY_2048::setPosition(int x, int z)
{
	mPositionX = x;
	mPositionZ = z;
}

//
// copy the board of m to this object
//
void MY_2048::copy(const BASE_SYSTEM *m)
{
	//
	// Implement your own stuff
	//

	const MY_2048 *p = dynamic_cast<const MY_2048 *>(m); //pointer conversion
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			this->mBoard[i][j] = p->mBoard[i][j];
		}
	}
}


void MY_2048::reset()
{
	for (int j = 0; j < mNZ; ++j) {
		for (int i = 0; i < mNX; ++i) {
			mBoard[j][i] = 0;
		}
	}

	//mNumFreeCells = mNX * mNZ;
	mEvent = 0;
}

void MY_2048::askForInput()
{
	//
	// Implement your own stuff
	//
	cout << "MY_2048" << endl;
	cout << "Key usage:" << endl;
	cout << "1: generate randomly the numbers 2 and 4 for all the cells" << endl;
	cout << "2: generate randomly the numbers 2, 4 and 8 for all the cells" << endl;
	cout << "3: generate randomly the numbers for all the cells" << endl;
	cout << "r: clear all the cells" << endl;
	cout << " " << endl;
	cout << "UP, DOWN, LEFT, RIGHT: move the numbers to the respective side" << endl;

}

//
// Generate a new number (2 or 4) randomly.
//
void MY_2048::generateNumber()
{
	//
	// Implement your own stuff
	//
	srand(time(NULL));
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (mBoard[i][j] == 0)
			{
				int type = rand() % 2;
				//cout << "Type is now" << type << endl;
				cout << "!!!!!!!!!!Generate new numbers!!!!!!!\n";
				if (type)
				{
					mBoard[i][j] = 2;
					generated_indicator = true;
				}
				else
				{
					mBoard[i][j] = 4;
					generated_indicator = true;
				}
				if (generated_indicator)
					break;
			}
		}
		if (generated_indicator)
		{
			generated_indicator = false;
			break;
		}
		
	}
	cout << "\n\n Board elements ::\n";
	for (int i = 3; i >= 0; i--)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << " " << mBoard[i][j];
			if (j == 3)
				cout << endl;
		}
	}

}

void MY_2048::moveDown()
{
	//
	// Implement your own stuff
	//
	/*for (int j = 0; j < 4; j++)
	for (int i = 0; i < 4; i++)
	{
	if (!mBoard[i][j])
	{
	for (int k = i + 1; k < 4; k++)
	{
	if (mBoard[k][j])
	{
	mBoard[i][j] = mBoard[k][j];
	mBoard[k][j] = 0;
	ismoved = true;
	break;
	}
	}
	}
	}*/
	//merge
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			if (mBoard[i][j]/* && mBoard[i][j] == mBoard[i + 1][j]*/)
			{

				for (int k = i + 1; k < 4; k++)
				{
					if (mBoard[i][j] == mBoard[k][j])
					{
						printf("%d is merged with %d \n", mBoard[i][j], mBoard[k][j]);
						mBoard[i][j] *= 2;
						mBoard[k][j] = 0;

						break;
					}
					else if (mBoard[k][j] != 0)
					{
						break;
					}
				}
			}
		}
	}
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (!mBoard[i][j])
			{
				for (int k = i + 1; k < 4; k++)
				{
					if (mBoard[k][j]!=0)
					{
						printf("At location row= %d col=%d will make %d move to new location row=%d col=%d\n", k, j, mBoard[k][j], i, j);
						mBoard[i][j] = mBoard[k][j];

						mBoard[k][j] = 0;
						ismoved = true;
						break;
					}
				}
			}
		}
	}
	if (ismoved)
	{
		generateNumber();
		ismoved = false;
	}
}

void MY_2048::moveUp()
{
	//
	// Implement your own stuff
	//
	/*for (int j = 0; j < 4; j++)
	for (int i = 3; i >= 0; i--)
	{
	if (!mBoard[i][j])
	{
	for (int k = i - 1; k >= 0; k--)
	{
	if (mBoard[k][j])
	{
	mBoard[i][j] = mBoard[k][j];
	mBoard[k][j] = 0;
	ismoved = true;
	break;

	}
	}
	}
	}*/
	for (int j = 0; j < 4; j++)
	{
		for (int i = 3; i >= 1; i--)
		{
			if (mBoard[i][j]/* && mBoard[i][j] == mBoard[i - 1][j]*/)
			{
				for (int k = i - 1; k >= 0; k--)
				{
					if (mBoard[i][j] == mBoard[k][j])
					{
						printf("%d is merged with %d \n", mBoard[i][j], mBoard[k][j]);
						mBoard[i][j] *= 2;
						mBoard[k][j] = 0;
						break;
					}
					else if (mBoard[k][j] != 0)
					{
						break;
					}
				}
			}
		}
	}
	for (int j = 0; j < 4; j++)
	{
		for (int i = 3; i >= 0; i--)
		{
			if (!mBoard[i][j])
			{
				for (int k = i - 1; k >= 0; k--)
				{
					if (mBoard[k][j]!=0)
					{
						printf("At location row= %d col=%d will make %d move to new location row=%d col=%d\n", k, j, mBoard[k][j], i, j);
						mBoard[i][j] = mBoard[k][j];

						mBoard[k][j] = 0;
						ismoved = true;
						break;

					}
				}
			}
		}
	}
	if (ismoved)
	{
		generateNumber();
		ismoved = false;
	}
}

void MY_2048::moveLeft()
{
	//
	// Implement your own stuff
	//
	/*for (int i = 0; i < 4; i++)
	for (int j = 0; j < 4; j++)
	{
	if (!mBoard[i][j])
	{
	for (int k = j + 1; k < 4; k++)
	{
	if (mBoard[i][k])
	{
	mBoard[i][j] = mBoard[i][k];
	mBoard[i][k] = 0;
	ismoved = true;
	break;
	}
	}
	}
	}*/
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (mBoard[i][j]/*&&mBoard[i][j] == mBoard[i][j + 1]*/)
			{
				for (int k = j + 1; k < 4; k++)
				{
					if (mBoard[i][j] == mBoard[i][k])
					{
						printf("%d is merged with %d \n", mBoard[i][j], mBoard[i][k]);
						mBoard[i][j] *= 2;
						mBoard[i][k] = 0;
						break;
					}
					else if (mBoard[i][k] != 0)
					{
						break;
					}
				}
			}
		}
	}
	//add2
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (!mBoard[i][j])
			{
				for (int k = j + 1; k < 4; k++)
				{
					if (mBoard[i][k]!=0)
					{
						printf("At location row= %d col=%d will make %d move to new location row=%d col=%d\n", i, k, mBoard[k][j], i, j);
						mBoard[i][j] = mBoard[i][k];

						mBoard[i][k] = 0;
						ismoved = true;
						break;
					}
				}
			}
		}
	}
	if (ismoved)
	{
		generateNumber();
		ismoved = false;
	}

}

void MY_2048::moveRight()
{
	//
	// Implement your own stuff
	//
	/*for (int i = 0; i < 4; i++)
	for (int j = 3; j >= 0; j--)
	{
	if (!mBoard[i][j])
	{
	for (int k = j - 1; k >= 0;k--)
	if (mBoard[i][k])
	{
	mBoard[i][j] = mBoard[i][k];
	mBoard[i][k] = 0;
	ismoved = true;
	break;
	}
	}
	}*/
	for (int i = 0; i < 4; i++)
	{
		for (int j = 3; j >= 1; j--)
		{
			if (mBoard[i][j] /*&& mBoard[i][j] == mBoard[i][j - 1]*/)
			{
				for (int k = j - 1; k >= 0; k--)
				{
					if (mBoard[i][k] == mBoard[i][j])
					{
						printf("%d is merged with %d \n", mBoard[i][j], mBoard[i][k]);
						mBoard[i][j] *= 2;
						mBoard[i][k] = 0;
						break;
					}
					else if (mBoard[i][k] != 0)
					{
						break;
					}
				}
			}
		}
	}
	//add2
	for (int i = 0; i < 4; i++)
	{
		for (int j = 3; j >= 0; j--)
		{
			if (!mBoard[i][j])
			{
				for (int k = j - 1; k >= 0; k--)
				{
					if (mBoard[i][k]!=0)
					{
						printf("At location row= %d col=%d will make %d move to new location row=%d col=%d\n", i, k, mBoard[k][j], i, j);
						mBoard[i][j] = mBoard[i][k];
						mBoard[i][k] = 0;
						ismoved = true;
						break;
					}
				}
			}
		}
	}

	if (ismoved)
	{
		generateNumber();
		ismoved = false;
	}
}

void MY_2048::generateNumbers_All_2to4()
{
	reset();
	//
	// Implement your own stuff
	//
	srand(time(NULL));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int type = rand() % 2 + 1;

			if (type == 1)
				mBoard[i][j] = 2;
			if (type == 2)
				mBoard[i][j] = 4;

		}
	}
}

void MY_2048::generateNumbers_All_2to8()
{
	reset();
	srand(time(NULL));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int type = rand() % 3;
			if (type == 0)
				mBoard[i][j] = 2;
			else if (type == 1)
				mBoard[i][j] = 4;
			else
				mBoard[i][j] = 8;
		}

	}
	//
	// Implement your own stuff
	//
}

void MY_2048::generateNumbers_All()
{
	reset();
	srand(time(NULL));
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			int type = rand() % 11;
			switch (type)
			{
			case 0:
				mBoard[i][j] = 2;
				break;
			case 1:
				mBoard[i][j] = 4;
				break;
			case 2:
				mBoard[i][j] = 8;
				break;
			case 3:
				mBoard[i][j] = 16;
				break;
			case 4:
				mBoard[i][j] = 32;
				break;
			case 5:
				mBoard[i][j] = 64;
				break;
			case 6:
				mBoard[i][j] = 128;
				break;
			case 7:
				mBoard[i][j] = 256;
				break;
			case 8:
				mBoard[i][j] = 512;
				break;
			case 9:
				mBoard[i][j] = 1024;
				break;
			case 10:
				mBoard[i][j] = 2048;
				break;
			}
			printf("at i=%d j=%d value is %d \n", i, j, mBoard[i][j]);

		}
	//
	// Implement your own stuff
	//

}

void MY_2048::handleKeyPressedEvent(unsigned char key)
{
	switch (key) {
	case 'r':
	case 'R':
		reset();
		break;
	case '1':
		generateNumbers_All_2to4();
		break;
	case '2':
		generateNumbers_All_2to8();
		break;
	case '3':
		generateNumbers_All();
		break;
	}
}

void MY_2048::handleSpecialKeyPressedEvent(unsigned char key)
{
	//cout << "MY_2048::handleSpecialKeyPressedEvent:" << key << endl;
	//BASE_SYSTEM *m;
	bool flgDone = false;

	if (!start_status)
	{
		reset();
		int type = rand() % 2;
		if (type)
			mBoard[3][0] = 2;
		else
		{
			mBoard[3][0] = 4;
		}
		start_status = true;
	}

	switch (key) {
	case GLUT_KEY_UP:
		/*if (!flgDone)
		mBoard[0][0] = 2;*/
		flgDone = true;
		//tmp_to_done();
		moveUp();
		//done_to_tmp();
		//copy(m);
		mEvent = GLUT_KEY_UP;
		break;
	case GLUT_KEY_DOWN:
		/*if (!flgDone)
		mBoard[0][0] = 2;*/
		flgDone = true;
		//tmp_to_done();
		moveDown();
		//done_to_tmp();
		//copy(m);
		mEvent = GLUT_KEY_DOWN;
		break;
	case GLUT_KEY_LEFT:
		/*if (!flgDone)
		mBoard[0][0] = 2;*/
		flgDone = true;
		//tmp_to_done();
		moveLeft();
		//done_to_tmp();
		//copy(m);
		mEvent = GLUT_KEY_LEFT;
		break;
	case GLUT_KEY_RIGHT:
		/*if (!flgDone)
		mBoard[0][0] = 2;*/
		flgDone = true;
		//tmp_to_done();
		moveRight();
		//done_to_tmp();
		//copy(m);
		mEvent = GLUT_KEY_RIGHT;
		break;

	}
	//
	// Implement your own stuff
	//
}

