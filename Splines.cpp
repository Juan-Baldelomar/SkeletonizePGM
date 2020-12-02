//
// Created by juan on 28/11/20.
//

#include "Splines.h"
#include "math.h"
#include "stack"

void Triangular_Superior(vector<vector<double> > &U, vector<double> &b, vector<double> &x) {
    int n = U.size();
    double X[n];

    for (int i = n - 1; i >= 0; i--) {
        double acc = 0;
        for (int j = n - 1; j > i; j--) {
            acc += U[i][j] * x[j];
        }
        if (U[i][i] == 0)
            cout << "Triangular Sup  Msg WARNING: A_[" << i << ", " << i << "] es nulo, se dividira por 0" << endl;

        x[i] = (b[i] - acc) / U[i][i];
    }
}

void Partial_pivot(vector<vector<double> > &A, int k, vector<double> &b) {
    int n = A.size();
    int i_max = k;
    double max = fabs(A[k][k]);

    //find MAX
    for (int i = k + 1; i < n; i++) {
        if (fabs(A[i][k]) > max) {
            i_max = i;
            max = fabs(A[i][k]);
        }
    }

    double temp;
    // swap file
    if (i_max != k) {
        for (int j = 0; j < n; j++) {
            temp = A[k][j];
            A[k][j] = A[i_max][j];
            A[i_max][j] = temp;
        }
        temp = b[k];
        b[k] = b[i_max];
        b[i_max] = temp;
    }
}

void Eliminacion_Gaussiana(vector<vector<double> > &A, vector<double> &b, vector<double> &x) {

    int n = A.size();
    //indice k indica la fila con la cual estamos transformando a una Triangular Superior
    for (int k = 0; k < n - 1; k++) {

        if (A[k][k] == 0)
            Partial_pivot(A, k, b);

        if (A[k][k] == 0)
            cout << "GEM  Msg WARNING: A_[" << k << ", " << k << "] es nulo, se dividira por 0" << endl;

        for (int i = k + 1; i < n; i++) {
            double m_ik = A[i][k] / A[k][k];
            for (int j = k; j < n; j++) {
                A[i][j] = A[i][j] - m_ik * A[k][j];
            }
            b[i] = b[i] - m_ik * b[k];
        }
    }
    Triangular_Superior(A, b, x);
}


Splines::Splines(vector<double> &x_, vector<double> &f_) {
    int n = x_.size();
    vector<double> xsegment_, fsegment_;
    int i = 0;
    while(i + 1<n){
        while (i + 1 < n && x_[i] <= x_[i + 1]) {
            if (x_[i] != x_[i+1]){
                xsegment_.push_back(x_[i]);
                fsegment_.push_back(f_[i]);
            }
            i++;
        }
        if (i<n && xsegment_.size() > 0){
            xsegment_.push_back(x_[i]);
            fsegment_.push_back(f_[i]);
        }
        buildSplineSegment(xsegment_, fsegment_);
        xsegment_.clear();
        fsegment_.clear();

        while( i + 1 < n && x_[i] == x_[i+1]){

        }

        stack<int> stk;
        while( i+1 < n && x_[i] >= x_[i+1]){
            if (x_[i] != x_[i+1])               //ignore points with same x (not a funcion)
                stk.push(i);
            i++;
        }
        if (i <n && stk.size()>0){
            stk.push(i);
        }

        while(!stk.empty()){
            int index = stk.top();
            xsegment_.push_back(x_[index]);
            fsegment_.push_back(f_[index]);
            stk.pop();
        }
        buildSplineSegment(xsegment_, fsegment_);
        xsegment_.clear();
        fsegment_.clear();
    }
}

void Splines::buildSplineSegment(vector<double> &x_, vector<double> &f_) {
    int n = x_.size();
    if (n <= 1) return;

    this->x_.push_back(vector<double>());
    this->f_.push_back(vector<double>());
    for (int i = 0; i<n; i++){
        this->x_.back().push_back(x_[i]);
        this->f_.back().push_back(f_[i]);
    }

    if (n<2) return;

    //build system
    vector<vector<double>> A(n-2, vector<double>(n-2, 0));
    vector<double> X(n-2, 0);
    vector<double> b(n-2, 0);

    if (n-2 > 1){
        for (int i = 1; i<n-1; i++){
            double h_i = x_[i] - x_[i-1];
            double h_ip = x_[i+1] - x_[i];
            int index = i-1;                            //i starts in 1, but matrix index starts in 0
            if (index == 0){
                A[index][0] = (h_i + h_ip)/3.0;
                A[index][1] = h_ip/6.0;
            }else if (index == n-3){
                A[index][index-1] = h_i/6.0;
                A[index][index] = (h_i + h_ip)/3.0;
            }else{
                A[index][index - 1] = h_i/6.0;
                A[index][index] = (h_i + h_ip)/3.0;;
                A[index][index + 1] = h_ip/6.0;
            }
            // 6/h^2 * (f_{i+1} -2 f_i + f_{i-1})
            b[index] = (1/h_ip) * (f_[i+1] - f_[i]) - 1/h_i * (f_[i] - f_[i-1]);
        }
    }else if (n-2 == 1){
        double h_i = x_[1] - x_[0];
        double h_ip = x_[2] - x_[1];
        A[0][0] = (h_i + h_ip)/3.0;
        b[0] = (1/h_ip) * (f_[2] - f_[1]) - 1/h_i * (f_[1] - f_[2]);
    }

    // calculate M

    Eliminacion_Gaussiana(A, b, X);
    M.push_back(vector<double>());
    M.back().push_back(0);             //M_0 = 0
    for (double sol : X)
        M.back().push_back(sol);

    M.back().push_back(0);               //M_n = 0
}

double Splines::P(double x, int i, int row) {
    int n = x_[0].size();

    if (n == 1) return f_[row][0];

    double h = x_[row][i] - x_[row][i-1];
    double a, b, c, d, e, f;

    a = (1.0/(6*h)) * pow(x_[row][i] - x, 3) * M[row][i-1];
    b = (1.0/(6*h)) * pow(x - x_[row][i-1], 3) * M[row][i];
    c = x/h * (f_[row][i] - f_[row][i-1]);
    d = -x/6.0 * (M[row][i] - M[row][i-1]) * h;
    e = 1/h * (x_[row][i] * f_[row][i-1] - x_[row][i-1] * f_[row][i]);
    f = -1/6.0 * (x_[row][i] * M[row][i-1] - x_[row][i-1] * M[row][i]) * h;

    return a + b + c + d + e + f;
}

//same method as P but when x_i > x_{i+1}
/*double Splines::reverseP(double x, int i) {
    int n = x_.size();
    if (n == 1) return f_[0];
    double h = x_[i-1] - x_[i];
    double a, b, c, d, e, f;

    a = (1/(6*h)) * pow(x_[i-1] - x, 3) * M[i];
    b = (1/(6*h)) * pow(x - x_[i], 3) * M[i-1];
    c = x/h * (f_[i-1] - f_[i]);
    d = -x/6 * (M[i-1] - M[i]) * h;
    e = 1/h * (x_[i-1] * f_[i] - x_[i] * f_[i-1]);
    f = -1/6 * (x_[i-1] * M[i] - x_[i] * M[i-1]) * h;

    return a + b + c + d + e + f;
}*/

vector<point> Splines::getCurve() {
    int n = x_.size();
    line l;
    for (int row = 0; row<n; row++){
        for (int i = 1; i<x_[row].size(); i++){
            int a = x_[row][i-1];
            int b = x_[row][i];
            int x = a;
            while(x<=b){
                int fx = P(x, i, row);
                l.push_back(point(x, fx));
                x++;
            }
        }
    }
    return  l;
}

