/*
 * Acceleration.h
 *
 * Class to manage the acceleration arrays in the simulation.
 *
 *  Created on: 10 Apr 2021
 *      Author: Mary-Ann Maheswaran
 */
#include "PhysicalProperty.h"

#ifndef ACCELERATION_H_
#define ACCELERATION_H_


class Acceleration : public PhysicalProperty {

public:

    Acceleration();
	void update(vector<double> &force,vector<double> &nodalmass, vector<double> &nodalarea, double densitycut);
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
void Acceleration::update(vector<double> &force,
						  vector<double> &nodalmass,
						  vector<double> &nodalarea,
						  double densitycut) {

	for (int n= 0; n < data.size(); n++) {
		double minmass = densitycut * nodalarea(n);
		data[n] = nodalmass[n] > minmass ? force[n] / nodalmass[n] : 0.0;
	}
}


/**
 * Print the contents of array.
 *
 */
void Acceleration::print() {

   vector<double>::iterator it;
   cout << "Acceleration: ";
   for (it = data.begin(); it != data.end(); ++it) {
       cout<<*it<<" ";
   }
   cout << "\n";

}

#endif /* ACCELERATION_H_ */
