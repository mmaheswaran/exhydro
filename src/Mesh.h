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
	int noVertices;

	vector<vector<int> > el2nodemap; 	//map element number to node number
	vector<vector<int> > elneighmap; 	//map element number to node number

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


private:
	vector<vector<double> > _nodePositions; //node positions
	vector<int> _region;					//region number of each element
	Isoparametrics iso;
};

Mesh::Mesh(int dimensions)
{

	DIMS = dimensions;
	numberNodes = 0;
	numberElements = 0;
	noVertices = 0;
	if(dimensions == 1) {
	  	noVertices = 2;
	}else if(dimensions == 2) {
		noVertices = 4;
	}else if(dimensions == 3) {
		noVertices = 8;
	}else {
		throw "Unacceptable number of dimensions in Mesh constructor, choose 1, 2 or 3.";
	}
}

void Mesh::nodePositions(const int node, const int dim, const double value) {
	_nodePositions[node][dim] = value;
}

void Mesh::region(const int element, const int value) {
	_region[element] = value;
}

void Mesh::printNodePos()
{

	for (const auto& inner : _nodePositions) {
	  for (const auto& item : inner) {
		cout << item << " ";
	  }

	  cout << endl;
	}
	cout << endl;
}

/*double Mesh:getVolume(int element) {

}*/

/**
 * 1D overloaded implementation of add a region to the mesh.
 * Assuming linear spacing.
 * @param noElements is number of elements in region
 * @param extents physical size of region
 * @param origin of region
 */
void Mesh::addRegion(int noElements, double extent, double origin, int regionNumber)
{

	double dx = extent/noElements; //spacing
	for(int i = 0; i < noElements; i++) {
		vector<double> pos{i*dx + origin};
		_nodePositions.push_back(pos);
		_region.push_back(regionNumber);
		vector<int> nodes{i, i+1};
		el2nodemap.push_back(nodes);
		numberNodes++;
		numberElements++;
	}

	if(noElements>0) {
		vector<double> pos{extent + origin};
		_nodePositions.push_back(pos);
	}

}

/**
 * 2D overloaded implementation of add a region to the mesh
 */
void Mesh::addRegion(int noElements[2], double extents[2], double origin[2], int regionNumber)
{

	double dx = extents[0]/noElements[0];
	double dy = extents[1]/noElements[1];
	                        //      (2)N
	double ox = origin[0];  //     3----2
	double oy = origin[1];  //(3)W |    |(1)E
	                        //     0----1
	                        //     (0)S
	//add 1st node left corner
	for(int j = 0; j < noElements[1]; j++) { //y-direction
	  for(int i = 0; i < noElements[0]; i++) { //x-direction
		  //node positions
		  vector<double> node0{ox+dx*i    ,oy+dy*j    };
		  vector<double> node1{ox+dx*(i+1),oy+dy*j    };
		  vector<double> node2{ox+dx*(i+1),oy+dy*(j+1)};
		  vector<double> node3{ox+dx*i    ,oy+dy*(j+1)};

		  //element numbers of neighbours
		  int eneigh = numberElements +1;
		  int wneigh = numberElements -1;
		  int nneigh = numberElements + noElements[0];
		  int sneigh = numberElements - noElements[0];
		  //mark out non-existent neighbours of edge elements
		  if (j==0) { //first row
			  sneigh = -1;
		  }
		  if (j==noElements[1]-1) {//last row
			  nneigh = -1;
		  }
		  if (i==0) { //first column
			  wneigh = -1;
		  }
		  if (i==noElements[0]-1) {//last column
			  eneigh = -1;
		  }
		  //add to element-element connectivity array
		  vector<int> neighbours{sneigh,eneigh,nneigh,wneigh};
		  elneighmap.push_back(neighbours);

		  int n0 = numberNodes;
		  int n1 = numberNodes+1;
		  int n2 = numberNodes+2;
		  int n3 = numberNodes+3;

		  //Assign element-node connectivity
		  if((sneigh<0)&(wneigh<0)) {
			  numberNodes+=4;
		  }else if((sneigh<0)&&(wneigh>=0)) {
			  n0 = el2nodemap[wneigh][1];
			  n3 = el2nodemap[wneigh][2];
			  numberNodes+=2;
		  }else if((wneigh<0)&&(sneigh>=0)) {
			  n1 = el2nodemap[sneigh][3];
			  n2 = el2nodemap[sneigh][2];
			  numberNodes+=2;
		  }else if((sneigh>=0)&&(wneigh>=0)&&(eneigh>=0)) {
			  n0 = el2nodemap[sneigh][3];
			  n1 = el2nodemap[sneigh][2];
			  n3 = el2nodemap[wneigh][2];
			  numberNodes++;
		  }
		  vector<int> nodes{n0,n1,n2,n3};
		  el2nodemap.push_back(nodes);
		  numberElements++;
	  }
	}
}



#endif /* MESH_H_ */
