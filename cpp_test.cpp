#include <stdio.h>
#include "MeanShift.h"
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
    vector<vector<double> > allPoints;
    vector<double> point1;
    point1.push_back(0);
    point1.push_back(0);
    vector<double> point2;
    point2.push_back(1);
    point2.push_back(1);
    vector<double> point3;
    point3.push_back(0);
    point3.push_back(1);
    vector<double> point4;
    point4.push_back(.5);
    point4.push_back(.5);
    vector<double> point5;
    point5.push_back(1);
    point5.push_back(0);
    allPoints.push_back(point1);
    allPoints.push_back(point2);
    allPoints.push_back(point3);
    allPoints.push_back(point4);
    allPoints.push_back(point5);
    MeanShift *msp = new MeanShift(NULL);
    vector<vector<double> > shifted_points = msp->cluster(allPoints, .9);
    for(int i=0; i<shifted_points.size(); i++){
        for(int dim = 0; dim<shifted_points[i].size(); dim++) {
            printf("%f ", shifted_points[i][dim]);
        }
        printf("\n");
    }
    return 0;
}