/*
 * ArtificialViscosity.h
 *
 *  Created on: 21 May 2021
 *      Author: Mary-Ann Maheswaran
 */

#include <vector>
#include <stdexcept>
#include "Pressure.h"
using namespace std;

#ifndef ARTIFICIALVISCOSITY_H_
#define ARTIFICIALVISCOSITY_H_

class ArtificialViscosity {

public:

	virtual ~ArtificialViscosity() {}
	double get(int index);
	void set(int index, double value);
	void add(double value);

	void dampen_shocks(Pressure &pressure);

	int size();
	void print();

protected:
	vector<double> artificialVisc;


};

/**
 * Get artificial viscosity at index
 * @param index
 */
double ArtificialViscosity::get(int index) {

	return artificialVisc[index];
}

/**
 * Set artificial viscosity at index
 * @param index
 * @param value
 */
void ArtificialViscosity::set(int index, double value) {

	artificialVisc[index] = value;
}

/**
 * Returns size of data structure.
 *
 */
int ArtificialViscosity::size() {

	return artificialVisc.size();

}

/**
 * Add artificial viscosity
 */
void dampen_shocks(Pressure &pressure) {

    if(pressure.size() != artificialVisc.size()) {
        throw std::length_error( "Artifical viscosity and pressure data different sizes!" );
    }
    for(int i=0; i < pressure.size(); i++) {
        pressure.addto(i, artificialVisc[i]);
    }


}


#endif /* ARTIFICIALVISCOSITY_H_ */
