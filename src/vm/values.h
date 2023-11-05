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
    }
};

/**------------------
 * Constructors
*/
#define NUMBER(value) (ScriptyValue){ScriptyValueType::NUMBER, .number = value}

#endif