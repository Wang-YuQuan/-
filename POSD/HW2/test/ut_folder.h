#pragma once 

#include <string>
#include "../src/folder.h"

using namespace std;

TEST(TestFolderSuites, Constructor) {
    Node * folder1 = new Folder("test_material/folder1");
    ASSERT_EQ("test_material/folder1", folder1->path());
    ASSERT_EQ("folder1", folder1->name());
    
    ASSERT_ANY_THROW(new Folder("test_material/unexisted folder"));
    ASSERT_ANY_THROW(new Folder("test_material/folder1/test1,txt"));

    delete folder1;
}

TEST(Folder, add_file) {
    Folder home1("test_material/folder1");
    File hello1("test_material/folder1/test1.txt");
    home1.add(&hello1);
    ASSERT_EQ("test1.txt", home1.getChildByName("test1.txt")->name());

    Folder home2("test_material/folder1");
    File hello2("test_material/folder2/test2.txt");
    ASSERT_ANY_THROW(home2.add(&hello2));
}

TEST(TestFolderSuites, GetChildByName) {
    Node * folder1 = new Folder("test_material/folder2");
    Node * file1 = new File("test_material/folder2/test2.txt");
    folder1->add(file1);
    Node * child = folder1->getChildByName("test2.txt");
    ASSERT_EQ(file1, child);

    Node * folder2 = new Folder("test_material/folder2/folder3");
    folder1->add(folder2);
    child = folder1->getChildByName("folder3");
    ASSERT_EQ(folder2, child);
    ASSERT_EQ("test_material/folder2/folder3", child->path());
    ASSERT_EQ("folder3", child->name());

    delete folder1;
    delete folder2;
    delete file1;
}

TEST(TestFolderSuites, Find) {
    Node * folder1 = new Folder("test_material/folder2");
    Node * file1 = new File("test_material/folder2/test2.txt");
    folder1->add(file1);
    Node * child = folder1->find("test_material/folder2/test2.txt");
    ASSERT_EQ(file1, child);

    Node * folder2 = new Folder("test_material/folder2/folder3");
    Node * file2 = new File("test_material/folder2/folder3/test3.txt");
    folder1->add(folder2);
    folder2->add(file2);
    child = folder1->find("test_material/folder2/folder3");
    ASSERT_EQ(folder2, child);
    child = folder1->find("test_material/folder2/folder3/test3.txt");
    ASSERT_EQ(file2, child);

    delete folder1;
    delete folder2;
    delete file1;
    delete file2;
}

TEST(TestFolderSuites, Remove) {
    Node * folder1 = new Folder("test_material/folder2");
    Node * folder2 = new Folder("test_material/folder2/folder3");
    Node * file1 = new File("test_material/folder2/test2.txt");
    Node * file2 = new File("test_material/folder2/folder3/test3.txt");
    folder1->add(file1);
    folder2->add(file2);
    folder1->add(folder2);

    Node * child = folder1->getChildByName("test2.txt");
    ASSERT_TRUE(nullptr!=child);
    ASSERT_EQ("test_material/folder2/test2.txt", child->path());
    folder1->remove("test_material/folder2/test2.txt");
    child = folder1->getChildByName("test2.txt");
    ASSERT_TRUE(nullptr==child);

    folder1->remove("test_material/folder2/folder3");
    child = folder1->getChildByName("folder3");
    ASSERT_TRUE(nullptr==child);

    delete folder1;
    delete folder2;
    delete file1;
    delete file2;
}

TEST(TestFolderSuites, NumberOfFiles) {
    Node * folder1 = new Folder("test_material/folder2");
    Node * folder2 = new Folder("test_material/folder2/folder3");
    Node * file1 = new File("test_material/folder2/test2.txt");
    Node * file2 = new File("test_material/folder2/folder3/test3.txt");
    folder1->add(file1);
    ASSERT_EQ(1, folder1->numberOfFiles());

    folder1->add(folder2);
    ASSERT_EQ(1, folder1->numberOfFiles());

    folder2->add(file2);
    ASSERT_EQ(2, folder1->numberOfFiles());
    ASSERT_EQ(1, folder2->numberOfFiles());

    delete folder1;
    delete folder2;
    delete file1;
    delete file2;
}

TEST(TestFolderSuites, StructChangeException) {
    Node * folder1 = new Folder("test_material/folder2");
    Node * folder2 = new Folder("test_material/folder2/folder3");
    Node * file1 = new File("test_material/folder2/test2.txt");
    Node * file2 = new File("test_material/folder2/folder3/test3.txt");
    folder1->add(file1);
    folder1->add(folder2);
    Iterator * iterator = folder1->createIterator();
    iterator->first();
    ASSERT_EQ(file1, iterator->currentItem());

    folder1->remove("test_material/folder2/test2.txt");
    ASSERT_ANY_THROW(iterator->first());
    ASSERT_ANY_THROW(iterator->next());

    delete folder1;
    delete folder2;
    delete file1;
    delete file2;
    delete iterator;
}