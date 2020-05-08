#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

void svg_begin(double width, double height);

void svg_end();


void svg_text(double left, double baseline, string text);
void svg_scale(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height, string stroke, string fill );
void show_histogram_svg(const vector<size_t>& bins, size_t scale0);
void scale (const vector<size_t>& bins, size_t scale0,size_t& interval);
#endif // SVG_H_INCLUDED
