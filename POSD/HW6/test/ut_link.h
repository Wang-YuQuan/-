#include <string>
#include "../src/folder.h"
#include "../src/link.h"

using namespace std;

TEST(Link, add_file) {
    Folder * home = new Folder("structure/home");
    File * hello = new File("structure/home/hello.txt");
    Link * link = new Link("structure/home", home);
    link->add(hello);

    ASSERT_EQ("hello.txt", link->getChildByName("hello.txt")->name());

    delete home;
    delete link;
}

TEST(Link, add_incorrect_path_file_to_folder) {
    Folder * home = new Folder("structure/home");
    File * hello = new File("structure/home/Documents/hello.txt");
    Link * link = new Link("structure/home", home);
    ASSERT_ANY_THROW(link->add(hello));
    
    delete home;
    delete hello;
    delete link;
}

TEST(Link, add_folder) {
    Folder * home = new Folder("structure/home");
    Folder * document = new Folder("structure/home/Documents");
    Link * link = new Link("structure/home", home);

    link->add(document);

    ASSERT_EQ("Documents", link->getChildByName("Documents")->name());

    delete home;
    delete link;
}

TEST(Link, rename) {
    Folder * home = new Folder("structure/home");
    Folder * document = new Folder("structure/home/Documents");
    Folder * favorites = new Folder("structure/home/Documents/favorites");
    File * hello = new File("structure/home/Documents/hello.txt");
    File * note = new File("structure/home/Documents/note.txt");

    Link * link = new Link("structure/home", home);
    link->add(document);
    Folder * linkToDocument = dynamic_cast<Folder *>(link->getChildByName("Documents"));
    linkToDocument->add(favorites);
    linkToDocument->add(hello);
    linkToDocument->add(note);

    home->rename("rename");
    ASSERT_EQ("structure/rename", home->path());
    ASSERT_EQ("structure/rename/Documents", document->path());
    ASSERT_EQ("structure/rename/Documents/favorites", favorites->path());
    ASSERT_EQ("structure/rename/Documents/hello.txt", hello->path());
    ASSERT_EQ("structure/rename/Documents/note.txt", note->path());

    delete home;
    delete link;
}