# Pisa formatter

### Executables

**pisa_formatter**: converts list of documents to the pisa-engine binary format: {.docs, .freqs, .sizes}.
Its input should be a text file where each line is a document.
 Each document starts with the document name (which should not have whitespaces) followed by a list of ascii terms separated by whitespaces which define the document.

This also generates a binary .terms file which has the information to convert from term to index
and is used by the query_transformer executable. This file stores all the unique terms from all the documents.

Usage:
```
./pisa_formatter --input_file="INPUT_FILE_PATH" --basename="PATH_TO_BASENAME/BASENAME"
```

Here basename is the prefix for each of the files generated.

**query_transformer**: transforms a list of queries, separated by line breaks, with terms contained
in the  .terms binary file. The output is a text file

Usage:
```
./query_transformer --queries="PATH_TO_QUERIES_FILE" --terms="PATH_TO_TERMS_FILE" --output="PATH_TO_OUTPUT_FILE"
```

**print_terms**: This reads a .terms file and prints the list of terms by the order of their index

Usage:
```
./print_terms --terms="PATH_TO_TERMS_FILE"
```

### Build

```
mkdir -p build
cd build
cmake ..
make
```