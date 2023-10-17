//
// Created by lucas on 08/10/23.
//

#ifndef APPTINYMESH_BEZIER_H
#define APPTINYMESH_BEZIER_H


#include "Node.h"

class Bezier : public Node {
private:
    std::vector<std::vector<Vector>> control_points;

    Vector value(double u, double v) const {
        return Vector();
    }

public:
    Bezier(const std::vector<std::vector<Vector>>& control_points_) : control_points(control_points_) {}
};


#endif //APPTINYMESH_BEZIER_H
