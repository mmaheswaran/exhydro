/*
 * ScalarProperty.h
 *
 * Container class for physical properties
 *
 * Abstract class for physical properties.
 *  Created on: 29 Mar 2021
 *      Author: Mary-Ann Maheswaran
 */

#include <cassert>
#include <vector>
#include <string>
using namespace std;

#ifndef SCALARPROPERTY_H_
#define SCALARPROPERTY_H_

class ScalarProperty {

public:

    ScalarProperty::ScalarProperty(const ScalarProperty &obj);
	virtual ~ScalarProperty() {}
	void init(int size, double initValue);

	void set_region(vector<int> regionInfo, int region,double initValue);

	const vector<double>& get_data() const { return data; }
    void set_data(vector<double> values);

    const string& get_name() const {return name; }
    void set_name(string newName);

	void print();

	double get(int index);
	void set(int index, double value);

	void add(vector<double> values);
	void add(double value);
	void addto(int index, double value);

	int size() {return data.size()};



protected:

	vector<double> data;
    string name;
};



#endif /* PHYSICALPROPERTY_H_ */
