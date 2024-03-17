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

struct ChannelInfo {
  mguid::DataTree default_val{mguid::ValueNodeType{}};
  std::optional<mguid::DataTree> shape{std::nullopt};
};

struct Node {
  using ParameterMap = std::unordered_map<std::string, mguid::DataTree>;
  using ChannelInfoMap = std::unordered_map<std::string, ChannelInfo>;

  Node& AddInputChannel(const std::string& name, ChannelInfo channel_info) {
    m_input_channels[name] = std::move(channel_info);
    return *this;
  }

  Node& AddOutputChannel(const std::string& name, ChannelInfo channel_info) {
    m_output_channels[name] = std::move(channel_info);
    return *this;
  }

  Node& AddEvaluationFunction(std::function<mguid::DataTree(const mguid::DataTree&)> func) {
    m_eval_func = std::move(func);
    return *this;
  }

  mguid::DataTree Evaluate(const mguid::DataTree& params) const {
    ValidateParams(params, m_input_channels);
    const auto result = m_eval_func(params);
    ValidateParams(result, m_output_channels);
    return result;
  }

private:
  void ValidateParams(const mguid::DataTree&, const ChannelInfoMap&) const {}

  ChannelInfoMap m_input_channels;
  std::function<mguid::DataTree(const mguid::DataTree&)> m_eval_func{
      [](const mguid::DataTree& input) -> mguid::DataTree { return input; }};

  ChannelInfoMap m_output_channels;
};

mguid::DataTree operator|(const mguid::DataTree& dt, const Node& node) { return node.Evaluate(dt); }

}  // namespace fleaux

#endif  // FLEAUX_FLEAUX_HPP
