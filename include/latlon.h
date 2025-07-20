#ifndef BEIDOU_GRID_LATLON_H_INCLUDED
#define BEIDOU_GRID_LATLON_H_INCLUDED

#include <iosfwd>

#include "printable.h"

namespace org {

class latlon
    : public printable {
public:
    latlon(double lat, double lon);
    latlon();

    double get_lat() const;
    double get_lon() const;
    void set_lat(double value);
    void set_lon(double value);

    latlon& operator+=(latlon const&);
    latlon& operator-=(latlon const&);
    latlon& operator*=(double);
    latlon& operator/=(double);

    latlon operator+(latlon const&) const;
    latlon operator-(latlon const&) const;
    latlon operator*(double) const;
    latlon operator/(double) const;
    latlon operator-() const;

    bool operator==(latlon const&) const;
    bool operator!=(latlon const&) const;

    void print(std::ostream& out) const;

    static
    latlon of(double lat, double lon);
protected:
    latlon& add_self(latlon const&);
    latlon& sub_self(latlon const&);
    latlon& scale_self(double);
    latlon& negate_self();
    bool equals(latlon const&) const;
private:
    double _M_lat;
    double _M_lon;
};
} // namespace org

#endif // BEIDOU_GRID_LATLON_H_INCLUDED
