#include "../src/json_builder.h"
#include "../src/json_object.h"
#include "../src/beautify_visitor.h"

TEST(VistorSuite, VistorNormal) {
    JsonObject * jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    BeautifyVisitor * visitor = new BeautifyVisitor();
    jo->accept(visitor);

    std::string expected = "{\n"
                           "    \"key1\": \"value1\"\n"
                           "}";
    ASSERT_EQ(expected, visitor->getResult());

    delete visitor;
    delete jo;
    // delete v1;
}

TEST(VistorSuite, VistorTwoNormal) {
    JsonObject * jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    Value * v2 = new StringValue("value2");
    jo->set("key1", v1);
    jo->set("key2", v2);
    BeautifyVisitor * visitor = new BeautifyVisitor();
    jo->accept(visitor);

    std::string expected = "{\n"
                           "    \"key1\": \"value1\",\n"
                           "    \"key2\": \"value2\"\n"
                           "}";
    ASSERT_EQ(expected, visitor->getResult());

    delete visitor;
    delete jo;
    // delete v1;
    // delete v2;
}

TEST(VistorSuite, VistorComplex) {
    JsonObject * jo1 = new JsonObject();
    JsonObject * jo2 = new JsonObject();
    JsonObject * jo3 = new JsonObject();
    JsonObject * jo4 = new JsonObject();
    Value * v1 = new StringValue("Robert C. Martin");
    Value * v2 = new StringValue("Clean Code");
    Value * v3 = new StringValue("Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides");
    Value * v4 = new StringValue("Design Patterns: Elements of Reusable Object-Oriented Software");
    jo1->set("author", v1);
    jo1->set("name", v2);
    jo2->set("author", v3);
    jo2->set("name", v4);
    jo3->set("clean code", jo1);
    jo3->set("design patterns", jo2);
    jo4->set("books", jo3);
    BeautifyVisitor * visitor = new BeautifyVisitor();
    jo4->accept(visitor);

    std::string expected = "{\n"
                           "    \"books\": {\n"
                           "        \"clean code\": {\n"
                           "            \"author\": \"Robert C. Martin\",\n"
                           "            \"name\": \"Clean Code\"\n"
                           "        },\n"
                           "        \"design patterns\": {\n"
                           "            \"author\": \"Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides\",\n"
                           "            \"name\": \"Design Patterns: Elements of Reusable Object-Oriented Software\"\n"
                           "        }\n"
                           "    }\n"
                           "}";
    ASSERT_EQ(expected, visitor->getResult());

    delete visitor;
    // delete jo1;
    // delete jo2;
    // delete jo3;
    delete jo4;
    // delete v1;
    // delete v2;
    // delete v3;
    // delete v4;
}