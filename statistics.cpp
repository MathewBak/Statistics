#include "statistics.h"
#include <algorithm>
#include <numeric>  //accumulate
#include <cmath>    //sqrt
#include <iterator> //ostream_iterator, back_inserter
#include <iomanip>  //setfill setw
#include <iostream> //cout

Statistics::Statistics() : data() {}

float Statistics::Average() const
{
    float to_return = std::accumulate(data.begin(), data.end(), 0.0f);
    return (to_return / Size());
}

int Statistics::Size() const
{
    return data.size();
}

namespace
{
    struct deviation_helper
    {
        const float average;
        deviation_helper(const float _ave) : average(_ave) {}

        float operator()(const float curr_pos, const int x) const
        {
            float return_val = curr_pos + (x - average) * (x - average);
            return return_val;
        }
    };

}

float Statistics::Deviation() const
{
    float distances = std::accumulate(data.begin(), data.end(), 0.0f, deviation_helper(Average()));

    float squared_distance = std::sqrt(distances / Size());
    return squared_distance;
}

namespace
{

    struct occurence
    {
        std::map<int, int> &repeats;
        std::map<int, int> all_repeates;
        int min;

        occurence(std::map<int, int> &_repeates, int _min) : repeats(_repeates), all_repeates(), min(_min) {}

        void operator()(const int target)
        {
            // if cant find the wanted val then there is none
            if (all_repeates.find(target) == all_repeates.end())
            {
                all_repeates.insert(std::make_pair(target, 0));
            }

            if (++all_repeates[target] > min) // incrementing the value that show reapeats by one
            {
                repeats[target] = all_repeates[target];
            }
        }
    };
}

std::map<int, int> Statistics::OccuresMoreThan(int min_repeats) const
{
    std::map<int, int> repeating_vals;
    std::for_each(data.begin(), data.end(), occurence(repeating_vals, min_repeats));

    return repeating_vals;
}

int Statistics::Minimum() const
{
    int min = *std::min_element(data.begin(), data.end());
    // std::cout<<min<<std::endl;
    return min;
}

int Statistics::Maximum() const
{

    int max = *std::max_element(data.begin(), data.end());
    // std::cout<<max<<std::endl;
    return max;
}

namespace
{
    struct histogram_helper
    {
        const int num_bins;
        const int start, end;
        std::vector<int> &val_list;

        histogram_helper(std::vector<int> &vals, const int bins, const int _start, const int _end) : num_bins(bins), start(_start), end(_end), val_list(vals) {}

        void operator()(const int val) const
        {
            if (val < start || val >= end)
            {
                return;
            }
            const int index = static_cast<int>(static_cast<float>(num_bins) * static_cast<float>(val - start) / static_cast<float>(end - start));
            // std::cout<< index <<std::endl;
            int index2 = round(index);
            // std::cout<< index2 << val <<std::endl;

            if (index < num_bins)
            {
                ++val_list[index];
            }
        }
    };

}

Statistics::ContainerType Statistics::Histogram(const int num_bins, const int start, const int end)
{
    std::vector<int> vals(num_bins, 0);
    vals.reserve(num_bins);

    std::for_each(data.begin(), data.end(), histogram_helper(vals, num_bins, start, end));
    return vals;
}

namespace
{
    struct draw_horizontal
    {
        void operator()(int x)
        {
            std::cout << std::setfill('*') << std::setw(x) << "";
            std::cout << std::endl;
        }
    };
}

void Statistics::DrawHistogramH(const int num_bins, const int start, const int end)
{
    ContainerType histogram_data = this->Histogram(num_bins, start, end);

    std::for_each(histogram_data.begin(), histogram_data.end(), draw_horizontal());
}

namespace{
    struct next_int {
        int i;
        next_int(): i(0){}
        int operator()()
        {
            
            return i++;
        }
    };
}

namespace{
    struct draw_char{
        int height;
        draw_char(int height): height(height){}
        void operator()(int freq)
        {
            std::cout<<  (freq >= height ? '*' : ' ' );
        }

    };
}

namespace{
    struct draw_verts{
        int t_height;
        std::vector<int> &histograph;

        draw_verts(int height, std::vector<int>& graph): t_height(height), histograph(graph){}

        void operator()(int curr_line )
        {
            std::for_each(histograph.begin(), histograph.end(), draw_char(t_height - curr_line));
            std::cout<<std::endl;
        }

    };
}

void Statistics::DrawHistogramV(const int num_bins, const int start, const int end)
{
    std::vector<int> histagram = Histogram(num_bins, start, end);

    int height = *std::max_element(histagram.begin(),histagram.end());

    std::vector<int> v(height);

    std::generate(v.begin(), v.end(), next_int());

    std::for_each(v.begin(),v.end(), draw_verts(height,histagram));

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
