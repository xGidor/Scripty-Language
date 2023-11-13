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
    LIST,
    NONETYPE
};

/**
 * Scripty Value
*/
struct ScriptyValue {
    ScriptyValueType type;
    union {
        float number;
        char* text;
    };
};


/* Value Type Constructors */
/* Null/NoneType Value Type*/
inline ScriptyValue NONE_()
{
    ScriptyValue result;
    result.type = ScriptyValueType::NONETYPE;
    return result;
}

/* Integer Value Type*/
inline ScriptyValue INTEGER_(int value) {
    ScriptyValue result;
    result.type = ScriptyValueType::INTEGER;
    result.number = std::floor(value);
    return result;
}

/* Float Value Type*/
inline ScriptyValue FLOAT_(float value) {
    ScriptyValue result;
    result.type = ScriptyValueType::FLOAT;
    result.number = value;
    return result;
}

/* String Value Type*/
inline ScriptyValue STRING_(std::string value) {
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
#define AS_STRING(ScriptyValue) ((char*)(ScriptyValue).text) // String accessor


#endif