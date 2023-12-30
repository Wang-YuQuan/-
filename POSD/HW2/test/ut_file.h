#pragma once 

#include "../src/file.h"

TEST(TestFileSuites, Constructor) {
    Node * file1 = new File("test_material/folder1/test1.txt");
    ASSERT_EQ("test_material/folder1/test1.txt", file1->path());
    ASSERT_EQ("test1.txt", file1->name());
    
    ASSERT_ANY_THROW(new File("test_material/unexisted file"));
    ASSERT_ANY_THROW(new File("test_material/src"));

    delete file1;
}