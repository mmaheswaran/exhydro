#include "Isoparametrics.h"
/**
 * Needs templating?
 */

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

/**
 * Get integral of shape functions' partial derivative 2D
 * int{\frac{\partial N_1}{\partial x}}, etc...
 * @param realnodpos position of nodes in real space
 */
void Isoparametrics::intPartialDerivative(double result[4], double* x, double* y) {

    double A1=get1stTerm(x);
    double A3=get3rdTerm(x);

    double B1=get1stTerm(y);
    double B3=get3rdTerm(y);

    result[0][0]=-B3+B1;
    result[1][0]= B3+B1;
    result[2][0]= B3-B1;
    result[3][0]=-B3-B1;
    result[0][1]= A3-A1;
    result[1][1]=-A3-A1;
    result[2][1]=-A3+A1;
    result[3][1]= A3-A1;


}

double Isoparametrics::get1stTerm(double* x) {
    return 0.25*(-x[0]+x[1]+x[2]-x[3]);
}

double Isoparametrics::get2ndTerm(double* x) {
    return 0.25*(x[0]-x[1]+x[2]-x[3]);
}

double Isoparametrics::get3rdTerm(double* x) {
    return 0.25*(-x[0]-x[1]+x[2]+x[3]);
}


void Isoparametrics::integralShapeFunctions(double result[4], double* x, double* y) {

    double A1=get1stTerm(x);
    double A2=get2ndTerm(x);
    double A3=get3rdTerm(x);

    double B1=get1stTerm(y);
    double B2=get2ndTerm(y);
    double B3=get3rdTerm(y);

    result[0] = (1./9.)*((3*B3-B2)*(3*A1-A2)-(3*A3-A2)*(3*B1-B2));
    result[1] = (1./9.)*((3*B3+B2)*(3*A1-A2)-(3*A3+A2)*(3*B1-B2));
    result[2] = (1./9.)*((3*B3+B2)*(3*A1+A2)-(3*A3+A2)*(3*B1+B2));
    result[3] = (1./9.)*((3*B3-B2)*(3*A1+A2)-(3*A3-A2)*(3*B1+B2));

}


/**
 * Calculate nodal area of a cell - 2D case, needs templating
 */
void Isoparametrics::calc_nodal_areas(double result[4][2], double* x, double* y) {

    intPartialDerivative(result, x, y);
    double dJ = detJ(x,y,0.0,0.0);
    //note to self: template with number of vertices = 2^D
    for (int i  = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] *= detJ;
        }
    }
}

/**
 * Calculate volume of a node within a specific element
 */
void Isoparametrics::calc_nodal_volume(double result[4], double* x, double* y) {

    integralShapeFunctions(result, x,y);
    double dJ = detJ(x,y,0.0,0.0);
    for (int i = 0; i < 4; i++) {
        result[i] *= detJ;
    }

}

