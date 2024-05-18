#pragma once

#include <set>

#include"RenderObject.h"
#include"Device.h"

class Renderer {
public:
	static Renderer* createRenderer(Device* device) {
		if (device)
			return new Renderer(device);
		else {
			std::cerr << "Create Renderer Failed";
			return nullptr;
		}
	}

	static void deleteRenderer(Renderer* renderer) {
		if (renderer)
			delete renderer;
	}

	void addRenderObject(RenderObject* renderObj) {
		_renderObjects.insert(renderObj);
	}
	void delRenderObject(RenderObject* renderObj) {
		if (_renderObjects.erase(renderObj))
			_renderObjects_to_del.insert(renderObj);
	}
	void render() {
		_device->clear();
		for (auto& obj : _renderObjects) {
			_device->putimage(obj->_img, obj->_x, obj->_y);
		}
		_device->flush();
		for (auto& obj : _renderObjects_to_del) {
			delete obj;
		}
		_renderObjects_to_del.clear();
	}
private:
	Renderer(Device* device) {
		_device = device;
		_renderObjects.clear();
	}
	~Renderer() {
		_device = nullptr;
		
		for (auto& obj : _renderObjects) {
			_device->putimage(obj->_img, obj->_x, obj->_y);
		}

		for (auto& obj : _renderObjects_to_del) {
			delete obj;
		}

		_renderObjects.clear();
		_renderObjects_to_del.clear();
	}
private:
	Device* _device;
	std::set<RenderObject*> _renderObjects;
	std::set<RenderObject*> _renderObjects_to_del;
};