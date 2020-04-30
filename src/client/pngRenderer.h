#ifndef PNG_RENDERER_H
#define PNG_RENDERER_H

#include <stdio.h>
#include <string>
#include <vector>
#include <string.h>
#include "fssimplewindow.h"
#include "yspng.h"

#define NUM_PNG_FILES 5

class pngRenderer {
private:
    std::vector<std::string> files;
    std::vector<GLuint> textures;
    std::vector<std::vector<float>> texCoors;
    std::vector<std::vector<float>> quadVertices;

    std::string findPathToImages();
    void initFilenames();

    GLuint initTexture(std::string filename);
    void buildTextures();
    
    void initQuadInfo();
    void drawQuad(GLuint texture, int start);

public:
    pngRenderer();
    ~pngRenderer() {}
    void draw();
};

#endif
