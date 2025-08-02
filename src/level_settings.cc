#include <memory>

#include "level_settings.h"

namespace beidou {
namespace grid {

layout const& level_settings::get_layout() const {
    return _M_layout;
}

layout& level_settings::get_layout() {
    return _M_layout;
}

void level_settings::set_layout(layout const &value) {
    _M_layout = value;
}

std::shared_ptr<layout_encoder>
level_settings::get_encoder() const {
    return _M_encoder;
}

void level_settings::set_encoder(
        std::shared_ptr<layout_encoder> value) {
    _M_encoder = value;
}

} // namespace grid
} // namespace beidou
