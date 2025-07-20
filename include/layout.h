#ifndef BEIDOU_GRID_LAYOUT_H_INCLUDED
#define BEIDOU_GRID_LAYOUT_H_INCLUDED

#include "grid.h"
#include "latlon.h"

namespace org {

class layout
    : public printable {
public:
    layout(
            int lon_ngrids,
            int lat_ngrids,
            latlon const&);
    layout();

    int get_lat_ngrids() const;
    int get_lon_ngrids() const;
    void set_lat_ngrids(int);
    void set_lon_ngrids(int);

    latlon const& get_origin() const;
    void set_origin(latlon const&);

    grid find_subgrid(
            grid const&,
            latlon const &,
            int &ilat, int &ilon) const;

    virtual
    void print(std::ostream&) const;
protected:
private:
    int _M_lat_ngrids;
    int _M_lon_ngrids;
    latlon _M_origin;
};

} // namespace org

#endif // BEIDOU_GRID_LAYOUT_H_INCLUDED
