#include "render-pipeline.hpp"
#include <GLES3/gl3.h>
#include <algorithm>

RenderPipeline::RenderPipeline() {}

void RenderPipeline::addItem(RenderItem *item) {
    this->renderItems.push_back(item);
    // TODO use item->zIndex
}

void RenderPipeline::removeItem(RenderItem *item) {
    this->renderItems.erase(
        std::remove(this->renderItems.begin(), this->renderItems.end(), item),
        this->renderItems.end());
}

void RenderPipeline::tick() {
    for (auto item : this->renderItems) {
        item->tick();
    }
}

void RenderPipeline::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto item : this->renderItems) {
        item->render();
    }
}

unsigned char* RenderPipeline::getPixelBuffer() {
    // We multiply width and height by 3 because we use RGB!
    unsigned char* buffer = (unsigned char *)malloc(64 * 32 * 3);

    // Copy entire screen
    glReadPixels(0, 0, 64, 32, GL_RGB, GL_UNSIGNED_BYTE, buffer);

    return buffer;
}
