//
// Created by Do Hyung Kwon on 11/12/18.
//

// This program implements Stacks and Queues using Singly Linked List, and it uses template for generic programming.

// Data Structure and Functions are separated into header file to easily maintain.
// Reference were passed as an argument to not duplicate.
#include <iostream>
#include <sstream>
#include <fstream>

#include "LinkedList.h"
#include "Functions.h"

// main function
int main() {
    // Input and Output File
    std::string InputFile;
    std::string OutputFile;
    std::string commands;

    // Lists of Queues and Stacks
    std::list<LinkedList<int> *> listSLi;
    std::list<LinkedList<double> *> listSLd;
    std::list<LinkedList<std::string> *> listSLs;

    // Prompt
    std::cout << "What is the name of the input file?" << std::endl;
    std::cin >> InputFile;

    std::cout << "What is the name of the output file?" << std::endl;
    std::cin >> OutputFile;

    // Input and Output Stream to easily read and write from files
    std::ifstream infile(InputFile);
    std::ofstream outfile(OutputFile);

    // getline reads the input file until the end of file, and each line is sent to split function that tokenize with
    // delimiter (white space). And then the tokenized commands are sent to parsing function.
    while (getline(infile, commands)) {
        std::vector<std::string> tokens = split(commands, ' ');
        outfile << "PROCESSING COMMAND: " << commands << std::endl;
        choose_list(listSLi, listSLd, listSLs, tokens, outfile);
    }
}

// I have chosen to use a split function with delimiter that could be use widely with any kind of delimiter
// returns vector<string> tokens that contains tokenized commands
std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);

    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// it chooses which list of LinkedList to use.
void choose_list(std::list<LinkedList<int> *> &listSLi, std::list<LinkedList<double> *> &listSLd,
                 std::list<LinkedList<std::string> *> &listSLs, const std::vector<std::string> &commands,
                 std::ofstream &outfile) {
    if (commands[1][0] == 'i') {
        parse_command(listSLi, commands, outfile);
    } else if (commands[1][0] == 'd') {
        parse_command(listSLd, commands, outfile);
    } else if (commands[1][0] == 's') {
        parse_command(listSLs, commands, outfile);
    }
}

// it is a parser that select which action to do from the command.
// included Error checking for inputting non-given command (not required but it will need for faulty check)
template<class T>
void parse_command(std::list<LinkedList<T> *> &lists, const std::vector<std::string> &commands, std::ofstream &outfile) {
    if (commands[0] == "create") {
        create(lists, commands, outfile);
    } else if (commands[0] == "push") {
        push(lists, commands, outfile);
    } else if (commands[0] == "pop") {
        pop(lists, commands, outfile);
    } else {
        outfile << "ERROR: Not Existing Command!" << std::endl;
    }
}

// it checks if the list already contains same name stack or queue, and then create stack or queue
// if it is not in the list
template<class T>
void create(std::list<LinkedList<T> *> &lists, const std::vector<std::string> &commands, std::ofstream &outfile) {
    for (LinkedList<T> *list: lists) {
        if (list->getName() == commands[1]) {
            outfile << "ERROR: This name already exists!" << std::endl;
            return;
        }
    }

    if (commands[2] == "queue") {
        create_queue(lists, commands);
    } else if (commands[2] == "stack") {
        create_stack(lists, commands);
    }
}

// create stack
template<class T>
void create_stack(std::list<LinkedList<T> *> &lists, const std::vector<std::string> &commands) {
    Stack<T> *tmp = new Stack<T>(commands[1]);
    lists.push_front(tmp);
}

// create queue
template<class T>
void create_queue(std::list<LinkedList<T> *> &lists, const std::vector<std::string> &commands) {
    Queue<T> *tmp = new Queue<T>(commands[1]);
    lists.push_front(tmp);
}

// it checks whether given stack or queue is in the lists and print out error. If it has the stack or queue,
// stringstream is used to easily convert to given type, and push the value to the stack or queue
template<class T>
void push(std::list<LinkedList<T> *> &lists, const std::vector<std::string> &commands, std::ofstream &outfile) {
    if (!check_existence(lists, commands[1], outfile)) {
        return;
    }
    for (LinkedList<T> *list: lists) {
        if (list->getName() == commands[1]) {
            std::stringstream ss(commands[2]);
            T val;
            ss >> val;
            list->push(val);
        }
    }
}

// it checks whether given stack or queue is in the lists and print out error. If it has the stack or queue,
// it first checks whether stack or queue is empty and if it is not empty it pops.
template<class T>
void pop(std::list<LinkedList<T> *> &lists, const std::vector<std::string> &commands, std::ofstream &outfile) {
    if (!check_existence(lists, commands[1], outfile)) {
        return;
    }
    for (LinkedList<T> *list: lists) {
        if (list->getName() == commands[1]) {
            if (!list->checkPop()) {
                outfile << "ERROR: This list is empty!" << std::endl;
                return;
            }
            outfile << "Value popped: " << list->top() << std::endl;
            list->pop();
            return;
        }
    }
}

// function to check if the given name already exists in the list of stack or queue
template<class T>
bool check_existence(std::list<LinkedList<T> *> &lists, const std::string &name, std::ofstream &outfile) {
    for (LinkedList<T> *list: lists) {
        if (list->getName() == name) {
            return true;
        }
    }
    outfile << "ERROR: This name does not exist!" << std::endl;
    return false;
}