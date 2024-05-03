#ifndef ARGPARSER_H
#define ARGPARSER_H

#include <stdlib.h>

enum ap_type {
  AP_FLAG,
  AP_FVALUE
};

// value of the argument parser

struct ap_value {
  // provided by user
  enum ap_type type;
  const char* desc;

  // results after parsing
  char is_exists;
  const char* value;
};

struct ap_value *ap_value_init(enum ap_type type, const char* desc);
void ap_value_delete(struct ap_value* value);

// argument parser

struct ap_parser {
  struct ap_value *sym_table[256];
};

struct ap_parser *ap_parser_init();
void ap_parser_delete(struct ap_parser *parser);
int ap_parser_add_argument(struct ap_parser *parser, char sname, 
                            struct ap_value *value);
int ap_parser_parse(struct ap_parser *parser, int argc, const char* argv[]);

// definitions

struct ap_value *ap_value_init(enum ap_type type, const char *desc) {
  struct ap_value *res = malloc(sizeof(struct ap_value));
  if (res == NULL) {
    return NULL;
  }
  res->type = type;
  res->desc = desc;
  res->is_exists = 0;
  res->value = NULL;
  return res;
}

void ap_value_delete(struct ap_value *value) {
  free(value);
}

struct ap_parser *ap_parser_init() {
  struct ap_parser *res = calloc(sizeof(struct ap_parser), 0);
  if (res == NULL) {
    return NULL;
  }
  return res;
}

void ap_parser_delete(struct ap_parser *parser) {
  free(parser);
}

int ap_parser_add_argument(struct ap_parser *parser, char sname, 
                           struct ap_value* value) {
  if (parser == NULL || // invalid parser
      value == NULL ||  // invalid value
      parser->sym_table[sname]) { // something already exists in the symbol table
    return -1; // something went w
  }
  parser->sym_table[sname] = value;
  return 0;
}

int ap_parser_parse(struct ap_parser *parser, int argc, const char* argv[]) {
  int i = 1;
  while (i < argc && argv[i][0] == '-' && argv[i][1] != 0 && argv[i][2] == 0) {
    // get the flag
    char flag = argv[i][1];
    struct ap_value* value = parser->sym_table[flag];
    if (value == NULL) {
      return -1;
    }
    value->is_exists = 1;
    if (value->type == AP_FVALUE) {
      if (i + 1 >= argc) {
        return -1;
      }
      value->value = argv[i + 1];
      i += 2;
    } else {
      i++;
    }
  }
  return i == argc ? 0 : -1;
}

#endif // ARGPARSER_H
