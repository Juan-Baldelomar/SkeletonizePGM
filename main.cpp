#include <iostream>

#include "PGMImage.h"
#include "ImgProcessing.h"
#include "Tools.h"

int main() {
    PGMImage image("Input/1_gt.pgm");
    //PGMImage image("Output/img1.pgm");
    ImgProcessing imgP;
    imgP.getSkeleton(image.pixels);
    imgP.getPoints(image.pixels);
    imgP.printLines();
    imgP.DecimateVisvalingam(0.5);
    imgP.printLines();
    imgP.getSplinesLines();
    imgP.printLines();
    imgP.drawLines(image.pixels);

    imgP.hausdorff();

    cout << imgP.errors << endl;
    image.writeFile("Output/img1.pgm");
    return 0;
}
