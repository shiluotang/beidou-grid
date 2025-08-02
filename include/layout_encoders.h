#ifndef BEIDOU_GRID_FIELD_ENCODER_H_INCLUDED
#define BEIDOU_GRID_FIELD_ENCODER_H_INCLUDED

#include <cmath>
#include <string>

namespace beidou {
namespace grid {

class layout;
class layout_encoder {
public:
    virtual
    ~layout_encoder();
    layout const* get_layout() const;
    void set_layout(layout const*);
    virtual
    std::string encode(int ilat, int ilon);
protected:
private:
    layout const *_M_layout;
};

class ordinal_encoder {
public:
    enum mode {
        DIGITS = 0,
        XDIGITS,
        ALPHABET,
    };

    explicit
    ordinal_encoder(mode m, int zero = 0, int width = 0, char fill_char = '0');
    ordinal_encoder();

    virtual
    std::string encode(int idx);

    mode get_mode() const;
    void set_mode(mode);
    int get_width() const;
    void set_width(int);
    char get_fillchar() const;
    void set_fillchar(char);
    int get_zero() const;
    void set_zero(int);

    static
    ordinal_encoder alphabet(char zero, int width = 0);
    static
    ordinal_encoder xdigits(int width = 0);
    static
    ordinal_encoder digits(int zero, int width = 0);
protected:
private:
    mode    _M_mode;
    int     _M_width;
    char    _M_fill_char;
    int     _M_zero;
};

class zorder_encoder
    : public layout_encoder {
public:
    virtual
    std::string encode(int ilat, int ilon);
protected:
private:
};

class lonlat_encoder
    : public layout_encoder {
public:
    lonlat_encoder(
            ordinal_encoder const &lon_encoder,
            ordinal_encoder const &lat_encoder);

    ordinal_encoder& get_lat_encoder();
    ordinal_encoder& get_lon_encoder();
    void get_lat_encoder(ordinal_encoder const&);
    void get_lon_encoder(ordinal_encoder const&);

    virtual
    std::string encode(int ilat, int ilon);
protected:
private:
    ordinal_encoder _M_lat_encoder;
    ordinal_encoder _M_lon_encoder;
};

} // namespace grid
} // namespace beidou

#endif // BEIDOU_GRID_FIELD_ENCODER_H_INCLUDED
