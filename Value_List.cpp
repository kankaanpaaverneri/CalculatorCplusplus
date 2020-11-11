#include "Value_List.h"
#include "Exceptions.h"

Value_List::Value_List()
    : list{nullptr} {
        list = new std::vector<Value>();
}

Value_List::Value_List(const Value_List &source)
    : list {nullptr} {
        list = new std::vector<Value>();
        *list = *source.list;
}

Value_List::~Value_List() {
    delete list;
}

bool Value_List::add_to_the_list(Value element) {
    list->push_back(element);
    return true;
}

void Value_List::display_list() const {
    for(Value &i: *list)
        i.display();
    std::cout << std::endl;
}

void Value_List::display_size() const {
    std::cout << list->size() << std::endl;
}

void Value_List::remove_next(unsigned int position) {
    for(unsigned int i {position}; i < list->size()-1; i++) {
        list->at(i) = list->at(i+1);
    }
    list->pop_back();
}

Value Value_List::do_the_math() {
    if(list->size() == 0)
        throw Do_The_Math_Ex();
    Value result = list->at(0);
    //FINDS CHAR THAT VALUE IS ^ AND CALCULATES THE RESULT
    for(unsigned int i {0}; i < list->size();) {
        result = list->at(i);
        Value next = list->at(i+1);
        if(result.get_ch() == '^') {
            result = count_pow(result, next);
            remove_next(i);
            list->at(i) = result;
        } else
            i++;
        if(i == list->size()-1)
            break;
    }
    if(list->size() != 1) {
        //FINDS CHAR THAT VALUE IS * OR / AND CALCULATES THE RESULT
        for(unsigned int i {0}; i < list->size();) {
            result = list->at(i);
            Value next = list->at(i+1);
            if(result.get_ch() == '*') {
                result = result * next;
                result.set_ch(next.get_ch());
                remove_next(i);
                list->at(i) = result;
            } else if(result.get_ch() == '/') {
                result = result / next;
                result.set_ch(next.get_ch());
                remove_next(i);
                list->at(i) = result;
            } else
                i++;
            if(i == list->size()-1)
                break;
        }
    }
    if(list->size() != 1) {
        //FINDS CHAR THAT VALUE IS + OR - AND CALCULATES THE RESULT
        for(unsigned int i {0}; i < list->size();) {
            result = list->at(i);
            Value next = list->at(i+1);
            if(result.get_ch() == '+') {
            result = result + next;
            result.set_ch(next.get_ch());
            remove_next(i);
            list->at(i) = result;
        } else if(result.get_ch() == '-') {
            result = result - next;
            result.set_ch(next.get_ch());
            remove_next(i);
            list->at(i) = result;
        } else
            i++;
        if(i == list->size()-1)
            break;
        }
    }

    return result;
}

Value Value_List::count_pow(Value cur, Value next) {
    Value element;
    double result = pow(cur.get_value(), next.get_value());
    element.set_value(result);
    element.set_ch(next.get_ch());
    return element;
}

void Value_List::fill_empty_with_results(std::vector<Value> results) {
    unsigned int j {0};
    for(unsigned int i {0}; i < list->size(); i++) {
        Value temp = list->at(i);
        if(temp.get_value() == 0 && temp.get_ch() == '?') {
            temp = results.at(j);
            list->at(i) = temp;
            j++;
        }
    }
}