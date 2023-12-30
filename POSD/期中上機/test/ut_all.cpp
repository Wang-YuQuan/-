#include <gtest/gtest.h>

#include "json_test.h"
#include "json_builder_test.h"
#include "json_visitor_test.h"
#include "json_iterator_test.h"
#include "json_parser_test.h"
#include "json_scanner_test.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
