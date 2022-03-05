#include "Isoparametrics.h"

// 1D bi-linear 
/**
 * Get real space coordinate from normal space in 1D.
 * @param nodesPos position of nodes in the element
 * @param
 */
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

/**
 * Calculate Jacobian using shape functions.
 * |J[0] J[1]| = |dx/dxi   dy/dxi |
 * |J[2] J[3]|   |dx/deta  dy/deta|
 * @param x positions of element vertices
 * @param y positions of element vertices
 * @param xi normal space position
 * @param eta normal space position
 */
void Isoparametrics::Jacobian(double J[4],
                              double* x,
                              double* y,
                              double xi,
                              double eta) {

  J[0] = 0.25*(-x[0]+x[1]+x[2]-x[3]) + 0.25*eta*(x[0]-x[1]+x[2]-x[3]);
  J[1] = 0.25*(-x[0]-x[1]+x[2]+x[3]) + 0.25* xi*(x[0]-x[1]+x[2]-x[3]);
  J[2] = 0.25*(-y[0]+y[1]+y[2]-y[3]) + 0.25*eta*(y[0]-y[1]+y[2]-y[3]);
  J[3] = 0.25*(-y[0]-y[1]+y[2]+y[3]) + 0.25* xi*(y[0]-y[1]+y[2]-y[3]);

}

/**
 * Return determinant of Jacobian.
 * @param x positions of element vertices
 * @param y positions of element vertices
 * @param xi normal space position
 * @param eta normal space position
 */
double Isoparametrics::detJ(double* x, double* y, double xi, double eta) {


  double J[4];
  Jacobian(J,x,y,xi,eta);
  return J[0]*J[3] - J[1]*J[2];

}

/**
 * Get volume of cell 2D implementation
 * dxdy = detJ*(dtheta)*(deta) = detJ*4
 * @param J array to store Jacobian calculation
 * @param x array to hold element x positions
 * @param y array to hold element y positions
 */
double Isoparametrics::getArea(double* x, double* y) {

    double J[4];
    return 4*detJ(x, y, 0.0, 0.0);
}

