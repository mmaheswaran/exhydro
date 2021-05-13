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
#include "Isoparametrics.h"
using namespace std;

#ifndef MESH_H_
#define MESH_H_

class Mesh {

public:
	Mesh(int dimensions);
	int numberNodes;						//number of nodes in simulation
	int numberElements; 					//number of elements in simulation
	int DIMS;								//number of spatial dimensions

	vector<vector<double> > el2nodemap; 	//map element number to node number

	double nodePositions(int index) {return _nodePositions[index];} //get
	double region(int index) {return _region[index];}

	void nodePositions(const int node, const int dim, const double value); //set
    void region(const int node, const int dim, const double value);

	void printNodePos();					//printNodePos node positions
	double getVolume(int element);			//get volume of an element

	void addRegion(int noElements, double extent, double origin, int regionNumber); 		  //1D
	void addRegion(int noElements[2], double extents[2], double origin[2], int regionNumber); //2D
	void addRegion(int noElements[3], double extents[3], double origin[3], int regionNumber); //3D

private:
	vector<vector<double> > _nodePositions; //node positions
	vector<int> _region;					//region number of each element
	Isoparametrics iso;
};

Mesh::Mesh(int dimensions) {

	DIMS = dimensions;
	numberNodes = 0;
	numberElements = 0;
}

void Mesh::nodePositions(const int node, const int dim, const double value) {
	_nodePositions[node][dim] = value;
}

void Mesh::region(const int node, const int dim, const double value) {
	_region[node][dim] = value;
}

void Mesh::printNodePos() {

	for (const auto& inner : _nodePositions) {
	  for (const auto& item : inner) {
		cout << item << " ";
	  }

	  cout << endl;
	}
	cout << endl;
}

double Mesh:getVolume(int element) {

}

/**
 * 1D overloaded implementation of add a region to the mesh.
 * Assuming linear spacing.
 * @param noElements is number of elements in region
 * @param extents physical size of region
 * @param origin of region
 */
void Mesh::addRegion(int noElements, double extent, double origin, int regionNumber) {

	double dx = extent/noElements; //spacing
	for(int i = numberNodes; i < numberNodes + noElements; i++) {
		_nodePositions[numberNodes].push_back(i*dx + origin);
		_region.push_back(regionNumber);
		el2nodemap[noElements][0] = i;
		el2nodemap[noElements][1] = i+1;
		numberNodes++;
		numberElements++;
	}
	if(noElements>0) _nodePositions[numberNodes].push_back(extent + origin);

}

/**
 * 2D overloaded implementation of add a region to the mesh
 */
void Mesh::addRegion(int noElements[2], double extents[2], double origin[2], int regionNumber) {

	double dx = extents[0]/noElements[0]; //spacing
	double dy = extents[1]/noElements[1]; //spacing
	for(int i = numberNodes; i < numberNodes + noElements; i++) {
		_nodePositions[numberNodes].push_back(i*dx + origin);
		_region.push_back(regionNumber);
		el2nodemap[noElements][0] = i;
		el2nodemap[noElements][1] = i+1;
		numberNodes++;
		numberElements++;
	}
	if(noElements>0) _nodePositions[numberNodes].push_back(extent + origin);


}

/**
 * 3D overloaded implementation of add a region to the mesh
 */
void Mesh::addRegion(int noElements[3], double extents[3], double origin[3], int regionNumber) {

}


#endif /* MESH_H_ */
