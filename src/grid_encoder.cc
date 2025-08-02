#include <string>
#include <sstream>

#include "layout.h"
#include "layout_encoders.h"
#include "grid_encoder.h"

namespace beidou {
namespace grid {

grid_encoder::grid_encoder()
    : _M_grid0(latlon(-88, -180), latlon(88, 180))
    , _M_level_manager()
{
    init();
}

std::string
grid_encoder::encode(double lat, double lon, int max_level) {
    return encode(latlon(lat, lon), max_level);
}

std::string
grid_encoder::encode(latlon const &p, int max_level) {
    grid g = _M_grid0;
    grid subgrid;
    int ilat, ilon;
    std::ostringstream oss;
    oss << (p.get_lat() >= 0 ? "N" : "S");
    for (int i = 0, n = max_level; i < n; ++i) {
        level_settings const &l = _M_level_manager.get_settings(i + 1);
        subgrid = l.get_layout().find_subgrid(g, p, ilat, ilon);
        l.get_encoder()->set_layout(&l.get_layout());
        oss << l.get_encoder()->encode(ilat, ilon);
        g = subgrid;
    }
    return oss.str();
}

void grid_encoder::init() {
    level_settings level;
    level.set_layout(
            layout(60, 44, latlon(0, -180)));
    level.set_encoder(std::make_shared<lonlat_encoder>(
                    ordinal_encoder::digits(1, 2),
                    ordinal_encoder::alphabet('A')
                ));
    _M_level_manager.set_settings(1, level);
    level.set_layout(layout(12, 8));
    level.set_encoder(std::make_shared<lonlat_encoder>(
                    ordinal_encoder::xdigits(),
                    ordinal_encoder::xdigits()
                ));
    _M_level_manager.set_settings(2, level);
    level.set_layout(layout(2, 3));
    level.set_encoder(std::make_shared<zorder_encoder>());
    _M_level_manager.set_settings(3, level);
    level.set_layout(layout(15, 10));
    level.set_encoder(std::make_shared<lonlat_encoder>(
                    ordinal_encoder::xdigits(),
                    ordinal_encoder::xdigits()
                ));
    _M_level_manager.set_settings(4, level);
    level.set_layout(layout(15, 15));
    level.set_encoder(std::make_shared<lonlat_encoder>(
                    ordinal_encoder::xdigits(),
                    ordinal_encoder::xdigits()
                ));
    _M_level_manager.set_settings(5, level);
    level.set_layout(layout(2, 2));
    level.set_encoder(std::make_shared<zorder_encoder>());
    _M_level_manager.set_settings(6, level);
    level.set_layout(layout(8, 8));
    level.set_encoder(std::make_shared<lonlat_encoder>(
                    ordinal_encoder::xdigits(),
                    ordinal_encoder::xdigits()
                ));
    _M_level_manager.set_settings(7, level);
    level.set_layout(layout(8, 8));
    level.set_encoder(std::make_shared<lonlat_encoder>(
                    ordinal_encoder::xdigits(),
                    ordinal_encoder::xdigits()
                ));
    _M_level_manager.set_settings(8, level);
    level.set_layout(layout(8, 8));
    level.set_encoder(std::make_shared<lonlat_encoder>(
                    ordinal_encoder::xdigits(),
                    ordinal_encoder::xdigits()
                ));
    _M_level_manager.set_settings(9, level);
    level.set_layout(layout(8, 8));
    level.set_encoder(std::make_shared<lonlat_encoder>(
                    ordinal_encoder::xdigits(),
                    ordinal_encoder::xdigits()
                ));
    _M_level_manager.set_settings(10, level);
}

} // namespace grid
} // namespace beidou
