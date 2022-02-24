/*
 * PhysicalProperty.h
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

#ifndef PHYSICALPROPERTY_H_
#define PHYSICALPROPERTY_H_

class PhysicalProperty {

public:

	virtual ~PhysicalProperty() {}
	void init(int size, double initValue);

	void setRegion(vector<int> regionInfo, int region,double initValue);

	const vector<double>& getData() const { return data; }
    void setData(vector<double> values);

    const string& getName() const {return name; }
    void setName(string newName);

	virtual void print() = 0;

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
