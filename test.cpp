#include "histogram.h"
#include "svg.h"
#include <cassert>
void
test_positive()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}
void
test_negative()
{
    double min = 0;
    double max = 0;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
}
void
test_same()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 1, 1}, min, max);
    assert(min == 1);
    assert(max == 1);
}

void
test_empty()
{
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}
void test_one()
{
    double min = 0;
    double max = 0;
    find_minmax({2}, min, max);
    assert(min == 2);
    assert(max == 2);
}


void test_scale_empty()
{size_t interval=1;
    scale({},5,interval);
    assert(interval == 1);
}

void test_scale1()
{
size_t interval;
    scale({3,5,9},3,interval);
    assert(interval==4);
}

int
main()
{
    test_positive();
    test_negative();
    test_same();
    test_empty();
    test_scale_empty();
    test_scale1();
}
