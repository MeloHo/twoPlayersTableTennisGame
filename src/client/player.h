#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <math.h>
#include <fslazywindow.h>
#include "Entity.h"

using namespace std;

class Player: public Entity {
private:
  int pos;
  float x, y, z;
  float faceNormal[3];
  vector<float> racket2d, handle2d, face2d, filler2d;
  vector<float> faceFrontVtx, faceFrontNom, faceFrontCol;
  vector<float> faceBackVtx, faceBackNom, faceBackCol;
  vector<float> racketFrontVtx, racketBackVtx, racketFrontNom, racketCol;
  vector<float> racketSideVtx, racketSideNom;
  vector<float> handleSideVtx, handleSideNom;
  vector<float> handleFrontVtx, handleBackVtx, handleFrontNom, handleCol;

  void makeHandle2d();
  void makeRacket2d();
  void makeFace2d();
  void makeHandle3d(float xFront, float xBack);
  void makeRacket3d(float xFront, float xBack);
  void makeFace3d(float xfront, float xback);
  void connectSurfaces(vector<float>& vec2d, vector<float>& vtx, vector<float>& nom, vector<float>& col, vector<float> targetCol, float xFront, float xBack);

  vector<float> crossProduct(vector<float> vec1, vector<float> vec2);

  void drawPolygon(vector<float>& vtx, vector<float>& nom, vector<float>& col);
  void drawQuads(vector<float>& vtx, vector<float>& nom, vector<float>& col);
public:
  Player();
  Player(float nx, float ny, float nz);
  ~Player() {}
  void draw();
  void updateNormal();
  void updatePosition(float nx, float ny);
};

#endif
