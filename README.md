# ap

Argument Parser in C

## Usage

```c
#include <stdio.h>

#include "ap.h"

int main(int argc, const char* argv[]) {
  struct ap_value *help = ap_value_init(AP_FLAG, "show help", "-h", "--help");
  struct ap_value *verbose = ap_value_init(AP_FLAG, "verbose", "-v", "--verbose");
  struct ap_value *output = ap_value_init(AP_FVALUE, "output file", "-o", "--out");

  struct ap_parser *parser = ap_parser_init("testprogram", "Test Program");

  ap_parser_add_argument(parser, help);
  ap_parser_add_argument(parser, verbose);
  ap_parser_add_argument(parser, output);


  int err = ap_parser_parse(parser, argc, argv);
  ap_parser_help(parser);
  if (err) {
    printf("Something went wrong while parsing\n");
    exit(1);
  }

  printf("\n");
  printf("help {is_exists:%d value:%s}\n", help->is_exists, help->value);
  printf("verbose {is_exists:%d value:%s}\n", verbose->is_exists, verbose->value);
  printf("output {is_exists:%d value:%s}\n", output->is_exists, output->value);
  
  ap_parser_delete(parser);

  ap_value_delete(help);
  ap_value_delete(verbose);
  ap_value_delete(output);

  return 0;
}
```
