#include "../src/node.h"
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/file_system_parser.h"
#include "../src/file_system_builder.h"

TEST(ParserTest, Parse) {
    FileSystemBuilder * builder = new FileSystemBuilder();
    FileSystemParser * parser = new FileSystemParser(builder);
    parser->setPath("structure/home/Documents");
    parser->parse();
    Folder * root = parser->getRoot();
    Iterator * it1 = root->createIterator(OrderBy::Name);
    Iterator *it2;

    it1->first();
    ASSERT_FALSE(it1->isDone());
    ASSERT_EQ("favorites", it1->currentItem()->name());

    it2 = it1->currentItem()->createIterator(OrderBy::Name);
    it2->first();
    ASSERT_FALSE(it2->isDone());
    ASSERT_EQ("clean-architecture.pdf", it2->currentItem()->name());

    it2->next();
    ASSERT_FALSE(it2->isDone());
    ASSERT_EQ("cqrs.pdf", it2->currentItem()->name());

    it2->next();
    ASSERT_FALSE(it2->isDone());
    ASSERT_EQ("domain-driven-design.pdf", it2->currentItem()->name());

    it2->next();
    ASSERT_TRUE(it2->isDone());

    it1->next();
    ASSERT_FALSE(it1->isDone());
    ASSERT_EQ("hello.txt", it1->currentItem()->name());

    it1->next();
    ASSERT_FALSE(it1->isDone());
    ASSERT_EQ("note.txt", it1->currentItem()->name());

    it1->next();
    ASSERT_TRUE(it1->isDone());
}