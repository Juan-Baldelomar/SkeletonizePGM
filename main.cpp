#include <iostream>

#include "PGMImage.h"
#include "ImgProcessing.h"
#include "Tools.h"

int main() {
    PGMImage image("Input/1_gt.pgm");
    //PGMImage image("Output/img1.pgm");
    //cout << image.pixels << endl;
    ImgProcessing imgP;
    imgP.getSkeleton(image.pixels);
    imgP.getPoints(image.pixels);
    cout << imgP.lines.size() << endl;
    imgP.drawLines(image.pixels);
    image.writeFile("Output/img1.pgm");
    return 0;
}
