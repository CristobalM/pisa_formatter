//
// Created by Cristobal Miranda, 2019
//

#ifndef PISA_FORMATTER_DOCS_PARSER_HPP
#define PISA_FORMATTER_DOCS_PARSER_HPP


#include <string>

class docs_parser {
  std::string input_file_name;
  std::string basename;

public:
  explicit docs_parser(std::string input_file_name, std::string basename);

  void parse();
  static uint32_t count_file_lines(std::ifstream &file);

};


#endif //PISA_FORMATTER_DOCS_PARSER_HPP
