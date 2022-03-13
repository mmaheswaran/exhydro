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

  void Jacobian(double J[4], double* x, double* y, double xi, double eta);
  double detJ(double* x, double* y, double xi, double eta);
  void getArea(double* x, double* y);
  void intPartialDerivative(double result[8],double* x, double* y);


};




#endif /* ISOPARAMETRICS_H_ */
