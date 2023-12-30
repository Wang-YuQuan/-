#include "../src/node.h"
#include "../src/file.h"

TEST(TestFileSuites, Name) {
    Node * file = new File("C:/Documents");
    ASSERT_EQ("Documents", file->name());
    delete file;
}

TEST(TestFileSuites, Path) {
    Node * file = new File("C:/Documents");
    ASSERT_EQ("C:/Documents", file->path());
    delete file;
}

TEST(TestFileSuites, NumberOfFiles) {
    Node * file = new File("C:/Documents");
    ASSERT_EQ(1, file->numberOfFiles());
    delete file;
}