#pragma once

#include <iostream>
#include <string>
#include <easyx.h>
#include "Color.h"

#if UNICODE
using String = std::wstring;
#else
using String = std::string;
#endif

class Device;
class Image {
	friend class Device;
public:
	Image(const Image&) = delete;

	Image(const String& path) {
		IMAGE img;

		loadimage(&img, path.c_str());

		if (img.getwidth() == 0 || img.getheight() == 0) {
			std::cout << path.c_str() << " open failed;\n";
			return;
		}

		_width = img.getwidth();
		
		_height = img.getheight();

		int max = _width * _height;
		
		_buffer = new Color[max];
		
		DWORD* src = GetImageBuffer(&img);

		BYTE a = 0, r = 0, g = 0, b = 0;

		for (int i = 0; i < max; i++){
			a = BYTE(src[i] >> 24);
			b = BYTE(src[i] >> 16);
			g = BYTE(src[i] >> 8);
			r = BYTE(src[i]);
			
			_buffer[i] = Color(r, g, b, a);
		}
	}

	Image(int w, int h, const Color& color) {
		_width = w;
		_height = h;
		int max = w * h;
		if (max == 0) {
			return;
		}
		_buffer = new Color[max];
		for (int i = 0; i < max; i++) {
			_buffer[i] = color;
		}

	}

	~Image() {
		if(_buffer)
		delete[] _buffer;
	}

	int getWidth()const {
		return _width;
	}

	int getHeight()const {
		return _height;
	}

private:
	int _width = 0, _height = 0;
	Color* _buffer = nullptr;
};