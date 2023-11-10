//
// Created by lucas on 09/11/23.
//

#include "Deformation.h"

Vector RotatePointAroundAxis(const Vector& point, const Vector& axis, float angle) {
    float cosAngle = cos(angle);
    float sinAngle = sin(angle);
    return point * cosAngle + Cross(axis, point) * sinAngle + axis * Dot(axis, point) * (1 - cosAngle);
}

Vector Twist::Warp(const Vector& point) {
    Vector normalizedAxis = Normalized(axis);

    float distanceAlongAxis = Dot(point, normalizedAxis);
    float twistAmount = strength * distanceAlongAxis;

    return RotatePointAroundAxis(point, normalizedAxis, twistAmount);
}

Mesh Twist::WarpMesh(Mesh& mesh) {
    std::vector<Vector> vertices;
    std::vector<Vector> normals;
    std::vector<int> indices;

    for (int i = 0; i < mesh.Vertexes(); ++i) {
        Vector p = Warp(mesh.Vertex(i));
        vertices.push_back(p);
        normals.push_back(p);
        indices.push_back(i);
    }

    return Mesh(vertices, normals, indices, indices);
}