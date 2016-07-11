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
 *     This is a template definitions file (*.tpp). Appended to the end of
 *     ppm_edit.hpp. Do not add it to the compiler as if it was a *.cpp file.
 *     The g++ compiler will do it on its own.
 *
 *     Changelog of library is located at the bottom of "ppm_edit.hpp"
 * 
 * Author:
 *     Clara Van Nguyen
 * 
 * For documentation and details on every function in this library, visit the following URL:
 * http://web.eecs.utk.edu/~ssmit285/lib/ppm_edit/cpp/index.html
 */

#ifndef __PPM_EDIT_CPP_T_HAN__
#define __PPM_EDIT_CPP_T_HAN__

#include "ppm_edit.hpp"

//using namespace CNDS;

#define __PPM_TEMPLATE \
	template <typename T>

//CN_SGrid Class
//Destructor
__PPM_TEMPLATE CNDS::CN_SGrid<T>::~CN_SGrid() {
	//Prevent memory leaks.
	free(_data);
}

//Get Functions
__PPM_TEMPLATE CNDS::cnpe_uint CNDS::CN_SGrid<T>::sizex() {
	//Returns the horizontal size of the grid.
	return xsize;
}

__PPM_TEMPLATE CNDS::cnpe_uint CNDS::CN_SGrid<T>::sizey() {
	//Returns the vertical size of the grid.
	return ysize;
}

__PPM_TEMPLATE CNDS::cnpe_uint CNDS::CN_SGrid<T>::size() {
	//Returns the total slots usable in the grid.
	return xsize * ysize;
}

__PPM_TEMPLATE T& CNDS::CN_SGrid<T>::at(cnpe_uint a, cnpe_uint b) {
	//Returns a reference to a data entry at a certain point.
	return *((T*)_data + ((b * xsize) + a));
}

__PPM_TEMPLATE T* CNDS::CN_SGrid<T>::data() {
	//Returns a pointer to the actual data itself.
	return data;
}

__PPM_TEMPLATE bool CNDS::CN_SGrid<T>::empty() {
	//Tells whether or not the grid is empty.
	return (xsize * ysize) == 0;
}

//Special Stuff
__PPM_TEMPLATE void CNDS::CN_SGrid<T>::_force_wipe(cnpe_uint a, cnpe_uint b) {
	//Wipes the table and sets it to a new size
	free(_data);
	xsize = a;
	ysize = b;
	_set();
}

__PPM_TEMPLATE void CNDS::CN_SGrid<T>::_set() {
	//Set memory up.
	//NOTE: Once this is set up, it can not be modified. Hence "simple" grid.
	_data = (T*) malloc(sizeof(T) * xsize * ysize);
}

#endif
