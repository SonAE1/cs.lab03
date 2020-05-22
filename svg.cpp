#include "svg.h"
#include <iostream>
#include <vector>
#include <cmath>
#include "histogram.h"
#include <sstream>
#include <windows.h>
#include <stdio.h>
using namespace std;


DWORD WINAPI GetVersion(void);


string
make_info_text()
{
    stringstream buffer;


    DWORD info = GetVersion();
    DWORD mask_major = 0b00000000'00000000'00000000'11111111;
    DWORD mask = 0x0000ffff;
    DWORD version = info & mask;
    DWORD platform = info>>16;


    if ((info & 0x80000000) == 0)
    {
        DWORD version_major = version & mask_major;
        DWORD version_minor = version >> 8;
        DWORD build = platform;
        buffer << "Windows v" << version_major << "." << version_minor << " (build " << build << ")  "<<'\n';

    }
    return buffer.str();
}

string
make_info_text1()
{
    stringstream buffer;

    char system_dir[MAX_PATH];
    char comp_name[MAX_COMPUTERNAME_LENGTH+1];
    DWORD size = sizeof(comp_name);
    GetComputerNameA(comp_name, &size);

    buffer << "Computer Name:" <<  comp_name;

    return buffer.str();
}


const size_t SCREEN_WIDTH = 800;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
void
svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end()
{
    cout << "</svg>\n";
}

void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black")
{
    cout << "<rect x='"<<x<<"' y='"<<y<<"' width='"<<width<<"' height='"<<height << "' stroke='"<<stroke<<"' fill='"<<fill<<"'/>";
}

void svg_text(double left, double baseline, string text)
{
    cout << "<text x='"<<left<<"' y='"<<baseline<<"'>"<<text<<"</text>";
}




void  scale (const vector<size_t>& bins, size_t scale0, size_t& interval)
{
    if (bins.size() != 0)
    {
        size_t max_bin = bins[1];

        if (max_bin%scale0!=0)
            interval =max_bin/scale0+1;
        else
            interval =max_bin/scale0;
    }

}



void show_histogram_svg(const vector<size_t>& bins, size_t scale0)
{
   const size_t SCREEN_WIDTH = 800;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;

    size_t max_bin = bins[0];

    const bool need = max_bin * BLOCK_WIDTH > MAX_ASTERISK;


    size_t interval;
    if (scale0>9 || scale0<2)
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, "ERROR");
    else
    {
        for (size_t bin : bins)
        {
            size_t height = bin;
            if (need)
            {
                const double scaling_factor = (double)MAX_ASTERISK / (max_bin * BLOCK_WIDTH);
                height = (size_t)(bin * scaling_factor);
            }

            const double bin_width = BLOCK_WIDTH * height;

            svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,"#000000","#A52A2A");
            top += BIN_HEIGHT;

        }

        scale ( bins,  scale0, interval);

        svg_text (TEXT_WIDTH,top + TEXT_BASELINE,"|");
        for(int i=1; i<=interval*scale0; i++)
        {
            if (i%scale0==0)
                svg_text(TEXT_WIDTH+i*BLOCK_WIDTH,top +TEXT_BASELINE,"|");
            else
                svg_text(TEXT_WIDTH+i*BLOCK_WIDTH,top+ TEXT_BASELINE,"-");
        }

        svg_text(TEXT_WIDTH,top+ 2*TEXT_BASELINE, to_string(0));
        for(int i=1; i<interval*scale0; i++)
        {
            if ((i%scale0!=0) || ((i % scale0== 0) && ((i > scale0))))
                svg_text(TEXT_WIDTH+i*BLOCK_WIDTH-1,top+ 2*TEXT_BASELINE," ");
            else
                svg_text(TEXT_WIDTH+i*BLOCK_WIDTH-1,top+ 2*TEXT_BASELINE, to_string(i));
        }

        svg_text(TEXT_WIDTH+interval * scale0*BLOCK_WIDTH,top+ 2*TEXT_BASELINE, to_string(interval * scale0) );
    }

    svg_text(1,top+ 3*TEXT_BASELINE, make_info_text());
    svg_text(1,top+ 4*TEXT_BASELINE, make_info_text1());

}

