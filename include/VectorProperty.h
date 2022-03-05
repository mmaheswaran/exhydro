/*
 * VectorProperty.h
 *
 *  Created on: 3 Mar 2022
 *      Author: maryann
 */

#ifndef VECTORPROPERTY_H_
#define VECTORPROPERTY_H_

#include <vector>
#include <iostream>

class VectorProperty {

public:

    virtual ~VectorProperty() {}
    void init(int size, int noDims, double initValue);

    /**
     * Set initial value for a region.  Assign same value to all dimensions.
     */
    void setRegion(vector<int> regionInfo,
                   int region,
                   vector<vector<int> > el2nodemap,
                   double initValue);

    /**
     * Set initial value of a dimension for a region.  Assign specific value to one dimension.
     */
    void setRegion(vector<int> regionInfo,
                   int region,
                   vector<vector<int> > el2nodemap,
                   int dimension,
                   double initValue);

    vector<double>& get(int index) {return data[index];} //get
    double get(int index, int dimension);

    void set(const int index, const int dim, const double value); //set

    const string& getName() const {return name; }
    void setName(string newName);

    void print();

    void add(vector<double> values);

    int size();


protected:

    vector<vector<double> > data;
    string name;
    int DIMS;

};



#endif /* VECTORPROPERTY_H_ */
