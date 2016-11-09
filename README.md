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
vector<vector<double> > points = load_points("test_simple.csv");
MeanShift *ms = new MeanShift(NULL);
double kernel_bandwidth = 2;
vector<vector<double> > shifted_points = ms->cluster(points, 2);
```

## Visualization for Linux

Install gnuplot and gnuplot-qt
```bash
sudo apt-get install gnuplot gnuplot-qt
```

Make and run the cpp_test
```bash
make
./MeanShift
```
The program will generate a csv file named "result.csv".

Plot it
```bash
gnuplot
plot 'test.csv' with points, 'result.csv' with points
```

## License
MIT License
