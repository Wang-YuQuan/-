#include "../src/json_object.h"
#include "../src/string_value.h"

TEST(JSonSuite, UnknownKey) {
    JsonObject * jo = new JsonObject;
    ASSERT_ANY_THROW(jo->getValue("key"));

    delete jo;
}

TEST(JSonSuite, OneKeyStringValue) {
    JsonObject * jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    ASSERT_EQ(v1, jo->getValue("key1"));
    ASSERT_EQ("{\n\"key1\":\"value1\"\n}", jo->toString());

    delete jo;
    // delete v1;
}

TEST(JSonSuite, TwoKeyStringValue) {
    JsonObject * jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value * v2 = new StringValue("value2");
    jo->set("key2", v2);
    ASSERT_EQ("\"value1\"", jo->getValue("key1")->toString());
    ASSERT_EQ("\"value2\"", jo->getValue("key2")->toString());
    ASSERT_EQ("{\n\"key1\":\"value1\",\n\"key2\":\"value2\"\n}", jo->toString());

    delete jo;
    // delete v1;
    // delete v2;
}

TEST(JSonSuite, Composite) {
    JsonObject * jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value * v2 = new StringValue("value2");
    jo->set("key2", v2);

    JsonObject *j_composite = new JsonObject;
    j_composite->set("keyc", jo);
    ASSERT_EQ(jo, j_composite->getValue("keyc"));
    ASSERT_EQ("{\n\"keyc\":{\n\"key1\":\"value1\",\n\"key2\":\"value2\"\n}\n}", j_composite->toString());

    delete j_composite;
    // delete jo;
    // delete v1;
    // delete v2;
}

TEST(JSonSuite, ComplexCompositeTest) {
    JsonObject * jo1 = new JsonObject;
    JsonObject * jo2 = new JsonObject();
    JsonObject * jo3 = new JsonObject();
    Value * v1 = new StringValue("value1");
    Value * v2 = new StringValue("value2");
    Value * v3 = new StringValue("value3");
    Value * v4 = new StringValue("value4");
    Value * v5 = new StringValue("value5");
    jo1->set("key1", v1);
    jo1->set("key2", v2);
    jo1->set("key3", jo2);
    jo2->set("key4", v3);
    jo2->set("key5", jo3);
    jo3->set("key6", v4);
    jo3->set("key7", v5);
    ASSERT_EQ(v1, jo1->getValue("key1"));
    ASSERT_EQ(v2, jo1->getValue("key2"));
    ASSERT_EQ(jo2, jo1->getValue("key3"));
    string expected = "{\n"
                      "\"key1\":\"value1\",\n"
                      "\"key2\":\"value2\",\n"
                      "\"key3\":{\n"
                      "\"key4\":\"value3\",\n"
                      "\"key5\":{\n"
                      "\"key6\":\"value4\",\n"
                      "\"key7\":\"value5\"\n"
                      "}\n"
                      "}\n"
                      "}";
    ASSERT_EQ(expected, jo1->toString());

    delete jo1;
    // delete jo2;
    // delete jo3;
    // delete v1;
    // delete v2;
    // delete v3;
    // delete v4;
    // delete v5;
}