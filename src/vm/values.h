#ifndef ScriptyValues_h
#define ScriptyValues_h

#include <cstring>
#include <cmath>

/**
 * Scripty Value Type
*/
enum class ScriptyValueType {
    INTEGER,
    FLOAT,
    STRING,
};

/**
 * Scripty Value tagged as number
*/
struct ScriptyValue {
    ScriptyValueType type;
    union {
        float number;
        char* text;
    };
};

/**------------------
 * Constructors
*/
inline ScriptyValue INTEGER(int value) {
    ScriptyValue result;
    result.type = ScriptyValueType::INTEGER;
    result.number = std::floor(value);
    return result;
}
inline ScriptyValue FLOAT(float value) {
    ScriptyValue result;
    result.type = ScriptyValueType::FLOAT;
    result.number = value;
    return result;
}

inline ScriptyValue STRING(std::string value) {
    ScriptyValue result;
    result.type = ScriptyValueType::STRING;
    result.text = new char[value.length() + 1];
    strcpy(result.text, value.c_str());
    return result;
}

/**
 * Accessors
*/
#define AS_INT(ScriptyValue) ((int)(ScriptyValue).number) // Number accessor (int)
#define AS_FLOAT(ScriptyValue) ((float)(ScriptyValue).number) // Number accessor (float)
#define AS_STRING(ScriptyValue) ((char[])(ScriptyValue).text) // String accessor


#endif