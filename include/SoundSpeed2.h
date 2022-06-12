/*
 * SoundSpeed.h
 *
 * Manages the sound speed objects and calls EOS
 *
 *  Created on: 10 Apr 2021
 *      Author: Mary-Ann Maheswaran
 */

#include <iostream>

#include "ScalarProperty.h"
#include "Energy.h"

#ifndef SOUNDSPEED_H_
#define SOUNDSPEED_H_


class SoundSpeed2 : public ScalarProperty {


public:

    SoundSpeed2();
    void update(Energy &energy);
    void print();

};


SoundSpeed2::SoundSpeed2() {
    name = "SoundSpeed2";
}

/**
 * EOS substitute for now
 */
void SoundSpeed2::update(Energy &energy) {


    for (int i= 0; i < data.size(); i++) {
        double eint = energy.get(i); //random ideal EOS need getEOS call
        double gamma = 1.4;
        data[i] = gamma * (gamma - 1.) * eint;
    }
}





#endif /* SOUNDSPEED_H_ */
