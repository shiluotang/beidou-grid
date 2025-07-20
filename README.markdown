# design

## pseudo code

```c++
class latlon {
public:
    latlon(double, double);
    latlon();

    double get_lat() const;
    double get_lon() const;
protected:
private:
    double _M_lat;
    double _M_lon;
};
```

```c++
class grid {
public:
    double get_lat_size() const;
    double get_lon_size() const;
protected:
private:
    latlon _M_left_bottom;
    latlon _M_right_top;
};
```

```c++
class field_codec {
public:
    void print(std::ostream&, int) const;
    int scan(std::istream&) const;
protected:
private:
};

class alphabelt_field_codec : public field_codec {
public:
    char encode(int idx) const {
        return static_cast<char>(_M_start_char + std::abs(idx));
    }

    int decode(char ch) {
        return ch - static_cast<int>(_M_start_char);
    }

    void print(std::ostream &out, int x) const {
        out << encode(x);
    }
protected:
private:
    char _M_start_char;
};

class code_codec {
public:
    std::string encode(int ilat, int ilon) const {
        std::ostringstream oss;
        _M_lat_codec.print(oss, ilat);
        _M_lon_codec.print(oss, ilon);
        return oss.str();
    }

    bool decode(std::string const &s, int &ilat, int &ilon) const {
        return false;
    }
protected:
private:
    field_codec _M_lat_codec;
    field_codec _M_lon_codec;
};
```

```c++
class layout {
public:
    layout(int, int, latlon);
    layout();

    int get_lat_ngrids() const;
    int get_lon_ngrids() const;
    latlon const& get_origin() const;

    grid divide(grid const &grid,
        latlon const &point,
        int &ilat,
        int &ilon) {
        return {};
    }
protected:
private:
    int _M_lat_ngrids;
    int _M_lon_ngrids;
    latlon _M_origin;
}
```

```c++
class level_settings {
public:
    layout const &get_layout() const;
    code_codec const &get_codec() const;
protected:
private:
    layout _M_layout;
    code_codec _M_codec;
};
```

```c++
class level_manager {
public:
    static level_manager& instance();
    level_settings const& of(int level) const;
protected:
private:
};
```

```c++
class encoder {
public:
    std::string encode(latlon const &pos, int max_level = 10) {
        grid grid = grid::global();
        grid subgrid;
        int ilat, ilon;
        std::ostringstream oss;
        for (int level = 0; level < max_level; ++level) {
            level_settings const &settings = level_manager::instance().of(level);
            grid = subgrid;
            subgrid = layout.divide(grid, pos, ilat, ilon);
            oss << settings.get_codec().encode(ilat, ilon);
        }
        return oss.str();
    }
protected:
private:
};
```

## encoders

| level | details    |
| :-    | :-         |
| 1     | 01~60, A~Z |
| 2     | 0~B, 0~7   |
| 3     | 0~5        |
| 4     | 0~E, 0~9   |
| 5     | 0~E, 0~E   |
| 6     | 0~3        |
| 7     | 0~7, 0~7   |
| 8     | 0~7, 0~7   |
| 9     | 0~7, 0~7   |
| 10    | 0~7, 0~7   |
