//
// Created by lucas on 20/09/23.
//

#include "Primitives.h"

void BoxImplicit::Polygonize(int n, Mesh& g, const Box& box, const double& epsilon) const {
    Node::Polygonize(n, g, box, epsilon);
}

double BoxImplicit::Value(const Vector &p) const {
    Vector q = Abs(p) - b;
    return std::max(std::max(q[0], q[1]), q[2]);
}

void Sphere::Polygonize(int n, Mesh& g, const Box& box, const double& epsilon) const {
    Node::Polygonize(n, g, box, epsilon);
}

double Sphere::Value(const Vector &p) const {
    return Norm(p - center) - radius;
}

void Capsule::Polygonize(int n, Mesh& g, const Box& box, const double& epsilon) const {
    Node::Polygonize(n, g, box, epsilon);
}

double Capsule::Value(const Vector &p) const {
    Vector pa = p - a; Vector ba = b - a;
    double h = Math::Clamp(Dot(pa, ba) / Dot(ba, ba), 0.0, 1.0);
    return Norm(pa - ba * h) - radius;
}

double Torus::Value(const Vector &point) const {
    Vector p = point;
    Vector q = Vector(Norm(Vector(p[0], 0, p[2])) - this->t[0], p[1], 0);
    return Norm(q) - this->t[1];
}

void Torus::Polygonize(int n, Mesh& g, const Box& box, const double& epsilon) const {
    Node::Polygonize(n, g, box, epsilon);
}

void Union::Polygonize(int n, Mesh& g, const Box& box, const double& epsilon) const {
    Node::Polygonize(n, g, box, epsilon);
}

double Union::Value(const Vector &p) const {
    return std::min(node1->Value(p), node2->Value(p));
}

void Intersection::Polygonize(int n, Mesh& g, const Box& box, const double& epsilon) const {
    Node::Polygonize(n, g, box, epsilon);
}

double Intersection::Value(const Vector &p) const {
    return std::max(node1->Value(p), node2->Value(p));
}

void Subtraction::Polygonize(int n, Mesh& g, const Box& box, const double& epsilon) const {
    Node::Polygonize(n, g, box, epsilon);
}

double Subtraction::Value(const Vector &p) const {
    return std::max(node1->Value(p), -node2->Value(p));
}

void SmoothUnion::Polygonize(int n, Mesh& g, const Box& box, const double& epsilon) const {
    Node::Polygonize(n, g, box, epsilon);
}

double SmoothUnion::Value(const Vector &p) const {
    double d1 = node1->Value(p);
    double d2 = node2->Value(p);
    double h = Math::Clamp(0.5 + 0.5 * (d2 - d1) / k, 0.0, 1.0);
    return Math::Lerp(d2, d1, h) - k * h * (1.0 - h);
}

void SmoothSubtraction::Polygonize(int n, Mesh& g, const Box& box, const double& epsilon) const {
    Node::Polygonize(n, g, box, epsilon);
}

double SmoothSubtraction::Value(const Vector &p) const {
    double d1 = node1->Value(p);
    double d2 = node2->Value(p);
    double h = Math::Clamp(0.5 - 0.5 * (d2 + d1) / k, 0.0, 1.0);
    return Math::Lerp(d2, -d1, h) + k * h * (1.0 - h);
}

void SmoothIntersection::Polygonize(int n, Mesh& g, const Box& box, const double& epsilon) const {
    Node::Polygonize(n, g, box, epsilon);
}

double SmoothIntersection::Value(const Vector &p) const {
    double d1 = node1->Value(p);
    double d2 = node2->Value(p);
    double h = Math::Clamp(0.5 - 0.5 * (d2 - d1) / k, 0.0, 1.0);
    return Math::Lerp(d2, d1, h) + k * h * (1.0 - h);
}





