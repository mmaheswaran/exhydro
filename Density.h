/*
 * Density.h
 *
 * Class to manage the density arrays in the simulation.
 *
 *  Created on: 30 Mar 2021
 *      Author: maryann
 */

#include "PhysicalProperty.h"

#ifndef DENSITY_H_
#define DENSITY_H_

class Density : public PhysicalProperty {

public:

	void update(vector<double> &mass, vector<double> &volume);
	void print();

};


/**
 * Updates the masses.
 * @param mass
 * @param volume
 */
void Density::update(vector<double> &mass, vector<double> &volume) {

	for (int i= 0; i < data.size(); i++) {
		data[i] = mass[i] / volume[i];
	}
}


/**
 * Print the contents of array.
 *
 */
void Density::print() {

   vector<double>::iterator it;
   cout << "Density: ";
   for (it = data.begin(); it != data.end(); ++it) {
       cout<<*it<<" ";
   }
   cout << "\n";

}

#endif /* DENSITY_H_ */
