#include "histogram.h"
#include <iostream>
#include "svg.h"
#include <vector>
#include <cmath>
using namespace std;
const size_t SCREEN_WIDTH = 800;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

struct Input
{
    vector<double> numbers;
    size_t bin_count;
    size_t scale;

};
vector<double>
input_numbers(istream& in,size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}



Input
read_input(istream& in)
{
    Input data;

    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    cerr << "Enter bin count:";
    in >>data.bin_count;

    cerr << "Enter number of scale:";
    in >> data.scale;

    return data;
}

 vector<size_t>
make_histogram( struct Input data)
{
     vector<size_t> bins(data.bin_count, 0);

    double min;
    double max;
    find_minmax(data.numbers, min, max);
    for(double x: data.numbers)
    {
        size_t bin_index=(x-min)/(max-min)*data.bin_count;
        if (bin_index==data.bin_count)
        {
            bin_index--;
        }
        bins[bin_index]++;
    }
    return bins;
}



int main()
{

    Input data = read_input(cin);
    const auto bins = make_histogram (data);
    show_histogram_svg(bins, data.scale);
    return 0;

}
