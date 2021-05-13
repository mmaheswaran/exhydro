/*
 * Volume.h
 *
 *  Created on: 3 Apr 2021
 *      Author: maryann
 */

#include <cassert>
#include "PhysicalProperty.h"

#ifndef VOLUME_H_
#define VOLUME_H_

class Volume : public PhysicalProperty{

public:

	void update(Mesh &mesh);
private:
	vector<double> data;

};

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


#endif /* VOLUME_H_ */
