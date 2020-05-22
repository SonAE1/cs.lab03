#include <curl/curl.h>
#include "histogram.h"
#include <iostream>
#include "svg.h"
#include <vector>
#include <cmath>
#include <sstream>
#include <string>
using namespace std;
const size_t SCREEN_WIDTH = 800;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;


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
read_input(istream& in, bool prompt)
{
    Input data;
    size_t number_count;

    if( prompt )
    {
        cerr << "Enter number count: ";
        in >> number_count;

        cerr << "Enter numbers: ";
        data.numbers = input_numbers(in, number_count);

        cerr << "Enter bin count:";
        in >>data.bin_count;

        //cerr << "Enter number of scale:";
        //in >> data.scale;
    }
    else
    {
        in >> number_count;
        data.numbers = input_numbers(in, number_count);
        in >>data.bin_count;
       // in >> data.scale;
    }
    return data;
}


vector<size_t>
make_histogram(Input data)
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

size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
      const size_t data_size = item_size * item_count;
      stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
      const char* items2 = reinterpret_cast<const char*>(items);
      buffer->write(items2, data_size);
    return data_size ;
}

Input
download(const string& address) {
    stringstream buffer;

   curl_global_init(CURL_GLOBAL_ALL);
    CURL* curl = curl_easy_init();

    if (curl)
    {
            CURLcode res;
            curl_easy_setopt(curl, CURLOPT_URL,address.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
            res = curl_easy_perform(curl);
            if(res!= CURLE_OK)
            {cout<< curl_easy_strerror(res)<< endl;
             exit(1);
            }
            curl_easy_cleanup(curl);


    }


    return read_input(buffer, false);
}


int main(int argc, char* argv[])
{  Input input;
    if (argc > 1) {
        input = download(argv[1]);
    } else {
        input = read_input(cin, true);
    }

    const auto bins = make_histogram(input);
    show_histogram_svg(bins, input.scale);
}


