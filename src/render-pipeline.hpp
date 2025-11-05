#pragma once
#include "./render-item.hpp"
#include <chrono>
#include <vector>

class RenderPipeline {
    private:
        std::chrono::steady_clock::time_point startTime;

        std::vector<RenderItem *> renderItems;

    public:
        RenderPipeline();

        void addItem(RenderItem *item);

        void removeItem(RenderItem *item);

        void tick();

        void render();

        unsigned char* getPixelBuffer();
};
