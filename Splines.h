//
// Created by juan on 28/11/20.
//

#ifndef PROYECTO_PA1_SPLINES_H
#define PROYECTO_PA1_SPLINES_H

#include <vector>
#include "Tools.h"
#include "ImgProcessing.h"

struct point;

using namespace std;

class Splines {
private:
    vector<vector<double>>M;
    vector<vector<double>>x_;
    vector<vector<double>>f_;
public:
    Splines(vector<double> &x_, vector<double> &f_);
    void buildSplineSegment(vector<double> &x_, vector<double> &f_);
    vector<point> getCurve();
    double P(double x, int i, int row);
    double reverseP(double x, int i);
};


#endif //PROYECTO_PA1_SPLINES_H
