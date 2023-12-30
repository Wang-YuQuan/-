#pragma once 

#include "../src/node.h"
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/iterator.h"
#include "../src/dfs_iterator.h"

TEST(IteratorSuiteTest, Normal) {
    Node * folder1 = new Folder("test_material/folder2");
    Node * folder2 = new Folder("test_material/folder2/folder3");
    Node * file1 = new File("test_material/folder2/test2.txt");
    folder1->add(folder2);
    folder1->add(file1);

    Iterator * folderIterator = folder1->createIterator();
    folderIterator->first();
    ASSERT_FALSE(folderIterator->isDone());
    ASSERT_EQ(folder2, folderIterator->currentItem());

    folderIterator->next();
    ASSERT_FALSE(folderIterator->isDone());
    ASSERT_EQ(file1, folderIterator->currentItem());

    folderIterator->next();
    ASSERT_TRUE(folderIterator->isDone());
}

TEST(IteratorSuiteTest, DFS) {
    Node * folder1 = new Folder("test_material");
    Node * folder2 = new Folder("test_material/folder1");
    Node * folder3 = new Folder("test_material/folder2");
    Node * folder4 = new Folder("test_material/folder2/folder3");
    Node * file1 = new File("test_material/folder1/test1.txt");
    Node * file2 = new File("test_material/folder2/test2.txt");
    Node * file3 = new File("test_material/folder2/folder3/test3.txt");
    folder1->add(folder2);
    folder1->add(folder3);
    folder2->add(file1);
    folder3->add(folder4);
    folder3->add(file2);
    folder4->add(file3);

    Iterator * dfsIterator = new DfsIterator(folder1);
    dfsIterator->first();
    ASSERT_FALSE(dfsIterator->isDone());
    ASSERT_EQ(folder2, dfsIterator->currentItem());

    dfsIterator->next();
    ASSERT_FALSE(dfsIterator->isDone());
    ASSERT_EQ(file1, dfsIterator->currentItem());

    dfsIterator->next();
    ASSERT_FALSE(dfsIterator->isDone());
    ASSERT_EQ(folder3, dfsIterator->currentItem());

    dfsIterator->next();
    ASSERT_FALSE(dfsIterator->isDone());
    ASSERT_EQ(folder4, dfsIterator->currentItem());

    dfsIterator->next();
    ASSERT_FALSE(dfsIterator->isDone());
    ASSERT_EQ(file3, dfsIterator->currentItem());

    dfsIterator->next();
    ASSERT_FALSE(dfsIterator->isDone());
    ASSERT_EQ(file2, dfsIterator->currentItem());

    dfsIterator->next();
    ASSERT_TRUE(dfsIterator->isDone());

    delete folder1;
    delete folder2;
    delete folder3;
    delete folder4;
    delete file1;
    delete file2;
    delete file3;
}

TEST(IteratorSuiteTest, BFS) {
    Node * folder1 = new Folder("test_material");
    Node * folder2 = new Folder("test_material/folder1");
    Node * folder3 = new Folder("test_material/folder2");
    Node * folder4 = new Folder("test_material/folder2/folder3");
    Node * file1 = new File("test_material/folder1/test1.txt");
    Node * file2 = new File("test_material/folder2/test2.txt");
    Node * file3 = new File("test_material/folder2/folder3/test3.txt");
    folder1->add(folder2);
    folder1->add(folder3);
    folder2->add(file1);
    folder3->add(folder4);
    folder3->add(file2);
    folder4->add(file3);

    Iterator * dfsIterator = new BfsIterator(folder1);
    dfsIterator->first();
    ASSERT_FALSE(dfsIterator->isDone());
    ASSERT_EQ(folder2, dfsIterator->currentItem());

    dfsIterator->next();
    ASSERT_FALSE(dfsIterator->isDone());
    ASSERT_EQ(folder3, dfsIterator->currentItem());

    dfsIterator->next();
    ASSERT_FALSE(dfsIterator->isDone());
    ASSERT_EQ(file1, dfsIterator->currentItem());

    dfsIterator->next();
    ASSERT_FALSE(dfsIterator->isDone());
    ASSERT_EQ(folder4, dfsIterator->currentItem());

    dfsIterator->next();
    ASSERT_FALSE(dfsIterator->isDone());
    ASSERT_EQ(file2, dfsIterator->currentItem());

    dfsIterator->next();
    ASSERT_FALSE(dfsIterator->isDone());
    ASSERT_EQ(file3, dfsIterator->currentItem());

    dfsIterator->next();
    ASSERT_TRUE(dfsIterator->isDone());

    delete folder1;
    delete folder2;
    delete folder3;
    delete folder4;
    delete file1;
    delete file2;
    delete file3;
}