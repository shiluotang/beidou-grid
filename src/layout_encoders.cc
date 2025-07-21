#include <cctype>
#include <iomanip>
#include <sstream>

#include "layout.h"
#include "layout_encoders.h"

namespace org {

layout_encoder::~layout_encoder() {
}

layout const* layout_encoder::get_layout() const {
    return _M_layout;
}

void layout_encoder::set_layout(layout const *value) {
    _M_layout = value;
}

std::string
layout_encoder::encode(int ilat, int ilon) {
    return "";
}

ordinal_encoder::ordinal_encoder(
        mode m,
        int zero,
        int width,
        char fill_char)
    : _M_mode(m)
    , _M_width(width)
    , _M_fill_char(fill_char)
    , _M_zero(zero)
{
}

ordinal_encoder::ordinal_encoder()
    : _M_mode(DIGITS)
    , _M_width(0)
    , _M_fill_char('0')
    , _M_zero(0)
{
}

std::string ordinal_encoder::encode(int idx) {
    std::ostringstream oss;
    if (_M_width > 0)
        oss << std::setw(_M_width) << std::setfill(_M_fill_char);
    if (_M_mode == XDIGITS) {
        oss << std::hex << std::uppercase;
        oss << (_M_zero + idx);
    } else if (_M_mode == ALPHABET) {
        char c = static_cast<char>(_M_zero) + idx;
        oss << c;
    } else if (_M_mode == DIGITS) {
        int n = _M_zero + idx;
        oss << n;
    }
    return oss.str();
}

ordinal_encoder::mode
ordinal_encoder::get_mode() const {
    return _M_mode;
}

void ordinal_encoder::set_mode(mode value) {
    _M_mode = value;
}

int ordinal_encoder::get_width() const {
    return _M_width;
}

void ordinal_encoder::set_width(int value) {
    _M_width = value;
}

char ordinal_encoder::get_fillchar() const {
    return _M_fill_char;
}

void ordinal_encoder::set_fillchar(char value) {
    _M_fill_char = value;
}

int ordinal_encoder::get_zero() const {
    return _M_zero;
}

void ordinal_encoder::set_zero(int value) {
    _M_zero = value;
}

ordinal_encoder
ordinal_encoder::alphabet(char zero, int width) {
    ordinal_encoder obj;
    obj.set_mode(ALPHABET);
    obj.set_width(width);
    obj.set_zero(zero);
    return obj;
}

ordinal_encoder
ordinal_encoder::xdigits(int width) {
    ordinal_encoder obj;
    obj.set_mode(XDIGITS);
    obj.set_width(width);
    return obj;
}

ordinal_encoder
ordinal_encoder::digits(int zero, int width) {
    ordinal_encoder obj;
    obj.set_mode(DIGITS);
    obj.set_width(width);
    obj.set_zero(zero);
    return obj;
}

std::string
zorder_encoder::encode(int ilat, int ilon) {
    if (!get_layout())
        return "";
    std::ostringstream oss;
    int n = get_layout()->get_lon_ngrids() * std::abs(ilat)
        + std::abs(ilon);
    oss << n;
    return oss.str();
}

lonlat_encoder::lonlat_encoder(
    ordinal_encoder const &lon_encoder,
    ordinal_encoder const &lat_encoder)
    : _M_lat_encoder(lat_encoder)
    , _M_lon_encoder(lon_encoder)
{
}


ordinal_encoder& lonlat_encoder::get_lat_encoder() {
    return _M_lat_encoder;
}

ordinal_encoder& lonlat_encoder::get_lon_encoder() {
    return _M_lat_encoder;
}

void lonlat_encoder::get_lat_encoder(ordinal_encoder const &value) {
    _M_lat_encoder = value;
}

void lonlat_encoder::get_lon_encoder(ordinal_encoder const &value) {
    _M_lon_encoder = value;
}

std::string
lonlat_encoder::encode(int ilat, int ilon) {
    std::ostringstream oss;
    oss << _M_lon_encoder.encode(std::abs(ilon));
    oss << _M_lat_encoder.encode(std::abs(ilat));
    return oss.str();
}

} // namespace org
