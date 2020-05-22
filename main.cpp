/*#include "histogram.h"
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
    DWORD version_major = version & mask_major ;
    DWORD version_minor = version >> 8;
    printf("Windows 16x-version is %x\n", version );
    printf("Windows decimal-version is %u\n", version );
    printf("Windows major version is %u\n", version_major);
    printf("Windows minor version is %u\n", version_minor );

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

}*/
#include <windows.h>
#include <stdio.h>

int main()
{
    DWORD dwVersion = 0;
    DWORD dwMajorVersion = 0;
    DWORD dwMinorVersion = 0;
    DWORD dwBuild = 0;

    dwVersion = GetVersion();

    // Get the Windows version.

    dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
    dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));

    // Get the build number.

    if (dwVersion < 0x80000000)
        dwBuild = (DWORD)(HIWORD(dwVersion));

    printf("Version is %d.%d (%d)\n",
                dwMajorVersion,
                dwMinorVersion,
                dwBuild);
}
