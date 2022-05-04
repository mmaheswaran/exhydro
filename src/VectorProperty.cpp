/*
 * VectorProperty.cpp
 *
 *  Created on: 3 Mar 2022
 *      Author: maryann
 */

#include <iostream>
#include "VectorProperty.h"

/**
 * Initialise vector array in all dimensions
 * @param size number of values in array
 * @param noDims number of dimensions in problem 1/2/3 D
 * @param initValue initial value of array
 *
 */
void VectorProperty::init(int size, int noDims, double initValue) {

    DIMS=noDims;

    data.resize(size);
    for (int i = 0; i < size; i++)
        data[i].resize(DIMS, initValue);

}

/**
 * Set initial value for a region.  Assign same value to all dimensions.
 * @param regionInfo array with region information
 * @param region region of interest
 * @param el2nodemap initial value of array
 * @param initValue initial value of array
 */
void VectorProperty::setRegion(vector<int> regionInfo,
        int region,
        vector<vector<int> > el2nodemap,
        double initValue) {

    for (int i= 0; i < el2nodemap.size(); i++) {
        if (regionInfo[i] == region) {
            for (int n = 0; n < el2nodemap[i].size(); n ++) {
                int node = el2nodemap[i][n];
                for (int d = 0; d < DIMS; d++) {
                    data[node][d] = initValue;
                }
            }
        }
    }
}


/**
 * Set initial value of a dimension for a region.  Assign specific value to one dimension.
 * @param regionInfo array with region information
 * @param region region of interest
 * @param el2nodemap initial value of array
 * @param dimension of interest
 * @param initValue initial value of array
 */
void VectorProperty::setRegion(vector<int> regionInfo,
        int region,
        vector<vector<int> > el2nodemap,
        int dimension,
        double initValue) {

    for (int i= 0; i < el2nodemap.size(); i++) {
        if (regionInfo[i] == region) {
            for (int n = 0; n < el2nodemap[i].size(); n ++) {
                int node = el2nodemap[i][n];
                for (int d = 0; d < DIMS; d++) {
                    if (d==dimension) {
                        data[node][d] = initValue;
                    }
                }
            }
        }
    }

}

/**
 * Get data at index and for a specific dimension
 * @param index of the property
 * @param dim dimension of interest 1/2/3 D
 */
double VectorProperty::get(const int index, const int dim) {

    return data[index][dim];


}


/**
 * Set data at index and for a specific dimension
 * @param index of the property
 * @param dim dimension of interest 1/2/3 D
 */
void VectorProperty::set(const int index, const int dim, const double value) {

    data[index][dim] = value;

}


/**
 * Set name of variable
 * @param newName
 */
void VectorProperty::setName(string newName) {

    name = newName;
}


/**
 * Add new value to array, for all vector dimensions.
 * @param values
 */
void VectorProperty::add(vector<double> values){

    data.push_back(values);

}


/**
 * Returm size of data array
 */
int * VectorProperty::size(){

    int sizes[2];
    sizes[0] = data.size();
    sizes[1] = data[0].size();
    return sizes;

}

/**
 * Print the contents of array.
 *
 */
void VectorProperty::print() {

  for (const auto &inner : data) {
         for (const auto &item : inner) {
             std::cout << item << " ";
         }

         std::cout << endl;
     }
     std::cout << endl;
}

