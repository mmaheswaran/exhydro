/*
 * Mass.h
 *
 * Class to manage the mass arrays in the simulation.
 *
 *  Created on: 24 Mar 2021
 *      Author: Mary-Ann Maheswaran
 */
#include "PhysicalProperty.h"

#ifndef MASS_H_
#define MASS_H_

class Mass : public PhysicalProperty {

public:

    Mass();
	void update(vector<double> &density, vector<double> &volume);
	void print();

};

Mass::Mass() {
    name = "Mass";
}

/**
 * Updates the masses.
 * @param density
 * @param volume
 */
void Mass::update(vector<double> &density, vector<double> &volume) {

	for (int i= 0; i < data.size(); i++) {
		data[i] = density[i] * volume[i];
	}
}

/**
 * Print the contents of array.
 *
 */
void Mass::print() {

   vector<double>::iterator it;
   cout << "Mass:\n";
   for (it = data.begin(); it != data.end(); ++it) {
       cout<<*it<<" ";
   }
   cout << "\n";

}


#endif /* MASS_H_ */
