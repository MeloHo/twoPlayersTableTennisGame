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
}

Table::Table(float nx, float ny, float nz) {
    x = nx;
    y = ny;
    z = nz;

    makeSurfacePnts();
    makeSurfacePl();
    makeSurfaceCol();
    makeMesh(surfacePl, surfacePnt, surfacePlCol, surfaceVtx, surfaceNom, surfaceCol);

    makeLinesPnts();
    makeLinesPl();
    makeLinesCol();
    makeMesh(linesPl, linesPnt, linesPlCol, linesVtx, linesNom, linesCol);
}

void Table::makeSurfacePnts() {
    surfacePnt = vector<vector<float>> {
        { 0.0f,  0.7625f,  1.37f },
        { 0.0f, -0.7625f,  1.37f },
        { 0.0f, -0.7625f, -1.37f },
        { 0.0f,  0.7625f, -1.37f },
        { -0.05f,  0.7625f,  1.37f },
        { -0.05f, -0.7625f,  1.37f },
        { -0.05f, -0.7625f, -1.37f },
        { -0.05f,  0.7625f, -1.37f }
    };
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
    surfacePlCol = vector<vector<float>> {
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
    };
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

void Table::makeLinesPnts() {
    linesPnt = vector<vector<float>> {
        // Outer edges
        { 0.0f,  0.7625f,  1.37f }, // 0
        { 0.0f, -0.7625f,  1.37f },
        { 0.0f, -0.7625f, -1.37f },
        { 0.0f,  0.7625f, -1.37f },
        // Inner edges
        { 0.0f,  0.7125f,  1.32f }, // 4
        { 0.0f, -0.7125f,  1.32f },
        { 0.0f, -0.7125f, -1.32f },
        { 0.0f,  0.7125f, -1.32f },
        // Inside points
        { 0.0f,  0.015f,  1.32f }, // 8
        { 0.0f, -0.015f,  1.32f },
        { 0.0f, -0.015f, -1.32f },
        { 0.0f,  0.015f, -1.32f }
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



void Table::draw() {
    // draw surface
    drawQuads(surfaceVtx, surfaceNom, surfaceCol);
    drawQuads(linesVtx, linesNom, linesCol);
}

