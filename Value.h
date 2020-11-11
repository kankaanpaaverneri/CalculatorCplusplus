#ifndef _VALUE_H_
#define _VALUE_H_
#include <iostream>
class Value {
    private:
        //ATTRIBUTES
        double value;
        char ch;
    public:
        //CONSTRUCTORS AND DESTRUCTORS
        Value();
        Value(const double value, const char ch);
        ~Value();

        //GETTERS AND SETTERS
        void set_value(const double value) {this->value = value;}
        const double get_value() const {return value;}
        void set_ch(const char ch) {this->ch = ch;}
        const char get_ch() const {return ch;}
        void display() const;

        //OPERATOR OVERLOADS
        Value &operator=(const Value &rhs);
        Value &operator+(const Value &rhs);
        Value &operator-(const Value &rhs);
        Value &operator*(const Value &rhs);
        Value &operator/(const Value &rhs);
};
#endif