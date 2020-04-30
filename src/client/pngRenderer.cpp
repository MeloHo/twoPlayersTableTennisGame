#include <stdio.h>
#include <iostream>
#include "pngRenderer.h"

pngRenderer::pngRenderer() {
    initFilenames();
    initQuadInfo();
    buildTextures();
}

std::string pngRenderer::findPathToImages() {

    char *symlinkpath = "lclient";
    char actualpath [PATH_MAX+1];

    std::string ptr = realpath(symlinkpath, actualpath);
    size_t found = 0, found2 = 0, temp = 0;
    while (found != std::string::npos) {
        found = ptr.find("/", temp);
        found2 = ptr.find("/", found+1);
        temp = found + 1;
        std::string sub = ptr.substr(found+1, found2-found-1);
        if (sub == "bin") {
            sub = ptr.substr(0, found+1);
            sub += "twoPlayersTableTennisGame/src/client/images";
            ptr = sub;
        }
    }
    return ptr;
}

void pngRenderer::initFilenames() {
    std::string dir = findPathToImages();
    files = std::vector<std::string> {
        dir + "/wood_tile.png",
        dir + "/wood_bg.png",
        dir + "/wall_left.png",
        dir + "/wall_right.png",
        dir + "/ceiling.png"
    };
}

GLuint pngRenderer::initTexture(std::string filename) {

    YsRawPngDecoder png;
	png.Decode(filename.c_str());

    GLuint texture;

    glGenTextures(1,&texture);  
    glBindTexture(GL_TEXTURE_2D,texture);  

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    glTexImage2D
        (GL_TEXTURE_2D,
         0,    // Level of detail
         GL_RGBA,
         png.wid,
         png.hei, 
         0,    // Border width, but not supported and needs to be 0.
         GL_RGBA,
         GL_UNSIGNED_BYTE,
         png.rgba);

    return texture;
}

void pngRenderer::buildTextures() {
    for (int i = 0; i < NUM_PNG_FILES; i++) {
        std::string file = files[i];
        textures.push_back(initTexture(file));
    }
}

void pngRenderer::initQuadInfo() {
    texCoors = std::vector<std::vector<float>> {
        { 0.0, 0.0 },
        { 3.0, 0.0 },
        { 3.0, 3.0 },
        { 0.0, 3.0 },

        { 0.0, 1.0 },
        { 1.0, 1.0 },
        { 1.0, 0.0 },
        { 0.0, 0.0 },

        { 0.0, 0.0 },
        { 1.0, 0.0 },
        { 1.0, 1.0 },
        { 0.0, 1.0 },

        { 0.0, 0.0 },
        { 1.0, 0.0 },
        { 1.0, 1.0 },
        { 0.0, 1.0 },

        { 0.0, 0.0 },
        { 2.0, 0.0 },
        { 2.0, 2.0 },
        { 0.0, 2.0 },
    };

    quadVertices = std::vector<std::vector<float>> {
        { -1.0, -2.0, 0.0 },
        { 2.5, -2.0, 0.0 },
        { 2.5, 4.0, 0.0 },
        { -1.0, 4.0, 0.0 },

        { -1.0, 4, -0.3 },
	    { 2.5, 4, -0.3 },
	    { 2.5, 4, 4.0 },
	    { -1.0, 4, 4.0 },

        { -1.0, -2, 0.0 },
        { -1.0, 4, 0.0 },
		{ -1.0, 4, 3.0 },
		{ -1.0, -2, 3.0 }, 

        { 2.5, -2, 3 },
		{ 2.5, 4, 3.0 },
		{ 2.5, 4, 0 },
		{ 2.5, -2, 0 },

		{ -1.0, -2.0, 3.0 },
		{ 2.5, -2.0, 3.0 },
		{ 2.5, 4.0, 3.0 },
		{ -1.0, 4.0, 3.0 }
    };
}

void pngRenderer::drawQuad(GLuint texture, int start) {

	glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    for (int i = start; i < start+4; i++) {
        glTexCoord2d(texCoors[i][0], texCoors[i][1]);   
        glVertex3f(quadVertices[i][0], quadVertices[i][1], quadVertices[i][2]);
    }
    glEnd();
}

void pngRenderer::draw() {

    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glColor4d(1.0,1.0,1.0,1.0);
    glEnable(GL_TEXTURE_2D);

    for (int i = 0; i < NUM_PNG_FILES; i++) {
        drawQuad(textures[i], i*4);
    }
	glBindTexture(GL_TEXTURE_2D, 0);        
}
