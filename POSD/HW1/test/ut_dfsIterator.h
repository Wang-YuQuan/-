#include "../src/iterator.h"
#include "../src/dfs_iterator.h"
#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"

TEST(TestDFSIteratorSuites, First) {
    Node * folder1 = new Folder("/Documents");
    Node * folder2 = new Folder("/Documents/Users");
    Node * folder3 = new Folder("/Documents/Users/Downloads");
    Node * file1 = new File("/Documents/test1.txt");
    Node * file2 = new File("/Documents/Users/test2.txt");
    Node * file3 = new File("/Documents/Users/Downloads/test3.txt");
    Node * file4 = new File("/Documents/test4.txt");
    folder1->add(file1);
    folder1->add(folder2);
    folder1->add(file4);
    folder2->add(file2);
    folder2->add(folder3);
    folder3->add(file3);
    Iterator * dfsIterator = folder1->createIterator("DFS");
    dfsIterator->first();
    ASSERT_EQ(file1, dfsIterator->currentItem());
}

TEST(TestDFSIteratorSuites, Next) {
    Node * folder1 = new Folder("/Documents");
    Node * folder2 = new Folder("/Documents/Users");
    Node * folder3 = new Folder("/Documents/Users/Downloads");
    Node * file1 = new File("/Documents/test1.txt");
    Node * file2 = new File("/Documents/Users/test2.txt");
    Node * file3 = new File("/Documents/Users/Downloads/test3.txt");
    Node * file4 = new File("/Documents/test4.txt");
    folder1->add(file1);
    folder1->add(folder2);
    folder1->add(file4);
    folder2->add(file2);
    folder2->add(folder3);
    folder3->add(file3);
    Iterator * dfsIterator = folder1->createIterator("DFS");
    dfsIterator->first();
    ASSERT_FALSE(dfsIterator->isDone());
    ASSERT_EQ(file1, dfsIterator->currentItem());

    dfsIterator->next();
    ASSERT_FALSE(dfsIterator->isDone());
    ASSERT_EQ(folder2, dfsIterator->currentItem());

    dfsIterator->next();
    ASSERT_FALSE(dfsIterator->isDone());
    ASSERT_EQ(file2, dfsIterator->currentItem());

    dfsIterator->next();
    ASSERT_FALSE(dfsIterator->isDone());
    ASSERT_EQ(folder3, dfsIterator->currentItem());

    dfsIterator->next();
    ASSERT_FALSE(dfsIterator->isDone());
    ASSERT_EQ(file3, dfsIterator->currentItem());

    dfsIterator->next();
    ASSERT_FALSE(dfsIterator->isDone());
    ASSERT_EQ(file4, dfsIterator->currentItem());

    dfsIterator->next();
    ASSERT_TRUE(dfsIterator->isDone());
}