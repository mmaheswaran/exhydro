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
	            Mass &nodalmass,
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
 * @param nodalmass at cell corners
 */
void Acceleration::update(Force &force,
						  Mass &nodalmass,
						  vector<double> &area,
                          int dim,
						  double densitycut) {

	for (int n= 0; n < data.size(); n++) {
		double minmass = densitycut * area(n);
		data[n] = nodalmass[n] > minmass ? force[n] / nodalmass[n] : 0.0;
	}
}



#endif /* ACCELERATION_H_ */
