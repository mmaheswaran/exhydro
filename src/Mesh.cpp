/*
 * Mesh.cpp
 *
 *  Created on: 21 Jan 2022
 *      Author: maryann
 */

#include "Mesh.h"
using namespace std;

/**
 * Initialise mesh with appropriate dimensions
 * @param dimensions
 */
Mesh::Mesh(int dimensions) {

    DIMS = 2; //dimensions;
    numberNodes = 0;
    numberElements = 0;
    noVertices = 0;

    if (dimensions == 1) {
        noVertices = 2;
    } else if (dimensions == 2) {
        noVertices = 4;
    } else if (dimensions == 3) {
        noVertices = 8;
    } else {
        throw "Unacceptable number of dimensions in Mesh constructor, choose 1, 2 or 3.";
    }
}


/**
 * Set region number of element
 * @param element
 * @param value
 */
void Mesh::region(const int element, const int value) {
    _region[element] = value;
}

void Mesh::updateNodePos(Velocity &nodevelocity, double timestep, int dim) {

    _nodepositions.update(nodevelocity, timestep, dim);
}

void Mesh::initVelBC(vector<double> xmin,
                     vector<double> xmax,
                     vector<double> valatxmin,
                     vector<double> valatxmax) {

    this.initNodeBC(xmin,xmax,valatxmin,valatxmax,velBC);
}

void Mesh::initNodeBC(vector<double> xmin,
                     vector<double> xmax,
                     vector<double> valatxmin,
                     vector<double> valatxmax,
                     vector<unordered_map<int, double> > &nodeBC) {

    unordered_map<int, double> umap;

    for (int dim= 0; dim < DIMS; dim++) {
        nodeBC.push_back(DIMS, umap);
        for(int node = 0; node < numberNodes; node++) {
            if(_nodepositions.get(node,dim) == xmin[dim] ) {
                nodeBC[dim][node] = valatxmin[dim];
            }
            if(_nodepositions.get(node,dim) == xmax[dim] ) {
                nodeBC[dim][node] = valatxmax[dim];
            }
        }
    }
}

void Mesh::printNodePos() {

    _nodepositions.print();
}

/**
 * Finite element implementation returning area of element - 2D implementation needs templating.
 * @param element number
 */
double Mesh::getVolume(int element) {

    vector<int> nodes = el2nodemap[element];
    double x[noVertices];
    double y[noVertices];
    for (int v = 0; v < noVertices; v++) {
        int n = nodes[v];
        x[v] = _nodepositions.get(n,0);
        y[v] = _nodepositions.get(n,1);
    }
    double detJ = iso.detJ(x, y, 0.0, 0.0);
    return 4 * detJ;

}

/**
 * 1D overloaded implementation of add a region to the mesh.
 * Assuming linear spacing.
 * @param noElements is number of elements in region
 * @param extents physical size of region
 * @param origin of region
 */
void Mesh::addRegion(int noElements, double extent, double origin,
        int regionNumber) {

    double dx = extent / noElements; //spacing
    for (int i = 0; i < noElements; i++) {
        vector<double> pos(i * dx + origin);
        _nodepositions.add(pos);
        _region.push_back(regionNumber);
        vector<int> nodes(i, i + 1);
        el2nodemap.push_back(nodes);
        numberNodes++;
        numberElements++;
    }

    if (noElements > 0) {
        vector<double> pos(extent + origin);
        _nodepositions.add(pos);
    }

}

/**
 * 2D overloaded implementation of add a region to the mesh
 */
void Mesh::addRegion(int noElements[2], double extents[2], double origin[2], int regionNumber) {

    double dx = extents[0] / noElements[0];
    double dy = extents[1] / noElements[1];
                            //      (2)N
    double ox = origin[0];  //     3----2
    double oy = origin[1];  //(3)W |    |(1)E
                            //     0----1
                            //      (0)S
                            //add 1st node left corner

    for (int j = 0; j < noElements[1]; j++) { //y-direction
        for (int i = 0; i < noElements[0]; i++) { //x-direction

            _region.push_back(regionNumber);

            //node positions
            vector<double> node0 { ox + dx * i, oy + dy * j };
            vector<double> node1 { ox + dx * (i + 1), oy + dy * j };
            vector<double> node2 { ox + dx * (i + 1), oy + dy * (j + 1) };
            vector<double> node3 { ox + dx * i, oy + dy * (j + 1) };

            //element numbers of neighbours
            int eneigh = numberElements + 1;
            int wneigh = numberElements - 1;
            int nneigh = numberElements + noElements[0];
            int sneigh = numberElements - noElements[0];
            //mark out non-existent neighbours of edge elements
            if (j == 0) { //first row
                sneigh = -1;
            }
            if (j == noElements[1] - 1) { //last row
                nneigh = -1;
            }
            if (i == 0) { //first column
                wneigh = -1;
            }
            if (i == noElements[0] - 1) { //last column
                eneigh = -1;
            }
            //add to element-element connectivity array
            vector<int> neighbours { sneigh, eneigh, nneigh, wneigh };
            elneighmap.push_back(neighbours);

            int n0 = numberNodes;
            int n1 = numberNodes + 1;
            int n2 = numberNodes + 2;
            int n3 = numberNodes + 3;

            //Assign element-node connectivity
            if ((sneigh < 0) & (wneigh < 0)) {
                numberNodes += 4;
            } else if ((sneigh < 0) && (wneigh >= 0)) {
                n0 = el2nodemap[wneigh][1];
                n3 = el2nodemap[wneigh][2];
                numberNodes += 2;
            } else if ((wneigh < 0) && (sneigh >= 0)) {
                n1 = el2nodemap[sneigh][3];
                n2 = el2nodemap[sneigh][2];
                numberNodes += 2;
            } else if ((sneigh >= 0) && (wneigh >= 0) && (eneigh >= 0)) {
                n0 = el2nodemap[sneigh][3];
                n1 = el2nodemap[sneigh][2];
                n3 = el2nodemap[wneigh][2];
                numberNodes++;
            }
            vector<int> nodes { n0, n1, n2, n3 };
            el2nodemap.push_back(nodes);
            numberElements++;
        }
    }
}

/**
 * Return divergence of a property per element
 * @param VectorProperty vector property you need to calculate divergence for
 */
vector<double> Mesh::calcDiv(VectorProperty &vp) {

    //get integral of partial derivative shape functions
    //*** need to generalise this divergence calculation routine **
    double intpdeshapefunction[noVertices][DIMS];
    vector<double> div;
    double x[noVertices];
    double y[noVertices];

    for(int i=0; i<numberElements; i++) {
        vector<double> coords = _nodePositions.get(i);
        for(int j =0; j < noVertices; j++) {
            x[j]=coords[j][0];
            y[j]=coords[j][1];
        }
        iso.intPartialDerivative(intpdeshapefunction, *x, *y);

        //multiply for each node along each dimension to get divergence in a element
        double d = 0.0;
        for(int j=0; j < noVertices; j++) {
            int node = el2nodemap[i][2];
            for(int k = 0; k < DIMS; k++) {
                d += vp[node][k] * intpdeshapefunction[j][k];
            }
        }
        div.push_back(d);
    }

    return div;


}

