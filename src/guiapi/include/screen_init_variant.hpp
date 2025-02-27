/**
 * @file screen_init_variant.hpp
 * @brief variant data type for screen initialization
 */

#pragma once

#include <cstdint>
#include <optional>

// TODO do not use selftest mask here, we need special enum for GUI
#if __has_include("printer_selftest.hpp")
    #include "printer_selftest.hpp" // SelftestMask_t
#endif

class screen_init_variant {
public:
    enum class type_t : uint8_t {
        data_not_valid,
        position,
        menu,
        selftest_mask
    };

    struct menu_t {
        uint8_t focused_index;
        uint8_t scroll_offset;
    };

    constexpr screen_init_variant()
        : type(type_t::data_not_valid)
        , position(0) {
    }
#if __has_include("printer_selftest.hpp")
    constexpr screen_init_variant(SelftestMask_t mask)
        : type(type_t::selftest_mask)
        , selftest_mask(mask) {
    }
#endif
    void SetPosition(uint16_t pos) {
        position = pos;
        type = type_t::position;
    }
    std::optional<uint16_t> GetPosition() {
        if (type != type_t::position) {
            return std::nullopt;
        }
        return position;
    }

    void SetMenuPosition(menu_t pos) {
        menu = pos;
        type = type_t::menu;
    }
    std::optional<menu_t> GetMenuPosition() {
        if (type != type_t::menu) {
            return std::nullopt;
        }
        return menu;
    }
#if __has_include("printer_selftest.hpp")
    void SetSelftestMask(SelftestMask_t mask) {
        selftest_mask = mask;
        type = type_t::selftest_mask;
    }
    std::optional<SelftestMask_t> GetSelftestMask() {
        if (type != type_t::selftest_mask) {
            return std::nullopt;
        }
        return selftest_mask;
    }
#endif

    constexpr bool IsValid() {
        return type != type_t::data_not_valid;
    }

private:
    type_t type;
    union {
        uint16_t position;
        menu_t menu;
#if __has_include("printer_selftest.hpp")
        SelftestMask_t selftest_mask;
#endif
    };
};
