#ifndef SEMANT_H_
#define SEMANT_H_

#include <assert.h>
#include <iostream>
#include "cool-tree.h"
#include "stringtab.h"
#include "symtab.h"
#include "list.h"
#include <map>
#include <set>
#include <vector>


#define TRUE 1
#define FALSE 0

class ClassTable;
typedef ClassTable *ClassTableP;

// This is a structure that may be used to contain the semantic
// information such as the inheritance graph.  You may use it or not as
// you like: it is only here to provide a container for the supplied
// methods.

class ClassTable {
private:
  int semant_errors;
  bool cycle_found;
  void install_basic_classes();
  void install_user_classes(Classes);
  void install_function_map();
  void check_cycle();
  void DFS_is_child(std::map<Symbol, int> visited_map, Symbol c, Symbol p, bool &);
  void DFS_has_cycle(std::map<Symbol, int> visited_map, Symbol c);
  
  void print_inherit_map();
  void print_class_map();
  void fatal();

  ostream& error_stream;

  //map from class name to class
  std::map<Symbol, class__class *> class_map;
  //map from class name and function name to function
  std::map<Symbol, std::map<Symbol, method_class*> > function_map;
  //inheritance map
  std::map<Symbol, std::set<Symbol> > inherit_graph;
  //class set
  std::set<Symbol> basic_class_set;
 

public:
  ClassTable(Classes);
  int errors() { return semant_errors; }
  ostream& semant_error();
  ostream& semant_error(Class_ c);
  ostream& semant_error(Symbol filename, tree_node *t);
 
  bool is_child (Symbol c1, Symbol c2);
  Symbol least_upper_bound(Symbol c1, Symbol c2);
  Class_ get_parent(Symbol);
  method_class get_method(Symbol class_name, Symbol method_name);
  std::vector<Symbol> get_signature(Symbol class_name, Symbol method_name);


};


#endif

