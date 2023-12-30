#include <string>
#include "../src/folder.h"

using namespace std;

TEST(Folder, normal) {
    Folder home("structure/home");

    ASSERT_EQ("home", home.name());
    ASSERT_EQ("structure/home", home.path());
}

TEST(Folder, invalid_folder) {
    ASSERT_ANY_THROW(Folder("/NOT/EXIST/PATH"));
}

TEST(Folder, invalid_folder_2) {
    ASSERT_ANY_THROW(Folder("structure/home/Documents/hello.txt"));
}

TEST(Folder, add_file) {
    Folder * home = new Folder("structure/home");
    File * hello = new File("structure/home/hello.txt");
    home->add(hello);

    ASSERT_EQ("hello.txt", home->getChildByName("hello.txt")->name());

    delete home;
}

TEST(Folder, add_incorrect_path_file_to_folder) {
    Folder * home = new Folder("structure/home");
    File * hello = new File("structure/home/Documents/hello.txt");
    ASSERT_ANY_THROW(home->add(hello));
    
    delete home;
    delete hello;
}

TEST(Folder, add_folder) {
    Folder * home = new Folder("structure/home");
    Folder * document = new Folder("structure/home/Documents");

    home->add(document);

    ASSERT_EQ("Documents", home->getChildByName("Documents")->name());

    delete home;
}

TEST(Folder, rename) {
    Folder * home = new Folder("structure/home");
    Folder * document = new Folder("structure/home/Documents");
    Folder * favorites = new Folder("structure/home/Documents/favorites");
    File * hello = new File("structure/home/Documents/hello.txt");
    File * note = new File("structure/home/Documents/note.txt");

    home->add(document);
    document->add(favorites);
    document->add(hello);
    document->add(note);

    home->rename("rename");
    ASSERT_EQ("structure/rename", home->path());
    ASSERT_EQ("structure/rename/Documents", document->path());
    ASSERT_EQ("structure/rename/Documents/favorites", favorites->path());
    ASSERT_EQ("structure/rename/Documents/hello.txt", hello->path());
    ASSERT_EQ("structure/rename/Documents/note.txt", note->path());

    delete home;
}