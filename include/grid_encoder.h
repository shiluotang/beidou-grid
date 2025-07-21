#ifndef BEIDOU_GRID_GRID_ENCODER_H_INCLUDED
#define BEIDOU_GRID_GRID_ENCODER_H_INCLUDED

#include "latlon.h"
#include "level_manager.h"

namespace org {

class grid_encoder {
public:
    grid_encoder();
    std::string encode(double lat, double lon, int max_level = 10);
    std::string encode(latlon const&, int max_level = 10);
protected:
private:
    grid _M_grid0;
    level_manager _M_level_manager;
};

} // namespace org

#endif // BEIDOU_GRID_ENCODER_H_INCLUDED
