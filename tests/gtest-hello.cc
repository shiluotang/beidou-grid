#include <cmath>

#include <gtest/gtest.h>

#include "grid_encoder.h"

namespace {

double degrees(double d, double m = 0.0, double s = 0.0) {
    double v = d;
    v += m / 60;
    v += s / 3600;
    return v;
}

} // namespace anonymous

TEST(gtest_encoder, test_nearest_corner) {
    using beidou::grid::grid;
    using beidou::grid::latlon;
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

TEST(gtest_encoder, test_real_data) {
    using beidou::grid::grid_encoder;
    using beidou::grid::latlon;
    grid_encoder encoder;
    std::map<std::string, latlon> data;
    data["N50J475493E"] = latlon(
            degrees(39, 59, 56.1444),
            degrees(116, 19, 14.3184));
    data["N50J475491E"] = latlon(
            degrees(39, 59, 59.7012),
            degrees(116, 19, 5.9808));
    data["N50J475492E"] = latlon(
            degrees(39, 59, 56.5260),
            degrees(116, 19, 9.3540));

    for (auto it = data.begin(), e = data.end(); it != e; ++it) {
        ASSERT_EQ(encoder.encode(it->second, 5), it->first);
    }
}
