#include <utility>
#include <fstream>
#include <iostream>
#include <memory>

//
// Created by Cristobal Miranda, 2019
//

#include "terms_reader.hpp"

terms_reader::terms_reader(std::string terms_file_name) : terms_file_name(std::move(terms_file_name)) {
  read_file();
}

void terms_reader::read_file() {
  std::ifstream file(terms_file_name, std::ios::binary);

  constexpr auto u32_sz = sizeof(uint32_t);

  {
    file.seekg(0, std::ifstream::end);
    uint32_t file_length = file.tellg();
    if(file_length < u32_sz){
      throw std::runtime_error("Can't read the number of terms in file " + terms_file_name);
    }
    file.seekg(0, std::ifstream::beg);
  }

  uint32_t nof_terms;
  file.read((char *)&nof_terms, u32_sz);

  for(uint32_t i = 0; i < nof_terms; i++){
    uint32_t term_length;
    file.read((char *)&term_length, u32_sz);

    std::string term(term_length, 0);
    file.read(term.data(), term_length * sizeof(char));
    auto insert_r = term_map_idx.insert({term, i});

    terms.push_back(&((*insert_r.first).first)); // to save space it only stores a pointer to the string, not the string itself
  }
}

bool terms_reader::term_exists(const std::string &term) {
  return term_map_idx.find(term) != term_map_idx.end();
}

void terms_reader::debug_read_terms() {
  for(const auto *s : terms){
    std::cout << *s << std::endl;
  }
}

uint32_t terms_reader::get_term_id(const std::string &term) {
  return term_map_idx[term];
}
