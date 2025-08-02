#include <ostream>

#include "latlon.h"

namespace beidou {
namespace grid {

latlon::latlon(double lat, double lon)
    : _M_lat(lat)
    , _M_lon(lon)
{
}

latlon::latlon()
    : _M_lat(0)
    , _M_lon(0)
{
}

double latlon::get_lat() const { return _M_lat; }
double latlon::get_lon() const { return _M_lon; }
void latlon::set_lat(double value) { _M_lat = value; }
void latlon::set_lon(double value) { _M_lon = value; }

latlon& latlon::operator+=(latlon const &other) {
    return add_self(other);
}

latlon& latlon::operator-=(latlon const &other) {
    return sub_self(other);
}

latlon& latlon::operator*=(double n) {
    return scale_self(n);
}

latlon& latlon::operator/=(double n) {
    return scale_self(1.0 / n);
}

latlon latlon::operator+(latlon const &other) const {
    return latlon(*this).add_self(other);
}

latlon latlon::operator-(latlon const &other) const {
    return latlon(*this).sub_self(other);
}

latlon latlon::operator*(double n) const {
    return latlon(*this).scale_self(n);
}

latlon latlon::operator/(double n) const {
    return latlon(*this).scale_self(1.0 / n);
}

latlon latlon::operator-() const {
    return latlon(*this).negate_self();
}

bool latlon::operator==(latlon const &other) const {
    return this->equals(other);
}

bool latlon::operator!=(latlon const &other) const {
    return this->equals(other);
}

void latlon::print(std::ostream& out) const {
    out << "{lat = " << _M_lat
        << ", lon = " << _M_lon
        << "}";
}

latlon latlon::of(double lat, double lon) {
    return latlon(lat, lon);
}

latlon& latlon::add_self(latlon const &other) {
    _M_lat += other._M_lat;
    _M_lon += other._M_lon;
    return *this;
}

latlon& latlon::sub_self(latlon const &other) {
    _M_lat -= other._M_lat;
    _M_lon -= other._M_lon;
    return *this;
}

latlon& latlon::scale_self(double n) {
    _M_lat *= n;
    _M_lon *= n;
    return *this;
}

latlon& latlon::negate_self() {
    _M_lat = -_M_lat;
    _M_lon = -_M_lon;
    return *this;
}

bool latlon::equals(latlon const &other) const {
    if (this == &other)
        return true;
    return _M_lat == other._M_lat
        && _M_lon == other._M_lon;
}

} // namespace grid
} // namespace beidou
