//
// Created by Do Hyung Kwon on 11/12/18.
//

#ifndef STACKANDQUEUE_FUNCTIONS_H
#define STACKANDQUEUE_FUNCTIONS_H

#include <list>
#include <vector>
#include "LinkedList.h"

template<class T>
void parse_command(std::list<LinkedList<T> *> &lists, const std::vector<std::string> &commands, std::ofstream &outfile);

template<class T>
void create(std::list<LinkedList<T> *> &lists, const std::vector<std::string> &commands, std::ofstream &outfile);

template<class T>
void create_queue(std::list<LinkedList<T> *> &lists, const std::vector<std::string> &commands);

template<class T>
void create_stack(std::list<LinkedList<T> *> &lists, const std::vector<std::string> &commands);

template<class T>
void pop(std::list<LinkedList<T> *> &lists, const std::vector<std::string> &commands, std::ofstream &outfile);

template<class T>
void push(std::list<LinkedList<T> *> &lists, const std::vector<std::string> &commands, std::ofstream &outfile);

template<class T>
bool check_existence(std::list<LinkedList<T> *> &lists, const std::string &name, std::ofstream &outfile);

std::vector<std::string> split(const std::string &s, char delimiter);

void choose_list(std::list<LinkedList<int> *> &listSLi, std::list<LinkedList<double> *> &listSLd,
                 std::list<LinkedList<std::string> *> &listSLs, const std::vector<std::string> &commands,
                 std::ofstream &outfile);

#endif //STACKANDQUEUE_FUNCTIONS_H
