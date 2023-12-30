#include "../src/json_builder.h"
#include "../src/json_scanner.h"
#include "../src/json_parser.h"
#include "../src/json_object.h"
#include "../src/beautify_visitor.h"

TEST(ParserSuite, Parse) {
    std::string json_string = "{\"books\":{\"clean code\":{\"author\": \"Robert C. Martin\",\"name\":\"Clean Code\"},\"design patterns\":{\"author\":\"Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides\",\"name\":\"Design Patterns: Elements of Reusable Object-Oriented Software\"}}}";
    JsonBuilder * builder = new JsonBuilder();
    JsonScanner * scanner = new JsonScanner();
    scanner->setInput(json_string);
    JsonParser * parser = new JsonParser(scanner, builder);
    parser->parse();
    JsonObject * jo = parser->getJsonObject();
    BeautifyVisitor * visitor = new BeautifyVisitor();
    jo->accept(visitor);
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
    delete builder;
    delete scanner;
    delete parser;
    delete jo;
}