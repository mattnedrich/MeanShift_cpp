#include <vector>

class MeanShift {
public:
    MeanShift() { set_kernel(NULL); }
    MeanShift(double (*_kernel_func)(double,double)) { set_kernel(kernel_func); }
    std::vector<std::vector<double> > cluster(const std::vector<std::vector<double> > &, double);
private:
    double (*kernel_func)(double,double);
    void set_kernel(double (*_kernel_func)(double,double));
    std::vector<double> shift_point(const std::vector<double> &, const std::vector<std::vector<double> > &, double);
};
