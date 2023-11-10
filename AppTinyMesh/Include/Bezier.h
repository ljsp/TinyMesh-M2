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

    static inline Bezier patch (int n, int m, int res, float offsetU, float offsetV) {
        return {n, m, res, offsetU, offsetV};
    }
    static inline Bezier patch(const std::vector<std::vector<Vector>>& control_points, int n, int m, int res) {
        return {control_points, n, m, res};
    }

    static inline Bezier curve(int n, int res, float offsetU, float offsetV) {
        return {n, 1, res, offsetU, offsetV};
    }

    static inline Bezier curve(const std::vector<Vector>& control_points, int n, int res) {
        return {control_points, n, 1, res};
    }

    std::vector<std::vector<Vector>> getControlPoints() const { return control_points; }
    void setControlPoints(const std::vector<std::vector<Vector>>& control_points) { this->control_points = control_points; }

    std::vector<Vector> randomControlPoints(int n, float offsetU, float offsetV) const;
    std::vector<std::vector<Vector>> randomControlPoints2D(int n, int m, float offsetU, float offsetV) const;

    Mesh Polygonize() const;
    static Mesh Revolution(Mesh & curveMesh, Vector axis, int res);

private:
    Bezier(int n, int m, int res, float offsetU, float offsetV);
    Bezier(const std::vector<Vector>& control_points, int n, int m, int res);
    Bezier(const std::vector<std::vector<Vector>>& control_points, int n, int m, int res);


    float Bernstein(int n, int i, float u) const;
    Vector evaluate(float u, float v) const;

    std::vector<std::vector<Vector>> control_points;
    unsigned int n, m, res;
};


#endif //APPTINYMESH_BEZIER_H
