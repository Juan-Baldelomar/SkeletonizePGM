//
// Created by juan on 27/11/20.
//

#include "ImgProcessing.h"
#include "Tools.h"
#include "math.h"


double perpendicularDistance(point p, point q){
    double delta_x = p.x - q.x;
    double delta_y = p.y - q.y;
    return sqrt(delta_x*delta_x + delta_y*delta_y);
}

void cleanPixels(vector<vector<pixel>>&pixels){
    int n = pixels.size(), m = 0;
    if (n>0) m = pixels[0].size();
    for (int i = 0; i<n; i++)
        for (int j = 0; j<m; j++)
            pixels[i][j] = 0;
}

void Pattern::setValues(pixel values[3][3]) {
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            matrix[i][j] = values[i][j];
}

void specialPattern::setValues(pixel values[4][4]) {
    for (int i = 0; i<4; i++)
        for (int j = 0; j<4; j++)
            matrix[i][j] = values[i][j];
}


Pattern::Pattern() {}

// build Pattern for a pixel
Pattern::Pattern(int i_c, int j_c, vector<vector<pixel>> &pixels) {
    int n = pixels.size();
    int m = pixels[0].size();

    for (int i = -1; i<= 1; i++){
        for (int j = -1; j<= 1; j++){

            int i_coord = i + i_c, j_coord = j + j_c;                         // coordinates of neighbors of pixel[i_c][j_c]
            if (i_coord < 0 || i_coord >= n || j_coord < 0 || j_coord >= m)   //image out of bounds
                matrix[i+1][j+1] = -1;                                        //real i, j index starts from 0, so -> i+1, j+1
            else
                matrix[i+1][j+1] = pixels[i_coord][j_coord];
        }
    }
    matrix[1][1] = 'c';                                                       //center pixel always has 'c' as value
    p8 = j_c + 2 < m? pixels[i_c][j_c + 2] : '-';                             // p8 and p9 for C and D Pattern
    p9 = i_c + 2 < n? pixels[i_c + 2][j_c] : '-';
}

void Pattern::print() {
    for (int i = 0; i<3; i++){
        for (int j = 0; j<3; j++){
            if (matrix[i][j] == 255 || matrix[i][j] == 0)
                cout << (int)matrix[i][j] << setw(5);
            else
                cout << matrix[i][j] << setw(5);
        }
        cout << setw(0);
        cout << endl;
    }
    if (p8 == 0 || p8 == 255)
        cout << "p8: " << (int)p8;
    else
        cout << "p8: " << p8;

    if (p9 == 0 || p9 == 255)
        cout << "  p9: " << (int)p9;
    else
        cout << "  p9: " << p9;
    cout << endl << endl;
}

ImgProcessing::ImgProcessing() {
    setPatterns();
}

void ImgProcessing::setPatterns() {
    pixel  v_A[3][3] = {{255, 255, 'y'},{255, 'c', 0},{255,255,'y'}};
    pixel  v_B[3][3] = {{255, 255, 255},{255, 'c', 255},{'y',0,'y'}};
    pixel  v_C[3][3] = {{'y', 255, 255},{0, 'c', 255},{'y',255,255}};
    pixel  v_D[3][3] = {{'y', 0, 'y'},{255, 'c', 255},{255,255,255}};
    pixel  v_E[3][3] = {{'x', 0, 0},{255, 'c', 0},{'x',255,'x'}};
    pixel  v_F[3][3] = {{'x', 255, 255},{0, 'c', 255},{0,0,'x'}};
    pixel  v_G[3][3] = {{0, 255, 0},{0, 'c', 255},{0,0,0}};
    pixel  v_H[3][3] = {{'x', 255, 'x'},{255, 'c', 0},{'x',0,0}};
    pixel  v_I[3][3] = {{0, 0, 'x'},{0, 'c', 255},{'x',255,255}};
    pixel  v_J[3][3] = {{0, 0, 0},{0, 'c', 255},{0,255,0}};
    pixel  v_K[3][3] = {{0, 0, 0},{0, 'c', 0},{255,255,255}};
    pixel  v_L[3][3] = {{255, 0, 0},{255, 'c', 0},{255,0,0}};
    pixel  v_M[3][3] = {{255, 255, 255},{0, 'c', 0},{0,0,0}};
    pixel  v_N[3][3] = {{0, 0, 255},{0, 'c', 255},{0,0,255}};

    pixel  v_O[4][4] = {{'x', 255, 'x', 255}, {255, 'x', 255, 255}, {'x', 255, 'c', 255}, {255, 255, 255, 0}};
    pixel  v_P[4][4] = {{255, 'x', 255, 'x'}, {255, 255, 'x', 255}, {255, 'c', 255, 'x'}, {0, 255, 255, 255}};
    pixel  v_Q[4][4] = {{0, 255, 255 ,255}, {255, 'c', 255, 'x'}, {255, 255, 'x', 255}, {255, 'x', 255, 'x'}};
    pixel  v_S[4][4] = {{255, 255, 255, 0}, {'x', 255, 'c', 255}, {255, 'x', 255, 255}, {'x', 255, 'x', 255}};

    pixel v_Middle[3][3] = {{255,255,255}, {255,255,255}, {255,255,255}};

    A.setValues(v_A);
    B.setValues(v_B);
    C.setValues(v_C);
    D.setValues(v_D);
    E.setValues(v_E);
    F.setValues(v_F);
    G.setValues(v_G);
    H.setValues(v_H);
    I.setValues(v_I);
    J.setValues(v_J);
    K.setValues(v_K);
    L.setValues(v_L);
    M.setValues(v_M);
    N.setValues(v_N);
    O.setValues(v_O);
    P.setValues(v_P);
    Q.setValues(v_Q);
    S.setValues(v_S);
    MIDDLE.setValues(v_Middle);

    C.p8 = 1;
    D.p9 = 1;
}


char ImgProcessing::getPattern(Pattern &patt) {
    if (patt == MIDDLE)
        return 0;
    if (patt == A)
        return 'A';
    if (patt == B)
        return 'B';
    if (patt == C)
        return 'C';
    if (patt == D)
        return 'D';
    if (patt == E)
        return 'E';
    if (patt == F)
        return 'F';
    if (patt == G)
        return 'G';
    if (patt == H)
        return 'H';
    if (patt == I)
        return 'I';
    if (patt == J)
        return 'J';
    if (patt == K)
        return 'K';
    if (patt == L)
        return 'L';
    if (patt == M)
        return 'M';
    if (patt == N)
        return 'N';

    return 0;   //no Pattern match
}



void ImgProcessing::getSkeleton(vector<vector<pixel>> &pixels){
    int n = pixels.size();
    int m = pixels[0].size();

    bool flag;
    do{
        flag = false;
        for (int i = 0; i<n; i++){
            for (int j = 0; j<m; j++){
                pixel &p = pixels[i][j];
                if (p==0) continue;
                Pattern patt(i, j, pixels);
                char patternID = getPattern(patt);
                if (patternID != 0){
                    p = 0; flag = true;
                }
            }
        }
    }while (flag);
}

vector<vector<pixel>> ImgProcessing::extractPixels(vector<vector<pixel>> &pixels) {
    int n = pixels.size(), m = 0;
    if (n>0) m = pixels[0].size();
    vector<vector<pixel>> copy(n, vector<pixel>(m, 0));

    for (int i = 0; i<n; i++)
        for (int j = 0; j<m; j++)
            copy[i][j] = pixels[i][j];

    return copy;
}

void ImgProcessing::getPoints(vector<vector<pixel>> &pixels) {
    int n = pixels.size(), m = 0;
    if (n>0) m = pixels[0].size();

    //clean previous points
    lines.clear();

    //create copy of pixels to work with
    vector<vector<pixel>> pixelsCopy = extractPixels(pixels);

    // create queue
    queue<point> cola;

    // find first pixel != 0
    for (int i = 0; i<n; i++){
        for (int j = 0; j<m; j++){
            if (pixelsCopy[i][j] == 255){
                lines.push_back(line());                 // push new line
                cola.push(point(i, j));               // push point in queue
                pixelsCopy[i][j] = 0;                    // erase point to avoid processing it again
            }
            while(!cola.empty()){
                point p = cola.front();
                lines.back().push_back(p);

                int neighborsCount = pushNeighbors(p, pixelsCopy, cola);
                if (neighborsCount > 1){                // biffurcation reached
                    lines.push_back(line());            // create new line
                }
                cola.pop();
            }
        }
    }

    // start traversing line following 255 values and setting to 0 values already traversed
        //if a pixel has more than one neighbor  with 255 we reached biffurcation, push all neighbors to queue and set current point as end
}

int ImgProcessing::pushNeighbors(point center, vector<vector<pixel>> &pixels, queue<point> &cola) {
    int n = pixels.size(), m = 0;
    if (n>0) m = pixels[0].size();

    int neighborsCount = 0;
    // review 8_neighbors
    for (int i = -1; i<=1; i++){
        for (int j = -1; j<=1; j++){
            if (i + center.x >= 0 && i+center.x < n && j + center.y >= 0 && j+center.y < m
                && pixels[i + center.x][j + center.y] == 255){

                cola.push(point(i+center.x, j+center.y));
                neighborsCount++;
                pixels[i+center.x][j+center.y] = 0;                        // erase point to avoid processing it again
            }
        }
    }
    return neighborsCount;
}

// function to draw the lines that are in the vector<vector<line>> lines
void ImgProcessing::drawLines(vector<vector<pixel>> &pixels) {
    cleanPixels(pixels);
    for (auto l : lines){
        for (auto p:l){
            pixels[p.x][p.y]=255;
        }
    }
}

void ImgProcessing::printLines() {
    cout << "-------------- PRINTING LINES --------------" << endl;
    for (auto l: lines){
        for (auto p:l){
            cout << "(" << p.x << ", " << p.y << ") \t";
        }
        cout << endl;
    }
}

void ImgProcessing::DecimateLines(double epsilon) {
    int n = lines.size();
    for (int i = 0; i<n; i++){
        line l = DouglasPeucker(lines[i], epsilon);
        lines[i].clear();
        for (auto p: l)
            lines[i].push_back(p);
    }
}

line ImgProcessing::DouglasPeucker(line &l, double epsilon) {
    int n = l.size();
    double dmax = 0;
    int index = 0;

    for (int i = 1; i<n; i++){
        point p = l[i-1], q = l[i];
        double distance = perpendicularDistance(p, q);
        if (distance > dmax){
            dmax = distance;
            index = i;
        }
    }

    line ResultLine;
    if (dmax > epsilon){
        line RL1, RL2;
        splitLine(l, RL1, RL2, 1, index, n);

        RL1 = DouglasPeucker(RL1, epsilon);
        RL2 = DouglasPeucker(RL2, epsilon);

        mergeLine(RL1, RL2, ResultLine);
    }else{
        for (auto p:l)
            ResultLine.push_back(p);
    }
    return ResultLine;
}

void ImgProcessing::splitLine(line &l,  line &l1, line &l2, int start, int split_index, int end) {
    int n = l.size();
    for (int i = start; i<split_index; i++)
        l1.push_back(l[i]);

    for (int i = split_index; i<end && i < n; i++)
        l2.push_back(l[i]);
}

void ImgProcessing::mergeLine(line &l1, line &l2, line &result) {
    for (auto p : l1)
        result.push_back(p);

    for (auto p: l2)
        result.push_back(p);
}


void ImgProcessing::getSplinesLines() {
    int n = lines.size();
    for (int i = 0; i<n; i++){
        vector<double> x_ = generateXVector(lines[i]);
        vector<double> f_ = generateYVector(lines[i]);
        Splines splines(x_, f_);
        line l = splines.getCurve();
        lines[i].clear();
        for (auto p : l)
            lines[i].push_back(p);
    }
}

vector<double> ImgProcessing::generateXVector(line l) {
    vector<double> x_;
    for (auto p : l){
        x_.push_back(p.x);
    }
    return x_;
}

vector<double> ImgProcessing::generateYVector(line l) {
    vector<double> y_;
    for (auto p : l){
        y_.push_back(p.y);
    }
    return y_;
}

void ImgProcessing::getExtremePoints(line l, int &a, int &b) {
    a = l[0].x;
    b = l[0].x;
    for (auto p : l){
        if (p.x < a)
            a = p.x;
        if (p.x > b)
            b = p.x;
    }
}

// Pattern B is always one of the predefined patterns of above
bool operator ==(Pattern& A, Pattern &B){
    /*cout << "A: " << endl;
    A.print();
    cout << "B: " << endl;
    B.print();*/

    bool y_flag = false;
    int y_counter = 0;
    for (int i = 0; i<3; i++){
        for (int j = 0; j<3; j++){
            if (A.matrix[i][j] == 'c')                   // ignore c element
                continue;

            if (B.matrix[i][j] != 'x' && A.matrix[i][j] != B.matrix[i][j]){                 // if B[i][j] and A[i][j] dont match
                 y_flag |= B.matrix[i][j] == 'y';                                           // is element in B[i][j] y ?
                if (B.matrix[i][j] == 'y' && A.matrix[i][j] == 0){
                    y_counter++;                                                            // if it is 'y' and A[i][j] == 0 at least one of y's is 0
                }else{
                    return false;                                                           // patterns dont match
                }
            }
        }
    }
    if ((B.p8 != '-' && A.p8 != B.p8) || (B.p9 != '-' && A.p9 != B.p9) )
        return false;

    return y_flag? y_counter>0 : true;         // if y_flag not activated return true, is it is then y_counter must be greater than 0 to return true
}

bool operator ==(const specialPattern& A, const specialPattern &B){
    bool y_flag = false;
    int y_counter = 0;
    for (int i = 0; i<4; i++){
        for (int j = 0; j<4; j++){
            if (A.matrix[i][j] == 'c')                   // ignore c point
                continue;

            if (B.matrix[i][j] != 'x' && A.matrix[i][j] != B.matrix[i][j]){                 // if B[i][j] and A[i][j] dont match
                return false;
            }
        }
    }
    return true;
}
