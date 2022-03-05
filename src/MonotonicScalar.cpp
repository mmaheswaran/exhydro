//Scalar Monotonic artificial viscosity method 2D implementation
#include "MonotonicScalar.h"

#include <math.h>
#include "Density.h"
#include "Velocity.h"
#include "SoundSpeed2.h"
#include <vector>
#include <algorithm>

MonotonicScalar::MonotonicScalar(double quadCoeff, double linearCoeff) {
  cquad = quadCoeff;
  clinear = linearCoeff;
}


//2D implementation - needs templating/generalising
void MonotonicScalar::calculate(Mesh &mesh,
                                Velocity &vel,
                                SoundSpeed2 &csqrd,
                                Density &density) {
  int noElements = mesh.numberElements;
  vector<vector<double> > dudx;
  vector<double>dxtopbottom;
  vector<double>dxleftright;

  int noSides = 4;
  for(int i=0; i < noElements; i++) {
    double area = mesh.getElementArea(i);
    vector<int> nodes = mesh.el2nodemap[i];

    vector<double> n1 = mesh.nodePositions(nodes[0]);
    vector<double> n2 = mesh.nodePositions(nodes[1]);
    vector<double> n3 = mesh.nodePositions(nodes[2]);
    vector<double> n4 = mesh.nodePositions(nodes[3]);

    double Lhorx = -(n2[0]+n3[0]-n4[0]-n1[0]);
    double Lhory =  (n2[1]+n3[1]-n4[1]-n1[1]);
    double Lverx =  (n1[0]+n2[0]-n3[0]-n4[0]);
    double Lvery = -(n1[0]+n2[0]-n3[0]-n4[0]);

    double lengthLhor = sqrt(Lhorx*Lhorx + Lhory*Lhory);
    double lengthLver = sqrt(Lverx*Lverx + Lvery*Lvery);

    dxtopbottom.push_back(lengthLhor > 0 ? area/lengthLhor : 0.0);
    dxleftright.push_back(lengthLver > 0 ? area/lengthLver : 0.0);

    vector<double> v1 = vel.get(nodes[0]);
    vector<double> v2 = vel.get(nodes[1]);
    vector<double> v3 = vel.get(nodes[2]);
    vector<double> v4 = vel.get(nodes[3]);


    vector<double> dudxelement;
    dudxelement.push_back((Lhorx*(v2[0] - v1[0]) + Lhory*(v2[1] - v1[1]))/area);
    dudxelement.push_back((Lverx*(v1[0] - v4[0]) + Lvery*(v1[1] - v4[1]))/area);
    dudxelement.push_back((Lhorx*(v2[0] - v3[0]) + Lhorx*(v2[1] - v3[1]))/area);
    dudxelement.push_back((Lverx*(v3[0] - v4[0]) + Lverx*(v3[1] - v4[1]))/area);

    dudx.push_back(dudxelement);

  }

  //calculate limiters and use to calculate artificial viscosity along each side.
  for(int i=0; i < noElements; i++) {
    for(int s = 0; s < 4; s++) {
      //determine left and right ratio of velocity gradients
      int left  = (s-1)%4;
      int right = (s+1)%4;
      int lneigh = mesh.elneighmap[i][left];
      int rneigh = mesh.elneighmap[i][right];

      double Ldudx = dudx[left][(s+1)%4];
      double Cdudx = dudx[i][s];
      double Rdudx = dudx[right][(s-1)%4];

      double Lratio = Ldudx/Cdudx;
      double Rratio = Rdudx/Cdudx;
      double cond1 = 0.5*(Lratio+Rratio);
      double cond2 = 2*Lratio;
      double cond3 = 2*Rratio;
      auto minval = std::min( {cond1, cond2, cond3, 1.0} );
      double phi = std::max( 0.0, minval );


      double dx;
      if(s%2==0) {
        dx = dxtopbottom[i];
      }else {
        dx = dxleftright[i];
      }

      double du = Cdudx*dx;
      double quadterm = cquad*density.get(i)*du*du*(1-phi*phi);
      double linearterm = clinear*density.get(i)*csqrd.get(i)*du*(1-phi);
      artificialVisc[i] += quadterm+linearterm;
    }
    artificialVisc[i]*=0.25; //average
  }
}
