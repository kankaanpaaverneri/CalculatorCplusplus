#ifndef _VALUE_LIST_H_
#define _VALUE_LIST_H_
#include <vector>
#include <cmath>

#include "Value.h"

class Value_List {
    private:
        std::vector<Value> *list;
    public:
        Value_List();
        Value_List(const Value_List &source);
        ~Value_List();
        bool add_to_the_list(Value element);
        void display_list() const;
        void display_size() const;
        void remove_next(unsigned int position);
        Value do_the_math();
        Value count_pow(Value cur, Value next);
        void fill_empty_with_results(std::vector<Value> results);
};
#endif