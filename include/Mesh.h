/*
 * Mesh.h
 *
 * Hydrodynamics mesh and isoparametrics
 * NOTE: Node numbering should correspond to isoparametric space numbering
 *
 * Explicit method to calculate the hydrodynamic conservation laws of the system in the
 * Lagrangian frame.
 *  Created on: 16 Apr 2021
 *      Author: Mary-Ann Maheswaran
 */

#include <vector>
#include <iostream>
#include <unordered_map>
#include "Isoparametrics.h"
#include "Position.h"
#include "Velocity.h"
#include "Volume.h"

using namespace std;

#ifndef MESH_H_
#define MESH_H_

class Mesh{

public:
    Mesh(int dimensions);
    ~Mesh() {};
    int numberNodes;					//number of nodes in simulation
    int numberElements; 			    //number of elements in simulation
    int DIMS;							//number of spatial dimensions
    int noVertices;

    vector<double> meshlims;            //array containing mesh limits in each dimension
                                        //meshlims[0] = minimum x/r
                                        //meshlims[1] = maximum x/r
                                        //meshlims[2] = minimum y/z
                                        //meshlims[3] = maximum z/z
                                        //meshlims[4] = minimum z
                                        //meshlims[5] = maximum z

    vector<vector<int> > el2nodemap; 	//map element number to node number
    vector<vector<int> > elneighmap; 	//map element number to neighbour element

    double region(int index) {return _region[index];} //get
    void region(const int element, const int value);  //set
    const vector<int>& getRegionData() const { return _region; }

    vector<double>& nodePositions(int index) {return _nodepositions.get(index);} //get
    void nodePositions(const int node, const int dim, const double value){_nodepositions.set(node,dim,value);} //set
    void updateNodePos(Velocity &nodevelocity, double timestep, int dim);

    // setup boundary conditions
    // values at boundaries in each dimension
    void initVelBC(vector<double> xmin,
                   vector<double> xmax,
                   vector<double> valatxmin,
                   vector<double> valatxmax);

  /*  void initElemBC(vector<double> xmin,
                    vector<double> xmax,
                    vector<double> valatxmin,
                    vector<double> valatxmax,
                    vector<unordered_map<int, double> > &elemBC);*/

    void printNodePos();				//printNodePos node positions

    void addRegion(int noElements, double extent, double origin, int regionNumber);           //1D
    void addRegion(int noElements[2], double extents[2], double origin[2], int regionNumber); //2D
    //void addRegion(int noElements[3], double extents[3], double origin[3], int regionNumber); //3D

    double getVolume(int index);

    vector<double> calcDiv(VectorProperty &vp);

    void calcNodalArea();

private:
    Position _nodepositions; //node positions
    vector<int> _region;     //region number of each element
    Isoparametrics iso;

    // Boundary conditions for component dimensions
    vector<unordered_map<int, double> > velBC;
   // vector<unordered_map<int, double> > pressBC;
   // vector<unordered_map<int, double> > energyBC;
    void findMeshLims();
    void initNodeBC(vector<double> xmin,
                    vector<double> xmax,
                    vector<double> valatxmin,
                    vector<double> valatxmax,
                    vector<unordered_map<int, double> > &nodeBC);



};




#endif /* MESH_H_ */
