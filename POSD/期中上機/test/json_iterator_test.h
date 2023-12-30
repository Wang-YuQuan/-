#include "../src/json_object.h"
#include "../src/string_value.h"
#include "../src/json_iterator.h"

TEST(IteratorSuite, JsonObjectIterator) {
    JsonObject * jo1 = new JsonObject;
    Value * v1 = new StringValue("value1");
    Value * v2 = new StringValue("value2");
    jo1->set("key1", v1);
    jo1->set("key2", v2);

    JsonIterator * iterator = jo1->createIterator();
    iterator->first();
    ASSERT_FALSE(iterator->isDone());
    ASSERT_EQ("key1", iterator->currentKey());
    ASSERT_EQ(v1, iterator->currentValue());

    iterator->next();
    ASSERT_FALSE(iterator->isDone());
    ASSERT_EQ("key2", iterator->currentKey());
    ASSERT_EQ(v2, iterator->currentValue());

    iterator->next();
    ASSERT_TRUE(iterator->isDone());

    delete iterator;
    delete jo1;
    // delete v1;
    // delete v2;
}

TEST(IteratorSuite, StringValueIterator) {
    Value * v1 = new StringValue("value1");

    JsonIterator * iterator = v1->createIterator();
    ASSERT_ANY_THROW(iterator->first());
    ASSERT_ANY_THROW(iterator->next());
    ASSERT_ANY_THROW(iterator->currentKey());
    ASSERT_ANY_THROW(iterator->currentValue());
    ASSERT_TRUE(iterator->isDone());

    delete iterator;
    delete v1;
}