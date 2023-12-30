#include <gtest/gtest.h>
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <list>
#include "../src/unit_of_work.h"
#include "../src/drawing_mapper.h"
#include "../src/inmemory_drawing_mapper.h"
#include "../src/painter_mapper.h"
#include "../src/inmemory_painter_mapper.h"
#include "../src/drawing.h"
#include "../src/triangle.h"
#include "../src/shape.h"
#include "../src/painter.h"
#include <memory>
#include <stdlib.h>
#include "../src/db_mode.h"

class InMemoryDBSuite : public ::testing::Test {
protected:
    void SetUp() override {
        DbMode::instance()->setMode(InMemory);

        prepare_data();
        dm = DrawingMapper::instance();
        dm->cleanCache();
        pm = PainterMapper::instance();
        pm->cleanCache();
    }

    void TearDown() override {
    }

    void prepare_data() {
        Painter * p0001 = new Painter("p_0001", "Patrick");
        PainterMapper::instance()->add(p0001);

        Painter * p0002 = new Painter("p_0002", "Mary");
        PainterMapper::instance()->add(p0002);

        std::list<Shape *> shape1;
        shape1.push_back(new Triangle(1, 1, 1));
        Drawing * d0001 = new Drawing("d_0001", p0001, shape1);
        DrawingMapper::instance()->add(d0001);

        std::list<Shape *> shape2;
        shape2.push_back(new Triangle(2, 2, 2));
        Drawing * d0002 = new Drawing("d_0002", p0001, shape2);
        DrawingMapper::instance()->add(d0002);

        std::list<Shape *> shape3;

        std::vector<Shape*> elements;
        elements.push_back(new Triangle(1, 1, 1));
        elements.push_back(new Triangle(2, 2, 2));
        elements.push_back(new Triangle(3, 3, 3));
        shape3.push_back(new Compound(elements));
        Drawing * d0003 = new Drawing("d_0003", p0002, shape3);
        DrawingMapper::instance()->add(d0003);
    }

    DrawingMapper * dm;
    PainterMapper * pm;
};

// ensure db setup teardown works alone
TEST_F(InMemoryDBSuite, Sanity) {
}

// new
TEST_F(InMemoryDBSuite, NewDrawingAndPainterThroughUoWAndFind) {
    UnitOfWork *uow = UnitOfWork::instance();
    Painter *painter = new Painter("p_0004", "Richard");
    uow->registerNew(painter);
    EXPECT_TRUE(uow->inNew(painter->id()));
    std::list<Shape *> shapes;
    shapes.push_back(new Triangle(2, 2, 3));
    shapes.push_back(new Triangle(4, 4, 4));
    shapes.push_back(new Triangle(9, 7, 5));
    Drawing *drawing = new Drawing("d_0005", painter, shapes);
    uow->registerNew(drawing);
    EXPECT_TRUE(uow->inNew(drawing->id()));

    uow->commit();

    dm->cleanCache();
    pm->cleanCache();
    Drawing * d = dm->find("d_0005");
    EXPECT_TRUE(uow->inClean(d->id()));
    ASSERT_EQ("p_0004", d->painter()->id());
    ASSERT_EQ("Richard", d->painter()->name());
    ASSERT_EQ("d_0005", d->id());
    ASSERT_EQ(7, d->getShape(0)->perimeter());
    ASSERT_EQ(12, d->getShape(1)->perimeter());
    ASSERT_EQ(21, d->getShape(2)->perimeter());
    delete drawing;
}

TEST_F(InMemoryDBSuite, CommitNewDrawingsWithOldPainter) {
    UnitOfWork *uow = UnitOfWork::instance();

    Painter *painter = PainterMapper::instance()->find("p_0001");
    std::list<Shape *> shapes;
    shapes.push_back(new Triangle(2, 2, 2));
    Drawing *drawing = new Drawing("d_0010", painter, shapes);
    uow->registerNew(drawing);

    ASSERT_TRUE(uow->inNew("d_0010"));

    uow->commit();

    ASSERT_FALSE(uow->inNew("d_0010"));
    ASSERT_TRUE(uow->inClean("p_0001"));
    ASSERT_TRUE(uow->inClean("d_0010"));
    // delete drawing;
}

// find
TEST_F(InMemoryDBSuite, findDrawing) {
    Drawing * drawing = dm->find("d_0001");

    EXPECT_TRUE(UnitOfWork::instance()->inClean("d_0001"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("d_0001"));
    EXPECT_TRUE(UnitOfWork::instance()->inClean("p_0001"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("p_0001"));
    ASSERT_EQ(drawing->id(), "d_0001");
    ASSERT_EQ(drawing->getShape(0)->perimeter(), 3);
    ASSERT_EQ(drawing->painter()->id(), "p_0001");
    ASSERT_EQ(drawing->painter()->name(), "Patrick");
}

// can't test db, find will find in Mapper
TEST_F(InMemoryDBSuite, findDrawingAndUpdate) {
    Drawing *drawing = dm->find("d_0001");
    Painter *painter = pm->find("p_0002");

    drawing->setPainter(painter);
    EXPECT_FALSE(UnitOfWork::instance()->inClean("d_0001"));
    EXPECT_TRUE(UnitOfWork::instance()->inDirty("d_0001"));
    UnitOfWork::instance()->commit();
    EXPECT_TRUE(UnitOfWork::instance()->inClean("d_0001"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("d_0001"));

    dm->cleanCache();
    Drawing *d = dm->find("d_0001");
    EXPECT_TRUE(UnitOfWork::instance()->inClean("d_0001"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("d_0001"));
    ASSERT_EQ("Mary", d->painter()->name());
}

TEST_F(InMemoryDBSuite, findPainterAndUpdate) {
    Painter *painter = pm->find("p_0002");

    painter->setName("Mary2");
    EXPECT_FALSE(UnitOfWork::instance()->inClean("p_0002"));
    EXPECT_TRUE(UnitOfWork::instance()->inDirty("p_0002"));
    UnitOfWork::instance()->commit();
    EXPECT_TRUE(UnitOfWork::instance()->inClean("p_0002"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("p_0002"));
    pm->cleanCache();

    Painter *p = pm->find("p_0002");
    EXPECT_TRUE(UnitOfWork::instance()->inClean("p_0002"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("p_0002"));
    ASSERT_EQ("Mary2", p->name());
}

TEST_F(InMemoryDBSuite, DeletePainterInNewWithoutCommit) {

    UnitOfWork *uow = UnitOfWork::instance();

    Painter *p = new Painter("p_0105", "Roy");
    uow->registerNew(p);
    ASSERT_TRUE(UnitOfWork::instance()->inNew(p->id()));
    ASSERT_FALSE(UnitOfWork::instance()->inDirty(p->id()));
    ASSERT_FALSE(UnitOfWork::instance()->inClean(p->id()));

    uow->registerDeleted(p);
    ASSERT_FALSE(UnitOfWork::instance()->inNew(p->id()));
    ASSERT_FALSE(UnitOfWork::instance()->inDirty(p->id()));
    ASSERT_FALSE(UnitOfWork::instance()->inClean(p->id()));
}

TEST_F(InMemoryDBSuite, DeletePainterInClean) {
    Painter *painter = pm->find("p_0002");

    EXPECT_FALSE(UnitOfWork::instance()->inDirty(painter->id()));
    EXPECT_TRUE(UnitOfWork::instance()->inClean(painter->id()));

    UnitOfWork::instance()->registerDeleted(painter);

    EXPECT_TRUE(UnitOfWork::instance()->inDeleted(painter->id()));
    EXPECT_FALSE(UnitOfWork::instance()->inClean(painter->id()));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty(painter->id()));
    EXPECT_FALSE(UnitOfWork::instance()->inNew(painter->id()));
    UnitOfWork::instance()->commit();

    Painter *p = pm->find("p_0002");
    ASSERT_EQ(nullptr, p);
}