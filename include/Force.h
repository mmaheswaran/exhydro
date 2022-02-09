/*
 * Force.h
 *
 * Class to manage the A. Barlow's compatible hydro force array.
 *
 *  Created on: 12 Apr 2021
 *      Author: Mary-Ann Maheswaran
 */
#include "PhysicalProperty.h"

#ifndef FORCE_H_
#define FORCE_H_

class Force : public PhysicalProperty {

public:

	void update(const vector<double> &pressure, const std::vector<double> &area,
				int nvertices, const vector< vector<int> > &el2nodmap);
	void print();

};

/**
 * Updates the force using pressure and area.
 * @param pressure - element centred
 * @param area - nodal area derived from isoparametrics
 * @param el2nodmap - element number to node number map
 */
void Force::update(const vector<double> &pressure,
				   std::vector<double> &area,
				   int nvertices,
				   const vector< vector<int> > &el2nodmap) {

	for (int el= 0; el < pressure.size(); el++) {
		for (int v = 0; v < nvertices; v++) {
			int node = el2nodmap[el][v];
			data[node] = pressure[el] * area[node];
		}

	}
}

/**
 * Print the contents of array.
 *
 */
void Force::print() {

   vector<double>::iterator it;
   cout << "Force: ";
   for (it = data.begin(); it != data.end(); ++it) {
       cout<<*it<<" ";
   }
   cout << "\n";

}


#endif /* FORCE_H_ */
