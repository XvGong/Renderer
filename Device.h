#pragma once

#include <string>
#include <exception>
#include <iostream>

#include "Image.h"

class Device {
public:
    Device(int width, int height)
        :_width(width)
        , _height(height)
        , _max(_width* _height)
    {
        _hwnd = initgraph(_width, _height);
        _screen = GetImageBuffer(NULL);
        _buffer = new DWORD[_max];
        //BeginBatchDraw();
    }

    ~Device() {
        closegraph();
        delete[] _buffer;
        //EndBatchDraw();
    }

    void putimage(Image* image, int x, int y) {
        int x1 = x, y1 = y, w = image->_width, h = image->_height;
        for (int y2 = 0; y2 < h; y2++) {
            for (int x2 = 0; x2 < w; x2++) {
                int x = x1 + x2;
                int y = y1 + y2;
                if (x >= 0 && x < _width && y >= 0 && y < _height) {
                    mix(x, y, image->_buffer[y2 * w + x2]);
                }
            }
        }
    }

    void mix(int x, int y, Color color) {
        DWORD src = _buffer[y * _width + x];
        _buffer[y * _width + x] = color.mix(src);
    }

    DWORD get(int x, int y) {
        try {
            return _buffer[y * _width + x];
        }
        catch (std::exception& e) {
            std::cerr << e.what() << "\n";
            exit(-1);
        }
    }

    inline int getWidth()const {
        return _width;
    }

    inline int getHeight()const {
        return _height;
    }

    void clear() {
        int size = 5;
        DWORD color = 0xffffff;
        for (int y = 0; y < _height; y++) {
            for (int x = 0; x < _width; x++) {
                int i = x / size, j = y / size;
                if ((i + j) % 2 == 0) {
                    color = 0xffffff;
                }
                else {
                    color = 0xcccccc;
                }
                _buffer[y * _width + x] = color;
            }
        }
    }

    inline void flush() {
        for (int i = 0; i < _max; i++) {
            _screen[i] = _buffer[i];
        }
        //FlushBatchDraw();
    }

private:

    HWND _hwnd;
    DWORD *_buffer = nullptr, *_screen = nullptr;
    int _width = 0, _height = 0, _max = 0;
};