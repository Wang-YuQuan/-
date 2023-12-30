#include "../src/node.h"
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/iterator.h"
#include "../src/file_system_builder.h"

TEST(BuilderTest, BuildFileAndFolder) {
    FileSystemBuilder * builder = new FileSystemBuilder();
    builder->buildFolder("structure");
    builder->buildFolder("structure/home");
    builder->buildFolder("structure/home/Documents");
    builder->buildFile("structure/home/Documents/hello.txt");
    builder->endFolder();
    builder->endFolder();
    builder->buildFolder("structure/visitor");
    builder->endFolder();
    builder->buildFile("structure/file.txt");
    builder->endFolder();

    Folder * root = builder->getRoot();
    Iterator * it1 = root->createIterator();
    Iterator *it2, *it3;
    it1->first();
    ASSERT_FALSE(it1->isDone());
    ASSERT_EQ("structure/home", it1->currentItem()->path());

    it2 = it1->currentItem()->createIterator();
    it2->first();
    ASSERT_FALSE(it2->isDone());
    ASSERT_EQ("structure/home/Documents", it2->currentItem()->path());

    it3 = it2->currentItem()->createIterator();
    it3->first();
    ASSERT_FALSE(it3->isDone());
    ASSERT_EQ("structure/home/Documents/hello.txt", it3->currentItem()->path());

    it3->next();
    ASSERT_TRUE(it3->isDone());

    it2->next();
    ASSERT_TRUE(it2->isDone());

    it1->next();
    ASSERT_FALSE(it1->isDone());
    ASSERT_EQ("structure/visitor", it1->currentItem()->path());

    it1->next();
    ASSERT_FALSE(it1->isDone());
    ASSERT_EQ("structure/file.txt", it1->currentItem()->path());

    it1->next();
    ASSERT_TRUE(it1->isDone());
}