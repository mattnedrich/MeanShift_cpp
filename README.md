## MeanShift++
MeanShift_cpp is an implementation of MeanShift clustering in C++

## Current Version
The current version is functional, but very limited

## Usage
The current programming model includes a class `MeanShift`. The MeanShift constructor takes a function pointer to a kernel function to be used in the clustering process. If `NULL`, it will use a Gaussian kernel.

Points are assumed to be `vector<double>`. Point collections are assumed to be `vector<vector<double> >`. This may change in the future.

To cluster a set of points, create a MeanShift object and call the `cluster` method with a collection of points and a kernel bandwidth. The shifted point will be returned as a `vector<vector<double> >`. Note that the points are not currently grouped into cluters, but rather shifted to their converged locations.

## Example
```cpp
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

MeanShift *ms = new MeanShift(NULL);
vector<vector<double> > shifted_points = ms->cluster(allPoints, .9);
```
