#include "../src/json_builder.h"
#include "../src/json_object.h"

TEST(BuilderSuite, builderStructureInner) {
    JsonBuilder * builder = new JsonBuilder();
    builder->buildObject("default");
    builder->buildObject("key1");
    builder->buildValue("key2", "value2");
    builder->endObject();
    builder->buildValue("key3", "value3");
    builder->endObject();

    JsonObject * object = builder->getJsonObject();
    ASSERT_EQ("{\n\"key1\":{\n\"key2\":\"value2\"\n},\n\"key3\":\"value3\"\n}", object->toString());

    delete builder;
    delete object;
}

TEST(BuilderSuite, builderStructureNormal) {
    JsonBuilder * builder = new JsonBuilder();
    builder->buildObject("default");
    builder->buildValue("key1", "value1");
    builder->buildValue("key2", "value2");
    builder->endObject();

    JsonObject * object = builder->getJsonObject();
    ASSERT_EQ("{\n\"key1\":\"value1\",\n\"key2\":\"value2\"\n}", object->toString());

    delete builder;
    delete object;
}