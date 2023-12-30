#include "../src/node.h"
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/file_system_scanner.h"

TEST(ScannerTest, NextNode) {
    FileSystemScanner * scanner = new FileSystemScanner();
    scanner->setPath("structure");

    scanner->nextNode();
    ASSERT_EQ("visitor", scanner->currentNodeName());
    ASSERT_FALSE(scanner->isDone());
    ASSERT_FALSE(scanner->isFile());
    ASSERT_TRUE(scanner->isFolder());

    scanner->nextNode();
    ASSERT_EQ("home", scanner->currentNodeName());
    ASSERT_FALSE(scanner->isDone());
    ASSERT_FALSE(scanner->isFile());
    ASSERT_TRUE(scanner->isFolder());

    scanner->nextNode();
    ASSERT_EQ("file.txt", scanner->currentNodeName());
    ASSERT_FALSE(scanner->isDone());
    ASSERT_TRUE(scanner->isFile());
    ASSERT_FALSE(scanner->isFolder());

    scanner->nextNode();
    ASSERT_TRUE(scanner->isDone());

    delete scanner;
}