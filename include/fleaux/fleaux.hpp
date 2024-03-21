/**
 * @brief TODO
 * @author Matthew Guidry (github: mguid65)
 * @date 3/16/24
 */

#ifndef FLEAUX_FLEAUX_HPP
#define FLEAUX_FLEAUX_HPP

#include <functional>
#include <string>
#include <unordered_map>
#include <utility>

#include <data_tree/data_tree.hpp>

namespace fleaux {

struct DataInfo {
  std::optional<mguid::DataTree> default_val{std::nullopt};
  std::optional<mguid::DataTree> shape{std::nullopt};
};

struct Node {
  using ParameterMap = std::unordered_map<std::string, mguid::DataTree>;
  using DataInfoMap = std::vector<std::pair<std::string, DataInfo>>;

  Node& SetInputInfo(DataInfoMap input_info) {
    m_input_info = std::move(input_info);
    return *this;
  }

  Node& SetOutputInfo(DataInfoMap output_info) {
    m_output_info = std::move(output_info);
    return *this;
  }

  Node& SetEvaluationFunction(std::function<mguid::DataTree(const mguid::DataTree&)> func) {
    m_eval_func = std::move(func);
    return *this;
  }

  mguid::DataTree Evaluate(const mguid::DataTree& params) const {
    if (const auto validation = ValidateParams(params, m_input_info); !validation.ok) {
      throw std::runtime_error("Invalid Parameter Shape");
    }

    const auto result = m_eval_func(params);

    if (const auto validation = ValidateParams(result, m_output_info); !validation.ok) {
      throw std::runtime_error("Invalid Result Shape");
    }

    return result;
  }

private:
  struct ValidationResult {
    bool ok{false};
    /* std::string what; */
  };

  /**
   * @brief Validate data shape against the provided DataInfoMap
   * @param data data to validate
   * @param shape data shape
   * @return ValidationResult which will either be good or bad and contain a reason
   */
  static ValidationResult ValidateParams([[maybe_unused]] const mguid::DataTree& data,
                                         const DataInfoMap& shape) {
    // Empty shape == Unconstrained Shape
    if (shape.empty()) { return ValidationResult{.ok = true}; }

    const auto n_params = shape.size();

    auto result = ValidationResult{.ok = true};
    // Begin Data Validation
    data.Visit(
        [&]([[maybe_unused]] const mguid::ObjectNodeType& obj) {
          for ([[maybe_unused]] const auto& [name, data_constraint] : shape) {}
        },
        [&]([[maybe_unused]] const mguid::ArrayNodeType& arr) {
          for ([[maybe_unused]] const auto& [name, data_constraint] : shape) {}
        },
        [&]([[maybe_unused]] const mguid::ValueNodeType& val) {
          if (n_params > 1) {
            result.ok = false;
            return;
          }
        });
    // End Data Validation

    return result;
  }

  DataInfoMap m_input_info;
  std::function<mguid::DataTree(const mguid::DataTree&)> m_eval_func{
      [](const mguid::DataTree& input) -> mguid::DataTree { return input; }};

  DataInfoMap m_output_info;
};

mguid::DataTree operator|(const mguid::DataTree& dt, const Node& node) { return node.Evaluate(dt); }

}  // namespace fleaux

#endif  // FLEAUX_FLEAUX_HPP
