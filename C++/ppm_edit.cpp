/*
 * PPM_Edit Library (C++ Version)
 *
 * Version 0.1.0 (Last Updated: 2016-07-11)
 *
 * Description:
 *     Implements a custom data structure made to handle images. This structure
 *     relies on CN_Grids to operate. As they are practically for this kind of
 *     structure exclusively. You can manipulate colours, import, and export
 *     PPM files flawlessly. It even supports PGM and PBM files.
 *
 *     Changelog of library is located at the bottom of "ppm_edit.hpp".
 *
 * Author:
 *     Clara Van Nguyen
 * 
 * For documentation and details on every function in this library, visit the following URL:
 * http://web.eecs.utk.edu/~ssmit285/lib/ppm_edit/cpp/index.html
 */

#include "ppm_edit.hpp"

//Define the PPM Class
//Destructor
CNDS::PPM::~PPM() {
	//TODO: idk lol
}

//Get Functions
CNDS::cnpe_uint CNDS::PPM::width() {
	return _width;
}

CNDS::cnpe_uint CNDS::PPM::height() {
	return _height;
}

CNDS::cnpe_uint CNDS::PPM::size() {
	return _width * _height;
}

CNDS::IMG::PPM_RGB& CNDS::PPM::at(CNDS::cnpe_uint a, CNDS::cnpe_uint b) {
	return img.at(a, b);
}

CNDS::IMG::PPM_RGB* CNDS::PPM::data() {
	return img._data;
}

bool CNDS::PPM::empty() {
	return (_width * _height) == 0;
}

//Special Stuff
void CNDS::PPM::_set() {
	//Set the grid's image properties
	img._force_wipe(_width, _height);
}
