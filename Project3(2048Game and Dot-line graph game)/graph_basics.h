//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//

#ifndef __MY_GRAPH_BASICS_H_
#define __MY_GRAPH_BASICS_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>
using std::vector;

class GRAPH_NODE {
public:
    GRAPH_NODE( ) {
        r = 1.0;
        p = vector3(0.0, 0.0, 0.0);
    }
    vector3 p;  //position
    double r;   //radius   
    int id;     // note: ID (identifier) may not be the sams as index.
	bool isalive;
	//
    // Add your own data members here
    //
};

class GRAPH_EDGE {
public:
    int nodeID[2];  // nodeID[0]: the first node
                    // nodeID[1]: the second node
    int id;         // note: ID (identifier) may not be the sams as index.
	bool isalive;
    //
    // Add your own data members here
    //
};

#endif