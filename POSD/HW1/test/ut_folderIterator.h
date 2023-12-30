#include "../src/iterator.h"
#include "../src/dfs_iterator.h"
#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"

TEST(TestFolderIteratorSuites, Next) {
    Node * folder1 = new Folder("/Documents");
    Node * folder2 = new Folder("/Documents/Users1");
    Node * folder3 = new Folder("/Documents/Users2");
    Node * file1 = new File("/Documents/test1.txt");
    Node * file2 = new File("/Documents/test2.txt");
    folder1->add(folder2);
    folder1->add(file1);
    folder1->add(folder3);
    folder1->add(file2);

    Iterator * folderIterator = folder1->createIterator("");
    folderIterator->first();
    ASSERT_FALSE(folderIterator->isDone());
    ASSERT_EQ(folder2, folderIterator->currentItem());

    folderIterator->next();
    ASSERT_FALSE(folderIterator->isDone());
    ASSERT_EQ(file1, folderIterator->currentItem());

    folderIterator->next();
    ASSERT_FALSE(folderIterator->isDone());
    ASSERT_EQ(folder3, folderIterator->currentItem());

    folderIterator->next();
    ASSERT_FALSE(folderIterator->isDone());
    ASSERT_EQ(file2, folderIterator->currentItem());

    folderIterator->next();
    ASSERT_TRUE(folderIterator->isDone());
}