//
// Created by lucas on 20/09/23.
//

#include "Primitives.h"
#include <glm/glm.hpp>

double BoxImplicit::Value(const Vector &p) const {
    Vector q = Abs(p) - b;
    return std::max(std::max(q[0], q[1]), q[2]);
}


double Sphere::Value(const Vector &p) const {
    return Norm(p - center) - radius;
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


double Bunny::Value(const Vector &p) const {
    if (Norm(p) > 1.) {
        return Norm(p)-.8;
    }
    glm::vec4 f00=sin(float(p[1])*glm::vec4(-3.02,1.95,-3.42,-.60)+float(p[2])*glm::vec4(3.08,.85,-2.25,-.24)-float(p[0])*glm::vec4(-.29,1.16,-3.74,2.89)+glm::vec4(-.71,4.50,-3.24,-3.50));
    glm::vec4 f01=sin(float(p[1])*glm::vec4(-.40,-3.61,3.23,-.14)+float(p[2])*glm::vec4(-.36,3.64,-3.91,2.66)-float(p[0])*glm::vec4(2.90,-.54,-2.75,2.71)+glm::vec4(7.02,-5.41,-1.12,-7.41));
    glm::vec4 f02=sin(float(p[1])*glm::vec4(-1.77,-1.28,-4.29,-3.20)+float(p[2])*glm::vec4(-3.49,-2.81,-.64,2.79)-float(p[0])*glm::vec4(3.15,2.14,-3.85,1.83)+glm::vec4(-2.07,4.49,5.33,-2.17));
    glm::vec4 f03=sin(float(p[1])*glm::vec4(-.49,.68,3.05,.42)+float(p[2])*glm::vec4(-2.87,.78,3.78,-3.41)-float(p[0])*glm::vec4(-2.65,.33,.07,-.64)+glm::vec4(-3.24,-5.90,1.14,-4.71));
    glm::vec4 f10=sin(glm::mat4(-.34,.06,-.59,-.76,.10,-.19,-.12,.44,.64,-.02,-.26,.15,-.16,.21,.91,.15)*f00+
                      glm::mat4(.01,.54,-.77,.11,.06,-.14,.43,.51,-.18,.08,.39,.20,.33,-.49,-.10,.19)*f01+
                      glm::mat4(.27,.22,.43,.53,.18,-.17,.23,-.64,-.14,.02,-.10,.16,-.13,-.06,-.04,-.36)*f02+
                      glm::mat4(-.13,.29,-.29,.08,1.13,.02,-.83,.32,-.32,.04,-.31,-.16,.14,-.03,-.20,.39)*f03+
                      glm::vec4(.73,-4.28,-1.56,-1.80))/float(1.0)+f00;
    glm::vec4 f11=sin(glm::mat4(-1.11,.55,-.12,-1.00,.16,.15,-.30,.31,-.01,.01,.31,-.42,-.29,.38,-.04,.71)*f00+
                      glm::mat4(.96,-.02,.86,.52,-.14,.60,.44,.43,.02,-.15,-.49,-.05,-.06,-.25,-.03,-.22)*f01+
                      glm::mat4(.52,.44,-.05,-.11,-.56,-.10,-.61,-.40,-.04,.55,.32,-.07,-.02,.28,.26,-.49)*f02+
                      glm::mat4(.02,-.32,.06,-.17,-.59,.00,-.24,.60,-.06,.13,-.21,-.27,-.12,-.14,.58,-.55)*f03+
                      glm::vec4(-2.24,-3.48,-.80,1.41))/float(1.0)+f01;
    glm::vec4 f12=sin(glm::mat4(.44,-.06,-.79,-.46,.05,-.60,.30,.36,.35,.12,.02,.12,.40,-.26,.63,-.21)*f00+
                      glm::mat4(-.48,.43,-.73,-.40,.11,-.01,.71,.05,-.25,.25,-.28,-.20,.32,-.02,-.84,.16)*f01+
                      glm::mat4(.39,-.07,.90,.36,-.38,-.27,-1.86,-.39,.48,-.20,-.05,.10,-.00,-.21,.29,.63)*f02+
                      glm::mat4(.46,-.32,.06,.09,.72,-.47,.81,.78,.90,.02,-.21,.08,-.16,.22,.32,-.13)*f03+
                      glm::vec4(3.38,1.20,.84,1.41))/float(1.0)+f02;
    glm::vec4 f13=sin(glm::mat4(-.41,-.24,-.71,-.25,-.24,-.75,-.09,.02,-.27,-.42,.02,.03,-.01,.51,-.12,-1.24)*f00+
                      glm::mat4(.64,.31,-1.36,.61,-.34,.11,.14,.79,.22,-.16,-.29,-.70,.02,-.37,.49,.39)*f01+
                      glm::mat4(.79,.47,.54,-.47,-1.13,-.35,-1.03,-.22,-.67,-.26,.10,.21,-.07,-.73,-.11,.72)*f02+
                      glm::mat4(.43,-.23,.13,.09,1.38,-.63,1.57,-.20,.39,-.14,.42,.13,-.57,-.08,-.21,.21)*f03+
                      glm::vec4(-.34,-3.28,.43,-.52))/float(1.0)+f03;
    f00=sin(glm::mat4(-.72,.23,-.89,.52,.38,.19,-.16,-.88,.26,-.37,.09,.63,.29,-.72,.30,-.95)*f10+
            glm::mat4(-.22,-.51,-.42,-.73,-.32,.00,-1.03,1.17,-.20,-.03,-.13,-.16,-.41,.09,.36,-.84)*f11+
            glm::mat4(-.21,.01,.33,.47,.05,.20,-.44,-1.04,.13,.12,-.13,.31,.01,-.34,.41,-.34)*f12+
            glm::mat4(-.13,-.06,-.39,-.22,.48,.25,.24,-.97,-.34,.14,.42,-.00,-.44,.05,.09,-.95)*f13+
            glm::vec4(.48,.87,-.87,-2.06))/float(1.4)+f10;
    f01=sin(glm::mat4(-.27,.29,-.21,.15,.34,-.23,.85,-.09,-1.15,-.24,-.05,-.25,-.12,-.73,-.17,-.37)*f10+
            glm::mat4(-1.11,.35,-.93,-.06,-.79,-.03,-.46,-.37,.60,-.37,-.14,.45,-.03,-.21,.02,.59)*f11+
            glm::mat4(-.92,-.17,-.58,-.18,.58,.60,.83,-1.04,-.80,-.16,.23,-.11,.08,.16,.76,.61)*f12+
            glm::mat4(.29,.45,.30,.39,-.91,.66,-.35,-.35,.21,.16,-.54,-.63,1.10,-.38,.20,.15)*f13+
            glm::vec4(-1.72,-.14,1.92,2.08))/float(1.4)+f11;
    f02=sin(glm::mat4(1.00,.66,1.30,-.51,.88,.25,-.67,.03,-.68,-.08,-.12,-.14,.46,1.15,.38,-.10)*f10+
            glm::mat4(.51,-.57,.41,-.09,.68,-.50,-.04,-1.01,.20,.44,-.60,.46,-.09,-.37,-1.30,.04)*f11+
            glm::mat4(.14,.29,-.45,-.06,-.65,.33,-.37,-.95,.71,-.07,1.00,-.60,-1.68,-.20,-.00,-.70)*f12+
            glm::mat4(-.31,.69,.56,.13,.95,.36,.56,.59,-.63,.52,-.30,.17,1.23,.72,.95,.75)*f13+
            glm::vec4(-.90,-3.26,-.44,-3.11))/float(1.4)+f12;
    f03=sin(glm::mat4(.51,-.98,-.28,.16,-.22,-.17,-1.03,.22,.70,-.15,.12,.43,.78,.67,-.85,-.25)*f10+
            glm::mat4(.81,.60,-.89,.61,-1.03,-.33,.60,-.11,-.06,.01,-.02,-.44,.73,.69,1.02,.62)*f11+
            glm::mat4(-.10,.52,.80,-.65,.40,-.75,.47,1.56,.03,.05,.08,.31,-.03,.22,-1.63,.07)*f12+
            glm::mat4(-.18,-.07,-1.22,.48,-.01,.56,.07,.15,.24,.25,-.09,-.54,.23,-.08,.20,.36)*f13+
            glm::vec4(-1.11,-4.28,1.02,-.23))/float(1.4)+f13;
    return dot(f00,glm::vec4(.09,.12,-.07,-.03))+dot(f01,glm::vec4(-.04,.07,-.08,.05))+
           dot(f02,glm::vec4(-.01,.06,-.02,.07))+dot(f03,glm::vec4(-.05,.07,.03,.04))-0.16;
}

double Translate::Value(const Vector &p) const {
    return node->Value(p - t);
}

double RotationX::Value(const Vector &p) const {
    glm::vec3 q(p[0], p[1], p[2]);
    // Theta to radians
    double theta_rad = glm::radians(theta);
    glm::mat3 m = glm::mat3(1.0, 0.0, 0.0,
                            0.0, cos(theta_rad), -sin(theta_rad),
                            0.0, sin(theta_rad), cos(theta_rad));
    q = m * q;
    return node->Value(Vector(q[0], q[1], q[2]));
}

double RotationY::Value(const Vector &p) const {
    glm::vec3 q(p[0], p[1], p[2]);
    double theta_rad = glm::radians(theta);
    glm::mat3 m = glm::mat3(cos(theta_rad), 0.0, sin(theta_rad),
                            0.0, 1.0, 0.0,
                            -sin(theta_rad), 0.0, cos(theta_rad));
    q = m * q;
    return node->Value(Vector(q[0], q[1], q[2]));
}

double RotationZ::Value(const Vector &p) const {
    glm::vec3 q(p[0], p[1], p[2]);
    double theta_rad = glm::radians(theta);
    glm::mat3 m = glm::mat3(cos(theta_rad), -sin(theta_rad), 0.0,
                            sin(theta_rad), cos(theta_rad), 0.0,
                            0.0, 0.0, 1.0);
    q = m * q;
    return node->Value(Vector(q[0], q[1], q[2]));
}

double Scale::Value(const Vector &p) const {
    Vector q = p;
    q *= s.Inverse();
    return node->Value(q);
}

double Union::Value(const Vector &p) const {
    return std::min(node1->Value(p), node2->Value(p));
}


double Intersection::Value(const Vector &p) const {
    return std::max(node1->Value(p), node2->Value(p));
}


double Subtraction::Value(const Vector &p) const {
    return std::max(node1->Value(p), -node2->Value(p));
}


double Melange::Value(const Vector &p) const {
    return Math::Lerp(node1->Value(p), node2->Value(p), k);
}


double SmoothUnion::Value(const Vector &p) const {
    double d1 = node1->Value(p);
    double d2 = node2->Value(p);
    double h = Math::Clamp(0.5 + 0.5 * (d2 - d1) / k, 0.0, 1.0);
    return Math::Lerp(d2, d1, h) - k * h * (1.0 - h);
}


double SmoothSubtraction::Value(const Vector &p) const {
    double d1 = node1->Value(p);
    double d2 = node2->Value(p);
    double h = Math::Clamp(0.5 - 0.5 * (d2 + d1) / k, 0.0, 1.0);
    return Math::Lerp(d2, -d1, h) + k * h * (1.0 - h);
}


double SmoothIntersection::Value(const Vector &p) const {
    double d1 = node1->Value(p);
    double d2 = node2->Value(p);
    double h = Math::Clamp(0.5 - 0.5 * (d2 - d1) / k, 0.0, 1.0);
    return Math::Lerp(d2, d1, h) + k * h * (1.0 - h);
}





