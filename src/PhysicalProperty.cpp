/*
 * PhysicalProperty.cpp
 *
 *  Created on: 20 Feb 2022
 *      Author: maryann
 */


#include "PhysicalProperty.h"
#include <iostream>

/**
 * Initialises data array.  Will re-initialise by clearing any existing elements first.
 * @param size the number of element needed in data array
 * @param initValue the initial value of the data array
 */
void PhysicalProperty::init(int size, double initValue) {

    data.resize(size, initValue);
}

void PhysicalProperty::setRegion(vector<int> regionInfo, int region, double initValue) {

    for (int i= 0; i < data.size(); i++) {
        if (regionInfo[i] == region) {
            data[i] = initValue;

        }
    }
}

/**
 * Get data at index
 * @param index
 */
double PhysicalProperty::get(int index) {

    return data[index];
}

/**
 * Set data at index
 * @param index
 * @param value
 */
void PhysicalProperty::set(int index, double value) {

    data[index] = value;
}


/**
 * Set data to new values
 * @param values from another vector
 */
void PhysicalProperty::setData(std::vector<double> values) {

    data = values;
}

/**
 * Set new name of physical property
 * @param newName
 */
void PhysicalProperty::setName(string newName) {

    name = newName;
}

/**
 * Adds new to existing values
 * @param values
 */
void PhysicalProperty::add(std::vector<double> values) {

    for (int i= 0; i < values.size(); i++) {
            data.push_back(values[i]);
    }
}

/**
 * Push new value to back of data array.
 * @param value
 */
void PhysicalProperty::add(double value) {

    data.push_back(value);
}

/**
 * Returns size of data structure.
 *
 */
int PhysicalProperty::size() {

    return data.size();

}



