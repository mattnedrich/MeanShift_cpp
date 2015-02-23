#include <stdio.h>
#include "MeanShift.h"
#include <vector>
#include <string>
#include <stdlib.h>
#include <sstream>

using namespace std;

vector<vector<double> > load_points(std::string filename) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen(filename.c_str(), "r");
    vector<vector<double> > points;
    while ((read = getline(&line, &len, fp)) != -1) {
        std::string str(line);
        std::istringstream ss(str);
        std::string token;
        double x, y;
        int i = 0;
        while(std::getline(ss, token, ',')){
            // printf("%s", token.c_str());
            if(i % 2 == 0){
                x = stod(token);
            } else {
                y = stod(token);
                vector<double> point;
                point.push_back(x);
                point.push_back(y);
                points.push_back(point);
            }
            i++;
        }
    }
    fclose(fp);
    return points;
}

void print_points(vector<vector<double> > points){
    for(int i=0; i<points.size(); i++){
        for(int dim = 0; dim<points[i].size(); dim++) {
            printf("%f ", points[i][dim]);
        }
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    vector<vector<double> > points = load_points("test_simple.csv");
    MeanShift *msp = new MeanShift(NULL);
    double kernel_bandwidth = 3;
    vector<vector<double> > shifted_points = msp->cluster(points, kernel_bandwidth);
    for(int i=0; i<shifted_points.size(); i++){
        for(int dim = 0; dim<shifted_points[i].size(); dim++) {
            printf("%f ", shifted_points[i][dim]);
        }
        printf("\n");
    }
    return 0;
}