#include <iostream>
#include "mySystem_GraphSystem.h"

using namespace std;

GRAPH_SYSTEM::GRAPH_SYSTEM()
{
	createDefaultGraph();
}

void GRAPH_SYSTEM::reset()
{

	//
	// Implement your own stuff
	//
	cout << "Reset part" << endl;
	mPassiveSelectedNode = NULL;
	mSelectedNode = NULL;
	node_vector.clear();
	edge_vector.clear();
	node_alive_indicator_array.clear();
	edge_alive_indicator_array.clear();
	edgeid = -1;
	nodeid = -1;
}

void GRAPH_SYSTEM::createDefaultGraph()
{
	//cout << "Ready for default reset~~~~~~~~~~~" << endl;
	reset();
	//cout << "After default reset~~~~~~~~~~~~~" << endl;
	int n_0 = addNode(0.0, 0.0, 0.0);
	int n_1 = addNode(5.0, 0.0, 0.0);
	int n_2 = addNode(0.0, 0.0, 5.0);
	//cout << "n0   " << n_0 << "n1   " << n_1 << "n2  " << n_2 << endl;
	addEdge(n_0, n_1);
	addEdge(n_1, n_2);
}

void GRAPH_SYSTEM::createNet_Horizontal(int nx, int ny)
{
	reset();
	for (int i = 0, j = 0, nodecount = 0; nodecount < 100; nodecount++)
	{
		addNode(5.0 * i, 0, 5.0*j, 1.0);
		i++;
		if ((nodecount + 1) % 10 == 0)
		{
			j++;
			i = 0;
		}
	}
	for (int i = 0, j = 0, edgecount = 0; edgecount < 90; edgecount++)  //i for vertical increment and j for horizontal
	{
		cout << "created edge count :" << edgecount+1 << endl;
		if (edgecount >= 9 && edgecount % 9 == 0)
		{
			j = 0;
			i += 10;
		}
		addEdge(i + j, i + j + 1);
		j++;
	}
}

void GRAPH_SYSTEM::createNet_Vertical(int nx, int ny)
{
	reset();
	float dx = 5.0;
	float dz = 5.0;
	for (int i = 0, j = 0, nodecount = 0; nodecount < 100; nodecount++)
	{
		addNode(5.0 * i, 0, 5.0*j, 1.0);
		i++;
		if ((nodecount + 1) % 10 == 0)
		{
			j++;
			i = 0;
		}
	}
	for (int i = 0, j = 0, edgecount = 0; edgecount < 90; edgecount++) //i for vertical increment and j for horizontal
	{
		cout << "created edge count :" << edgecount+1 << endl;
		if (edgecount >= 9 && edgecount % 9 == 0)
		{
			i = 0;
			j++;
		}
		addEdge(i + j, i + j + 10);
		i += 10;
	}
}

void GRAPH_SYSTEM::createRandomGraph(int nx, int ny)
{
	reset();
	for (int i = 0, j = 0, nodecount = 0; nodecount < 100; nodecount++)
	{
		addNode(5.0 * i, 0, 5.0*j, 1.0);
		i++;
		if ((nodecount + 1) % 10 == 0)
		{
			j++;
			i = 0;
		}
	}
	srand(time(NULL));
	for (int edgecount = 1; edgecount <= 10; edgecount++)
	{
		int node1_ram = rand() % 100;
		int node2_ram = rand() % 100;
		addEdge(node1_ram, node2_ram);
	}
}

void GRAPH_SYSTEM::createRadialGraph(int nx, int ny)
{
	reset();
	for (int i = 0, j = 0, nodecount = 0; nodecount < 100; nodecount++)
	{
		addNode(5.0 * i, 0, 5.0*j, 1.0);
		i++;
		if ((nodecount + 1) % 10 == 0)
		{
			j++;
			i = 0;
		}
	}
	srand(time(NULL));
	int node1_ram = rand() % 100;
	for (int edgecount = 1; edgecount <= 10; edgecount++)
	{
		int node2_ram = rand() % 100;
		addEdge(node1_ram, node2_ram);
	}
}

int GRAPH_SYSTEM::addNode(float x, float y, float z, float r)
{
	nodeid++;
	added_node.id = nodeid;
	added_node.p = vector3(x, y, z);
	added_node.r = r;
	added_node.isalive = true;
	node_vector.push_back(added_node);
	//printf("Addnode ID:%d ,Location: x y z=%f,%f,%f\n", nodeid, x, y, z);
	return nodeid;
}

int GRAPH_SYSTEM::addEdge(int nodeID_0, int nodeID_1)
{

	edgeid++;
	added_edge.id = edgeid;
	added_edge.nodeID[0] = nodeID_0;
	added_edge.nodeID[1] = nodeID_1;
	added_edge.isalive = true;
	edge_vector.push_back(added_edge);
	//printf("Addedge ID:%d Connect node %d and %d\n", edgeid, nodeID_0, nodeID_1);
	return edgeid;
}

void GRAPH_SYSTEM::askForInput()
{
	cout << "GRAPH_SYSTEM" << endl;
	cout << "Key usage:" << endl;
	cout << "1: create a default graph" << endl;
	cout << "2: create a graph with 10x10 nodes. Connect the consecutive nodes horizontally" << endl;
	cout << "3: create a graph with 10x10 nodes. Connect the consecutive nodes vertically" << endl;
	cout << "4: create a graph with 10x10 nodes. Create 10 randomly generated edges" << endl;
	cout << "5: create a graph with 10x10 nodes. Create 10 randomly generated edges attached at a random node" << endl;
	cout << "Delete: delete a node and all the edges attached at it" << endl;
	cout << "Spacebar: unselect the selected node" << endl;
	cout << " " << endl;
	cout << "Use the mouse to select nodes and add edges" << endl;
	cout << "Click the left button to select/unselect or create an edge" << endl;
	cout << " " << endl;
	cout << "A selected node is highlighted as red." << endl;

}

// Find the nearest node to the given position (x, y, z).
// Note that we work in x-z plane only. y should be set to 0.
// The squared distance of the node and the given position should be stored in cur_distance2.
//
//
GRAPH_NODE *GRAPH_SYSTEM::findNearestNode(double x, double z, double &cur_distance2) const
{
	GRAPH_NODE *n = 0;
	cur_distance2 = -1.0;
	for (int i = 0; i < node_vector.size(); i++)
	{
		if (!node_vector[i].isalive)
			continue;
		else
		{
			const GRAPH_NODE * cur_node = &node_vector[i];
			double dx = cur_node->p.x - x;
			double dz = cur_node->p.z - z;
			double d2 = dx*dx + dz*dz;
			if (cur_distance2 < 0.0 || d2 < cur_distance2)
			{
				cur_distance2 = d2;
				n = (GRAPH_NODE *)cur_node;
			}
		}
	}
	return n;
}

void GRAPH_SYSTEM::clickAt(double x, double z)
{
	double cur_d2;
	GRAPH_NODE *n = findNearestNode(x, z, cur_d2);
	if (n == 0) {
		mSelectedNode = 0;
		return;
	}
	//
	// A nearest node may not be touched by the mouse cursor.
	// Thus we need their distance to check.
	//
	if (cur_d2 > n->r*n->r) {
		mSelectedNode = 0;
		return;

	}
	if (mSelectedNode == n) {
		mSelectedNode = 0;
		return;
	}
	if (mSelectedNode != 0) {
		addEdge(mSelectedNode->id, n->id);
		mSelectedNode = 0;
		return;
	}
	mSelectedNode = n;
}

void GRAPH_SYSTEM::deleteNode(int nodeID) {
	//
	// Implement your own stuff
	//
	cout << "Delete node position at x y z :" << node_vector[nodeID].p.x << "," << node_vector[nodeID].p.y << "," << node_vector[nodeID].p.z << endl;
	node_vector[nodeID].isalive = false;
}

void GRAPH_SYSTEM::deleteSelectedNode()
{
	if (mSelectedNode == NULL) return;
	deleteNode(mSelectedNode->id);
	for (int i = 0; i < edge_vector.size(); i++)
	{
		if (!edge_vector[i].isalive)
			continue;
		else if (edge_vector[i].nodeID[0] == mSelectedNode->id || edge_vector[i].nodeID[1] == mSelectedNode->id) //Indirected graph
		{
			edge_vector[i].isalive = false;
			cout << "Delete edge connect nodeID " << edge_vector[i].nodeID[0] << "and " << edge_vector[i].nodeID[1] << endl;
		}
	}
	mSelectedNode = 0;
	mPassiveSelectedNode = 0;
}

bool GRAPH_SYSTEM::isSelectedNode() const
{
	return mSelectedNode != 0;
}

void GRAPH_SYSTEM::getInfoOfSelectedPoint(double &r, vector3 &p) const
{
	if (isSelectedNode() == false) return;
	r = mSelectedNode->r;
	p = mSelectedNode->p;
}

void GRAPH_SYSTEM::handleKeyPressedEvent(unsigned char key)
{
	switch (key) {
	case 127: // delete
		deleteSelectedNode();
		break;

	case '1':
		createDefaultGraph();
		mSelectedNode = 0;
		break;
	case '2':
		createNet_Horizontal(10, 10);
		mSelectedNode = 0;
		break;

	case '3':
		createNet_Vertical(10, 10);

		break;
	case '4':
		createRandomGraph(10, 10);
		mSelectedNode = 0;

		break;
	case '5':
		createRadialGraph(10, 10);
		mSelectedNode = 0;
		break;

	case ' ':
		mSelectedNode = 0;
		break;
	}
}

void GRAPH_SYSTEM::handlePassiveMouseEvent(double x, double z)
{
	double cur_d2;
	GRAPH_NODE *n = findNearestNode(x, z, cur_d2);
	if (n == 0) return;
	if (cur_d2 > n->r*n->r) {
		mPassiveSelectedNode = 0;
		return;
	}
	mPassiveSelectedNode = n;
}

int GRAPH_SYSTEM::getNumOfNodes() const
{
	//
	// Implement your own stuff
	//
	return node_vector.size(); // remove this line
}

void GRAPH_SYSTEM::getNodeInfo(int nodeIndex, double &r, vector3 &p) const
{
	if (node_vector[nodeIndex].isalive)
	{
		r = node_vector[nodeIndex].r;
		p = node_vector[nodeIndex].p;
	}
	else
	{
		r = 0.0;
	}
}

int GRAPH_SYSTEM::getNumOfEdges() const
{
	return edge_vector.size(); // remove this line
}

vector3 GRAPH_SYSTEM::getNodePositionOfEdge(int edgeIndex, int nodeIndex) const
{
	if (edge_vector[edgeIndex].isalive)
		return node_vector[edge_vector[edgeIndex].nodeID[nodeIndex]].p;

	else
		return vector3(0, 0, 0);
}
