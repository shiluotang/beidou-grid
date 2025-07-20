#ifndef BEIDOU_GRID_GRID_H_INCLUDED
#define BEIDOU_GRID_GRID_H_INCLUDED

#include <iosfwd>

#include "printable.h"
#include "latlon.h"

namespace org {

class grid
    : public printable {
public:
    grid(latlon const &a, latlon const &b);
    grid();

    latlon const& get_left_bottom() const;
    latlon const& get_right_top() const;
    latlon get_left_top() const;
    latlon get_right_bottom() const;
    latlon get_center() const;

    void set_left_bottom(latlon const&);
    void set_right_top(latlon const&);

    double lat_degrees() const;
    double lon_degrees() const;

    bool operator==(grid const&) const;
    bool operator!=(grid const&) const;
    bool contains(latlon const&) const;
    bool contains(grid const&) const;

    latlon nearest_corner(latlon const&, int *quadrant = 0) const;

    virtual
    void print(std::ostream&) const;
protected:
    bool equals(grid const&) const;
private:
    latlon _M_left_bottom;
    latlon _M_right_top;
};

} // namespace org

#endif // BEIDOU_GRID_GRID_H_INCLUDED
