/*
 * ArtificialViscosity.h
 *
 *  Created on: 21 May 2021
 *      Author: Mary-Ann Maheswaran
 */

#include <vector>
using namespace std;

#ifndef ARTIFICIALVISCOSITY_H_
#define ARTIFICIALVISCOSITY_H_

class ArtificialViscosity {

public:

	void calcArtificialViscosity();
	vector<double> artificialVisc(int index) {return _artificialVisc[index];} //get

private:



};



#endif /* ARTIFICIALVISCOSITY_H_ */
