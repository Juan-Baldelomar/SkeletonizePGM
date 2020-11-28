//
// Created by juan on 27/11/20.
//

#ifndef PROYECTO_PA1_IMGPROCESSING_H
#define PROYECTO_PA1_IMGPROCESSING_H

#include "vector"
#include "iostream"
using namespace std;

typedef unsigned char pixel;

struct Pattern{
public:
    pixel matrix[3][3];
    pixel p8 = '-', p9 = '-';
    Pattern();
    Pattern(int i_c, int j_c, vector<vector<pixel>> &pixels);
    void setValues(pixel values[3][3]);
    void print();
};

struct specialPattern{
public:
    pixel matrix[5][5];
    void setValues(pixel values[4][4]);
};

class ImgProcessing{
public:
    Pattern A, B, C, D, E, F, G, H, I, J, K, L, M, N, MIDDLE;
    specialPattern O, P, Q, S;
    ImgProcessing();
    void setPatterns();
    char getPattern(Pattern &patt);
    void getSkeleton(vector<vector<pixel>> &pixels);
    void getPoints(vector<vector<pixel>> &pixels);
};

bool operator ==( Pattern& A,  Pattern &B);
bool operator ==(const specialPattern& A, const specialPattern &B);

#endif //PROYECTO_PA1_IMGPROCESSING_H
