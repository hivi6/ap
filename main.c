#include <stdio.h>

#include "ap.h"

int main(int argc, const char* argv[]) {
  printf("argc:%d argv:%p\n", argc, argv);
  for (int i = 0; i < argc; i++) {
    printf("argv[%d]:%s\n", i, argv[i]);
  }

  struct ap_parser *parser = ap_parser_init();

  struct ap_value *help = ap_value_init(AP_FLAG, "show help");
  struct ap_value *verbose = ap_value_init(AP_FLAG, "verbose");
  struct ap_value *object_file = ap_value_init(AP_FVALUE, "object file");

  ap_parser_add_argument(parser, 'h', help);
  ap_parser_add_argument(parser, 'v', verbose);
  ap_parser_add_argument(parser, 'o', object_file);
  int res = ap_parser_parse(parser, argc, argv);
  if (res) {
    printf("Something went wrong while parsing\n");
    return 1;
  }

  printf("help { is_exists:%d value:%s }\n", 
         help->is_exists, help->value);
  printf("verbose { is_exists:%d value:%s }\n", 
         verbose->is_exists, verbose->value);
  printf("object_file { is_exists:%d value:%s }\n", 
         object_file->is_exists, object_file->value);

  ap_parser_delete(parser);
  ap_value_delete(help);
  ap_value_delete(verbose);
  ap_value_delete(object_file);

  return 0;
}

