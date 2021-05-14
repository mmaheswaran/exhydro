/*
 * Energy.h
 *
 *  Created on: 13 Apr 2021
 *      Author: Mary-Ann Maheswaran
 */

#include "PhysicalProperty.h"

#ifndef PHYSICS_ENERGY_H_
#define PHYSICS_ENERGY_H_

class Energy : public PhysicalProperty {

public:

	void update(vector<double> &force,
				vector<double> &velocity,
				vector<double> &mass,
			    double masscut,
				double timestep,
			    int nvertices,
				vector< vector<int> > &el2nodmap);
	void print();

};

/**
 * Updates the energy using compatible hydro scheme.
 * @param force - node centred
 * @param velocity - node centred
 * @param mass - element centred
 * @param masscut - mass cutoff, avoid divide by zero
 * @param timestep
 * @param nvertices - number of vertices in an element
 * @param el2nodmap - map element number to node number
 */
void Energy::update(vector<double> &force,
					vector<double> &velocity,
					vector<double> &mass,
					double masscut,
					double timestep,
					int nvertices,
					vector< vector<int> > &el2nodmap)
{
	for (int el= 0; el < mass.size(); el++) {
		for (int v = 0; v < nvertices; v++) {

			int node = el2nodmap[el][v];
			double m = std::max(mass[el], masscut);

			data[el] += -(force[node] * velocity[node]) * timestep / m;
		}
	}

}

/**
 * Print the contents of array.
 *
 */
void Energy::print() {

   vector<double>::iterator it;
   cout << "Energy: ";
   for (it = data.begin(); it != data.end(); ++it) {
       cout<<*it<<" ";
   }
   cout << "\n";

}
#endif /* PHYSICS_ENERGY_H_ */
