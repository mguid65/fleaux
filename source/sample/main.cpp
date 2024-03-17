/**
 * @brief TODO
 * @author Matthew Guidry (github: mguid65)
 * @date 3/16/24
 */

#include <iostream>
#include <tuple>

#include <data_tree/data_tree.hpp>

#include "fleaux/fleaux.hpp"

static auto Print = fleaux::Node{}.AddEvaluationFunction([](const auto& data) {
  data.Visit(
      [](mguid::ObjectNodeType&) { std::cout << "Object"; },
      [](mguid::ArrayNodeType&) { std::cout << "Array"; },
      [](mguid::ValueNodeType& value_node) {
        value_node.Visit(
            [](mguid::NumberType& value) { value.Visit([](auto number) { std::cout << number; }); },
            [](mguid::BoolType& value) {
              std::cout << std::boolalpha << value << std::noboolalpha;
            },
            [](mguid::StringType& value) { std::cout << value; },
            [](mguid::NullType& value) { std::cout << value; });
      });
  return data;
});

static auto Println = fleaux::Node{}.AddEvaluationFunction([](const auto& data) {
  data | Print;
  std::cout << std::endl;
  return data;
});

static auto Add =
    fleaux::Node{}
        .AddInputChannel("lhs", fleaux::ChannelInfo{})
        .AddInputChannel("rhs", fleaux::ChannelInfo{})
        .AddEvaluationFunction([](const auto& data) {
          static constexpr auto common =
              [](const auto& expected_lhs_inner,
                 const auto& expected_rhs_inner) -> std::optional<mguid::DataTree> {
            if (const auto [lhs, rhs] = std::tuple(expected_lhs_inner->TryGetNumber(),
                                                   expected_rhs_inner->TryGetNumber());
                lhs.has_value() && rhs.has_value()) {
              if (const auto lhs_uint = lhs->GetUInt(); lhs_uint.has_value()) {
                if (const auto rhs_uint = rhs->GetUInt(); rhs_uint.has_value()) {
                  return mguid::DataTree{*lhs_uint + *rhs_uint};
                } else if (const auto rhs_int = rhs->GetInt(); rhs_int.has_value()) {
                  return mguid::DataTree{static_cast<mguid::IntegerType>(*lhs_uint) + *rhs_int};
                } else if (const auto rhs_double = rhs->GetDouble(); rhs_double.has_value()) {
                  return mguid::DataTree{static_cast<mguid::DoubleType>(*lhs_uint) + *rhs_double};
                }
              } else if (const auto lhs_int = lhs->GetInt(); lhs_int.has_value()) {
                if (const auto rhs_uint = rhs->GetUInt(); rhs_uint.has_value()) {
                  return mguid::DataTree{*lhs_int + static_cast<mguid::IntegerType>(*rhs_uint)};
                } else if (const auto rhs_int = rhs->GetInt(); rhs_int.has_value()) {
                  return mguid::DataTree{*lhs_int + *rhs_int};
                } else if (const auto rhs_double = rhs->GetDouble(); rhs_double.has_value()) {
                  return mguid::DataTree{static_cast<mguid::DoubleType>(*lhs_int) + *rhs_double};
                }
              } else if (const auto lhs_double = lhs->GetDouble(); lhs_double.has_value()) {
                if (const auto rhs_uint = rhs->GetUInt(); rhs_uint.has_value()) {
                  return mguid::DataTree{*lhs_double + static_cast<mguid::DoubleType>(*rhs_uint)};
                } else if (const auto rhs_int = rhs->GetInt(); rhs_int.has_value()) {
                  return mguid::DataTree{*lhs_double + static_cast<mguid::DoubleType>(*rhs_int)};
                } else if (const auto rhs_double = rhs->GetDouble(); rhs_double.has_value()) {
                  return mguid::DataTree{*lhs_double + *rhs_double};
                }
              }
            }
            return std::nullopt;
          };

          if (const auto [expected_lhs_named, expected_rhs_named] =
                  std::tuple(data.TryGet("lhs"), data.TryGet("rhs"));
              expected_lhs_named.has_value() && expected_rhs_named.has_value()) {
            if (const auto result = common(expected_lhs_named, expected_rhs_named);
                result.has_value()) {
              return *result;
            }
          } else if (const auto [expected_lhs, expected_rhs] =
                         std::tuple(data.TryGet(0), data.TryGet(1));
                     expected_lhs.has_value() && expected_rhs.has_value()) {
            if (const auto result = common(expected_lhs, expected_rhs); result.has_value()) {
              return *result;
            }
          }
          throw std::runtime_error{"Incorrect operand types for \"Add\" operation"};
        });

auto main() -> int {
  using mguid::ArrayNodeType;
  using mguid::DataTree;

  DataTree{ArrayNodeType{DataTree{2}, DataTree{3}}} | Add | Println | Println | Println | Println;
  DataTree{"Hello, World"} | Print;
}