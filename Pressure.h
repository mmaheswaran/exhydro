/*
 * Pressure.h
 *
 * Manages the pressure objects and calls EOS
 *
 *  Created on: 7 Apr 2021
 *      Author: maryann
 */


#include "PhysicalProperty.h"

#ifndef PRESSURE_H_
#define PRESSURE_H_


class Pressure : public PhysicalProperty {


public:

	void updatePressure(const vector<double> &density, const vector<double> &energy);
	void print();

};


/**
 * EOS substitute for now
 */
void Pressure::updatePressure(const vector<double> &density, const vector<double> &energy) {


	for (int i= 0; i < data.size(); i++) {
		data[i] = density[i] * energy[i] * (1.4 - 1); //random thing need getEOS call
	}
}

/**
 * Print the contents of array.
 *
 */
void Pressure::print() {

   vector<double>::iterator it;
   cout << "Pressure: ";
   for (it = data.begin(); it != data.end(); ++it) {
       cout<<*it<<" ";
   }
   cout << "\n";

}

#endif /* PRESSURE_H_ */
