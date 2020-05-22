#include "histogram.h"
#include <iostream>
#include "svg.h"
#include <vector>
#include <cmath>
#include <cstdio>
using namespace std;
const size_t SCREEN_WIDTH = 800;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

int printf(const char* format, ...);


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


void make_histogram(const vector<double>& numbers, double max, double min, size_t bin_count, vector <size_t>& bins )
{

    for(double x: numbers)
    {
        size_t bin_index=(x-min)/(max-min)*bin_count;
        if (bin_index==bin_count)
        {
            bin_index--;
        }
        bins[bin_index]++;
    }
}




int main()
{
    const char* name = "Alina Son";
int year = 2001;
printf ("%s was born in %d.\n", name, year);
printf ("n = %08x\n", 0x1234567);
return 0;

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
