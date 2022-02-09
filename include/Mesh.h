/*
 * Mesh.h
 *
 * Hydrodynamics mesh and isoparametrics
 * NOTE: Node numbering should correspond to isoparametric space numbering
 *
 *  Created on: 16 Apr 2021
 *      Author: Mary-Ann Maheswaran
 */

#include <vector>
#include <iostream>
#include "Isoparametrics.h"

using namespace std;

#ifndef MESH_H_
#define MESH_H_

class Mesh{

public:
    Mesh(int dimensions);
	~Mesh() {};
	int numberNodes;						//number of nodes in simulation
	int numberElements; 					//number of elements in simulation
	int DIMS;								//number of spatial dimensions
	int noVertices;

	vector<vector<int> > el2nodemap; 	//map element number to node number
	vector<vector<int> > elneighmap; 	//map element number to neighbour element

	vector<double>& nodePositions(int index) {return _nodePositions[index];} //get
	double region(int index) {return _region[index];}

	void nodePositions(const int node, const int dim, const double value); //set
	void region(const int element, const int value);
	const vector<int>& getRegionData() const { return _region; }

	void printNodePos();					//printNodePos node positions
//	double getVolume(int element);			//get volume of an element

	void addRegion(int noElements, double extent, double origin, int regionNumber);        //1D
	void addRegion(int noElements[2], double extents[2], double origin[2], int regionNumber); //2D
	//void addRegion(int noElements[3], double extents[3], double origin[3], int regionNumber); //3D

	double getElementArea(int index);


private:
	vector<vector<double> > _nodePositions; //node positions
	vector<int> _region;					//region number of each element
	Isoparametrics iso;
};




#endif /* MESH_H_ */
