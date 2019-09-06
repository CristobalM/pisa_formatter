//
// Created by Cristobal Miranda, 2019
//

#ifndef PISA_FORMATTER_UTIL_HPP
#define PISA_FORMATTER_UTIL_HPP

#include <string>
#include <memory>
#include <vector>

#include "cxxopts/cxxopts.hpp"

struct summary_opts {
  std::string option, description;
  std::shared_ptr<cxxopts::Value> value;
};

using vsopts = std::vector<summary_opts>;

inline void check_missing_opts(cxxopts::ParseResult &result_opt, vsopts &vso){
  for(auto &so : vso){
    if (result_opt[so.option].count() < 1) {
      throw std::runtime_error("--" + so.option + " option is missing: " + so.description);
    }
  }
}

std::unique_ptr<cxxopts::ParseResult> parse_input_cline(cxxopts::Options &options,
        std::vector<summary_opts> &opts, int argc, char **argv){

  auto acc_opts = options.add_options();
  for (auto &opt : opts) {
    acc_opts(opt.option, opt.description, opt.value);
  }


  std::unique_ptr<cxxopts::ParseResult> result_opt_ptr;

  try {
    result_opt_ptr = std::make_unique<cxxopts::ParseResult>(options.parse(argc, argv));
  }
  catch (const cxxopts::argument_incorrect_type &e) {
    throw std::runtime_error("Invalid input: type error\nReason: " + std::string(e.what()));
  }

  check_missing_opts(*result_opt_ptr, opts);

  return result_opt_ptr;
}

#endif //PISA_FORMATTER_UTIL_HPP
