#include <gtest/gtest.h>
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <list>
#include <memory>
#include "../src/unit_of_work.h"
#include "../src/drawing_mapper.h"
#include "../src/painter_mapper.h"
#include "../src/drawing.h"
#include "../src/shape.h"
#include "../src/compound.h"
#include "../src/triangle.h"

class DBSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {
        create_drawing_table();
        create_painter_table();
        populate_drawings();
        populate_painters();
        dm = DrawingMapper::instance();
        pm = PainterMapper::instance();
        dm->setDB("resource/drawing.db");
        pm->setDB("resource/painter.db");
    }

    void TearDown() override
    {
        drop_drawing_table();
        drop_painter_table();
        sqlite3_close(db);
        sqlite3_close(db_p);
        dm->closeDB();
        pm->closeDB();
        dm->destoryInstance();
        pm->destoryInstance();
    }

    void create_drawing_table()
    {
        ASSERT_EQ(0, sqlite3_open("resource/drawing.db", &db));
        const char *stmt = "CREATE TABLE drawing ("
                           "ID         char(6) PRIMARY KEY     not null,"
                           "painter    varchar(50)             not null,"
                           "shapes varchar(1028),"
                           "FOREIGN KEY(painter) REFERENCES painter(ID))";
        int rc = sqlite3_exec(db, stmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void drop_drawing_table()
    {
        const char *dropStmt = "DROP TABLE drawing";
        int rc = sqlite3_exec(db, dropStmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void create_painter_table()
    {
        ASSERT_EQ(0, sqlite3_open("resource/painter.db", &db_p));
        const char *stmt = "CREATE TABLE painter ("
                           "ID         char(6) PRIMARY KEY     not null,"
                           "name    varchar(50)             not null)";
        int rc = sqlite3_exec(db_p, stmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void drop_painter_table()
    {
        const char *dropStmt = "DROP TABLE painter";
        int rc = sqlite3_exec(db_p, dropStmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void populate_drawings()
    {
        const char *s1 = "INSERT INTO drawing"
                         "(ID, painter, shapes)"
                         "values"
                         "('d_0001', 'p_0001', 'triangle 1 1 1')";
        int rc = sqlite3_exec(db, s1, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);

        const char *s2 = "INSERT INTO drawing"
                         "(ID,  painter,   shapes)"
                         "values"
                         "('d_0002', 'p_0001', 'triangle 2 2 2')";
        rc = sqlite3_exec(db, s2, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);

        const char *s3 = "INSERT INTO drawing"
                         "(ID,  painter,   shapes)"
                         "values"
                         "('d_0003', 'p_0002', 'compound { triangle 1 1 1 triangle 2 2 2 } triangle 3 3 3')";
        rc = sqlite3_exec(db, s3, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);
    }

    void populate_painters()
    {
        const char *s1 = "INSERT INTO painter"
                         "(ID, name)"
                         "values"
                         "('p_0001', 'Patrick')";
        int rc = sqlite3_exec(db_p, s1, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);

        const char *s2 = "INSERT INTO painter"
                         "(ID, name)"
                         "values"
                         "('p_0002', 'Mary')";
        rc = sqlite3_exec(db_p, s2, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);
    }

    void display_err_msg_and_fail_if_any(int rc)
    {
        if (rc)
        {
            std::cout << "db error: " << err_msg << std::endl;
        }
        sqlite3_free(err_msg);
        ASSERT_EQ(SQLITE_OK, rc);
    }

    sqlite3 * db;
    sqlite3 * db_p;
    char * err_msg = nullptr;
    DrawingMapper * dm;
    PainterMapper * pm;
};

TEST_F(DBSuite, Sanity) {

}

TEST_F(DBSuite, findOperation)
{
    UnitOfWork * uow = UnitOfWork::instance();
    Drawing * drawing = dm->find("d_0001");
    
    ASSERT_TRUE(uow->inClean("d_0001"));
    ASSERT_FALSE(uow->inDirty("d_0001"));
    ASSERT_TRUE(uow->inClean("p_0001"));
    ASSERT_FALSE(uow->inDirty("p_0001"));
    ASSERT_EQ(drawing->id(), "d_0001");
    ASSERT_EQ(drawing->getShape(0)->perimeter(), 3);
    ASSERT_EQ(drawing->painter()->id(), "p_0001");
    ASSERT_EQ(drawing->painter()->name(), "Patrick");
    
    uow->destoryInstance();
}

TEST_F(DBSuite, CreateOperation) {
    Painter * painter = new Painter("p_0003", "Tommy");
    UnitOfWork::instance()->registerNew(painter);
    ASSERT_FALSE(UnitOfWork::instance()->inClean("p_0003"));
    ASSERT_TRUE(UnitOfWork::instance()->inNew("p_0003"));
    UnitOfWork::instance()->commit();
    ASSERT_TRUE(UnitOfWork::instance()->inClean("p_0003"));
    ASSERT_FALSE(UnitOfWork::instance()->inNew("p_0003"));
    ASSERT_EQ("p_0003", pm->instance()->find("p_0003")->id());
    ASSERT_EQ("Tommy", pm->instance()->find("p_0003")->name());

    std::list<Shape *> shapes;
    shapes.push_back(new Triangle(1, 1, 1));
    shapes.push_back(new Triangle(2, 2, 2));
    shapes.push_back(new Triangle(3, 3, 3));
    Drawing * drawing = new Drawing("d_0004", painter, shapes);
    UnitOfWork::instance()->registerNew(drawing);
    ASSERT_FALSE(UnitOfWork::instance()->inClean("d_0004"));
    ASSERT_TRUE(UnitOfWork::instance()->inNew("d_0004"));
    UnitOfWork::instance()->commit();
    ASSERT_TRUE(UnitOfWork::instance()->inClean("d_0004"));
    ASSERT_FALSE(UnitOfWork::instance()->inNew("d_0004"));
    dm->cleanCache();
    pm->cleanCache();
    ASSERT_EQ("d_0004", dm->instance()->find("d_0004")->id());
    ASSERT_EQ(3, dm->instance()->find("d_0004")->getShape(0)->perimeter());
    ASSERT_EQ(6, dm->instance()->find("d_0004")->getShape(1)->perimeter());
    ASSERT_EQ(9, dm->instance()->find("d_0004")->getShape(2)->perimeter());

    UnitOfWork::instance()->destoryInstance();
}

TEST_F(DBSuite, UpdateOperation) {
    Painter * painter = pm->find("p_0001");
    UnitOfWork * uow = UnitOfWork::instance();
    ASSERT_EQ("p_0001", painter->id());
    ASSERT_EQ("Patrick", painter->name());
    painter->setName("Tony");
    ASSERT_FALSE(UnitOfWork::instance()->inClean("p_0001"));
    ASSERT_TRUE(UnitOfWork::instance()->inDirty("p_0001"));
    uow->commit();
    ASSERT_TRUE(UnitOfWork::instance()->inClean("p_0001"));
    ASSERT_FALSE(UnitOfWork::instance()->inDirty("p_0001"));
    pm->cleanCache();
    painter = pm->find("p_0001");
    ASSERT_EQ("p_0001", painter->id());
    ASSERT_EQ("Tony", painter->name());

    Drawing * drawing = dm->find("d_0003");
    ASSERT_EQ("d_0003", drawing->id());
    ASSERT_EQ("p_0002", drawing->painter()->id());
    ASSERT_EQ("Mary", drawing->painter()->name());
    drawing->setPainter(painter);
    ASSERT_FALSE(UnitOfWork::instance()->inClean("d_0003"));
    ASSERT_TRUE(UnitOfWork::instance()->inDirty("d_0003"));
    uow->commit();
    ASSERT_TRUE(UnitOfWork::instance()->inClean("d_0003"));
    ASSERT_FALSE(UnitOfWork::instance()->inDirty("d_0003"));
    dm->cleanCache();
    drawing = dm->find("d_0003");
    ASSERT_EQ("d_0003", drawing->id());
    ASSERT_EQ("p_0001", drawing->painter()->id());
    ASSERT_EQ("Tony", drawing->painter()->name());

    uow->destoryInstance();
}

TEST_F(DBSuite, DeleteOperation) {
    Painter * painter = pm->find("p_0001");
    UnitOfWork * uow = UnitOfWork::instance();
    uow->registerDeleted(painter);
    ASSERT_FALSE(UnitOfWork::instance()->inClean("p_0001"));
    ASSERT_TRUE(UnitOfWork::instance()->inDeleted("p_0001"));
    uow->commit();
    ASSERT_FALSE(UnitOfWork::instance()->inClean("p_0001"));
    ASSERT_FALSE(UnitOfWork::instance()->inDeleted("p_0001"));
    pm->cleanCache();
    painter = pm->find("p_0001");
    ASSERT_EQ(nullptr, painter);

    Drawing * drawing = dm->find("d_0001");
    uow->registerDeleted(drawing);
    ASSERT_FALSE(UnitOfWork::instance()->inClean("d_0001"));
    ASSERT_TRUE(UnitOfWork::instance()->inDeleted("d_0001"));
    uow->commit();
    ASSERT_FALSE(UnitOfWork::instance()->inClean("d_0001"));
    ASSERT_FALSE(UnitOfWork::instance()->inDeleted("d_0001"));
    dm->cleanCache();
    drawing = dm->find("d_0001");
    ASSERT_EQ(nullptr, drawing);

    Painter * newPainter = new Painter("p_0005", "Amy");
    uow->registerNew(newPainter);
    uow->registerDeleted(newPainter);
    ASSERT_FALSE(UnitOfWork::instance()->inNew("p_0005"));
    ASSERT_TRUE(UnitOfWork::instance()->inDeleted("p_0005"));
    
    delete newPainter;
    uow->destoryInstance();
}