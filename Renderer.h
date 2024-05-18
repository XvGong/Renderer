#pragma once

#include <set>

#include"RenderObject.h"
#include"Device.h"

class Renderer {
	struct CompareByOrder {
		bool operator()(const RenderObject* a, const RenderObject* b) const {
			return a->_layerOrder > b->_layerOrder;
		}
	};
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
		if (renderer) {
			renderer->clearAllObjects();
			delete renderer;
		}
	}

	void addRenderObject(RenderObject* renderObj) {
		_renderObjects.insert(renderObj);
	}

	void delRenderObject(RenderObject* renderObj) {
		if (_renderObjects.erase(renderObj))
			_renderObjects_to_del.insert(renderObj);
	}

	void clearAllObjects() {
		for (auto i : _renderObjects) {
			_renderObjects_to_del.insert(i);
		}
		_renderObjects.clear();
	}

	void render() {
		_device->clear();
		for (auto& obj : _renderObjects) {
			_device->putimage(obj->_img, obj->_x, obj->_y);
		}
		_device->flush();
	}
private:
	Renderer(Device* device) {
		_device = device;
		_renderObjects.clear();
	}
	~Renderer() {
		_device = nullptr;

		for (auto& obj : _renderObjects_to_del) {
			delete obj;
		}

		_renderObjects_to_del.clear();
	}
private:
	Device* _device;
	std::set<RenderObject*, CompareByOrder> _renderObjects;
	std::set<RenderObject*> _renderObjects_to_del;
};