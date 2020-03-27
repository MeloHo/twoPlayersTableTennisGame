#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <math.h>
#include <fslazywindow.h>
#include "Entity.h"

#define PI 3.14159
#define ANGLE_RESOLUTION PI/32.0
#define MAX_Y_ANGLE PI/3.0
#define MAX_Z_ANGLE PI/2.5
#define MAX_Y_TRANS 40.0
#define MAX_Z_TRANS 60.0

using namespace std;

class Player: public Entity {
private:
  int winWid, winHei;
  int mx, my;
  float x, y, z;
  float dx, dy, dz;
  float ay, az;
  vector<float> faceNom;
  vector<float> racket2d, handle2d, face2d, filler2d;
  // original vertices
  vector<float> faceFrontVtx, faceFrontNom, faceFrontCol;
  vector<float> faceBackVtx, faceBackNom, faceBackCol;
  vector<float> racketFrontVtx, racketBackVtx, racketFrontNom, racketCol;
  vector<float> racketSideVtx, racketSideNom;
  vector<float> handleSideVtx, handleSideNom;
  vector<float> handleFrontVtx, handleBackVtx, handleFrontNom, handleCol;
  // for holding transformed vertices
  vector<float> faceFrontVtxTf, faceFrontNomTf;
  vector<float> faceBackVtxTf, faceBackNomTf;
  vector<float> racketFrontVtxTf, racketBackVtxTf, racketFrontNomTf;
  vector<float> racketSideVtxTf, racketSideNomTf;
  vector<float> handleSideVtxTf, handleSideNomTf;
  vector<float> handleFrontVtxTf, handleBackVtxTf, handleFrontNomTf;

  void makeHandle2d();
  void makeRacket2d();
  void makeFace2d();
  void makeHandle3d(float xFront, float xBack);
  void makeRacket3d(float xFront, float xBack);
  void makeFace3d(float xfront, float xback);
  void connectSurfaces(vector<float>& vec2d, vector<float>& vtx, vector<float>& nom, vector<float>& col, vector<float> targetCol, float xFront, float xBack);

  vector<float> crossProduct(vector<float> vec1, vector<float> vec2);
  void translateVector(vector<float>& vec, vector<float>& dest);
  void rotateVector(vector<float>& vec, vector<float>& dest);
  void mapCoorToAng();
  void mapCoorToTrans();

  void drawPolygon(vector<float>& vtx, vector<float>& nom, vector<float>& col);
  void drawQuads(vector<float>& vtx, vector<float>& nom, vector<float>& col);
public:
  Player();
  Player(float nx, float ny, float nz);
  ~Player() {}
  void draw();
  void getMouseCoor(int x, int y);
  void updateWinSize(int wid, int hei);
  void update(int mx, int my);
};

#endif
