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


void test_scale1()
{
size_t interval;
    scale({3,5,10},3,interval);
    assert(interval==4);
}


void test_scale_one()
{size_t interval;
    scale({5},5,interval);
    assert(interval == 1);
}

void test_scale_same ()
{
    size_t interval;
    scale({1, 1 ,1 },3,interval);
    assert(interval==1);
}



int
main()
{
    test_positive();
    test_negative();
    test_same();
    test_empty();
    test_scale_one();
    test_scale1();
    test_scale_same ();
}
