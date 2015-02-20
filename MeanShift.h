#include <vector>

using namespace std;

class MeanShift {
public:
    MeanShift (double (*_kernel_func)(double,double) );
    vector<vector<double> > cluster(vector<vector<double> >, double);
private:
    double (*kernel_func)(double,double);
    vector<double> shift_point(vector<double>, vector<vector<double> >, double);
};