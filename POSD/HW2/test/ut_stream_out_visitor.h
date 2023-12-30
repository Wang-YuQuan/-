#include <string>
#include "../src/node.h"
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/stream_out_visitor.h"

TEST(TestStreamOutVisitorSuites, GetResultFolder) {
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

    StreamOutVisitor * visitor = new StreamOutVisitor();
    folder1->accept(visitor);
    std::string out = "_____________________________________________\ntest_material/folder1/test1.txt\n---------------------------------------------\nfile1 content\nsecond line\nlast line\n_____________________________________________\n\n_____________________________________________\ntest_material/folder2/folder3/test3.txt\n---------------------------------------------\nfile3 content\nsecond line\nlast line\n_____________________________________________\n\n_____________________________________________\ntest_material/folder2/test2.txt\n---------------------------------------------\nfile2 content\nsecond line\nlast line\n_____________________________________________\n\n";
    ASSERT_EQ(out, visitor->getResult());

    delete folder1;
    delete folder2;
    delete folder3;
    delete folder4;
    delete file1;
    delete file2;
    delete file3;
}

TEST(TestStreamOutVisitorSuites, GetResultFile) {
    Node * file1 = new File("test_material/folder1/test1.txt");
    StreamOutVisitor * visitor = new StreamOutVisitor();
    file1->accept(visitor);
    std::string out = "_____________________________________________\ntest_material/folder1/test1.txt\n---------------------------------------------\nfile1 content\nsecond line\nlast line\n_____________________________________________\n";
    ASSERT_EQ(out, visitor->getResult());
}