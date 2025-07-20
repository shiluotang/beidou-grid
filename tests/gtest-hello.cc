#define _USE_MATH_DEFINES 1
#include <cmath>
#include <iomanip>

#include <gtest/gtest.h>

#include <layout.h>
#include <layout_encoders.h>

namespace {
} // namespace anonymous

int test_point(org::latlon const &point) {
    using org::grid;
    using org::layout;
    using org::layout_encoder;
    using org::zorder_encoder;
    using org::ordinal_encoder;
    using org::lonlat_encoder;
    using org::latlon;
    grid g(latlon(-88, -180), latlon(88, 180));
    grid subgrid;
    std::vector<layout> layouts;
    layouts.push_back(layout(60, 44, latlon(0, -180)));
    layouts.push_back(layout(12, 8, latlon(0, 0)));
    layouts.push_back(layout(2, 3, latlon(0, 0)));
    layouts.push_back(layout(15, 10, latlon(0, 0)));
    layouts.push_back(layout(15, 15, latlon(0, 0)));
    layouts.push_back(layout(2, 2, latlon(0, 0)));
    layouts.push_back(layout(8, 8, latlon(0, 0)));
    layouts.push_back(layout(8, 8, latlon(0, 0)));
    layouts.push_back(layout(8, 8, latlon(0, 0)));
    layouts.push_back(layout(8, 8, latlon(0, 0)));
    std::vector<std::shared_ptr<layout_encoder>> layout_encoders;
    // level 1
    layout_encoders.push_back(
            std::make_shared<lonlat_encoder>(ordinal_encoder::digits(1, 2), ordinal_encoder::alphabet('A')));
    // level 2
    layout_encoders.push_back(
            std::make_shared<lonlat_encoder>(ordinal_encoder::xdigits(), ordinal_encoder::xdigits()));
    // level 3
    layout_encoders.push_back(std::make_shared<zorder_encoder>());
    // level 4
    layout_encoders.push_back(
            std::make_shared<lonlat_encoder>(ordinal_encoder::xdigits(), ordinal_encoder::xdigits()));
    // level 5
    layout_encoders.push_back(
            std::make_shared<lonlat_encoder>(ordinal_encoder::xdigits(), ordinal_encoder::xdigits()));
    // level 6
    layout_encoders.push_back(std::make_shared<zorder_encoder>());
    // level 7
    layout_encoders.push_back(
            std::make_shared<lonlat_encoder>(ordinal_encoder::xdigits(), ordinal_encoder::xdigits()));
    // level 8
    layout_encoders.push_back(
            std::make_shared<lonlat_encoder>(ordinal_encoder::xdigits(), ordinal_encoder::xdigits()));
    // level 9
    layout_encoders.push_back(
            std::make_shared<lonlat_encoder>(ordinal_encoder::xdigits(), ordinal_encoder::xdigits()));
    // level 10
    layout_encoders.push_back(
            std::make_shared<lonlat_encoder>(ordinal_encoder::xdigits(), ordinal_encoder::xdigits()));
    std::cout << "----------------------------------" << std::endl;
    std::cout << "g = " << g << std::endl;
    int ilat, ilon;
    unsigned int lat_ngrids = 1;
    unsigned int lon_ngrids = 1;
    std::ostringstream oss;
    oss << (point.get_lat() >= 0 ? "N" : "S");
    for (size_t i = 0, n = layouts.size(); i < n; ++i) {
        subgrid = layouts[i].find_subgrid(g, point, ilat, ilon);
        lat_ngrids *= layouts[i].get_lat_ngrids();
        lon_ngrids *= layouts[i].get_lon_ngrids();
        std::cout << "level = " << (i + 1) << std::endl;
        std::cout << "lat_ngrids = " << layouts[i].get_lat_ngrids() << std::endl;
        std::cout << "lon_ngrids = " << layouts[i].get_lon_ngrids() << std::endl;
        std::cout << "subgrid = " << subgrid << std::endl;
        std::cout << "ilon = " << ilon << std::endl;
        std::cout << "ilat = " << ilat << std::endl;
        if (!g.contains(subgrid) && g != subgrid)
            return false;
        if (i < layout_encoders.size()) {
            layout_encoders[i]->set_layout(&layouts[i]);
            std::string code = layout_encoders[i]->encode(ilat, ilon);
            std::cout << "code = " << code << std::endl;
            oss << code;
        }
        g = subgrid;
    }
    std::cout << oss.str() << std::endl;
    return true;
}

TEST(gtest_hello, test1) {
    ASSERT_TRUE(test_point(org::latlon(31, 121)));
    ASSERT_TRUE(test_point(org::latlon(-31, 121)));
    ASSERT_TRUE(test_point(org::latlon(-31, -121)));
    ASSERT_TRUE(test_point(org::latlon(31, -121)));
    ASSERT_TRUE(test_point(org::latlon(0, 0)));
}

TEST(gtest_hello, test2) {
    double const R = 6371000;
    double const PI = std::asin(1) * 2;
    double const DEG2RAD = PI / 180;
    double const RAD2DEG = 180 / PI;
    double const L = 0.015;
    double theta = 0;
    theta = L / R * RAD2DEG;
    double degs = theta;
    double mins = theta * 60;
    double secs = mins * 60;
    std::cout
        << "L(" << L << " m)"
        << " = " << theta << " deg"
        << " = " << mins << " min"
        << " = " << secs << " sec"
        << std::endl;
}

TEST(gtest_hello, test3) {
    using org::grid;
    using org::latlon;
    latlon lb(28, 120);
    latlon rt(32, 126);
    latlon lt(32, 120);
    latlon rb(28, 126);
    grid g(lb, rt);
    ASSERT_EQ(g.get_left_bottom(), lb);
    ASSERT_EQ(g.get_right_top(), rt);
    ASSERT_EQ(g.get_left_top(), lt);
    ASSERT_EQ(g.get_right_bottom(), rb);
}
