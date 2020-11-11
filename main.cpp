#include <iostream>

#include "Value.h"
#include "Value_List.h"
#include "Util.h"
#include "Exceptions.h"

using namespace std;

int main() {
    valikko();

    char main_buffer[BUFFER_SIZE+1];
    unsigned int i {0};

    fgets(main_buffer, BUFFER_SIZE, stdin);

    Value_List main_list;
    vector<Value_List> brackets;

    /*
    THIS LOOP WILL READ main_buffer AND STORE POSSIBLE BRACKETS IN TO INDIVIDUAL VECTORS called bracket
    WHEN BRACKETS ARE READ THEN THE main_buffer WILL BE READ IN TO IT´S OWN VECTOR main_list
    */
    while(true) {
        char *sub_buffer = nullptr;
        try {
            if((sub_buffer = check_the_buffer_for_brackets(main_buffer, i)) == nullptr) {
                //IF THERE ARE NO BRACKETS IN THE main_buffer THEN THIS BLOCK WILL EXECUTE
                read_the_buffer(main_buffer, main_list);
                break;
            } else {
                //IF THERE IS A BRACKET FOUND IN THE MAIN BUFFER, THEN THIS BLOCK WILL EXECUTE
                Value_List bracket;
                if(read_the_buffer(sub_buffer, bracket) != false)
                    brackets.push_back(bracket);
                delete [] sub_buffer;
            }
        }
        catch(const Buffer_Ex &ex) {
            cerr << "EXCEPTION THROWN: check_the_buffer_for_brackets" << endl;
            delete [] sub_buffer;
            break;
        }
    }

    //CREATING A VECTOR WHICH WILL CONTAIN THE RESULTS OF THE 
    vector<Value> bracket_results;
    if(brackets.size() != 0) {
        for(Value_List list: brackets) {
            bracket_results.push_back(list.do_the_math());
        }
    }
    if(bracket_results.size() != 0)
        main_list.fill_empty_with_results(bracket_results); //fill_empty_with_results WILL FILL ALL THE EMPTY SLOTS OF THE main_list
    try {
        main_list.do_the_math(); //FINALY WE CALCULATE THE main_list
    }
    catch(const Do_The_Math_Ex &ex) {
        cerr << "EXCEPTION THROWN: main_list WAS EMPTY" << endl;
    }
    main_list.display_list();
    return 0;
}