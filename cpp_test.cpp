#include <stdio.h>
#include <stdlib.h>
#include "MeanShift.h"

using namespace std;

vector<vector<double> > load_points(const char *filename) {
    vector<vector<double> > points;
    FILE *fp = fopen(filename, "r");
    char line[50];
    while (fgets(line, sizeof(line), fp) != NULL) {
        double x, y;
        char *x_str = line;
        char *y_str = line;
        while (*y_str != '\0') {
            if (*y_str == ',') {
                *y_str++ = 0;
                x = atof(x_str);
                y = atof(y_str);
                vector<double> point;
                point.push_back(x);
                point.push_back(y);
                points.push_back(point);
                break;
            }
            ++y_str;
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
    MeanShift *msp = new MeanShift();
    double kernel_bandwidth = 3;

    vector<vector<double> > points = load_points("test.csv");
    vector<vector<double> > shifted_points = msp->cluster(points, kernel_bandwidth);

    FILE *fp = fopen("result.csv", "w");
    if(!fp){
        perror("Couldn't write result.csv");
        exit(0);
    }
    for(int i=0; i<shifted_points.size(); i++){
        for(int dim = 0; dim<shifted_points[i].size(); dim++) {
            printf("%f ", shifted_points[i][dim]);
            fprintf(fp, dim?",%f":"%f", shifted_points[i][dim]);
        }
        printf("\n");
        fprintf(fp, "\n");
    }
    fclose(fp);
    return 0;
}
