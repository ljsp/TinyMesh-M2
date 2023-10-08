//
// Created by lucas on 20/09/23.
//

#ifndef APPTINYMESH_PRIMITIVES_H
#define APPTINYMESH_PRIMITIVES_H


#include "Node.h"

class BoxImplicit : public Node{

public:
    BoxImplicit(const Vector& pb) : b(pb) {};
    double Value(const Vector& p) const override;
private:
    Vector b;
};

class Sphere : public Node{

public:
    Sphere(const Vector& c, double r) : center(c), radius(r) {}
    double Value(const Vector& p) const override;

private:
    Vector center;
    double radius;
};

class Capsule : public Node{

public:
    Capsule(const Vector& pa, const Vector& pb, const double r) : a(pa), b(pb), radius(r) {}
    double Value(const Vector& p) const override;

private:
    Vector a,b;
    double radius;
};

class Torus : public Node{

public:
    Torus(const Vector& p1, const Vector& t1) : center(p1), t(t1) {};
    double Value(const Vector& p) const override;

private:
    Vector center,t;
};

class Union : public Node {
public:
    Union(Node* n1, Node* n2) : node1(n1), node2(n2) {};
    double Value(const Vector& p) const override;
private:
    Node* node1;
    Node* node2;
};

class Intersection : public Node {
public:
    Intersection(Node* n1, Node* n2) : node1(n1), node2(n2) {};
    double Value(const Vector& p) const override;
private:
    Node* node1;
    Node* node2;
};

class Subtraction : public Node {
public:
    Subtraction(Node* n1, Node* n2) : node1(n1), node2(n2) {};
    double Value(const Vector& p) const override;
private:
    Node* node1;
    Node* node2;
};

class SmoothUnion : public Node {
public:
    SmoothUnion(Node* n1, Node* n2, double k) : node1(n1), node2(n2), k(k) {};
    double Value(const Vector& p) const override;
private:
    Node* node1;
    Node* node2;
    double k;
};

class SmoothSubtraction : public Node {
public:
    SmoothSubtraction(Node* n1, Node* n2, double k) : node1(n1), node2(n2), k(k) {};
    double Value(const Vector& p) const override;
private:
    Node* node1;
    Node* node2;
    double k;
};

class SmoothIntersection : public Node {
public:
    SmoothIntersection(Node* n1, Node* n2, double k) : node1(n1), node2(n2), k(k) {};
    double Value(const Vector& p) const override;
private:
    Node* node1;
    Node* node2;
    double k;
};

#endif //APPTINYMESH_PRIMITIVES_H
