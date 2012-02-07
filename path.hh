#ifndef PATH_HH
#define PATH_HH

#include "position.hh"
#include <list>

class Path {

public:
    explicit Path();
    ~Path();

    void add( Position const & pos );

    bool step(); // returns whether step was valid
    void reset();
    void clear();

    bool empty() const;

    int length() const;

    std::list< Position >::iterator const current() const;
    std::list< Position >::const_iterator end() const;

    Position destination() const;

    Path const operator+( Path const & rhs ) const;

    Path & operator=( Path const & rhs );
    Path & operator+=( Path const & rhs );

    void print() const;

private:
    std::list< Position > _path;
    std::list< Position >::iterator _cur;
};

#endif // PATH_HH
