/*
 * ScalarMonotonic.h
 *
 *
 *  Created on: 28 May 2021
 *      Author: Mary-Ann Maheswaran
 */

#include "ArtificialViscosity.h"
#include "Mesh.h"
#include "Velocity.h"
#include "SoundSpeed2.h"
#include "Density.h"
#include <math.h>

#ifndef SCALARMONOTONIC_H_
#define SCALARMONOTONIC_H_

class ScalarMonotonic : public ArtificialViscosity {

public:

	ScalarMonotonic(double quadCoeff, double linearCoeff);
	void calculate(Mesh &mesh, Velocity &velx, Velocity &vely, SoundSpeed2 &csqrd, Density &density);

private:
	double cquad;
	double clinear;

};

ScalarMonotonic::ScalarMonotonic(double quadCoeff, double linearCoeff) {
	cquad = quadCoeff;
	clinear = linearCoeff;
}

void ScalarMonotonic::calculate(Mesh        &mesh,
                                Velocity    &velx,
								Velocity    &vely,
								SoundSpeed2 &csqrd,
								Density     &density)
{

	int noElements = mesh.numberElements;
	vector<vector<double>> dudx;
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

		double dxtopbottom = lengthLhor > 0 ? area/lengthLhor : 0.0;
		double dxleftright = lengthLver > 0 ? area/lengthLver : 0.0;

		double v1x = velx.get(nodes[0]);
		double v2x = velx.get(nodes[1]);
		double v3x = velx.get(nodes[2]);
		double v4x = velx.get(nodes[3]);

		double v1y = vely.get(nodes[0]);
		double v2y = vely.get(nodes[1]);
		double v3y = vely.get(nodes[2]);
		double v4y = vely.get(nodes[3]);

		vector<double> dudxelement;
		dudxelement.push_back((Lhorx*(v2x - v1x) + Lhory*(v2y - v1y))/area);
		dudxelement.push_back((Lverx*(v1x - v4x) + Lvery*(v1y - v4y))/area);
		dudxelement.push_back((Lhorx*(v2x - v3x) + Lhorx*(v2y - v3y))/area);
		dudxelement.push_back((Lverx*(v3x - v4x) + Lverx*(v3y - v4y))/area);

		dudx.push_back(dudxelement);

	}

}


#endif /* SCALARMONOTONIC_H_ */
