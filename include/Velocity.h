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
	void print();

};

Velocity::Velocity() {
    name = "Velocity";
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


/**
 * Print the contents of array.
 *
 */
void Velocity::print() {

  vector<double>::iterator it;
  std::cout << "Nodal velocity:\n";
  for (it = data.begin(); it != data.end(); ++it) {
    std::cout<<*it<<" ";
  }
  std::cout << "\n";

}



#endif /* VELOCITY_H_ */
