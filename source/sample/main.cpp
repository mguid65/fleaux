/**
 * @brief TODO
 * @author Matthew Guidry (github: mguid65)
 * @date 3/16/24
 */

#include <iostream>
#include <tuple>

#include <data_tree/data_tree.hpp>

#include "fleaux/fleaux.hpp"

static auto PRINT = fleaux::Node{}.AddEvaluationFunction([](const auto& data) {
  std::cout << data;
  return data;
});

static auto PRINTLN = fleaux::Node{}.AddEvaluationFunction([](const auto& data) {
  data | PRINT;
  std::cout << std::endl;
  return data;
});

static auto ADD =
    fleaux::Node{}
        .AddInputChannel("lhs", fleaux::ChannelInfo{})
        .AddInputChannel("rhs", fleaux::ChannelInfo{})
        .AddEvaluationFunction([](const auto& data) {
          static constexpr auto common =
              [](const auto& expected_lhs_inner,
                 const auto& expected_rhs_inner) -> std::optional<mguid::NumberType> {
            if (const auto [lhs, rhs] = std::tuple(expected_lhs_inner->TryGetNumber(),
                                                   expected_rhs_inner->TryGetNumber());
                lhs.has_value() && rhs.has_value()) {
              return *lhs + *rhs;
            }
            return std::nullopt;
          };

          if (const auto [expected_lhs_named, expected_rhs_named] =
                  std::tuple(data.TryGet("lhs"), data.TryGet("rhs"));
              expected_lhs_named.has_value() && expected_rhs_named.has_value()) {
            if (const auto result = common(expected_lhs_named, expected_rhs_named);
                result.has_value()) {
              return mguid::DataTree{*result};
            }
          } else if (const auto [expected_lhs, expected_rhs] =
                         std::tuple(data.TryGet(0), data.TryGet(1));
                     expected_lhs.has_value() && expected_rhs.has_value()) {
            if (const auto result = common(expected_lhs, expected_rhs); result.has_value()) {
              return mguid::DataTree{*result};
            }
          }
          throw std::runtime_error{"Incorrect operand types for \"ADD\" operation"};
        });

static auto SUBTRACT =
    fleaux::Node{}
        .AddInputChannel("lhs", fleaux::ChannelInfo{})
        .AddInputChannel("rhs", fleaux::ChannelInfo{})
        .AddEvaluationFunction([](const auto& data) {
          static constexpr auto common =
              [](const auto& expected_lhs_inner,
                 const auto& expected_rhs_inner) -> std::optional<mguid::NumberType> {
            if (const auto [lhs, rhs] = std::tuple(expected_lhs_inner->TryGetNumber(),
                                                   expected_rhs_inner->TryGetNumber());
                lhs.has_value() && rhs.has_value()) {
              return *lhs - *rhs;
            }
            return std::nullopt;
          };

          if (const auto [expected_lhs_named, expected_rhs_named] =
                  std::tuple(data.TryGet("lhs"), data.TryGet("rhs"));
              expected_lhs_named.has_value() && expected_rhs_named.has_value()) {
            if (const auto result = common(expected_lhs_named, expected_rhs_named);
                result.has_value()) {
              return mguid::DataTree{*result};
            }
          } else if (const auto [expected_lhs, expected_rhs] =
                         std::tuple(data.TryGet(0), data.TryGet(1));
                     expected_lhs.has_value() && expected_rhs.has_value()) {
            if (const auto result = common(expected_lhs, expected_rhs); result.has_value()) {
              return mguid::DataTree{*result};
            }
          }
          throw std::runtime_error{"Incorrect operand types for \"SUBTRACT\" operation"};
        });

static auto MULTIPLY =
    fleaux::Node{}
        .AddInputChannel("lhs", fleaux::ChannelInfo{})
        .AddInputChannel("rhs", fleaux::ChannelInfo{})
        .AddEvaluationFunction([](const auto& data) {
          static constexpr auto common =
              [](const auto& expected_lhs_inner,
                 const auto& expected_rhs_inner) -> std::optional<mguid::NumberType> {
            if (const auto [lhs, rhs] = std::tuple(expected_lhs_inner->TryGetNumber(),
                                                   expected_rhs_inner->TryGetNumber());
                lhs.has_value() && rhs.has_value()) {
              return *lhs * *rhs;
            }
            return std::nullopt;
          };

          if (const auto [expected_lhs_named, expected_rhs_named] =
                  std::tuple(data.TryGet("lhs"), data.TryGet("rhs"));
              expected_lhs_named.has_value() && expected_rhs_named.has_value()) {
            if (const auto result = common(expected_lhs_named, expected_rhs_named);
                result.has_value()) {
              return mguid::DataTree{*result};
            }
          } else if (const auto [expected_lhs, expected_rhs] =
                         std::tuple(data.TryGet(0), data.TryGet(1));
                     expected_lhs.has_value() && expected_rhs.has_value()) {
            if (const auto result = common(expected_lhs, expected_rhs); result.has_value()) {
              return mguid::DataTree{*result};
            }
          }
          throw std::runtime_error{"Incorrect operand types for \"MULTIPLY\" operation"};
        });

static auto DIVIDE =
    fleaux::Node{}
        .AddInputChannel("lhs", fleaux::ChannelInfo{})
        .AddInputChannel("rhs", fleaux::ChannelInfo{})
        .AddEvaluationFunction([](const auto& data) {
          static constexpr auto common =
              [](const auto& expected_lhs_inner,
                 const auto& expected_rhs_inner) -> std::optional<mguid::NumberType> {
            if (const auto [lhs, rhs] = std::tuple(expected_lhs_inner->TryGetNumber(),
                                                   expected_rhs_inner->TryGetNumber());
                lhs.has_value() && rhs.has_value()) {
              return *lhs / *rhs;
            }
            return std::nullopt;
          };

          if (const auto [expected_lhs_named, expected_rhs_named] =
                  std::tuple(data.TryGet("lhs"), data.TryGet("rhs"));
              expected_lhs_named.has_value() && expected_rhs_named.has_value()) {
            if (const auto result = common(expected_lhs_named, expected_rhs_named);
                result.has_value()) {
              return mguid::DataTree{*result};
            }
          } else if (const auto [expected_lhs, expected_rhs] =
                         std::tuple(data.TryGet(0), data.TryGet(1));
                     expected_lhs.has_value() && expected_rhs.has_value()) {
            if (const auto result = common(expected_lhs, expected_rhs); result.has_value()) {
              return mguid::DataTree{*result};
            }
          }
          throw std::runtime_error{"Incorrect operand types for \"SUBTRACT\" operation"};
        });

auto main() -> int {
  using ARR = mguid::ArrayNodeType;
  using DT = mguid::DataTree;
  using namespace mguid::literals;

  DT{ARR{DT{ARR{{DT{ARR{DT{5}, DT{5}}} | ADD}, DT{5}}} | ADD, DT{2}}} | SUBTRACT | PRINTLN;
  DT{"Hello, World!"} | PRINT;
}