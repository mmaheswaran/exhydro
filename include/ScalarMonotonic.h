/*
 * ScalarMonotonic.h
 *
 * Reference:
 * "An adaptive multi-material Arbitrary Lagrangian Eulerian algorithm for
 * computational shock hydrodynamics.", Thesis, Swansea University, A. Barlow, 2002.
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


#endif /* SCALARMONOTONIC_H_ */
