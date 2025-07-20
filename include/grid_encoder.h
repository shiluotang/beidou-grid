#ifndef BEIDOU_GRID_GRID_ENCODER_H_INCLUDED
#define BEIDOU_GRID_GRID_ENCODER_H_INCLUDED

#include "grid.h"
#include "layout.h"

namespace org {

class grid_encoder {
public:
    std::string encode(double lat, double lon, int max_level);
protected:
private:
};

} // namespace org

#endif // BEIDOU_GRID_ENCODER_H_INCLUDED
