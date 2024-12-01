#ifndef STATISTICS_H
#define STATISTICS_H
#include <vector>    //vector
#include <algorithm> //copy
#include <ostream>   //ostream
#include <istream>   //istream
#include <map>       //map

class Statistics {
    private:
        typedef std::vector<int> ContainerType;
        ContainerType data;
    public:
        Statistics();
        int Average();
        float Deviation();
        template <typename T> Statistics( T const* b, T const* e );
        friend std::ostream& operator<<( std::ostream& out, Statistics const& stat );
        friend std::istream& operator>>( std::istream& in, Statistics & stat );
};



template <typename T>
Statistics::Statistics( T const* b, T const* e ) : data(e-b) {
    std::copy( b, e, data.begin() ); // we can use regular pointers to specify ranges!
}

#endif
