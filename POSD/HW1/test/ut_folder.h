#include "../src/node.h"
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/iterator.h"

TEST(TestFolderSuites, Name) {
    Node * folder = new Folder("C:/Documents");
    ASSERT_EQ("Documents", folder->name());
    delete folder;
}

TEST(TestFolderSuites, Path) {
    Node * folder = new Folder("C:/Documents");
    ASSERT_EQ("C:/Documents", folder->path());
    delete folder;
}

TEST(TestFolderSuites, Add) {
    Node * folder1 = new Folder("C:/Documents");
    Node * folder2 = new Folder("C:/Documents/user");
    folder1->add(folder2);
    Iterator * it = folder1->createIterator();
    it->first();
    int count = 0;
    while(!it->isDone()){
        count++;
        it->next();
    }
    ASSERT_EQ(1, count);

    Node * folder3 = new Folder("C:/Downloads/user");
    ASSERT_ANY_THROW(folder1->add(folder3));
    it->first();
    count = 0;
    while(!it->isDone()){
        count++;
        it->next();
    }
    ASSERT_EQ(1, count);

    delete folder1;
    delete it;
}

TEST(TestFolderSuites, GetChildByName) {
    Node * folder1 = new Folder("C:/Documents");
    Node * file1 = new File("C:/Documents");
    ASSERT_ANY_THROW(folder1->add(file1));
    Node * child = folder1->getChildByName("Documents");
    ASSERT_EQ(nullptr, child);

    Node * file2 = new File("C:/Documents/test1.txt");
    folder1->add(file2);
    child = folder1->getChildByName("test1.txt");
    ASSERT_TRUE(nullptr!=child);
    ASSERT_EQ("C:/Documents/test1.txt", child->path());
    ASSERT_EQ("test1.txt", child->name());

    Node * folder2 = new Folder("C:/Documents/Users");
    Node * file3 = new File("C:/Documents/Users/test2.txt");
    folder2->add(file3);
    folder1->add(folder2);
    child = folder1->getChildByName("test2.txt");
    ASSERT_TRUE(nullptr!=child);
    ASSERT_EQ("C:/Documents/Users/test2.txt", child->path());
    ASSERT_EQ("test2.txt", child->name());

    delete folder1;
    delete folder2;
    delete file1;
    delete file2;
    delete file3;
}

TEST(TestFolderSuites, Find) {
    Node * folder1 = new Folder("C:/Documents");
    Node * file1 = new File("C:/Documents");
    ASSERT_ANY_THROW(folder1->add(file1));
    Node * child = folder1->find("Documents");
    ASSERT_EQ(nullptr, child);

    Node * file2 = new File("C:/Documents/test1.txt");
    folder1->add(file2);
    child = folder1->find("C:/Documents/test1.txt");
    ASSERT_TRUE(nullptr!=child);
    ASSERT_EQ("C:/Documents/test1.txt", child->path());

    Node * folder2 = new Folder("C:/Documents/Users");
    Node * file3 = new File("C:/Documents/Users/test2.txt");
    folder2->add(file3);
    folder1->add(folder2);
    child = folder1->find("C:/Documents/Users/test2.txt");
    ASSERT_TRUE(NULL!=child);
    ASSERT_EQ("C:/Documents/Users/test2.txt", child->path());

    delete folder1;
    delete folder2;
    delete file1;
    delete file2;
    delete file3;
}

TEST(TestFolderSuites, Remove) {
    Node * folder1 = new Folder("C:/Documents");
    Node * folder2 = new Folder("C:/Documents/Users");
    Node * file1 = new File("C:/Documents/test1.txt");
    Node * file2 = new File("C:/Documents/Users/test2.txt");
    folder1->add(file1);
    folder2->add(file2);
    folder1->add(folder2);

    Node * child = folder1->getChildByName("test1.txt");
    ASSERT_TRUE(nullptr!=child);
    ASSERT_EQ("C:/Documents/test1.txt", child->path());
    folder1->remove("C:/Documents/test1.txt");
    child = folder1->getChildByName("test1.txt");
    ASSERT_TRUE(nullptr==child);

    folder1->remove("C:/Documents/Users/test2.txt");
    child = folder1->getChildByName("test2.txt");
    ASSERT_TRUE(nullptr==child);

    delete folder1;
    delete folder2;
    delete file1;
    delete file2;
}

TEST(TestFolderSuites, NumberOfFiles) {
    Node * folder1 = new Folder("C:/Documents");
    Node * folder2 = new Folder("C:/Documents/Users");
    Node * file1 = new File("C:/Documents/test1.txt");
    Node * file2 = new File("C:/Documents/Users/test2.txt");
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