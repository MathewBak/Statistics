#ifndef STATISTICS_H
#define STATISTICS_H
#include <vector>    //vector
#include <algorithm> //copy
#include <ostream>   //ostream
#include <istream>   //istream
#include <map>       //map

class Statistics
{
private:
    typedef std::vector<int> ContainerType;
    ContainerType data;

public:
    Statistics();

    float Average() const;
    int Size() const;
    float Deviation() const;
    std::map<int,int> OccuresMoreThan(int min_repeats) const;
    int Minimum() const ;
    int Maximum() const;
    ContainerType Histogram(const int num_bins, const int start, const int end );
    void DrawHistogramH(const int num_bins, const int start, const int end );
    void DrawHistogramV(const int num_bins, const int start, const int end );
    template <typename T>
    Statistics(T const *b, T const *e);

    template <typename T>
    void RemoveIf(const T &target);

    friend std::ostream &operator<<(std::ostream &out, Statistics const &stat);
    friend std::istream &operator>>(std::istream &in, Statistics &stat);
};

template <typename T>
void Statistics::RemoveIf(const T &target)
{
    //inside goes through the list and put all the target vals to the back, then returns a iterator to the,
    //start of the target value portion at  the back and erase goes through that till the end getting rid of them
    data.erase(std::remove_if(data.begin(), data.end(), target),data.end());
}

template <typename T>
Statistics::Statistics(T const *b, T const *e) : data(e - b)
{
    std::copy(b, e, data.begin()); // we can use regular pointers to specify ranges!
}

#endif
