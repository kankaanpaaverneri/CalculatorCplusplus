#include "Value.h"

Value::Value()
    : Value(0, '0') {
}

Value::Value(const double value, const char ch)
    : value{value}, ch{ch} {
}

Value::~Value() {

}

void Value::display() const {
    std::cout << get_value() << " " << get_ch() << " ";
}

//OPERATOR OVERLOAD IMPLEMENTATION
Value &Value::operator=(const Value &rhs) {
    if(this == &rhs)
        return *this;
    else {
        this->value = rhs.value;
        this->ch = rhs.ch;
        return *this;
    }
}

Value &Value::operator+(const Value &rhs) {
    this->value = this->value + rhs.value;
    return *this;
}

Value &Value::operator-(const Value &rhs) {
    this->value = this->value - rhs.value;
    return *this;
}

Value &Value::operator*(const Value &rhs) {
    this->value = this->value * rhs.value;
    return *this;
}

Value &Value::operator/(const Value &rhs) {
    this->value = this->value / rhs.value;
    return *this;
}