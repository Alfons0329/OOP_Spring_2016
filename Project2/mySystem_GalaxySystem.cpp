//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//
#include "mySystem_GalaxySystem.h"
#include <iostream>
#include <time.h>
#include <cmath>
using namespace std;

namespace {
    double getRandDouble( double L, double U ) {
        return L + (U-L)*rand( )/(double) RAND_MAX;
    }
};

GALAXY_SYSTEM::GALAXY_SYSTEM( )
{
    mTimeStep = 0.0025; 
    mMaxV = 100.0;
    mNumOfObjs = 100;
    mNumLargeObjs = 2;
    mMinR = 0.5;            //minimum radius of objects
    mMaxR = 3.0;            //maximum radius of objects
    mSpaceSize = 300.0;
    mG = 5.0;               //gravitational constant
    generateObjects( );
}

/*
Generate randomly the positions,  
velocities and radii of the objects.

Also, if the objects are large, 
set their masses to be a large number.

The mass of an  object depends on the object's radius.

The position of an object is inside 
[-halfSpaceSize, halfSpaceSize]x[-halfSpaceSize, halfSpaceSize].

The velocity of an object is inside
[-100.0, 100]x[-100.0, 100].

Initialize the alive flag of each object.
the alive flag indicates whether the object is alive or not.
If the object is not alive, ignore it in all the calculations.

If there's only one large object,
set its position to the origin
and set its velocity to zero.

*/
void GALAXY_SYSTEM::generateObjects( )
{
    //Fill in here
	mX.resize(mNumOfObjs);
	mY.resize(mNumOfObjs);
	mR.resize(mNumOfObjs);
	mMass.resize(mNumOfObjs);
	mVx.resize(mNumOfObjs);
	mVy.resize(mNumOfObjs);
	mFx.resize(mNumOfObjs);
	mFy.resize(mNumOfObjs);
	mAlive.resize(mNumOfObjs);
	srand(time(NULL));

	for (int i = 0; i<mNumOfObjs; i++)//Initialize all the force to be zero first
	{
		mFx[i] = 0.0;
		mFy[i] = 0.0;
	}
	if (mNumLargeObjs == 1)
	{
		mX[0] = 0.0;
		mY[0] = 0.0;
		mR[0] = mMaxR*2.0;
		mMass[0] = mMaxR*mMaxR * 1000.0;
		mVx[0] = 0.0;
		mVy[0] = 0.0;
		mAlive[0] = true;
	}
	else
	{
		for (int i = 0; i < mNumLargeObjs; i++)/*像是-0.5*mspacesize就能讓她正好有負右有正
			因為低於一半的自動變負 高於一半的變正 而且還能在範圍內*/
		{
			mX[i] = (rand() / (double)RAND_MAX)*mSpaceSize - 0.5*mSpaceSize;
			mY[i] = (rand() / (double)RAND_MAX)*mSpaceSize - 0.5*mSpaceSize;
			mR[i] = mMaxR*2.0;
			mMass[i] = mMaxR*mMaxR * 1000.0;
			/*mVx[i] = 200.0*(0.5 - (rand() / (double)RAND_MAX));
			mVy[i] = 200.0*(0.5 - (rand() / (double)RAND_MAX));*/
			mVx[i] = 0.0;
			mVy[i] = 0.0;
			mAlive[i] = true;

		}
	}
	for (int i = mNumLargeObjs; i<mNumOfObjs; i++)
	{
			mX[i] = (rand() / (double)RAND_MAX)*mSpaceSize - 0.5*mSpaceSize;
			mY[i] = (rand() / (double)RAND_MAX)*mSpaceSize - 0.5*mSpaceSize;
			mR[i] = (rand() / (double)RAND_MAX)*(mMaxR - mMinR) + mMinR;
			//mR[i] = ((rand()) / (double)RAND_MAX*((mMaxR - mMinR) * 10.0)) / 10.0 + mMinR;
			mMass[i] = (double)(mR[i] * mR[i]);
			mVx[i] = 200.0*(0.5 - (rand() / (double)RAND_MAX));
			mVy[i] = 200.0*(0.5 - (rand() / (double)RAND_MAX));
			mAlive[i] = true;
	}

}

/*
Handle the key events.
*/
bool GALAXY_SYSTEM::handleKeyPressedEvent( int key )
{
	bool flgHandled = false;
	switch (key)
	{
	case '1':
		mNumLargeObjs = 1;
		flgHandled = true;
		generateObjects();
		break;
	case '2':
		mNumLargeObjs = 2;
		flgHandled = true;
		generateObjects();
		break;
	case '3':
		mNumLargeObjs = 3;
		flgHandled = true;
		generateObjects();
		break;
	}
	return flgHandled;
}

/*
Generate the objects.
Call generateObjects( ).
*/
void GALAXY_SYSTEM::reset( )
{
	mNumLargeObjs = 2;
	generateObjects( );
}

/*
Show the system title.
Show the key usage.
*/
void GALAXY_SYSTEM::askForInput( )
{
	cout << "GALAXY_SYSTEM::askForInput" << endl;
	cout << "Key usage:" << endl;
	cout << "1: one large object" << endl;
	cout << "2: two large objects" << endl;
	cout << "3: three large objects" << endl;
	cout << "r: reset" << endl;
}

/*
Return the number of objects
return mNumOfObjs
*/
int GALAXY_SYSTEM::getNumOfObjs( ) const
{
	return mNumOfObjs;
}

/*
Get the object information based on the object index.
(x,y) = position
r = radius
Return the alive flag.
*/
bool GALAXY_SYSTEM::getObjInfo( int objIndex, double &x, double &y, double &r ) const
{
    x = mX[objIndex];
    y =mY[objIndex];
    r = mR[objIndex];

    return mAlive[objIndex];

}

/*
Merge the objects if they overlap with each other.
Modify the velocities of the objects after merging
based on the conservation of momentum.
Set the alive flags of the objects accordingly.

Pseudo-code

For each pair of the objects
  if they do not overlap continue
  If they overlap
    do
      turn off the alive flag of the object with smaller radius
      compute the new velocity of the larger object
*/
void GALAXY_SYSTEM::mergeObjects( )
{
	for (int i = 0; i < mNumOfObjs; i++)
	{
		if (mAlive[i]==false)
			continue;
		for (int j = i + 1; j < mNumOfObjs; j++)
		{
			if (mAlive[j]==false)
				continue;
			if(((mX[i] - mX[j])*(mX[i] - mX[j]) +(mY[i] - mY[j])*(mY[i] - mY[j]))<=(mR[i]+mR[j])*(mR[i]+mR[j]))//要改成連心距
			{
				if (mMass[i] >= mMass[j])
				{
					mVx[i] = (double)((mVx[i] * mMass[i] + mVx[j] * mMass[j]) / (mMass[i] + mMass[j]));
					mVy[i] = (double)((mVy[i] * mMass[i] + mVy[j] * mMass[j]) / (mMass[i] + mMass[j]));
					mMass[i] += mMass[j];
					//mMass[j] = 0.0;
					mAlive[j] = false;
				}

				else
				{
					mVx[j] = (double)((mVx[i] * mMass[i] + mVx[j] * mMass[j]) / (mMass[i] + mMass[j]));
					mVy[j] = (double)((mVy[i] * mMass[i] + mVy[j] * mMass[j]) / (mMass[i] + mMass[j]));
					mMass[j] += mMass[i];
					//mMass[i] = 0.0;
					mAlive[i] = false;
				}
			}
		}			
	}	

}

/*
Update the position of the objects
Steps:
1. compute the forces exerting on each object
2. compute the velocity of each object
3. compute the position of each object

Constraints:
The component of a velocity must be inside [-mMaxV, mMaxV].

The component of a position must be inside [-halfSpaceSize, halfSpaceSize].
Warp the position if it's outside of the range.
Consider a position (x,y).
If x > halfSpaceSize, set x = -halfSpaceSize;


*/
void GALAXY_SYSTEM::update( ) 
{
    mergeObjects( ); // merge objects first if they overlap with each other
    
    //
    //Fill in here
    //compute forces exerting on objects
	for (int i = 0; i < mNumOfObjs;i++)
	{
		mFx[i] = 0.0;
		mFy[i] = 0.0;
	}
	for (int i = 0; i < mNumOfObjs; i++)
	{
		if (!mAlive[i])
			continue;
		for (int j = i + 1; j < mNumOfObjs; j++)
		{
			if (!mAlive[j])
				continue;

			double distance = sqrt((mX[i] - mX[j])*(mX[i] - mX[j]) + (mY[i] - mY[j])*(mY[i] - mY[j]));
			double mij = mMass[i] * mMass[j];

			double nx = (mX[i] - mX[j]) / distance;
			double ny = (mY[i] - mY[j]) / distance;

			mFx[i] -= mij*mG*nx / (distance*distance); 	//notice the negative sign	
			mFy[i] -= mij*mG*ny / (distance*distance);	//notice the negative sign

			mFx[j] += mij*mG*nx / (distance*distance);	//notice the positive sign
			mFy[j] += mij*mG*ny / (distance*distance);  //notice the positive sign
			if (!mAlive[i])
			continue;

		}

		mX[i] = mX[i] + mVx[i] * mTimeStep;
		mY[i] = mY[i] + mVy[i] * mTimeStep;

		if (mX[i]>mSpaceSize / 2.0)
			mX[i] = -mSpaceSize / 2.0;
		else if (mX[i] < -mSpaceSize / 2.0)
			mX[i] = mSpaceSize / 2.0;

		if (mY[i]>mSpaceSize / 2.0)
			mY[i] = -mSpaceSize / 2.0;
		else if (mY[i] < -mSpaceSize / 2.0)
			mY[i] = mSpaceSize / 2.0;

		mVx[i] += (mFx[i] / mMass[i]) * mTimeStep;
		mVy[i] += (mFy[i] / mMass[i])* mTimeStep;

		if (mVx[i]>100.0)
			mVx[i] = 100.0;
		else if (mVx[i]<-100.0)
			mVx[i] = -100.0;
		if (mVy[i]>100.0)
			mVy[i] = 100.0;
		else if (mVy[i]<-100.0)
			mVy[i] = -100.0;
	}
	//compute the velocity of objects
    //compute positions of objects
    //make sure the objects inside the space
}