#include "path.hh"
#include <algorithm>

Path::Path() {
}

Path::~Path() {
}

void
Path::add( Position const & pos ) {
    if( _path.empty() || _path.rbegin()->isNeighbor( pos ) )
        _path.push_back( pos );
}

bool
Path::step() {
    if( _cur != _path.end() ) {
        _cur++;
        if( _cur == _path.end() )
            return false;
        return true;
    }
    return false;
}

void
Path::reset() {
    _cur = _path.begin();
}

void
Path::clear() {
    _path.clear();
    _cur = _path.end();
}

bool
Path::empty() const {
    return _path.empty();
}

int
Path::length() const {
    return _path.size();
}

std::list< Position >::iterator const
Path::current() const {
    return _cur;
}

std::list< Position >::const_iterator
Path::end() const {
    return _path.end();
}

Path const
Path::operator+( Path const & rhs ) const {
    if( this->_path.back().distanceTo( rhs._path.front() ) > 1 )
        return Path();

    Path p = Path();
    for( auto it = this->_path.begin(); it != this->_path.end(); it++ )
        p.add( *it );
    for( auto it = rhs._path.begin(); it != rhs._path.end(); it++ )
        p.add( *it );
    p.reset();
    return p;
}

Path &
Path::operator+=( Path const & rhs ) {
    if( this->_path.back().distanceTo( rhs._path.front() ) > 1 )
        return *this;

    for( auto it = rhs._path.begin(); it != rhs._path.end(); it++ )
        this->add( *it );
    return *this;
}

Path &
Path::operator=( Path const & rhs ) {
    this->clear();
    for( auto it = rhs._path.begin(); it != rhs._path.end(); it++ )
        this->add( *it );
    return *this;
}

void
Path::print() const {
    for( auto it = _path.begin(); it != _path.end(); it++ )
        std::cout << *it << std::endl;
}
