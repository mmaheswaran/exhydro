/*
 * Volume.h
 *
 *  Created on: 3 Apr 2021
 *      Author: Mary-Ann Maheswaran
 */


#include "ScalarProperty.h"
#include "Mesh.h"

#ifndef VOLUME_H_
#define VOLUME_H_

class Volume : public ScalarProperty{

public:

    Volume();
	void update(Mesh &mesh);
    void print();
};

Volume::Volume() {
    name = "Volume";
}

/**
 * Updates the volume mesh terms.
 */
void Volume::update(Mesh &mesh) {

	for (int i= 0; i < data.size(); i++) {

		double volume = mesh.get_volume(i);

		assert(volume > 0 && "ERROR: volume 0 or negative.");
		data[i] = volume;
	}
}



#endif /* VOLUME_H_ */
