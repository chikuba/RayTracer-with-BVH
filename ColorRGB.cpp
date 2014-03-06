#ifndef COLOR_H_INCLUDED
#include "ColorRGB.h"
#endif

ColorRGB::ColorRGB() {
    this->red_f   = 
    this->green_f =
    this->blue_f  = 0.0f;
}

ColorRGB::ColorRGB(const float &red, const float &green, const float &blue) {
	this->red_f   = red;
	this->green_f = green;
	this->blue_f  = blue;
}

ColorRGB::~ColorRGB() {}

ColorRGB ColorRGB::operator+=(const ColorRGB &color) {
	this->red_f   += color.red_f;
	this->green_f += color.green_f;
	this->blue_f  += color.blue_f;
	
    return *this;
}

bool ColorRGB::operator!=(const ColorRGB &color) const {
    if((this->red_f != color.red_f) || (this->green_f != color.green_f) || (this->blue_f != color.blue_f)) {
		
        return true;
		
    } else return false;
}

ColorRGB ColorRGB::operator*(const ColorRGB &color) {
	ColorRGB temp_c(*this);
	
	temp_c.red_f   *= color.red_f;
	temp_c.green_f *= color.green_f;
	temp_c.blue_f  *= color.blue_f;
	
	return temp_c;
}

ColorRGB ColorRGB::operator*(const float &f) {
	ColorRGB temp_c(*this);
	
	temp_c.red_f   *= f;
	temp_c.green_f *= f;
	temp_c.blue_f  *= f;
	
	return temp_c;
}

// never go outside the allowed values
void ColorRGB::Control() {
	this->red_f   = Encode(Math::Min(this->red_f, 1.0f));
	this->green_f = Encode(Math::Min(this->green_f, 1.0f));
	this->blue_f  = Encode(Math::Min(this->blue_f, 1.0f));
}
