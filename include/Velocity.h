/*
 * Velocity.h
 *
 * Class to manage the nodal velocity arrays in the simulation.
 *
 *  Created on: 3 Apr 2021
 *      Author: Mary-Ann Maheswaran
 */

#include "PhysicalProperty.h"

#ifndef VELOCITY_H_
#define VELOCITY_H_

class Velocity : public PhysicalProperty {

public:

    Velocity();
	void update(vector<double> &acceleration, double timestep);

};

Velocity::Velocity() {
    name = "Volume";
}

/**
 * Update velocities using acceleration
 * @param acceleration
 * @param timestep
 */
void Velocity::update(vector<double> &acceleration, double timestep) {

	for (int i= 0; i < data.size(); i++) {

		data[i] = data[i] + acceleration[i] * timestep;

	}
}




#endif /* VELOCITY_H_ */
