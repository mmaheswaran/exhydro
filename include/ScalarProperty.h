/*
 * ScalarProperty.h
 *
 * Container class for physical properties
 *
 * Abstract class for physical properties.
 *  Created on: 29 Mar 2021
 *      Author: Mary-Ann Maheswaran
 */

#include <vector>
#include <string>
using namespace std;

#ifndef SCALARPROPERTY_H_
#define SCALARPROPERTY_H_

class ScalarProperty {

public:

	virtual ~ScalarProperty() {}
	void init(int size, double initValue);

	void setRegion(vector<int> regionInfo, int region,double initValue);

	const vector<double>& getData() const { return data; }
    void setData(vector<double> values);

    const string& getName() const {return name; }
    void setName(string newName);

	void print();

	double get(int index);
	void set(int index, double value);
	void add(vector<double> values);
	void add(double value);

	int size();

protected:

	vector<double> data;
    string name;
};



#endif /* PHYSICALPROPERTY_H_ */
