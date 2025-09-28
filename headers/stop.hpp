#pragma once

#include <string>
#include <tuple>
#include <ostream>
#include <functional>
#include <format>

struct Stop {
    std::string name;
    unsigned int x = 0, y = 0;
    bool on_demand;

    Stop(std::string n = {}, unsigned int _x = 0, unsigned int _y = 0, bool _on_demand = false): name(std::move(n)), x(_x), y(_y), on_demand(_on_demand) {}
    friend std::ostream& operator<<(std::ostream& os, const Stop& obj) {
        std::string on_demand = obj.on_demand ? "[ON_DEMAND ONLY]" : "";
        os << obj.name << " (" << obj.x << "," << obj.y << ") " << on_demand;
        return os;
    }
    bool operator == (const Stop& other) const { return std::tie(name, x, y, on_demand) == std::tie(other.name, other.x, other.y, other.on_demand); }
    bool operator != (const Stop& other) const { return !((*this) == other); }
    bool operator < (const Stop& other) const { return std::tie(name, x, y) < std::tie(other.name, other.x, other.y); }
    bool operator > (const Stop& other) const { return std::tie(name, x, y) > std::tie(other.name, other.x, other.y); }
};

namespace std {
    template <>
    struct hash<Stop> {
        std::size_t operator()(const Stop& stop) const {
            return ( ( std::hash<std::string>()(stop.name) ^ (std::hash<unsigned int>()(stop.x) << 1) ) >> 1)
                   ^ (std::hash<unsigned int>()(stop.y) << 1);
        }
    };

    template <typename CharT>
    struct formatter<Stop, CharT> {
        constexpr auto parse(std::basic_format_parse_context<CharT>& ctx) {
            return ctx.begin();
        }

        // <-- note the added 'const' here
        template <typename FormatContext>
        auto format(const Stop& stop, FormatContext& ctx) const -> decltype(ctx.out()) {
            std::string on_demand = stop.on_demand ? "[ON_DEMAND ONLY]" : "";
            return std::format_to(ctx.out(), "{} ({}, {}) {}", stop.name, stop.x, stop.y, on_demand);
        }
    };
}
