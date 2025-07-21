#include "level_manager.h"

namespace org {

level_manager::level_manager()
    : _M_levels(10)
{
}

level_settings const&
level_manager::get_settings(int level) {
    return _M_levels.at(level - 1);
}

void level_manager::set_settings(
        int level,
        level_settings const &value) {
    if (level > _M_levels.size())
        _M_levels.reserve(level);
    _M_levels[level - 1] = value;
}

} // namespace org
