#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <vector>
#include <math.h>
#include <fslazywindow.h>
#include "Entity.h"

using namespace std;

class Table: public Entity {
private:
    float x, y, z;
    float faceNormal[3];

    vector<vector<float>> surfacePnt;
    vector<vector<int>> surfacePl;
    vector<vector<float>> surfacePlCol;
    vector<float> surfaceVtx, surfaceNom, surfaceCol;

    vector<vector<float>> linesPnt;
    vector<vector<int>> linesPl;
    vector<vector<float>> linesPlCol;
    vector<float> linesVtx, linesNom, linesCol;
    
    void makeSurfacePnts();
    void makeSurfacePl();
    void makeSurfaceCol();

    void makeLinesPnts();
    void makeLinesPl();
    void makeLinesCol();

    void makeMesh(vector<vector<int>> Pl, vector<vector<float>> Vtx, vector<vector<float>> Col, vector<float> &meshVtx, vector<float> &meshNom, vector<float> &meshCol);

    vector<float> crossProduct(vector<float> vec1, vector<float> vec2);

    void drawPolygon(vector<float>& vtx, vector<float>& nom, vector<float>& col);
    void drawQuads(vector<float>& vtx, vector<float>& nom, vector<float>& col);
public:
    Table();
    Table(float nx, float ny, float nz);
    ~Table() {}
    void draw();
};

#endif
