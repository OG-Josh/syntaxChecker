/*
 * Assignment3.cpp
 *
 *  Created on: Mar 27, 2020
 */

#include <iostream>
#include <string>
#include <fstream>
#include "GenStack.h"

bool SyntaxChecker(string filename);
bool isOpenBracket(char delimeter);
bool isCloseBracket(char delimeter);
bool matchBaracket(char open, char close);
char getCloseBaracket(char open);
char getOpenBaracket(char close);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Used: " << argv[0] << " <file name>" << endl;
        return 1;
    }
    string filename = argv[1];
    while (true) {
        if (SyntaxChecker(filename)) {
            cout << "The delimiter syntax of file: " << filename << " is fine."
                    << endl;
            cout << "Do you want to check another file? (Y/N): ";
            string promt;
            cin >> promt;
            if (promt == "Y" || promt == "y") {
                cout << "Please enter the filename: ";
                cin >> filename;
            }
            else
            {
                break;
            }
        } else {
            break;
        }
    }
    return 0;
}

bool SyntaxChecker(string filename) {
    bool result = true;
    ifstream input(filename);
    if (!input.is_open()) {
        cout << "Can not open file. Please check!!!" << endl;
        result = false;
    } else {
        GenStack<char> stack;
        char delimeter;
        int lineNumber = 1;
        bool isEOF = true;
        while (input.get(delimeter)) {
            if (delimeter == '\n')
                ++lineNumber;
            else if (isOpenBracket(delimeter)) {
                // If this is open bracket. Just push to stack
                stack.push(delimeter);
            } else if (isCloseBracket(delimeter)) {
                if (stack.empty()) {
                    cout << "Line: " << lineNumber << ": Missing '"
                            << getOpenBaracket(delimeter) << "'." << endl;
                    result = false;
                    isEOF = false;
                    break;
                } else {
                    // If this is close bracket. Need to check the open before
                    char open = stack.top(); // Take the top of stack
                    if (matchBaracket(open, delimeter)) {
                        // If this is match. Just pop from stack
                        stack.pop();
                    } else {
                        // This is not match. Need to be print out the error
                        cout << "Line: " << lineNumber << ": Expect '"
                                << getCloseBaracket(open) << "' and found '"
                                << delimeter << "'." << endl;
                        result = false;
                        isEOF = false;
                        break;
                    }
                }
            } else {
                // Another character. Don't care this.
                continue;
            }
        }
        // Reach the end of file. Check the stack
        if (isEOF == true && stack.size() != 0) {
            char open = stack.top();
            cout << "Reached end of file. Missing '" << getCloseBaracket(open)
                    << "'." << endl;
            result = false;
        }
        input.close();
    }
    return result;
}

bool isOpenBracket(char delimeter) {
    bool result = false;
    switch (delimeter) {
    case '(':
    case '{':
    case '[':
        result = true;
        break;
    default:
        break;
    }
    return result;
}

bool isCloseBracket(char delimeter) {
    bool result = false;
    switch (delimeter) {
    case ')':
    case '}':
    case ']':
        result = true;
        break;
    default:
        break;
    }
    return result;
}

bool matchBaracket(char open, char close) {
    bool result = false;
    if (open == '(' && close == ')')
        result = true;
    else if (open == '[' && close == ']')
        result = true;
    else if (open == '{' && close == '}')
        result = true;
    return result;
}

char getCloseBaracket(char open) {
    char result = ' ';
    switch (open) {
    case '(':
        result = ')';
        break;
    case '{':
        result = '}';
        break;
    case '[':
        result = ']';
        break;
    default:
        break;
    }
    return result;

}

char getOpenBaracket(char close) {
    char result = ' ';
    switch (close) {
    case ')':
        result = '(';
        break;
    case '}':
        result = '{';
        break;
    case ']':
        result = '[';
        break;
    default:
        break;
    }
    return result;
}
