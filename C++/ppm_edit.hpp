/*
 * PPM_Edit Library (C++ Version)
 *
 * Version 0.1.0 (Last Updated: 2016-07-11)
 *
 * Description:
 *     Implements a custom data structure made to handle images. This structure
 *     relies on CN_SGrids to operate. As they are practically for this kind of
 *     structure exclusively. You can manipulate colours, import, and export
 *     PPM files flawlessly. It even supports PGM and PBM files.
 *
 *     NOTE: CN_SGrids are defined as well and are a simplified version of
 *     CN_Grids exclusively for this library.
 *
 *     Changelog of library is located at the bottom of this file.
 * 
 * Author:
 *     Clara Van Nguyen
 * 
 * For documentation and details on every function in this library, visit the following URL:
 * http://web.eecs.utk.edu/~ssmit285/lib/ppm_edit/cpp/index.html
 */

#ifndef __PPM_EDIT_CPP_HAN__
#define __PPM_EDIT_CPP_HAN__

//C++ Includes
#include <utility>

//C Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

namespace CNDS {
	//Extend the CN Data Structure Namespace
	typedef unsigned int  cnpe_uint;
	typedef unsigned char cnpe_byte;

	namespace IMG {
		//Structs for PPM Colours
		struct PPM_RGB {
			//Constructors/Initialisation Lists
			PPM_RGB():
				R(0), G(0), B(0) {};
			PPM_RGB(cnpe_byte a, cnpe_byte b, cnpe_byte c):
				R(a), G(b), B(c) {};

			//Data
			cnpe_byte R, G, B;
		};
	}

	//Simple Grid Data Structure
	template <typename T>
	class CN_SGrid {
		friend class PPM;
		public:
			//Constructors/Initialisation Lists
			CN_SGrid():
				xsize(0), ysize(0) { _set(); };
			CN_SGrid(cnpe_uint a, cnpe_uint b):
				xsize(a), ysize(b) { _set(); };
			
			//Destructor
			~CN_SGrid();

			//Get Functions
			cnpe_uint sizex();
			cnpe_uint sizey();
			cnpe_uint size ();
			T& at(cnpe_uint, cnpe_uint);
			T* data();
			bool empty();

			//Set Functions
		private:
			//Special Stuff
			void _force_wipe(cnpe_uint, cnpe_uint);
			void _set();

			//Data
			cnpe_uint xsize, ysize;
			T* _data;
	};
		
	//PPM Image Structure
	class PPM {
		public:
			//Constructors/Initialisation Lists
			PPM():
				_width(0), _height(0) { _set(); };
			PPM(cnpe_uint a, cnpe_uint b):
				_width(a), _height(b) { _set(); };

			//Destructor
			~PPM();
			
			//Get Functions
			cnpe_uint     width ();
			cnpe_uint     height();
			cnpe_uint     size  ();
			IMG::PPM_RGB& at    (cnpe_uint, cnpe_uint);
			IMG::PPM_RGB* data  ();
			bool          empty ();
		private:
			//Special Stuff
			void _set();

			//Data
			cnpe_uint _width, _height;
			CN_SGrid<IMG::PPM_RGB> img;

		protected:

	};
}

#include "ppm_edit.tpp" //To get the compiler to shut up

#endif

/****************************************\
    * ** ***    CHANGELOG    *** ** *
\****************************************/

/*
	2016-07-11 (0.1.0)
	  - Started writing PPM_Edit (C++ Version)
*/
