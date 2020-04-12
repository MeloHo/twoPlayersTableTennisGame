#include "table.h"

Table::Table() {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;

    makeSurfacePnts();
    makeSurfacePl();
    makeSurfaceCol();
    makeMesh(surfacePl, surfacePnt, surfacePlCol, surfaceVtx, surfaceNom, surfaceCol);

    makeLinesPnts();
    makeLinesPl();
    makeLinesCol();
    makeMesh(linesPl, linesPnt, linesPlCol, linesVtx, linesNom, linesCol);

    makeLegPnts();
    makeLegPl();
    makeLegCol();
    buildLegs();
    makeMesh(legPl, legPnt, legPlCol, legVtx, legNom, legCol);
    makeMesh(supPl, supPnt, legPlCol, supVtx, supNom, supCol);

    makeClipPnts();
    makeClipPl();
    makeClipCol();
    makeMesh(clipPl, clipPnt, clipPlCol, clipVtx, clipNom, clipCol);

    makeNetPnts();
    makeNetPl();
    makeNetCol();
    makeMesh(netPl, netPnt, netPlCol, netVtx, netNom, netCol);

    makeCordPnts();
    makeCordPl();
    makeCordCol();
    buildCords();
    makeMesh(vertCordPl, vertCordPnt, cordPlCol, vertCordVtx, vertCordNom, vertCordCol);
    makeMesh(horzCordPl, horzCordPnt, cordPlCol, horzCordVtx, horzCordNom, horzCordCol);
}


Table::Table(float nx, float ny, float nz) {
    x = nx;
    y = ny;
    z = nz;

    makeSurfacePnts();
    makeSurfacePl();
    makeSurfaceCol();
    translate(surfacePnt, {x, y, z});
    makeMesh(surfacePl, surfacePnt, surfacePlCol, surfaceVtx, surfaceNom, surfaceCol);

    makeLinesPnts();
    makeLinesPl();
    makeLinesCol();
    translate(linesPnt, {x, y, z});
    makeMesh(linesPl, linesPnt, linesPlCol, linesVtx, linesNom, linesCol);

    makeLegPnts();
    makeLegPl();
    makeLegCol();
    translate(legPnt, {x, y, z});
    translate(supPnt, {x, y, z});
    buildLegs();
    makeMesh(legPl, legPnt, legPlCol, legVtx, legNom, legCol);
    makeMesh(supPl, supPnt, legPlCol, supVtx, supNom, supCol);

    makeClipPnts();
    makeClipPl();
    makeClipCol();
    translate(clipPnt, {x, y, z});
    makeMesh(clipPl, clipPnt, clipPlCol, clipVtx, clipNom, clipCol);

    makeNetPnts();
    makeNetPl();
    makeNetCol();
    translate(netPnt, {x, y, z});
    makeMesh(netPl, netPnt, netPlCol, netVtx, netNom, netCol);
    
    makeCordPnts();
    makeCordPl();
    makeCordCol();
    translate(vertCordPnt, {x, y, z});
    translate(horzCordPnt, {x, y, z});
    buildCords();
    makeMesh(vertCordPl, vertCordPnt, cordPlCol, vertCordVtx, vertCordNom, vertCordCol);
    makeMesh(horzCordPl, horzCordPnt, cordPlCol, horzCordVtx, horzCordNom, horzCordCol);
}


void Table::makeSurfacePnts() {
    surfacePnt = vector<vector<float>> {
        {  0.7625f,  1.37f,  0.0f },
        { -0.7625f,  1.37f,  0.0f },
        { -0.7625f, -1.37f,  0.0f },
        {  0.7625f, -1.37f,  0.0f },
        {  0.7625f,  1.37f, -0.05f },
        { -0.7625f,  1.37f, -0.05f },
        { -0.7625f, -1.37,  -0.05f },
        {  0.7625f, -1.37,  -0.05f }
    };

    faceNormal[0] = 0.0;
    faceNormal[1] = 0.0;
    faceNormal[2] = 1.0;
}

void Table::makeSurfacePl() {
    surfacePl = vector<vector<int>> {
        { 4, 5, 6, 7 }, // Lower surface
        { 0, 4, 5, 1 }, // Upper side
        { 1, 5, 6, 2 }, // Left side
        { 2, 6, 7, 3 }, // Lower side
        { 3, 7, 4, 0 }  // Right side
    };
}

void Table::makeSurfaceCol() {
    vector<vector<float>> cols(5, {153.0/255.0, 92.0/255.0, 33.0/255.0});
    surfacePlCol = cols;
    // surfacePlCol = vector<vector<float>> {
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // { 0.0f, 0.0f, 0.0f, 0.0f },
    // };
}


void Table::makeLinesPnts() {
    linesPnt = vector<vector<float>> {
        // Outer edges
        {  0.7625f,  1.37f, 0.0f }, // 0
        { -0.7625f,  1.37f, 0.0f },
        { -0.7625f, -1.37f, 0.0f },
        {  0.7625f, -1.37f, 0.0f },
        // Inner edges
        {  0.7125f,  1.32f, 0.0f }, // 4
        { -0.7125f,  1.32f, 0.0f },
        { -0.7125f, -1.32f, 0.0f },
        {  0.7125f, -1.32f, 0.0f },
        // Inside points
        {  0.015f,  1.32f, 0.0f }, // 8
        { -0.015f,  1.32f, 0.0f },
        { -0.015f, -1.32f, 0.0f },
        {  0.015f, -1.32f, 0.0f }
    };
}

void Table::makeLinesPl() {
    linesPl = vector<vector<int>> {
        { 4, 8, 11, 7 }, // Right region
        { 9, 5, 6, 10 }, // Left region
        { 0, 1, 5, 4 },  // Upper line
        { 1, 2, 6, 5 },  // Left line
        { 2, 3, 7, 6 },  // Lower line
        { 3, 0, 4, 7 },  // Right line
        { 8, 9, 10, 11 } // Middle line
    };
}

void Table::makeLinesCol() {
    linesPlCol = vector<vector<float>> {
        { 91.0f/255.0f, 110.0f/255.0f, 151.0f/255.0f, 0.0f },
        { 91.0f/255.0f, 110.0f/255.0f, 151.0f/255.0f, 0.0f },
        { 1.0f, 1.0f, 1.0f, 0.0f },
        { 1.0f, 1.0f, 1.0f, 0.0f },
        { 1.0f, 1.0f, 1.0f, 0.0f },
        { 1.0f, 1.0f, 1.0f, 0.0f },
        { 1.0f, 1.0f, 1.0f, 0.0f }
    };
}

void Table::makeLegPnts() {
    legPnt = vector<vector<float>> {
        // Leg
        { -0.33f, 1.0f, -0.05f },
        { -0.43f, 1.0f, -0.05f },
        { -0.43f, 0.95f, -0.05f },
        { -0.33f, 0.95f, -0.05f },
        { -0.33f, 1.0f, -0.7f },
        { -0.43f, 1.0f, -0.7f },
        { -0.43f, 0.95f, -0.7f },
        { -0.33f, 0.95f, -0.7f }  
    };
    supPnt = vector<vector<float>> {
        { -0.33f, 0.95f, -0.38f },
        { -0.43f, 0.95f, -0.38f },
        { -0.43f, 0.29f, -0.38f },
        { -0.33f, 0.29f, -0.38f },
        { -0.33f, 0.95f, -0.33f },
        { -0.43f, 0.95f, -0.33f },
        { -0.43f, 0.29f, -0.33f },
        { -0.33f, 0.29f, -0.33f }
    };
}

void Table::makeLegPl() {
    legPl = vector<vector<int>> {
        { 4, 5, 6, 7 }, // Lower surface
        { 0, 4, 5, 1 }, // Upper side
        { 1, 5, 6, 2 }, // Left side
        { 2, 6, 7, 3 }, // Lower side
        { 3, 7, 4, 0 }  // Right side
    };
    supPl = vector<vector<int>> {
        { 4, 5, 6, 7 }, // Lower surface
        { 0, 4, 5, 1 }, // Upper side
        { 1, 5, 6, 2 }, // Left side
        { 2, 6, 7, 3 }, // Lower side
        { 3, 7, 4, 0 }  // Right side
    };
}

void Table::makeLegCol() {
    vector<vector<float>> cols(5*8, {153.0/255.0, 92.0/255.0, 33.0/255.0});
    legPlCol = cols;
}

void Table::buildLegs() {
    vector<vector<float>> origin(legPnt);
    vector<vector<int>> originPl(legPl);
    for (int j = 0; j < 3; j++) {
        translate(origin, {0.0, -0.66f, 0.0});
        vector<vector<float>> temp(origin);    
        legPnt.insert(legPnt.end(), temp.begin(), temp.end());

        for (auto &inds : originPl) {
            inds[0] += 8;
            inds[1] += 8;
            inds[2] += 8;
            inds[3] += 8;
        }
        vector<vector<int>> tempPl(originPl);
        legPl.insert(legPl.end(), tempPl.begin(), tempPl.end());
    }

    translate(origin, {0.38*2, 0.66*4, 0.0});
    for (int j = 0; j < 4; j++) {
        translate(origin, {0.0, -0.66f, 0.0});
        vector<vector<float>> temp(origin);    
        legPnt.insert(legPnt.end(), temp.begin(), temp.end());

        for (auto &inds : originPl) {
            inds[0] += 8;
            inds[1] += 8;
            inds[2] += 8;
            inds[3] += 8;
        }
        vector<vector<int>> tempPl(originPl);
        legPl.insert(legPl.end(), tempPl.begin(), tempPl.end());
    }
    buildSup();
}

void Table::buildSup() {
    vector<vector<float>> origin(supPnt);
    vector<vector<int>> originPl(supPl);
    for (int j = 0; j < 1; j++) {
        translate(origin, {0.0, -1.32f, 0.0});
        vector<vector<float>> temp(origin);    
        supPnt.insert(supPnt.end(), temp.begin(), temp.end());

        for (auto &inds : originPl) {
            inds[0] += 8;
            inds[1] += 8;
            inds[2] += 8;
            inds[3] += 8;
        }
        vector<vector<int>> tempPl(originPl);
        supPl.insert(supPl.end(), tempPl.begin(), tempPl.end());
    }

    translate(origin, {0.38*2, 1.32*2, 0.0});
    for (int j = 0; j < 2; j++) {
        translate(origin, {0.0, -1.32f, 0.0});
        vector<vector<float>> temp(origin);    
        supPnt.insert(supPnt.end(), temp.begin(), temp.end());

        for (auto &inds : originPl) {
            inds[0] += 8;
            inds[1] += 8;
            inds[2] += 8;
            inds[3] += 8;
        }
        vector<vector<int>> tempPl(originPl);
        supPl.insert(supPl.end(), tempPl.begin(), tempPl.end());
    }
}

void Table::makeClipPnts() {
    clipPnt = vector<vector<float>> {
        // Left clip
        // Lower rect
        { -0.7625f,  0.02f, -0.05f },
        { -0.9155f,  0.02f, -0.05f },
        { -0.9155f, -0.02f, -0.05f },
        { -0.7625f, -0.02f, -0.05f },
        // Upper rect
        { -0.7625f,  0.02f, 0.0f },
        { -0.9155f,  0.02f, 0.0f },
        { -0.9155f, -0.02f, 0.0f },
        { -0.7625f, -0.02f, 0.0f },
        // Left pole
        // Lower rect
        { -0.8955f,  0.02f, 0.0f },
        { -0.9155f,  0.02f, 0.0f },
        { -0.9155f, -0.02f, 0.0f },
        { -0.8955f, -0.02f, 0.0f },
        // Upper rect
        { -0.8955f,  0.02f, 0.16f },
        { -0.9155f,  0.02f, 0.16f },
        { -0.9155f, -0.02f, 0.16f },
        { -0.8955f, -0.02f, 0.16f },
        // Right clip
        // Lower rect
        { 0.7625f,  0.02f, -0.05f },
        { 0.9155f,  0.02f, -0.05f },
        { 0.9155f, -0.02f, -0.05f },
        { 0.7625f, -0.02f, -0.05f },
        // Upper rect
        { 0.7625f,  0.02f, 0.0f },
        { 0.9155f,  0.02f, 0.0f },
        { 0.9155f, -0.02f, 0.0f },
        { 0.7625f, -0.02f, 0.0f },
        // Left pole
        // Lower rect
        { 0.8955f,  0.02f, 0.0f },
        { 0.9155f,  0.02f, 0.0f },
        { 0.9155f, -0.02f, 0.0f },
        { 0.8955f, -0.02f, 0.0f },
        // Upper rect
        { 0.8955f,  0.02f, 0.16f },
        { 0.9155f,  0.02f, 0.16f },
        { 0.9155f, -0.02f, 0.16f },
        { 0.8955f, -0.02f, 0.16f }

    };
}

void Table::makeClipPl() {
    clipPl = vector<vector<int>> {
        // Left clip
        // Base
        { 0, 1, 2, 3 }, // Upper surface
        { 4, 5, 6, 7 }, // Lower surface
        { 0, 4, 5, 1 }, // Upper side
        { 1, 5, 6, 2 }, // Left side
        { 2, 6, 7, 3 }, // Lower side
        { 3, 7, 4, 0 }, // Right side
        // Pole
        { 8,  9,  10, 11 },
        { 12, 13, 14, 15 },
        { 8,  12, 13, 9 },
        { 9,  13, 14, 10 },
        { 10, 14, 15, 11 },
        { 11, 15, 12, 8 },
        // Right clip
        // Base
        { 16, 17, 18, 19 }, // Upper surface
        { 20, 21, 22, 23 }, // Lower surface
        { 16, 20, 21, 17 }, // Upper side
        { 17, 21, 22, 18 }, // Left side
        { 18, 22, 23, 19 }, // Lower side
        { 19, 23, 20, 16 }, // Right side
        // Pole
        { 24, 25, 26, 27 },
        { 28, 29, 30, 31 },
        { 24, 28, 29, 25 },
        { 25, 29, 30, 26 },
        { 26, 30, 31, 27 },
        { 27, 31, 28, 24 }
    };
}

void Table::makeClipCol() {
    vector<vector<float>> cols(24, {0/255.0, 56/255.0, 22/255.0});
    clipPlCol = cols;
    // clipPlCol = vector<vector<float>> {
        // Left clip
        // Base
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // Pole
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // Right clip
        // Base
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // Pole
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // { 0.0f, 0.0f, 0.0f, 0.0f },
        // { 0.0f, 0.0f, 0.0f, 0.0f }
    // };
}

void Table::makeNetPnts() {
    // Straps
    netPnt = vector<vector<float>> {
        // Left strap
        { -0.8655f,  0.005f, 0.0f },
        { -0.8955f,  0.005f, 0.0f },
        { -0.8955f, -0.005f, 0.0f },
        { -0.8655f, -0.005f, 0.0f },
        { -0.8655f,  0.005f, 0.153f },
        { -0.8955f,  0.005f, 0.153f },
        { -0.8955f, -0.005f, 0.153f },
        { -0.8655f, -0.005f, 0.153f },
        // Right strap
        { 0.8655f,  0.005f, 0.0f },
        { 0.8955f,  0.005f, 0.0f },
        { 0.8955f, -0.005f, 0.0f },
        { 0.8655f, -0.005f, 0.0f },
        { 0.8655f,  0.005f, 0.153f },
        { 0.8955f,  0.005f, 0.153f },
        { 0.8955f, -0.005f, 0.153f },
        { 0.8655f, -0.005f, 0.153f },
        // Bottom strap
        {  0.8655f,  0.005f, 0.01f },
        { -0.8655f,  0.005f, 0.01f },
        { -0.8655f, -0.005f, 0.01f },
        {  0.8655f, -0.005f, 0.01f },
        {  0.8655f,  0.005f, 0.0f },
        { -0.8655f,  0.005f, 0.0f },
        { -0.8655f, -0.005f, 0.0f },
        {  0.8655f, -0.005f, 0.0f },
        // Top strap
        {  0.8655f,  0.005f, 0.153f },
        { -0.8655f,  0.005f, 0.153f },
        { -0.8655f, -0.005f, 0.153f },
        {  0.8655f, -0.005f, 0.153f },
        {  0.8655f,  0.005f, 0.123f },
        { -0.8655f,  0.005f, 0.123f },
        { -0.8655f, -0.005f, 0.123f },
        {  0.8655f, -0.005f, 0.123f }
    };
} 

void Table::makeNetPl() {
    netPl = vector<vector<int>> {
        // Left strap
        { 0, 1, 2, 3 }, // Upper surface
        { 4, 5, 6, 7 }, // Lower surface
        { 0, 4, 5, 1 }, // Upper side
        { 1, 5, 6, 2 }, // Left side
        { 2, 6, 7, 3 }, // Lower side
        { 3, 7, 4, 0 }, // Right side
        // Right strap
        { 8,  9,  10, 11 },
        { 12, 13, 14, 15 },
        { 8,  12, 13, 9 },
        { 9,  13, 14, 10 },
        { 10, 14, 15, 11 },
        { 11, 15, 12, 8 },
        // Bottom strap
        { 16, 17, 18, 19 }, // Upper surface
        { 20, 21, 22, 23 }, // Lower surface
        { 16, 20, 21, 17 }, // Upper side
        { 17, 21, 22, 18 }, // Left side
        { 18, 22, 23, 19 }, // Lower side
        { 19, 23, 20, 16 },
        // Top strap
        { 24, 25, 26, 27 },
        { 28, 29, 30, 31 },
        { 24, 28, 29, 25 },
        { 25, 29, 30, 26 },
        { 26, 30, 31, 27 },
        { 27, 31, 28, 24 }
    };
}

void Table::makeNetCol() {
    vector<vector<float>> cols(18, {0/255.0, 0/255.0, 0/255.0});
    vector<vector<float>> whiteStrapCols(6, {1.0, 1.0, 1.0});
    cols.insert(cols.end(), whiteStrapCols.begin(), whiteStrapCols.end());
    netPlCol = cols;
}

void Table::makeCordPnts() {
    vertCordPnt = vector<vector<float>> {
        { -0.8535f,  0.0025f, 0.123f },
        { -0.8585f, 0.0025f, 0.123f },
        { -0.8585f, -0.0025f, 0.123f },
        { -0.8535f, -0.0025f, 0.123f },
        { -0.8535f,  0.0025f, 0.0f },
        { -0.8585f, 0.0025f, 0.0f },
        { -0.8585f, -0.0025f, 0.0f },
        { -0.8535f, -0.0025f, 0.0f },
    };
    horzCordPnt = vector<vector<float>> {
        {  0.8655f,  0.0025f, 0.1185f },
        { -0.8655f,  0.0025f, 0.1185f },
        { -0.8655f, -0.0025f, 0.1185f },
        {  0.8655f, -0.0025f, 0.1185f },
        {  0.8655f,  0.0025f, 0.1135f },
        { -0.8655f,  0.0025f, 0.1135f },
        { -0.8655f, -0.0025f, 0.1135f },
        {  0.8655f, -0.0025f, 0.1135f },
    };
}

void Table::makeCordPl() {
    vertCordPl = vector<vector<int>> {
        { 0, 1, 2, 3 }, // Upper surface
        { 4, 5, 6, 7 }, // Lower surface
        { 0, 4, 5, 1 }, // Upper side
        { 1, 5, 6, 2 }, // Left side
        { 2, 6, 7, 3 }, // Lower side
        { 3, 7, 4, 0 }, // Right side
    };
    horzCordPl = vector<vector<int>> {
        { 0, 1, 2, 3 }, // Upper surface
        { 4, 5, 6, 7 }, // Lower surface
        { 0, 4, 5, 1 }, // Upper side
        { 1, 5, 6, 2 }, // Left side
        { 2, 6, 7, 3 }, // Lower side
        { 3, 7, 4, 0 }, // Right side
    };
}

void Table::makeCordCol() {
    vector<vector<float>> cols(vertCordPl.size()*(int)(1.8/CORD_GAP), {0/255.0, 0/255.0, 0/255.0});
    cordPlCol = cols;
}

void Table::buildCords() {
    vector<vector<float>> originVert(vertCordPnt);
    vector<vector<int>> originVertPl(vertCordPl);
    for (int i = 0; i < (int)(1.711 / CORD_GAP); i++) {
        translate(originVert, {CORD_GAP, 0.0, 0.0});
        vector<vector<float>> temp(originVert);    
        vertCordPnt.insert(vertCordPnt.end(), temp.begin(), temp.end());

        for (auto &inds : originVertPl) {
            inds[0] += 8;
            inds[1] += 8;
            inds[2] += 8;
            inds[3] += 8;
        }
        vector<vector<int>> tempPl(originVertPl);
        vertCordPl.insert(vertCordPl.end(), tempPl.begin(), tempPl.end());
    }

    vector<vector<float>> originHorz(horzCordPnt);
    vector<vector<int>> originHorzPl(horzCordPl);
    for (int j = 0; j < (int)(0.123 / CORD_GAP); j++) {
        translate(originHorz, {0.0, 0.0, -CORD_GAP});
        vector<vector<float>> temp(originHorz);
        horzCordPnt.insert(horzCordPnt.end(), temp.begin(), temp.end());

        for (auto &inds : originHorzPl) {
            inds[0] += 8;
            inds[1] += 8;
            inds[2] += 8;
            inds[3] += 8;
        }
        vector<vector<int>> tempPl(originHorzPl); 
        horzCordPl.insert(horzCordPl.end(), tempPl.begin(), tempPl.end()); 
    }
}

void Table::translate(vector<vector<float>> &pnts, vector<float> vec) {
    for (auto &pnt : pnts) {
        pnt[0] += vec[0];
        pnt[1] += vec[1];
        pnt[2] += vec[2];
    }
}

void Table::makeMesh(vector<vector<int>> Pl, vector<vector<float>> Vtx, vector<vector<float>> Col, vector<float> &meshVtx, vector<float> &meshNom, vector<float> &meshCol) {
    // Iterate through polygons
    for (int i = 0; i < Pl.size(); i++) {
        auto pl = Pl[i];
        auto col = Col[i];

        auto v1 = Vtx[pl[0]];
        auto v2 = Vtx[pl[1]];
        auto v3 = Vtx[pl[2]];

        auto nom = crossProduct({ v2[0] - v1[0], v2[1] - v1[1], v2[2] - v1[2] }, { v3[0] - v1[0], v3[1] - v1[1], v3[2] - v1[2] });
        // Iterate through vertices
        for (auto index : pl) {
            vector<float> vtx = Vtx[index];
            meshVtx.push_back(vtx[0]); // x
            meshVtx.push_back(vtx[1]); // y
            meshVtx.push_back(vtx[2]); // z
            meshNom.push_back(nom[0]);
            meshNom.push_back(nom[1]); 
            meshNom.push_back(nom[2]);  
            meshCol.push_back(col[0]);
            meshCol.push_back(col[1]);
            meshCol.push_back(col[2]); 
            meshCol.push_back(col[3]);
        }
    }
}

vector<float> Table::crossProduct(vector<float> vec1, vector<float> vec2) {
    vector<float> norm = {vec1[1]*vec2[2] - vec1[2]*vec2[1],
                          vec1[2]*vec2[0] - vec1[0]*vec2[2],
                          vec1[0]*vec2[1] - vec1[1]*vec2[0]};

    float mag = sqrt(pow(norm[0], 2.0f) + pow(norm[1], 2.0f) + pow(norm[2], 2.0f));

    norm[0] /= mag;
    norm[1] /= mag;
    norm[2] /= mag;
    return norm;
}

void Table::drawPolygon(vector<float>& vtx, vector<float>& nom, vector<float>& col) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_FLOAT, 0, col.data());
    glNormalPointer(GL_FLOAT, 0, nom.data());
    glVertexPointer(3, GL_FLOAT, 0, vtx.data());
    glDrawArrays(GL_POLYGON, 0, vtx.size()/3);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void Table::drawQuads(vector<float>& vtx, vector<float>& nom, vector<float>& col) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_FLOAT, 0, col.data());
    glNormalPointer(GL_FLOAT, 0, nom.data());
    glVertexPointer(3, GL_FLOAT, 0, vtx.data());
    glDrawArrays(GL_QUADS, 0, vtx.size()/3);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void Table::drawLines(vector<vector<float>> vtx, vector<int> col) {

    glColor3ub(col[0], col[1], col[2]);

    glBegin(GL_LINES);
    
    int n;
    for (int i = 0; i < vtx.size(); i++) {
        if (i == vtx.size() - 1) {
            n = 0;
        } else {
            n = i + 1;
        }
        glVertex3f(vtx[i][0], vtx[i][1], vtx[i][2]);
        glVertex3f(vtx[n][0], vtx[n][1], vtx[n][2]);
    }

    glEnd();
}



void Table::draw() {
    // draw surface
    drawQuads(surfaceVtx, surfaceNom, surfaceCol);
    drawQuads(linesVtx, linesNom, linesCol);
    drawQuads(legVtx, legNom, legCol);
    drawQuads(supVtx, supNom, supCol);
    drawQuads(clipVtx, clipNom, clipCol);
    drawQuads(netVtx, netNom, netCol);
    drawQuads(vertCordVtx, vertCordNom, vertCordCol);
    drawQuads(horzCordVtx, horzCordNom, horzCordCol);   

    drawLines(surfacePnt, {0, 0, 0});
    vector<vector<float>> straps(netPnt.begin()+24,netPnt.end());
    drawLines(straps, {0, 0, 0});
}

