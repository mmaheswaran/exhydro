/*
 * Acceleration.h
 *
 * Class to manage the acceleration arrays in the simulation.
 *
 *  Created on: 10 Apr 2021
 *      Author: Mary-Ann Maheswaran
 */
#include "ScalarProperty.h"
#include "Force.h"
#include "Mass.h"

#ifndef ACCELERATION_H_
#define ACCELERATION_H_


class Acceleration : public ScalarProperty {

public:

    Acceleration();
	void update(Force &force,
	            Mass &mass,
	            vector<double> &area,
                int dim,
	            double densitycut);
	void print();

};

Acceleration::Acceleration() {
    name = "Acceleration";
}

/**
 * Updates the acceleration arrays.
 * @param force
 * @param mass
 * @param area
 * @param dimension to update
 * @param density cut-off
 */
void Acceleration::update(Force &force,
						  Mass &mass,
						  vector<double> &area,
						  double densitycut) {

    int size[2] = force.size();
    int n = size[0];
    int DIMS = size[1];
	for (int i= 0; i < n; i++) {
		double minmass = densitycut * area(i);
		for (int d = 0; d < DIMS; d++) {
		    data[i][d] = mass.get(i) > minmass ? force.get(i,d) / mass.get(i) : 0.0;
		}
	}
}



#endif /* ACCELERATION_H_ */
