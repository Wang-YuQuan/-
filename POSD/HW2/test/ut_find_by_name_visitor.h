#include <string>
#include "../src/node.h"
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/find_by_name_visitor.h"

TEST(TestFindByNameVisitorSuites, GetPaths) {
    Node * folder1 = new Folder("test_material");
    Node * folder2 = new Folder("test_material/folder1");
    Node * folder3 = new Folder("test_material/folder2");
    Node * folder4 = new Folder("test_material/folder2/folder3");
    Node * file1 = new File("test_material/folder1/test1.txt");
    Node * file2 = new File("test_material/folder2/test2.txt");
    Node * file3 = new File("test_material/folder2/folder3/test3.txt");
    Node * file4 = new File("test_material/folder2/folder3/test1.txt");
    folder1->add(folder2);
    folder1->add(folder3);
    folder2->add(file1);
    folder3->add(folder4);
    folder3->add(file2);
    folder4->add(file3);
    folder4->add(file4);

    FindByNameVisitor * visitor = new FindByNameVisitor("test1.txt");
    folder1->accept(visitor);
    ASSERT_EQ(2, visitor->getPaths().size());

    delete folder1;
    delete folder2;
    delete folder3;
    delete folder4;
    delete file1;
    delete file2;
    delete file3;
    delete file4;
}