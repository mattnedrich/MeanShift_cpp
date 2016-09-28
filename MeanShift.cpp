#include <stdio.h>
#include <math.h>
#include "MeanShift.h"

using namespace std;

#define EPSILON 0.0000001

double euclidean_distance(const vector<double> &point_a, const vector<double> &point_b){
    double total = 0;
    for(int i=0; i<point_a.size(); i++){
        total += (point_a[i] - point_b[i]) * (point_a[i] - point_b[i]);
    }
    return sqrt(total);
}

double gaussian_kernel(double distance, double kernel_bandwidth){
    double temp =  exp(-1.0/2.0 * (distance*distance) / (kernel_bandwidth*kernel_bandwidth));
    return temp;
}

void MeanShift::set_kernel( double (*_kernel_func)(double,double) ) {
    if(!_kernel_func){
        kernel_func = gaussian_kernel;
    } else {
        kernel_func = _kernel_func;    
    }
}

vector<double> MeanShift::shift_point(const vector<double> &point, const vector<vector<double> > &points, double kernel_bandwidth) {
    vector<double> shifted_point = point;
    for(int dim = 0; dim<shifted_point.size(); dim++){
        shifted_point[dim] = 0;
    }
    double total_weight = 0;
    for(int i=0; i<points.size(); i++){
        vector<double> temp_point = points[i];
        double distance = euclidean_distance(point, temp_point);
        double weight = kernel_func(distance, kernel_bandwidth);
        for(int j=0; j<shifted_point.size(); j++){
            shifted_point[j] += temp_point[j] * weight;
        }
        total_weight += weight;
    }

    for(int i=0; i<shifted_point.size(); i++){
        shifted_point[i] /= total_weight;
    }
    return shifted_point;
}

vector<vector<double> > MeanShift::meanshift(const vector<vector<double> > & points, double kernel_bandwidth){
    vector<bool> stop_moving(points.size(), false);
    vector<vector<double> > shifted_points = points;
    double max_shift_distance;
    do {
        max_shift_distance = 0;
        for(int i=0; i<shifted_points.size(); i++){
            if (!stop_moving[i]) {
                vector<double>point_new = shift_point(shifted_points[i], points, kernel_bandwidth);
                double shift_distance = euclidean_distance(point_new, shifted_points[i]);
                if(shift_distance > max_shift_distance){
                    max_shift_distance = shift_distance;
                }
                if(shift_distance <= EPSILON) {
                    stop_moving[i] = true;
                }
                shifted_points[i] = point_new;
            }
        }
        printf("max_shift_distance: %f\n", max_shift_distance);
    } while (max_shift_distance > EPSILON);
    return shifted_points;
}

vector<Cluster> MeanShift::cluster(
    const vector<vector<double> > & points, 
    const vector<vector<double> > & shifted_points)
{
    vector<Cluster> clusters;

    for (int i = 0; i < shifted_points.size(); i++) {

        int c = 0;
        for (; c < clusters.size(); c++) {
            if (euclidean_distance(shifted_points[i], clusters[c].mode) <= EPSILON) {
                break;
            }
        }

        if (c == clusters.size()) {
            Cluster clus;
            clus.mode = shifted_points[i];
            clusters.push_back(clus);
        }

        clusters[c].support.push_back(points[i]);
    }

    return clusters;
}

vector<Cluster> MeanShift::cluster(const vector<vector<double> > & points, double kernel_bandwidth){
    vector<vector<double> > shifted_points = meanshift(points, kernel_bandwidth);
    return cluster(points, shifted_points);
}
