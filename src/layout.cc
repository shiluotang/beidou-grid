#include <cmath>
#include <ostream>
#include <iostream>

#include "latlon.h"
#include "grid.h"
#include "layout.h"

namespace org {
layout::layout(
        int lon_ngrids,
        int lat_ngrids,
        latlon const& origin)
    : _M_lat_ngrids(lat_ngrids)
    , _M_lon_ngrids(lon_ngrids)
    , _M_origin(origin)
{
}

layout::layout()
    : _M_lat_ngrids(0)
    , _M_lon_ngrids(0)
    , _M_origin(0, 0)
{
}

int layout::get_lat_ngrids() const {
    return _M_lat_ngrids;
}

int layout::get_lon_ngrids() const {
    return _M_lon_ngrids;
}

void layout::set_lat_ngrids(int value) {
    _M_lat_ngrids = value;
}

void layout::set_lon_ngrids(int value) {
    _M_lon_ngrids = value;
}

latlon const& layout::get_origin() const {
    return _M_origin;
}

void layout::set_origin(latlon const &value) {
    _M_origin = value;
}

grid layout::find_subgrid(
        grid const &g,
        latlon const &p,
        int &ilat,
        int &ilon) const {
    double lat_h = g.lat_degrees() / _M_lat_ngrids;
    double lon_h = g.lon_degrees() / _M_lon_ngrids;
    int quadrant = 0;
    latlon origin = g.nearest_corner(_M_origin, &quadrant);
    double olat = origin.get_lat();
    double olon = origin.get_lon();
    latlon p2 = p - origin;
    ilat = static_cast<int>(p2.get_lat() / lat_h);
    ilon = static_cast<int>(p2.get_lon() / lon_h);
    latlon a;
    latlon b;
    int dlat_sign = 1;
    int dlon_sign = 1;
    switch (quadrant) {
        case 1:
            dlat_sign = +1;
            dlon_sign = +1;
            break;
        case 2:
            dlat_sign = -1;
            dlon_sign = +1;
            break;
        case 3:
            dlat_sign = -1;
            dlon_sign = -1;
            break;
        case 4:
            dlat_sign = +1;
            dlon_sign = -1;
            break;
        default:
            dlat_sign = (ilat >= 0 ? 1 : -1);
            dlon_sign = (ilon >= 0 ? 1 : -1);
            break;
    }
    a.set_lat(olat + (ilat + 0) * lat_h);
    a.set_lon(olon + (ilon + 0) * lon_h);
    b.set_lat(olat + (ilat + 1 * dlat_sign) * lat_h);
    b.set_lon(olon + (ilon + 1 * dlon_sign) * lon_h);
    grid subgrid(a, b);
    return subgrid;
}

void layout::print(std::ostream &out) const {
    out << "{lat_ngrids = " << _M_lat_ngrids
        << ", lon_ngrids = " << _M_lon_ngrids
        << ", origin = " << _M_origin
        << "}";
}

} // namespace org
