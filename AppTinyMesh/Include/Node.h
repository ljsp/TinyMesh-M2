//
// Created by lucas on 20/09/23.
//

#ifndef APPTINYMESH_NODE_H
#define APPTINYMESH_NODE_H


#include "mathematics.h"
#include "mesh.h"

class Node {

public:
    Node();
    ~Node();

    virtual double Value(const Vector&) const;
protected:
    //virtual void Union(const Node&, const Node&) const;
    //virtual void Intersection(const Node&, const Node&) const;
    //virtual void Difference(const Node&, const Node&) const;

    virtual Vector Gradient(const Vector&) const;
    virtual Vector Normal(const Vector&) const;
    virtual void Polygonize(int, Mesh&, const Box&, const double& = 1e-4) const;
    Vector Dichotomy(Vector, Vector, double, double, double, const double& = 1.0e-4) const;

    static const double Epsilon; //!< Epsilon value for partial derivatives
    static int TriangleTable[256][16]; //!< Two dimensionnal array storing the straddling edges for every marching cubes configuration.
    static int edgeTable[256];    //!< Array storing straddling edges for every marching cubes configuration.
};


#endif //APPTINYMESH_NODE_H
