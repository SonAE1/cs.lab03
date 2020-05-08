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
input_numbers(size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}


vector<size_t> make_histogram(istream& in )
{
    vector<size_t> result(bin_count);
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
        result[bin_index]++;
    }
    return result;
}

vector<double>
input_numbers(istream& in, size_t count)
{
    in >> count;
}


Input
read_input(istream& in)
{size_t number_count;

    Input data;

    cerr << "Enter number count: ";
    cin >> number_count;

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    cerr << "Enter bin count:";
    cin >>data.bin_count;

    cerr << "Enter number of scale:";
    cin >> data.scale;

    return data;
}

int main()
{

    Input data = read_input(cin);
    const auto bins = make_histogram (data.numbers, data.bin_count) ;
    show_histogram_svg(bins, data.scale);
    return 0;

}
