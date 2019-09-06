//
// Created by Cristobal Miranda, 2019
//

#ifndef PISA_FORMATTER_TERMS_READER_HPP
#define PISA_FORMATTER_TERMS_READER_HPP


#include <string>
#include <vector>
#include <unordered_map>

class terms_reader {
  std::string terms_file_name;

  std::vector<const std::string*> terms;
  std::unordered_map<std::string, uint32_t> term_map_idx;

  void read_file();
public:
  explicit terms_reader(std::string  terms_file_name);

  bool term_exists(const std::string &term);
  uint32_t get_term_id(const std::string &term);

  void debug_read_terms();
};


#endif //PISA_FORMATTER_TERMS_READER_HPP
