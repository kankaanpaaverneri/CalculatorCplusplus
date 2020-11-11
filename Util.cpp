#include "Util.h"
#include "Exceptions.h"

void valikko() {
    std::cout << "=== CALCULATOR ===" << std::endl;
    std::cout << std::endl;
    std::cout << ": ";
}

void heap_error(const char *buffer) {
    if(buffer == nullptr) {
        std::cout << "HEAP OUT OF MEMORY" << std::endl;
        exit(1);
    }
}

char *check_the_buffer_for_brackets(const char *buffer, unsigned int &cur_location) {
    char *sub_buffer = new char[std::strlen(buffer)+1]; // IF SUCCESSFUL, THIS IS FREE´D OUTSIDE OF THIS FUNCTION
    heap_error(sub_buffer);

    for(unsigned int i {cur_location}; i < std::strlen(buffer); i++) {
        if(buffer[i] == '(') {
            exception_handling(buffer, sub_buffer);
            i++;
            unsigned int j {0};
            unsigned int k = i;
            for(j = 0; j < std::strlen(buffer); j++) {
                sub_buffer[j] = buffer[k];
                k++;
                if(sub_buffer[j] == ')') {
                    sub_buffer[j] = buffer[k];
                    j++;
                    break;
                }
            }
            sub_buffer[j] = '\0';
            cur_location = k;
            return sub_buffer;
        }
    }
    delete [] sub_buffer;
    return nullptr;
}

bool read_the_buffer(const char *buffer, Value_List &values) {
    //READS THE BUFFER AND STORES NUMERIC VALUES AND + - * / CHARRACTES IN TO THE values OBJECT
    Value temp;
    for(unsigned int i {0}; i < std::strlen(buffer); i++) {
        double val = read_digit(&buffer[i], i);
        char c = read_ch(&buffer[i]);

        if(c == '0')
            return false;
        
        //IF buffer HAS OPEN BRAKCET ( IN IT. READING JUMPS AHEAD UNTIL WE SEE A CLOSED BRACKET )
        try {
            if(c == '(')
                c = jump_over_bracket(&buffer[i], i);
        }
        catch(const Buffer_Ex &ex) {
            std::cerr << "EXCEPTION THROWN: jump_over_bracket()" << std::endl;
            return false;
        }

        temp.set_value(val);
        temp.set_ch(c);
        values.add_to_the_list(temp);
    }
    //READ THE BUFFER AGAIN FOR BRACKETS
    return true;
}

double read_digit(const char *buffer, unsigned int &jumps) {
    double value {0};
    char *digits = new char[std::strlen(buffer)+1];
    unsigned int i {0};

    //IF IN FRONT OF A DIGIT IS A MINUS SIGN, THIS ENSURES THAT THE MINUS SIGN IS ALSO INCLUDED
    if(buffer[i] == '-') {
        digits[i] = buffer[i];
        i++;
    }

    //DIGITS ARRAY READS ONLY VALUES BETWEEN 1-9 AND . SIGN FOR DECIMAL NUMBERS!
    while((buffer[i] >= '0' && buffer[i] <= '9') || buffer[i] == '.') {
        if(buffer[i] == '.') {
            digits[i] = buffer[i];
            i++;
        }
        digits[i] = buffer[i];
        i++;
    }
    digits[i] = '\0';
    jumps += i; //Update the amount of jumps to be made in the read_the_buffer() function loop
    value = atof(digits); //Converts the values in digits array in to a single double variable
    delete [] digits;
    return value;
}

char read_ch(const char *buffer) {
    char ch {'0'};

    switch(*buffer) {
        case '+':
            ch = *buffer;
            break;
        case '-':
            ch = *buffer;
            break;
        case '*':
            ch = *buffer;
            break;
        case '/':
            ch = *buffer;
            break;
        case '^':
            ch = *buffer;
            break;
        case '(':
            ch = *buffer;
            break;
        case ')':
            ch = *buffer;
            break;
        case '=':
            ch = *buffer;
            break;
        default:
            ch = '0';
            break;
    }
    return ch;
}

char jump_over_bracket(const char *buffer, unsigned int &jumps) {
    unsigned int i {0};
    char c {'0'};
    exception_handling(buffer, nullptr);
    while(buffer[i] != ')') {
        i++;
    }
    i++;
    jumps += i;
    c = '?';
    return c;
}

//THIS CHECKS IF THE BUFFER CONTAINS A CLOSING BRACKET )
//OTHERWISE WE MIGHT LOOP FOR EVER
void exception_handling(const char *buffer, char *sub_buffer) {
    unsigned int i {0};
    while(i < std::strlen(buffer)) {
        if(buffer[i] == ')')
            break;
        if(buffer[i] == '\n') {
            if(sub_buffer != nullptr) {
                delete [] sub_buffer;
            }
            throw Buffer_Ex();
        }
        i++;
    }
}