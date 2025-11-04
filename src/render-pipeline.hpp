#pragma once
#include "./render-item.hpp"
#include <vector>

class RenderPipeline {
    private:
        std::vector<RenderItem *> renderItems;

    public:
        RenderPipeline();

        void addItem(RenderItem *item);

        void removeItem(RenderItem *item);

        void tick();

        void render();

        unsigned char* getPixelBuffer();
};
