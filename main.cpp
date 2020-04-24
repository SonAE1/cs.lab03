#include "histogram.h"
#include <iostream>
#include "svg.h"
#include <vector>
#include <cmath>
using namespace std;
const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
int main()
{
    size_t number_count;

    cerr << "Enter number count:";
    cin >> number_count;

    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter bin count:";
    cin >> bin_count;

    size_t scale;
    cerr << "Enter number of scale:";
    cin >> scale;



    vector <size_t> bins(bin_count, 0);



    double min, max;
    find_minmax(numbers, min, max);
    make_histogram ( numbers, max, min, bin_count, bins );
    show_histogram_svg(bins, scale);
    return 0;

}
