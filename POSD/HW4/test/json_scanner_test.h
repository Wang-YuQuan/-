#include "../src/json_scanner.h"

TEST(ScannerSuite, ScanAllText) {
    JsonScanner * scanner = new JsonScanner();
    scanner->setInput("{\"A\":\"B\"}");
    char token;

    token = scanner->next();
    ASSERT_EQ('{', token);
    ASSERT_FALSE(scanner->isDone());

    token = scanner->next();
    ASSERT_EQ('"', token);
    ASSERT_FALSE(scanner->isDone());

    token = scanner->next();
    ASSERT_EQ('A', token);
    ASSERT_FALSE(scanner->isDone());

    token = scanner->next();
    ASSERT_EQ('"', token);
    ASSERT_FALSE(scanner->isDone());

    token = scanner->next();
    ASSERT_EQ(':', token);
    ASSERT_FALSE(scanner->isDone());

    token = scanner->next();
    ASSERT_EQ('"', token);
    ASSERT_FALSE(scanner->isDone());

    token = scanner->next();
    ASSERT_EQ('B', token);
    ASSERT_FALSE(scanner->isDone());

    token = scanner->next();
    ASSERT_EQ('"', token);
    ASSERT_FALSE(scanner->isDone());

    token = scanner->next();
    ASSERT_EQ('}', token);
    ASSERT_FALSE(scanner->isDone());

    token = scanner->next();
    ASSERT_TRUE(scanner->isDone());

    delete scanner;
}