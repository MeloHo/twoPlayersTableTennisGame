#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <vector>
#include <math.h>
#include "fssimplewindow.h"
#include "Entity.h"

using namespace std;

#define CORD_T 0.005
#define CORD_GAP 0.03

class Table: public Entity {
private:
    float x, y, z;
    float faceNormal[3];

    vector<vector<float>> surfacePnt;   // List of 3D vertices
    vector<vector<int>> surfacePl;      // List of groups of indices representing polygons
    vector<vector<float>> surfacePlCol; // List of colors for each polygon
    vector<float> surfaceVtx, surfaceNom, surfaceCol; // List of sequential values for mesh rendering

    vector<vector<float>> linesPnt;
    vector<vector<int>> linesPl;
    vector<vector<float>> linesPlCol;
    vector<float> linesVtx, linesNom, linesCol;

    vector<vector<float>> legPnt, supPnt;
    vector<vector<int>> legPl, supPl;
    vector<vector<float>> legPlCol;
    vector<float> legVtx, legNom, legCol;
    vector<float> supVtx, supNom, supCol;

    vector<vector<float>> clipPnt;
    vector<vector<int>> clipPl;
    vector<vector<float>> clipPlCol;
    vector<float> clipVtx, clipNom, clipCol;

    vector<vector<float>> netPnt;
    vector<vector<int>> netPl;
    vector<vector<float>> netPlCol;
    vector<float> netVtx, netNom, netCol;

    vector<vector<float>> vertCordPnt, horzCordPnt;
    vector<vector<int>> vertCordPl, horzCordPl;
    vector<vector<float>> cordPlCol;
    vector<float> vertCordVtx, vertCordNom, vertCordCol;
    vector<float> horzCordVtx, horzCordNom, horzCordCol;
    
    void makeSurfacePnts(); // Build list of surface points
    void makeSurfacePl();   // Build list of polygons
    void makeSurfaceCol();  // Build list of colors

    void makeLinesPnts();
    void makeLinesPl();
    void makeLinesCol();

    void makeLegPnts();
    void makeLegPl();
    void makeLegCol();
    void buildLegs();
    void buildSup();

    void makeClipPnts();
    void makeClipPl();
    void makeClipCol();
    
    void makeNetPnts();
    void makeNetPl();
    void makeNetCol();

    void makeCordPnts();
    void makeCordPl();
    void makeCordCol();
    void buildCords();

    void translate(vector<vector<float>> &pnts, vector<float> vec);

    void makeMesh(vector<vector<int>> Pl, vector<vector<float>> Vtx, vector<vector<float>> Col, vector<float> &meshVtx, vector<float> &meshNom, vector<float> &meshCol);

    vector<float> crossProduct(vector<float> vec1, vector<float> vec2);

    void drawPolygon(vector<float>& vtx, vector<float>& nom, vector<float>& col);
    void drawQuads(vector<float>& vtx, vector<float>& nom, vector<float>& col);
    void drawLines(vector<vector<float>> vtx, vector<int> col);
public:
    Table();
    Table(float nx, float ny, float nz);
    ~Table() {}
    void draw();
    vector<float> getNormal() const;
};

#endif
