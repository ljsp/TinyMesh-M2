//
// Created by lucas on 08/10/23.
//

#ifndef APPTINYMESH_BEZIER_H
#define APPTINYMESH_BEZIER_H

#include "Node.h"
#include "mesh.h"

class Bezier {
public:
    Bezier() = default;

    Bezier(int n, int m, int quality, float offsetU, float offsetV);
    Bezier(const std::vector<std::vector<Vector>>& control_points, int n, int m, int quality);

    std::vector<std::vector<Vector>> randomControlPoints(int n, int m, float offsetU, float offsetV) const;

    Mesh Polygonize() const;

private:
    float Bernstein(int n, int i, float u) const;
    Vector evaluate(float u, float v) const;

    std::vector<std::vector<Vector>> control_points;
    unsigned int n, m, res;
};


#endif //APPTINYMESH_BEZIER_H
