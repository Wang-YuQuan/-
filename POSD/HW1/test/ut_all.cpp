#include <gtest/gtest.h>
#include "ut_file.h"
#include "ut_folder.h"
#include "ut_folderIterator.h"
#include "ut_dfsIterator.h"
#include "ut_bfsIterator.h"

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}