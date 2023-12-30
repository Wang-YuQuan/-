#include "../src/iterator.h"
#include "../src/dfs_iterator.h"
#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"

TEST(TestBFSIteratorSuites, First) {
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
    Iterator * bfsIterator = folder1->createIterator("BFS");
    bfsIterator->first();
    ASSERT_EQ(file1, bfsIterator->currentItem());
}

TEST(TestBFSIteratorSuites, Next) {
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
    Iterator * bfsIterator = folder1->createIterator("BFS");
    bfsIterator->first();
    ASSERT_FALSE(bfsIterator->isDone());
    ASSERT_EQ(file1, bfsIterator->currentItem());

    bfsIterator->next();
    ASSERT_FALSE(bfsIterator->isDone());
    ASSERT_EQ(folder2, bfsIterator->currentItem());

    bfsIterator->next();
    ASSERT_FALSE(bfsIterator->isDone());
    ASSERT_EQ(file4, bfsIterator->currentItem());

    bfsIterator->next();
    ASSERT_FALSE(bfsIterator->isDone());
    ASSERT_EQ(file2, bfsIterator->currentItem());

    bfsIterator->next();
    ASSERT_FALSE(bfsIterator->isDone());
    ASSERT_EQ(folder3, bfsIterator->currentItem());

    bfsIterator->next();
    ASSERT_FALSE(bfsIterator->isDone());
    ASSERT_EQ(file3, bfsIterator->currentItem());

    bfsIterator->next();
    ASSERT_TRUE(bfsIterator->isDone());
}