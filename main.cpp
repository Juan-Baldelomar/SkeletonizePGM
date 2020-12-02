#include <iostream>

#include "PGMImage.h"
#include "ImgProcessing.h"
#include "Tools.h"

int main() {
    vector<double> x, y;
    x.push_back(0); y.push_back(1);
    x.push_back(1); y.push_back(-8);
    x.push_back(2); y.push_back(-30);
    x.push_back(3); y.push_back(-59);
    Splines splines(x, y);
    cout << splines.P(2.6, 3,0) << endl;



    PGMImage image("Input/1_gt.pgm");
    //PGMImage image("Output/img1.pgm");
    //cout << image.pixels << endl;
    ImgProcessing imgP;
    imgP.getSkeleton(image.pixels);
    imgP.getPoints(image.pixels);
    imgP.printLines();
    imgP.DecimateLines(0.5);
    imgP.printLines();
    imgP.getSplinesLines();
    imgP.printLines();
    imgP.drawLines(image.pixels);
    //cout << image.pixels << endl;
    image.writeFile("Output/img1.pgm");
    return 0;
}
