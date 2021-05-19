/*
 * Isoparametrics.h
 *
 * Manages the finite element, isoparametric terms.
 *  Created on: 26 Apr 2021
 *      Author: Mary-Ann Maheswaran
 */
#include <vector>
using namespace std;

#ifndef ISOPARAMETRICS_H_
#define ISOPARAMETRICS_H_

class Isoparametrics {

public:

	double getPos(vector<double> &nodesPos, double xi);
	double getPos(vector<double> &nodesPos, double xi, double eta);
	double getPos(vector<double> &nodesPos, double xi, double eta, double zeta);
	//vector<double> getJacobian(vector<double> &nodesPos, double xi, double eta);

private:

};


// 1D bi-linear
double Isoparametrics::getPos(vector<double> &nodesPos, double xi) {

	double pos = nodesPos[0]*(1-xi);
	pos += nodesPos[1]*(1+xi);

	return 0.5*pos;
}

// 2D bi-linear
double Isoparametrics::getPos(vector<double> &nodesPos, double xi, double eta) {

	double pos = nodesPos[0]*(1-xi)*(1-eta);
	pos += nodesPos[1]*(1+xi)*(1-eta);
	pos += nodesPos[2]*(1+xi)*(1+eta);
	pos += nodesPos[3]*(1-xi)*(1+eta);

	return 0.25*pos;
}

// 3D bi-linear
double Isoparametrics::getPos(vector<double> &nodesPos, double xi, double eta, double theta) {

	double pos = nodesPos[0]*(1-xi)*(1-eta)*(1-theta);
	pos += nodesPos[1]*(1+xi)*(1-eta)*(1-theta);
	pos += nodesPos[2]*(1+xi)*(1+eta)*(1-theta);
	pos += nodesPos[3]*(1-xi)*(1+eta)*(1-theta);
	pos += nodesPos[4]*(1-xi)*(1-eta)*(1+theta);
	pos += nodesPos[5]*(1+xi)*(1-eta)*(1+theta);
	pos += nodesPos[6]*(1+xi)*(1+eta)*(1+theta);
	pos += nodesPos[7]*(1-xi)*(1+eta)*(1+theta);

	return 0.125*pos;
}



#endif /* ISOPARAMETRICS_H_ */
