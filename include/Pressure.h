/*
 * Pressure.h
 *
 * Manages the pressure objects and calls EOS
 *
 *  Created on: 7 Apr 2021
 *      Author: Mary-Ann Maheswaran
 */


#include "ScalarProperty.h"
#include "Density.h"
#include "Energy.h"

#ifndef PRESSURE_H_
#define PRESSURE_H_


class Pressure : public ScalarProperty {


public:

    Pressure();
	void updatePressure(Density &density, Energy &energy);
	void print();

};

Pressure::Pressure() {
    name = "Pressure";
}

/**
 * EOS substitute for now
 */
void Pressure::updatePressure(Density &density, Energy &energy) {


	for (int i= 0; i < data.size(); i++) {
		data[i] = density.get(i) * energy.get(i) * (1.4 - 1); //random ideal EOS, need getEOS call
	}
}

#endif /* PRESSURE_H_ */
