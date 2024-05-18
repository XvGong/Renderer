#pragma once

#include "Image.h"

class Renderer;

class RenderObject {
	friend class Renderer;
public:
	RenderObject(Image* img, int x, int y, int layerOrder) 
		:_img(img)
		,_x(x)
		,_y(y)
		,_layerOrder(layerOrder)
	{
	
	}

	bool operator <(const RenderObject& obj) const{
		return obj._layerOrder < _layerOrder;
	}
private:
	Image* _img=nullptr;
	int _x = 0, _y = 0, _layerOrder = 0;
};