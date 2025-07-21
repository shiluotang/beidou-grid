#ifndef BEIDOU_GRID_LEVEL_MANAGER_H_INCLUDED
#define BEIDOU_GRID_LEVEL_MANAGER_H_INCLUDED

#include <vector>

#include "level_settings.h"

namespace org {

class level_manager {
public:
    level_manager();

    level_settings const& get_settings(int);
    void set_settings(int, level_settings const&);
protected:
private:
    std::vector<level_settings> _M_levels;
};

} // namespace org

#endif // BEIDOU_GRID_LEVEL_MANAGER_H_INCLUDED
