#ifndef ScriptyValues_h
#define ScriptyValues_h

/**
 * Scripty Value Type
*/
enum class ScriptyValueType {
    NUMBER,
    STRING,
};

/**
 * Scripty Value tagged as number
*/
struct ScriptyValue {
    ScriptyValueType type;
    union {
        double number;
        std::string text;
    };
};

/**------------------
 * Constructors
*/
inline ScriptyValue NUMBER(double value) {
    ScriptyValue result;
    result.type = ScriptyValueType::NUMBER;
    result.number = value;
    return result;
}

inline ScriptyValue STRING(std::string value) {
    ScriptyValue result;
    result.type = ScriptyValueType::STRING;
    result.text = value;
    return result;
}

/**
 * Accessors
*/
#define AS_NUMBER(ScriptyValue) ((double)(ScriptyValue).number) // Number accessor
#define AS_STRING(ScriptyValue) ((std::string)(ScriptyValue).text) // String accessor


#endif