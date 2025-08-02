#ifndef BEIDOU_GRID_LEVEL_SETTINGS_H_INCLUDED
#define BEIDOU_GRID_LEVEL_SETTINGS_H_INCLUDED

#include <memory>

#include "layout.h"
#include "layout_encoders.h"

namespace beidou {
namespace grid {

class level_settings {
public:
    layout const& get_layout() const;
    layout& get_layout();
    void set_layout(layout const&);

    std::shared_ptr<layout_encoder> get_encoder() const;
    void set_encoder(std::shared_ptr<layout_encoder>);
protected:
private:
    layout _M_layout;
    std::shared_ptr<layout_encoder> _M_encoder;
};

} // namespace grid
} // namespace beidou

#endif // BEIDOU_GRID_LEVEL_SETTINGS_H_INCLUDED
