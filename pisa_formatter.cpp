#include <cassert>
#include <algorithm>
#include <fstream>
#include <regex>
#include <iostream>
#include <vector>

#include "cxxopts/cxxopts.hpp"
#include "docs_parser.hpp"

#include "util.hpp"

int main(int argc, char **argv) {
  static const std::string word_regex = "([^\\s]+)";

  static const std::string input_file_optid = "input_file";
  static const std::string basename = "basename";



  cxxopts::Options options("pisa_formatter", "converts input documents into pisa format");

  std::vector<summary_opts> opts = {
          {input_file_optid,  "path to the documents file", cxxopts::value<std::string>()},
          {basename,  "output basename", cxxopts::value<std::string>()}
  };



  auto result_opt_ptr = parse_input_cline(options, opts, argc, argv);
  auto &result_opt = *result_opt_ptr;



  docs_parser dp(result_opt[input_file_optid].as<std::string>(), result_opt[basename].as<std::string>());

  dp.parse();


  return 0;
}