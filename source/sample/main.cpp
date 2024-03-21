/**
 * @brief TODO
 * @author Matthew Guidry (github: mguid65)
 * @date 3/16/24
 */

#include <iostream>
#include <tuple>

#include <data_tree/data_tree.hpp>

#include "fleaux/fleaux.hpp"

using namespace mguid::literals;
static auto Print = fleaux::Node{}.SetEvaluationFunction([](const auto& data) {
  std::cout << data;
  return data;
});

static auto Println = fleaux::Node{}.SetEvaluationFunction([](const auto& data) {
  data | Print;
  std::cout << std::endl;
  return data;
});

static auto Add =
    fleaux::Node{}
        .SetInputInfo({{"lhs", fleaux::DataInfo{.shape = mguid::DataTree{mguid::ObjectNodeType{
                                                    {"type", "Number"_DT_STR}}}}},
                       {"rhs", fleaux::DataInfo{.shape = mguid::DataTree{mguid::ObjectNodeType{
                                                    {"type", "Number"_DT_STR}}}}}})
        .SetOutputInfo({{"result", fleaux::DataInfo{}}})
        .SetEvaluationFunction([](const auto& data) {
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

static auto Subtract =
    fleaux::Node{}
        .SetInputInfo({{"lhs", fleaux::DataInfo{.shape = mguid::DataTree{mguid::ObjectNodeType{
                                                    {"type", "Number"_DT_STR}}}}},
                       {"rhs", fleaux::DataInfo{.shape = mguid::DataTree{mguid::ObjectNodeType{
                                                    {"type", "Number"_DT_STR}}}}}})
        .SetOutputInfo({{"result", fleaux::DataInfo{}}})
        .SetEvaluationFunction([](const auto& data) {
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

static auto Multiply =
    fleaux::Node{}
        .SetInputInfo({{"lhs", fleaux::DataInfo{.shape = mguid::DataTree{mguid::ObjectNodeType{
                                                    {"type", "Number"_DT_STR}}}}},
                       {"rhs", fleaux::DataInfo{.shape = mguid::DataTree{mguid::ObjectNodeType{
                                                    {"type", "Number"_DT_STR}}}}}})
        .SetOutputInfo({{"result", fleaux::DataInfo{}}})
        .SetEvaluationFunction([](const auto& data) {
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

static auto Divide =
    fleaux::Node{}
        .SetInputInfo({{"lhs", fleaux::DataInfo{.shape = mguid::DataTree{mguid::ObjectNodeType{
                                                    {"type", "Number"_DT_STR}}}}},
                       {"rhs", fleaux::DataInfo{.shape = mguid::DataTree{mguid::ObjectNodeType{
                                                    {"type", "Number"_DT_STR}}}}}})
        .SetOutputInfo({{"result", fleaux::DataInfo{}}})
        .SetEvaluationFunction([](const auto& data) {
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
          throw std::runtime_error{"Incorrect operand types for \"Divide\" operation"};
        });

using mguid::ArrayNodeType;
using mguid::DataTree;
using mguid::ObjectNodeType;
using mguid::ValueNodeType;

template <typename... TDataTrees>
DataTree Arr(TDataTrees&&... tree_list) {
  return DataTree{ArrayNodeType{std::forward<TDataTrees>(tree_list)...}};
}

template <typename TDataTrees>
DataTree Val(TDataTrees&& value) {
  return DataTree{ValueNodeType{std::forward<TDataTrees>(value)}};
}

DataTree Obj(std::initializer_list<std::pair<const std::string, DataTree>> args) {
  return DataTree{ObjectNodeType{args}};
}

template <typename TFunc>
fleaux::Node Lazy(TFunc&& func) {
  return fleaux::Node().SetEvaluationFunction(std::forward<TFunc>(func));
};

auto main() -> int {
  using namespace mguid::literals;

  auto AddPrint = Lazy([](DataTree dt) { return dt | Add | Println; });

//  Obj({{"lhs", Val(4)}, {"rhs", Val(6)}}) | AddPrint;

  Arr(Val(5), Val(6)) | AddPrint;

//  Val("Hello, World!") | Println;
//
//  Val(true) | Println;
}