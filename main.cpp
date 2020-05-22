#include "histogram.h"
#include <iostream>
#include "svg.h"
#include <vector>
#include <cmath>
#include <windows.h>
using namespace std;
const size_t SCREEN_WIDTH = 800;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

DWORD WINAPI GetVersion(void);

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
    DWORD info = GetVersion();
    DWORD mask_major = 0b00000000'00000000'00000000'11111111;
    DWORD mask = 0x0000ffff;
    DWORD version = info & mask;
    DWORD platform = info>>16;
    DWORD version_major = version & mask_major;
    DWORD version_minor = version >> 8;

    if ((info & 0x80000000) == 0)
    {
        DWORD build = platform;
        printf("Windows v%u.%u (build %u)\n", version_major, version_minor, build);
    }

    char system_dir[MAX_PATH];
    char comp_name[MAX_COMPUTERNAME_LENGTH+1];
    DWORD size = sizeof(comp_name);
    GetSystemDirectory(system_dir, MAX_PATH);
    GetComputerNameA(comp_name, &size);
    printf("System directory: %s\n", system_dir); // System directory: C:\Windows
    printf("Computer name: %s\n", comp_name);
    return 0 ;

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
