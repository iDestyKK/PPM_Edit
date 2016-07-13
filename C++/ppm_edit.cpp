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
//Constructor
CNDS::PPM::PPM(const char* fname) {
	open(fname);
}

//Destructor
CNDS::PPM::~PPM() {
	//TODO: idk lol
}

//Open Functions
void CNDS::PPM::open(const char* fname) {
	//Opens a PPM, PGM, or PBM file based on their first 2 bytes.
	FILE* fp = fopen(fname, "rb");
	if (fp == NULL)
		return; //You failed.
	cnpe_byte header[3];
	header[2] = '\0';
	fread(header, 1, 2, fp);
	printf("%s\n", header);
	
	cnpe_byte _mode = header[1] - 0x30;

	if (header[0] != 'P' || _mode > 6)
		return; //Header Fail
	
	if (_mode < 0x4)
		fclose(fp);
	else {
		//Go on and get the width and height IF the file is Binary...
		ifstream _fp(fname);
		std::string garbage;
		_fp >> garbage >> _width >> _height;
		_fp.close();
		_set();
	}

	//Now for the fun
	switch (_mode) {
		case 0x1: _open_pbm_ascii (fname); break; //PBM ASCII
		case 0x2: _open_pgm_ascii (fname); break; //PGM ASCII
		case 0x3: _open_ppm_ascii (fname); break; //PPM ASCII
		case 0x4: _open_pbm_binary(fp   ); break; //PBM BINARY
		case 0x5: _open_pgm_binary(fp   ); break; //PGM BINARY
		case 0x6: _open_ppm_binary(fp   ); break; //PPM BINARY
	}
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

void CNDS::PPM::_open_ppm_ascii(const char* fname) {
	//P3
	ifstream fp(fname);
	if (fp.fail()) return;
	std::string garbage;
	cnpe_uint _range;
	fp >> garbage >> _width >> _height >> _range;
	_set();
	for (cnpe_uint i = 0; i < _width * _height; i++) {
		IMG::PPM_RGB& _REF = at(i % _width, i / _width);
		cnpe_uint r, g, b;
		fp >> r >> g >> b;
		_REF.R = (cnpe_byte)r;
		_REF.G = (cnpe_byte)g;
		_REF.B = (cnpe_byte)b;
	}

	fp.close();
}

void CNDS::PPM::_open_pgm_ascii(const char* fname) {
	//P2
	ifstream fp(fname);
	if (fp.fail()) return;
	std::string garbage;
	cnpe_uint _range;
	fp >> garbage >> _width >> _height >> _range;
	_set();
	for (cnpe_uint i = 0; i < _width * _height; i++) {
		IMG::PPM_RGB& _REF = at(i % _width, i / _width);
		cnpe_uint c;
		fp >> c;
		c *= (0xFF / _range);
		_REF.R = (cnpe_byte)c;
		_REF.G = (cnpe_byte)c;
		_REF.B = (cnpe_byte)c;
	}

	fp.close();
}

void CNDS::PPM::_open_pbm_ascii(const char* fname) {
	//P1
	ifstream fp(fname);
	if (fp.fail()) return;
	std::string garbage;
	fp >> garbage >> _width >> _height;
	_set();
	for (cnpe_uint i = 0; i < _width * _height; i++) {
		IMG::PPM_RGB& _REF = at(i % _width, i / _width);
		cnpe_uint c;
		fp >> c;
		c = (c == 1) ? 0x00 : 0xFF;
		_REF.R = (cnpe_byte)c;
		_REF.G = (cnpe_byte)c;
		_REF.B = (cnpe_byte)c;
	}

	fp.close();
}

void CNDS::PPM::_open_ppm_binary(FILE* fp) {
	//P6
	//This one is literally the EASIEST one to process...
	//Get size of the file
	fseek(fp, (size_t)0, SEEK_END);
	cnpe_uint __sz = ftell(fp);
	rewind(fp);

	cnpe_uint _c = 0;
	while (_c != 3)
		if (fgetc(fp) == 0x0A) _c++;
	__sz -= ftell(fp);

	//Now to read bytes...
	fread(data(), 1, __sz, fp);
	fclose(fp);
}

void CNDS::PPM::_open_pgm_binary(FILE* fp) {
	//P5
	//Get size of the file
	fseek(fp, (size_t)0, SEEK_END);
	cnpe_uint __sz = ftell(fp);
	rewind(fp);

	cnpe_uint _c = 0;
	while (_c != 3)
		if (fgetc(fp) == 0x0A) _c++;
	__sz -= ftell(fp);

	//Now to read bytes...
	cnpe_byte* _tmp = (cnpe_byte *) malloc(__sz);
	fread(_tmp, 1, __sz, fp);
	for (_c = 0; _c < __sz; _c++) {
		IMG::PPM_RGB& _TMP = at(_c % _width, _c / _width);
		_TMP.R = _tmp[_c];
		_TMP.G = _tmp[_c];
		_TMP.B = _tmp[_c];
	}
	free(_tmp);
	fclose(fp);
}

void CNDS::PPM::_open_pbm_binary(FILE* fp) {
	//P4
	//Get size of the file
	fseek(fp, (size_t)0, SEEK_END);
	cnpe_uint __sz = ftell(fp);
	rewind(fp);

	cnpe_uint _c = 0, c;
	while (_c != 3)
		if (fgetc(fp) == 0x0A) _c++;
	__sz -= ftell(fp);

	//Now to read bytes...
	cnpe_byte* _tmp = (cnpe_byte *) malloc(__sz);
	fread(_tmp, 1, __sz, fp);
	for (_c = 0; c < __sz; _c++) {
		IMG::PPM_RGB& _TMP = at(_c % _width, _c / _width);
		c = (_tmp[_c] == 1) ? 0x00 : 0xFF ;
		_TMP.R = c;
		_TMP.G = c;
		_TMP.B = c;
	}
	fclose(fp);
}
