/*
 * Velocity.h
 *
 * Class to manage the nodal velocity arrays in the simulation.
 *
 *  Created on: 3 Apr 2021
 *      Author: Mary-Ann Maheswaran
 */

#include "VectorProperty.h"
#include "Acceleration.h"

#ifndef VELOCITY_H_
#define VELOCITY_H_

class Velocity : public VectorProperty {

public:

    Velocity();
	void update(Acceleration &acceleration, double timestep);

};

Velocity::Velocity() {
    name = "Velocity";
}

/**
 * Update velocities using acceleration
 * @param acceleration
 * @param timestep
 */
void Velocity::update(Acceleration &acceleration, double timestep, int dim) {

	for (int i= 0; i < data.size(); i++) {

		data[i][dim] += accel.get(i,dim) * timestep;

	}
}





#endif /* VELOCITY_H_ */
