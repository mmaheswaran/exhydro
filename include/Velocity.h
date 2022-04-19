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
#include "Pressure.h"
#include "Mass.h"

#ifndef VELOCITY_H_
#define VELOCITY_H_

class Velocity : public VectorProperty {

public:

    Velocity();
	void update(Acceleration &acceleration, double timestep, int DIMS);
	void update(Pressure &pressure, Mass &mass, double timestep, int DIMS);

};

Velocity::Velocity() {
    name = "Velocity";
}

/**
 * Update velocities using acceleration
 * @param acceleration
 * @param timestep
 */
void Velocity::update(Acceleration &acceleration, double timestep, int DIMS) {

	for (int i= 0; i < data.size(); i++) {
	    for (int d = 0; d < DIMS; d++) {

	        data[i][d] += accel.get(i,d) * timestep;
	    }
	}
}

/**
 * Update velocities using pressure
 * @param acceleration
 * @param timestep
 */
void Velocity::update(Mesh &mesh, Pressure &pressure, Mass &mass, double timestep, int DIMS) {

    vector<double> divpress = mesh.calDiv(pressure);
    for (int i= 0; i < data.size(); i++) {
        for (int d = 0; d < DIMS; d++) {
            data[i][d] += accel.get(i,d) * timestep;
        }

    }
}





#endif /* VELOCITY_H_ */
