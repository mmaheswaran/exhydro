/*
 * Volume.h
 *
 *  Created on: 3 Apr 2021
 *      Author: Mary-Ann Maheswaran
 */

#include <cassert>
#include "PhysicalProperty.h"

#ifndef VOLUME_H_
#define VOLUME_H_

class Volume : public PhysicalProperty{

public:

    Volume();
	void update(Mesh &mesh);
    void print();
private:
	vector<double> data;

};

Volume::Volume() {
    name = "Volume";
}

/**
 * Updates the volume mesh terms.
 */
void Volume::update(Mesh &mesh) {

	for (int i= 0; i < data.size(); i++) {

		double volume = mesh.getVolume(i);

		assert(volume > 0 && "ERROR: volume 0 or negative.");
		data[i] = volume;
	}
}

/**
 * Print the contents of array.
 *
 */
void Volume::print() {

    vector<double>::iterator it;
    std::cout << "Volume of elements:\n";
    for (it = data.begin(); it != data.end(); ++it) {
        std::cout<<*it<<" ";
    }
    std::cout << "\n";

}


#endif /* VOLUME_H_ */
