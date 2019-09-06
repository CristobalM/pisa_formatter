

//
// Created by Cristobal Miranda, 2019
//
#include <memory>
#include <fstream>
#include <vector>

#include <unordered_map>
#include <sstream>
#include <utility>

#include <regex>

#include "docs_parser.hpp"


docs_parser::docs_parser(std::string input_file_name, std::string basename) :
input_file_name(std::move(input_file_name)),
basename(std::move(basename))
{

}


void docs_parser::parse() {
  static const std::string word_regex = "([^\\s]+)";
  static const std::regex word_regex_load(word_regex);


  std::ifstream file(input_file_name);


  std::unordered_map<std::string, uint32_t> terms_indexes;
  std::vector<std::string> terms_strings;
  std::unordered_map<std::string, uint32_t> docs_indexes;
  std::unordered_map<uint32_t, std::vector<std::pair<uint32_t, uint32_t>>> terms_to_docs_freq;
  std::vector<uint32_t> doc_sizes;


  std::string line;
  uint32_t term_counter = 0;
  uint32_t doc_counter = 0;


  while(std::getline(file, line)){
    std::vector<std::string> words(std::sregex_token_iterator(line.begin(),line.end(), word_regex_load),
                                           std::sregex_token_iterator());
    if(words.empty()){
      continue;
    }

    std::unordered_map<uint32_t, uint32_t> term_freq_current_doc;
    doc_sizes.push_back(words.size());


    auto &doc_name = words[0];
    uint32_t doc_idx;
    if(docs_indexes.find(doc_name) == docs_indexes.end()){
      doc_idx = doc_counter++;
      docs_indexes[doc_name] = doc_idx;
    }
    else{
      doc_idx = docs_indexes[doc_name];
    }

    for(auto i = 1ul; i < words.size(); i++){
     const auto &current_word = words[i];

     uint32_t current_word_index;
     if(terms_indexes.find(current_word) == terms_indexes.end()){
       current_word_index = term_counter++;
       terms_strings.push_back(current_word);
       auto &word_ = terms_strings[terms_strings.size()-1];
       terms_indexes[word_] = current_word_index;
     }
     else{
       current_word_index = terms_indexes[current_word];
     }

     if(term_freq_current_doc.find(current_word_index) == term_freq_current_doc.end()){
       term_freq_current_doc[current_word_index] = 0;
     }
     term_freq_current_doc[current_word_index]++;
    }

    for(const auto &tfcd_it : term_freq_current_doc){
      const auto word_idx = tfcd_it.first;
      const auto freq = tfcd_it.second;
      terms_to_docs_freq[word_idx].emplace_back(doc_idx, freq);
    }
  }

  std::ofstream docs_file(basename + ".docs", std::ios::binary);
  std::ofstream freqs_file(basename + ".freqs", std::ios::binary);
  std::ofstream sizes_file(basename + ".sizes", std::ios::binary);
  std::ofstream terms_file(basename + ".terms", std::ios::binary);

  auto docs_qty = (uint32_t)docs_indexes.size();
  constexpr auto u32_sz = sizeof(uint32_t);
  constexpr auto one_sz = static_cast<uint32_t>(1);
  docs_file.write((char *)&one_sz, u32_sz);
  docs_file.write((char *)&docs_qty, u32_sz);

  terms_file.write((char *)&term_counter, u32_sz);

  for(auto i = 0ul; i < term_counter; i++){
    const auto word_list = terms_to_docs_freq[i];
    const auto word_docs_qty = static_cast<uint32_t>(word_list.size());

    docs_file.write((char *)&word_docs_qty, u32_sz);
    freqs_file.write((char *)&word_docs_qty, u32_sz);
    for(const auto &w_p : word_list){
      const auto doc_id = w_p.first;
      const auto term_freq_in_doc = w_p.second;
      docs_file.write((char *)&doc_id, u32_sz);
      freqs_file.write((char *)&term_freq_in_doc, u32_sz);
    }
    const auto &current_term = terms_strings[i];
    const auto term_sz = (uint32_t)current_term.size();
    const auto *c_str = current_term.c_str();
    terms_file.write((char *)&term_sz, u32_sz);
    terms_file.write(c_str, term_sz * sizeof(char));
  }

  sizes_file.write((char *)&docs_qty, u32_sz);
  for(auto doc_size : doc_sizes){
    sizes_file.write((char *)&doc_size, u32_sz);
  }
}

uint32_t docs_parser::count_file_lines(std::ifstream &file) {
  uint32_t counter = 0;
  file.clear();
  file.seekg(0, std::ios::beg);
  std::string line;
  while(std::getline(file, line)){
    counter++;
  }
  file.clear();
  file.seekg(0, std::ios::beg);
  return counter;
}
