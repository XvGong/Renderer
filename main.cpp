#include "Renderer.h"
#include <chrono>

using namespace std::chrono;

int main() {
    
    Device device(640, 480);
    
    auto renderer = Renderer::createRenderer(&device);

    Image img1("D:/Project/Renderer/1.png");
    Image img2("D:/Project/Renderer/2.png");

    auto task1 = new RenderObject(&img1, 10, 10, 5);
    auto task2 = new RenderObject(&img2, 50, 50, 7);

    renderer->addRenderObject(task1);
    renderer->addRenderObject(task2);

    auto start = steady_clock::now();
    renderer->render();
    auto end = steady_clock::now();

    std::cout << duration_cast<milliseconds>(end - start).count();

    std::cin.get();

    Renderer::deleteRenderer(renderer);

    return 0;
}