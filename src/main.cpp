#include <chrono>
#include <cstdio>
#include <led-matrix.h>
#include <unistd.h>
#include "gl-init.hpp"
#include <signal.h>
#include "render-items/image-item.hpp"
#include "render-pipeline.hpp"

using namespace rgb_matrix;

bool interrupted = false;

void interruptHandler(int s) {
    printf("Caught signal %d\n", s);

    interrupted = true;
}

void setPixels(Canvas *canvas, unsigned char *pixelBuffer) {
    int i = 0;
    for (int y = 0; y < 32; y++) {
        for (int x = 0; x < 64; x++) {
            unsigned char r = pixelBuffer[i];
            unsigned char g = pixelBuffer[i + 1];
            unsigned char b = pixelBuffer[i + 2];
            
            // 04/11/25 Had to flip X here because it was backwards, unsure why, might cause issues in the near future
            canvas->SetPixel(63 - x, y, r, g, b); 
           
            i += 3;
        }
    }
}

int main() {
    signal(SIGINT, interruptHandler);

    initOpenGL(); // opengl has to be init'd before the RGBMatrix for some
                  // reason

    RGBMatrix::Options matrix_options;
    rgb_matrix::RuntimeOptions runtime_opt;

    matrix_options.rows = 32;
    matrix_options.cols = 64;
    matrix_options.hardware_mapping = "adafruit-hat";

    RGBMatrix *matrix =
        RGBMatrix::CreateFromOptions(matrix_options, runtime_opt);

    if (matrix == NULL)
        return 1;

    printf("Size: %dx%d. Hardware gpio mapping: %s\n", matrix->width(),
           matrix->height(), matrix_options.hardware_mapping);

    Canvas *canvas = matrix;

    RenderPipeline pipeline;
    ImageItem item;
    pipeline.addItem(&item);

    int targetFPS = 10;
    int targetTimeMilliseconds = 1000000.0f / targetFPS;

    printf("Starting main loop\n");

    while (!interrupted) {
        auto startTime = std::chrono::high_resolution_clock::now();

        pipeline.tick();
        pipeline.render();
        unsigned char* pixels = pipeline.getPixelBuffer();
        setPixels(canvas, pixels);
        free(pixels);

        int tickTime =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now() - startTime)
                .count();
        int remainingSleepTime = std::max(targetTimeMilliseconds - tickTime, 0);
        usleep(remainingSleepTime);
    }

    canvas->Clear();

    return 0;
}
