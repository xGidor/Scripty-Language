#ifndef ScriptyValues_h
#define ScriptyValues_h

/**
 * Scripty Value Type
*/
enum class ScriptyValueType {
    NUMBER,
};

/**
 * Scripty Value tagged as number
*/
struct ScriptyValue {
    ScriptyValueType type;
    union {
        double number;
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

/**
 * Accessors
*/
#define AS_NUMBER(ScriptyValue) ((double)(ScriptyValue).number)

#endif