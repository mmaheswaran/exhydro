/*
 * ScalarProperty.cpp
 *
 *  Created on: 20 Feb 2022
 *      Author: maryann
 */


#include <iostream>
#include "ScalarProperty.h"

/**
 * Copy constructor
 */
ScalarProperty::ScalarProperty(const ScalarProperty &obj) {

    for (int i= 0; i < obj.size(); i++) {
        data.push_back(obj.get(i));
    }
}

/**
 * Initialises data array.  Will re-initialise by clearing any existing elements first.
 * @param size the number of element needed in data array
 * @param initValue the initial value of the data array
 */
void ScalarProperty::init(int size, double initValue) {

    data.resize(size, initValue);
}

void ScalarProperty::setRegion(vector<int> regionInfo, int region, double initValue) {

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
double ScalarProperty::get(int index) {

    return data[index];
}

/**
 * Set data at index
 * @param index
 * @param value
 */
void ScalarProperty::set(int index, double value) {

    data[index] = value;
}


/**
 * Set data to new values
 * @param values from another vector
 */
void ScalarProperty::setData(std::vector<double> values) {

    data = values;
}

/**
 * Set new name of physical property
 * @param newName
 */
void ScalarProperty::setName(string newName) {

    name = newName;
}

/**
 * Adds new to existing values
 * @param values
 */
void ScalarProperty::add(std::vector<double> values) {

    for (int i= 0; i < values.size(); i++) {
            data.push_back(values[i]);
    }
}

/**
 * Push new value to back of data array.
 * @param value
 */
void ScalarProperty::add(double value) {

    data.push_back(value);
}


void ScalarProperty::addTo(int index, double value) {
    assert(data.size() < index+1 && "ERROR: Tried to add to existing data, but no entry exists.");
    data[index] += value;
}


/**
 * Print the contents of array.
 *
 */
void ScalarProperty::print() {

    vector<double>::iterator it;
    cout << this.name << ":"\n";
    for (it = data.begin(); it != data.end(); ++it) {
        cout<<*it<<" ";
    }
    cout << "\n";

}


