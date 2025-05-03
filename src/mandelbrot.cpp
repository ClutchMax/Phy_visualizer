#include <iostream>
#include <fstream>

using namespace std;



int findMandelbrot(double cr, double ci, int max_iter){
    int i = 0;
    double zr = 0.0, zi = 0.0;
    while ( i < max_iter && (zr*zr + zi*zi < 4.0)){
        double temp = zr*zr - zi*zi + cr;
        zi = 2.0 * zr * zi + ci;
        zr = temp;
        i++;
    }
    return i;
}

double mapToReal(int x, int imgWidth, double minR, double maxR){
    double range = maxR - minR;
    return x * (range / imgWidth) + minR;
}

double mapToImaginary(int y, int imgHeight, double minI, double maxI){
    double range = maxI - minI;
    return y * (range / imgHeight) + minI;
}


int main(int argc, char** argv){

    

    int imgWidth = 1024;
    int imgHeight = 1024;
    int maxN = 2000;

    double minR = -1.5;
    double maxR = 0.7;
    double minI = -1.0;
    double maxI = 1.0;


    ofstream fout("output_img.ppm");
    fout << "P3" << endl;
    fout << imgWidth << " " << imgHeight << " " << endl;
    fout << "256" << endl;



    for(int y = 0 ; y < imgHeight ; y++){
        for(int x = 0 ; x < imgWidth ; x++){
            double cr = mapToReal(x, imgWidth, minR, maxR);
            double ci = mapToImaginary(y, imgHeight, minI, maxI);

            int n = findMandelbrot(cr, ci, maxN);

            int r = ((n) %256);
            int g = (n%256);
            int b = (n%256);

            fout << r << " " << g << " " << b << " ";
        }
        fout << endl;
    }
    fout.close();

    return 0;
}