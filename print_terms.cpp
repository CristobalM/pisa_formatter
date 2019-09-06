//
// Created by Cristobal Miranda, 2019
//

#include <string>

#include "cxxopts/cxxopts.hpp"

#include "util.hpp"
#include "terms_reader.hpp"

int main(int argc, char **argv) {
  static const std::string word_regex = "([^\\s]+)";

  static const std::string terms_idxes_file_label = "terms";


  cxxopts::Options options("query_transformer", "converts query file with terms to indexes query file");

  std::vector<summary_opts> opts = {
          {terms_idxes_file_label,  "path to terms binary file", cxxopts::value<std::string>()}
  };

  auto result_opt_ptr = parse_input_cline(options, opts, argc, argv);
  auto &result_opt = *result_opt_ptr;

  auto terms_file_name = result_opt[terms_idxes_file_label].as<std::string>();


  terms_reader tr(terms_file_name);

  tr.debug_read_terms();



  return 0;
}