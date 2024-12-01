#include "statistics.h"
#include <numeric>  //accumulate
#include <cmath>    //sqrt
#include <iterator> //ostream_iterator, back_inserter
#include <iomanip>  //setfill setw
#include <iostream> //cout




Statistics::Statistics() : data() {}

int Statistics::Average()
{
    int to_return = std::accumulate(data.begin(), data.end(), data[0]);
    return (to_return / data.capacity());
}



int sub_from_avg(int data1, int data2)
{
    //need to use this.average() here but dont know how
    float one_over_end = 1.0f/data2;
    // int temp = stat.Average();
    return data2 - 3;
}

float Statistics::Deviation()
{
    float to_return = std::accumulate(data.begin(), data.end(), data[0], sub_from_avg);
    return to_return;
}




std::ostream &operator<<(std::ostream &out, Statistics const &stat)
{
    std::copy(stat.data.begin(), stat.data.end(),
              std::ostream_iterator<int>(out, " "));
    return out;
}

std::istream &operator>>(std::istream &in, Statistics &stat)
{
    std::copy(std::istream_iterator<int>(in),
              std::istream_iterator<int>(),
              std::back_inserter(stat.data));
    return in;
}
