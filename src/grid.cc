#include <ostream>
#include <algorithm>
#include <iostream>

#include "latlon.h"
#include "printable.h"

#include "grid.h"

namespace org {

grid::grid(latlon const &a, latlon const &b)
    : _M_left_bottom()
    , _M_right_top()
{
    _M_left_bottom.set_lat(std::min(a.get_lat(), b.get_lat()));
    _M_left_bottom.set_lon(std::min(a.get_lon(), b.get_lon()));
    _M_right_top.set_lat(std::max(a.get_lat(), b.get_lat()));
    _M_right_top.set_lon(std::max(a.get_lon(), b.get_lon()));
}

grid::grid()
    : _M_left_bottom()
    , _M_right_top()
{
}

latlon const& grid::get_left_bottom() const {
    return _M_left_bottom;
}

latlon const& grid::get_right_top() const {
    return _M_right_top;
}

latlon grid::get_left_top() const {
    return latlon(_M_right_top.get_lat(), _M_left_bottom.get_lon());
}

latlon grid::get_right_bottom() const {
    return latlon(_M_left_bottom.get_lat(), _M_right_top.get_lon());
}

latlon grid::get_center() const {
    return (_M_left_bottom + _M_right_top) * 0.5;
}

void grid::set_left_bottom(latlon const &value) {
    _M_left_bottom = value;
}

void grid::set_right_top(latlon const &value) {
    _M_right_top = value;
}

double grid::lat_degrees() const {
    return _M_right_top.get_lat() - _M_left_bottom.get_lat();
}

double grid::lon_degrees() const {
    return _M_right_top.get_lon() - _M_left_bottom.get_lon();
}

bool grid::operator==(grid const &other) const {
    return this->equals(other);
}

bool grid::operator!=(grid const &other) const {
    return !this->equals(other);
}

bool grid::contains(latlon const &point) const {
    return _M_left_bottom.get_lat() <= point.get_lat()
        && _M_left_bottom.get_lon() <= point.get_lon()
        && _M_right_top.get_lat() >= point.get_lat()
        && _M_right_top.get_lon() >= point.get_lon();
}

bool grid::contains(grid const &g) const {
    return contains(g.get_left_bottom())
        && contains(g.get_right_top());
}

latlon grid::nearest_corner(latlon const &origin, int *quadrant) const {
    if (quadrant)
        *quadrant = 0;
    if (contains(origin))
        return origin;
    latlon c = get_center() - origin;
    int quadrant_idx = 0;
    if (c.get_lon() >= 0 && c.get_lat() >= 0) {
        // quadrant 1
        c = get_left_bottom();
        quadrant_idx = 1;
    } else if (c.get_lon() >= 0 && c.get_lat() < 0) {
        // quadrant 2
        c = get_left_top();
        quadrant_idx = 2;
    } else if (c.get_lon() < 0 && c.get_lat() < 0) {
        // quadrant 3
        c = get_right_top();
        quadrant_idx = 3;
    } else if (c.get_lon() < 0 && c.get_lat() >= 0) {
        // quadrant 4
        c = get_right_bottom();
        quadrant_idx = 4;
    }
    if (quadrant)
        *quadrant = quadrant_idx;
    return c;
}

void grid::print(std::ostream &out) const {
    out << "{LB = " << _M_left_bottom
        << ", RT = " << _M_right_top
        << "}";
}

bool grid::equals(grid const &other) const {
    if (this == &other)
        return true;
    return _M_left_bottom == other._M_left_bottom
        && _M_right_top == other._M_right_top;
}

} // namespace org
