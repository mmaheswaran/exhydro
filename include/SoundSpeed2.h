/*
 * SoundSpeed.h
 *
 * Manages the sound speed objects and calls EOS
 *
 *  Created on: 10 Apr 2021
 *      Author: Mary-Ann Maheswaran
 */

#include <iostream>
#include "PhysicalProperty.h"

#ifndef SOUNDSPEED_H_
#define SOUNDSPEED_H_


class SoundSpeed2 : public PhysicalProperty {


public:

    SoundSpeed2();
    void updateSoundSpeed(const vector<double> &energy);
    void print();

};


SoundSpeed2::SoundSpeed2() {
    name = "SoundSpeed2";
}

/**
 * EOS substitute for now
 */
void SoundSpeed2::updateSoundSpeed(const vector<double> &energy) {


    for (int i= 0; i < data.size(); i++) {
        double eint = energy[i]; //random ideal EOS need getEOS call
        double gamma = 1.4;
        data[i] = gamma * (gamma - 1.) * eint;
    }
}


/**
 * Print the contents of array.
 *
 */
void SoundSpeed2::print() {

    vector<double>::iterator it;
    std::cout << "Sound speed squared:\n";
    for (it = data.begin(); it != data.end(); ++it) {
        std::cout<<*it<<" ";
    }
    std::cout << "\n";

}



#endif /* SOUNDSPEED_H_ */
