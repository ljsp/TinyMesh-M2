//
// Created by lucas on 09/11/23.
//

#ifndef APPTINYMESH_DEFORMATION_H
#define APPTINYMESH_DEFORMATION_H

#include <cmath>
#include "mathematics.h"
#include "mesh.h"

class Twist {
public:
    inline Twist(float strength, Vector axis) : strength(strength), axis(axis) {}
    Mesh WarpMesh(Mesh& mesh);
    Vector Warp(const Vector& point);

private:
    Vector axis;
    float strength;
};


#endif //APPTINYMESH_DEFORMATION_H
