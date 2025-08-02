#include "json.h"

int main()
{
    // Example 1: complex JSON with comments
    std::string_view ComplexJsonSource = R"({
        // This is a test JSON file.
        "name": "John Doe",
        "age": 30,
        "isStudent": false,
        "courses": [
            /* Block comment for courses */
            {"title": "History", "credits": 3},
            {"title": "Math", "credits": 4}
        ],
        "address": null
    })";

    std::cout << "--- Parsing valid JSON with comments ---" << '\n';
    try {
        json::JsonValue data = json::parse(ComplexJsonSource);
        std::cout << "Parse successful. Serialized output:\n" << data << '\n';

        // Accessing data
        std::cout << "\n--- Accessing data ---" << '\n';
        std::cout << "Name: " << data.asObject().at("name").asString() << '\n';
        double age = data.asObject().at("age").asNumber();
        std::cout << "Age: " << age << '\n';
        std::cout << "First course title: "
                  << data.asObject()
                       .at("courses")
                       .asArray()[0]
                       .asObject()
                       .at("title")
                       .asString()
                  << '\n';

    } catch (const json::ParsingError& e) {
        std::cerr << "Parsing failed: " << e.what() << '\n';
    }

    std::cout << "\n\n--- Parsing invalid JSON to test error reporting ---"
              << '\n';

    // Example 2: Missing comma le gasp
    std::string_view invalidJsonSource = R"({
        "key1": "value1"
        "key2": "value2"
    })";

    try {
        json::JsonValue data = json::parse(invalidJsonSource);
    } catch (const json::ParsingError& e) {
        std::cerr << "Caught expected error: " << e.what() << '\n';
    }

    // Example 3: Unterminated string
    std::string_view unterminatedStringSource =
      R"({ "key": "value is not closed })";
    try {
        json::JsonValue data = json::parse(unterminatedStringSource);
    } catch (const json::ParsingError& e) {
        std::cerr << "Caught expected error: " << e.what() << '\n';
    }

    // Example 4: EXTRA COMMA AT THE END GASP???
    std::string_view extraCommaJsonSource =
      R"({ "key": "value that makes it seem like there is another value", })";
    try {
        json::JsonValue data = json::parse(extraCommaJsonSource);
    } catch (const json::ParsingError& e) {
        std::cerr << "Caught expected error: " << e.what() << '\n';
    }

    return 0;
}
