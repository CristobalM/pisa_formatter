//
// Created by Cristobal Miranda, 2019
//
#include <cassert>
#include <string>
#include <fstream>
#include <regex>

#include "cxxopts/cxxopts.hpp"

#include "terms_reader.hpp"
#include "util.hpp"

int main(int argc, char **argv){

  static const std::string terms_idxes_file_label = "terms";
  static const std::string queries_file_label = "queries";
  static const std::string output_file_label = "output";


  cxxopts::Options options("query_transformer", "converts query file with terms to indexes query file");

  std::vector<summary_opts> opts = {
          {terms_idxes_file_label,  "path to terms binary file", cxxopts::value<std::string>()},
          {queries_file_label,  "path to queries file", cxxopts::value<std::string>()},
          {output_file_label,  "path to output file", cxxopts::value<std::string>()}
  };

  auto result_opt_ptr = parse_input_cline(options, opts, argc, argv);
  auto &result_opt = *result_opt_ptr;

  auto terms_file_name = result_opt[terms_idxes_file_label].as<std::string>();
  auto queries_file_name = result_opt[queries_file_label].as<std::string>();
  auto output_file_name = result_opt[output_file_label].as<std::string>();


  terms_reader tr(terms_file_name);
  std::ifstream queries_file(queries_file_name);
  std::ofstream output_file(output_file_name);

  static const std::string word_regex_str = "([^\\s]+)";

  std::regex word_regex(word_regex_str);

  std::string line;
  while(std::getline(queries_file, line)){
    std::vector<std::string> words(std::sregex_token_iterator(line.begin(),line.end(), word_regex),
                                   std::sregex_token_iterator());
    if(words.empty()){
      continue;
    }

    std::stringstream ss;

    uint32_t counter = 0;
    for(const auto &word : words){
      if(!tr.term_exists(word)){
        throw std::runtime_error("Term '" + word + "' not found on terms file: " + terms_file_name);
      }

      auto term_id = tr.get_term_id(word);
      ss << term_id;
      if(counter < words.size() - 1){
        ss << " ";
      }
      else{
        ss << "\n";
      }

      counter++;
    }
    output_file << ss.str();
  }



  return 0;
}