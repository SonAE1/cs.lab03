#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED
#include <vector>
using namespace std;
void find_minmax(const vector<double> numbers, double& min, double& max);
void show_histogram_text(vector<size_t> bins);
struct Input
{
    vector<double> numbers;
    size_t bin_count;
    size_t scale;

};


#endif // HISTOGRAM_H_INCLUDED





