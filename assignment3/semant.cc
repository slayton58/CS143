

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "semant.h"
#include "utilities.h"


extern int semant_debug;
extern char *curr_filename;

//////////////////////////////////////////////////////////////////////
//
// Symbols
//
// For convenience, a large number of symbols are predefined here.
// These symbols include the primitive type and method names, as well
// as fixed names used by the runtime system.
//
//////////////////////////////////////////////////////////////////////
static Symbol
    arg,
    arg2,
    Bool,
    concat,
    cool_abort,
    copy,
    Int,
    in_int,
    in_string,
    IO,
    length,
    Main,
    main_meth,
    No_class,
    No_type,
    Object,
    out_int,
    out_string,
    prim_slot,
    self,
    SELF_TYPE,
    Str,
    str_field,
    substr,
    type_name,
    val;
//
// Initializing the predefined symbols.
//
static void initialize_constants(void)
{
    arg         = idtable.add_string("arg");
    arg2        = idtable.add_string("arg2");
    Bool        = idtable.add_string("Bool");
    concat      = idtable.add_string("concat");
    cool_abort  = idtable.add_string("abort");
    copy        = idtable.add_string("copy");
    Int         = idtable.add_string("Int");
    in_int      = idtable.add_string("in_int");
    in_string   = idtable.add_string("in_string");
    IO          = idtable.add_string("IO");
    length      = idtable.add_string("length");
    Main        = idtable.add_string("Main");
    main_meth   = idtable.add_string("main");
    //   _no_class is a symbol that can't be the name of any
    //   user-defined class.
    No_class    = idtable.add_string("_no_class");
    No_type     = idtable.add_string("_no_type");
    Object      = idtable.add_string("Object");
    out_int     = idtable.add_string("out_int");
    out_string  = idtable.add_string("out_string");
    prim_slot   = idtable.add_string("_prim_slot");
    self        = idtable.add_string("self");
    SELF_TYPE   = idtable.add_string("SELF_TYPE");
    Str         = idtable.add_string("String");
    str_field   = idtable.add_string("_str_field");
    substr      = idtable.add_string("substr");
    type_name   = idtable.add_string("type_name");
    val         = idtable.add_string("_val");
}

ClassTable::ClassTable(Classes classes) : semant_errors(0) , error_stream(cerr) {
  cout<<"calling class table constructor"<<endl;
  install_basic_classes();
  install_user_classes(classes);

  install_function_map();
  print_inherit_map();
  
  check_cycle();
  if(cycle_found)
  {
    cerr<<"Circle found!"<<endl;
    fatal();
  }
}



/* Methods for ClassTable */

void ClassTable::install_basic_classes() {

  // The tree package uses these globals to annotate the classes built below.
  // curr_lineno  = 0;
  Symbol filename = stringtable.add_string("<basic class>");

  // The following demonstrates how to create dummy parse trees to
  // refer to basic Cool classes.  There's no need for method
  // bodies -- these are already built into the runtime system.

  // IMPORTANT: The results of the following expressions are
  // stored in local variables.  You will want to do something
  // with those variables at the end of this method to make this
  // code meaningful.

  //
  // The Object class has no parent class. Its methods are
  //        abort() : Object    aborts the program
  //        type_name() : Str   returns a string representation of class name
  //        copy() : SELF_TYPE  returns a copy of the object
  //
  // There is no need for method bodies in the basic classes---these
  // are already built in to the runtime system.

  Class_ Object_class =
    class_(Object,
    No_class,
    append_Features(
    append_Features(
    single_Features(method(cool_abort, nil_Formals(), Object, no_expr())),
    single_Features(method(type_name, nil_Formals(), Str, no_expr()))),
    single_Features(method(copy, nil_Formals(), SELF_TYPE, no_expr()))),
    filename);

  //
  // The IO class inherits from Object. Its methods are
  //        out_string(Str) : SELF_TYPE       writes a string to the output
  //        out_int(Int) : SELF_TYPE            "    an int    "  "     "
  //        in_string() : Str                 reads a string from the input
  //        in_int() : Int                      "   an int     "  "     "
  //
  Class_ IO_class =
    class_(IO,
    Object,
    append_Features(
    append_Features(
    append_Features(
    single_Features(method(out_string, single_Formals(formal(arg, Str)),
    SELF_TYPE, no_expr())),
    single_Features(method(out_int, single_Formals(formal(arg, Int)),
    SELF_TYPE, no_expr()))),
    single_Features(method(in_string, nil_Formals(), Str, no_expr()))),
    single_Features(method(in_int, nil_Formals(), Int, no_expr()))),
    filename);

  //
  // The Int class has no methods and only a single attribute, the
  // "val" for the integer.
  //
  Class_ Int_class =
    class_(Int,
    Object,
    single_Features(attr(val, prim_slot, no_expr())),
    filename);

  //
  // Bool also has only the "val" slot.
  //
  Class_ Bool_class =
    class_(Bool, Object, single_Features(attr(val, prim_slot, no_expr())),filename);

  //
  // The class Str has a number of slots and operations:
  //       val                                  the length of the string
  //       str_field                            the string itself
  //       length() : Int                       returns length of the string
  //       concat(arg: Str) : Str               performs string concatenation
  //       substr(arg: Int, arg2: Int): Str     substring selection
  //
  Class_ Str_class =
    class_(Str,
    Object,
    append_Features(
    append_Features(
    append_Features(
    append_Features(
    single_Features(attr(val, Int, no_expr())),
    single_Features(attr(str_field, prim_slot, no_expr()))),
    single_Features(method(length, nil_Formals(), Int, no_expr()))),
    single_Features(method(concat,
    single_Formals(formal(arg, Str)),
    Str,
    no_expr()))),
    single_Features(method(substr,
    append_Formals(single_Formals(formal(arg, Int)),
    single_Formals(formal(arg2, Int))),
    Str,
    no_expr()))),
    filename);

  //add these basic class names:
  basic_class_set.insert(Object);
  basic_class_set.insert(IO);
  basic_class_set.insert(Int);
  basic_class_set.insert(Bool);
  basic_class_set.insert(Str);
  basic_class_set.insert(SELF_TYPE);  //TODO: is this needed?
  //add these class mapping from name to class:
  class_map.insert(std::make_pair(Object, (class__class *)Object_class));
  class_map.insert(std::make_pair(IO, (class__class *)IO_class));
  class_map.insert(std::make_pair(Int, (class__class *)Int_class));
  class_map.insert(std::make_pair(Bool, (class__class *)Bool_class));
  class_map.insert(std::make_pair(Str, (class__class *)Str_class));
  //populate the inherit graph with the basic classes:
  inherit_graph[No_class].insert(Object);
  inherit_graph[Object].insert(IO);
  inherit_graph[Object].insert(Int);
  inherit_graph[Object].insert(Bool);
  inherit_graph[Object].insert(Str);
}

void ClassTable::install_user_classes( Classes classes )
{
  bool contains_main = false;
  for (int i = classes->first(); classes->more(i); i = classes->next(i))
  {
      //iterate over all the classes: cls
      class__class* cls = (class__class *) classes->nth(i);

      //check class redefinition:
      if(class_map.count(cls->get_name()))
        semant_error(cls->get_filename(), cls)<<"Class "<<cls->get_name()<<" was previously defined"<<endl;
      
      //check basic class redefinition:
      if(basic_class_set.count(cls->get_name()))
        semant_error(cls->get_filename(), cls)<<"Redefinition of basic class "<<cls->get_name()<<endl;
      
      //if Main class exist
      if(cls->get_name() == Main)
        contains_main = true;
      
      //populate the class map with current class cls
      class_map.insert(std::make_pair(cls->get_name(), cls));
  }
  if (!contains_main)
    semant_error()<<"Class Main is not defined."<<endl;

  print_class_map();
  
  // second iteration: begin insert the parent-child:
  for (int i = classes->first(); classes->more(i); i = classes->next(i))
  {
    class__class * cls = (class__class *) classes->nth(i);
    Symbol parent = cls->get_parent();
    
    // inherit from basic class
    if( parent == Int || parent == Str || parent == Bool ) {
      semant_error(cls->get_filename(), cls)<<"class "<<cls->get_name()<<" can't inherit class "<<parent<<endl;
      fatal();
    }
    // inherit from SELF_TYPE
    if ( parent == SELF_TYPE ){
      semant_error(cls->get_filename(), cls)<<"class "<<cls->get_name()<<" can't inherit from SELF_TYPE"<<endl;
      fatal();
    }

    // inherit from non-existing parent
    if ( class_map.count(parent)==0 )   {
      semant_error(cls->get_filename(), cls)<<"class "<<cls->get_name()<<" inheriting from non-existing parent"<<endl;
      fatal();
    }

    // Finally add the child to the parent key in the inherit graph
    inherit_graph[parent].insert(cls->get_name());
  }
  //To debug least upper bound:
  //Symbol c1, c2, common;
  //for (int i = classes->first(); classes->more(i); i = classes->next(i))
  //{
  //  class__class * cls = (class__class *) classes->nth(i);
  //  // To debug is_child:
  //  // cout<<cls->get_name()<<" is child of Oject: "<<is_child(cls->get_name(), Object)<<endl;
  //  if (!strcmp(cls->get_name()->get_string(),"D7"))
  //    c1=cls->get_name();
  //  if (!strcmp(cls->get_name()->get_string(),"D5"))
  //    c2=cls->get_name();
  //}
  //common = least_upper_bound(c1, c2);
  //cout<<c1<<" and "<<c2<<" is commoned at "<<common<<endl;


}

void ClassTable::install_function_map()
{
  //throw std::exception("The method or operation is not implemented.");
}


class__class* ClassTable::get_parent( Symbol class_name )
{
  class__class *cls = (class__class *) class_map[class_name];
  return class_map[cls->get_parent()];
}

bool ClassTable::is_child (Symbol c, Symbol p)
{
  //cout<<"is child called"<<endl;
  bool c_is_child = false;
  std::map<Symbol, int> visited_map;
  std::map<Symbol, std::set<Symbol> > ::iterator iter;
  std::set<Symbol>::iterator iter2;

  // set visited color to all zero
  for (iter = inherit_graph.begin(); iter != inherit_graph.end(); ++iter)
  {
    visited_map[iter->first] = 0;
    for (iter2 = iter->second.begin(); iter2 != iter->second.end(); ++iter2)
      visited_map[*iter2] = 0;
  }

  DFS_is_child(visited_map, c, p, c_is_child);
  return c_is_child;

}

void ClassTable::DFS_is_child(std::map<Symbol, int> visited_map, Symbol c, Symbol p, bool &c_is_child)
{
  //visit p  
  if (p == c)
    c_is_child = true;

  // mark p as visited
  visited_map[p] = 1;

  // recursively visit p's child
  for (std::set<Symbol>::iterator iter = inherit_graph[p].begin(); iter != inherit_graph[p].end(); ++iter)
  {
    if (visited_map[*iter] == 0)
       DFS_is_child(visited_map, c, *iter, c_is_child);    
  }
  
}

void ClassTable::check_cycle()
{
  cycle_found = false;
  std::map<Symbol, int> visited_map;
  std::map<Symbol, std::set<Symbol> > ::iterator iter;
  std::set<Symbol>::iterator iter2;

  // set visited color to all zero
  for (iter = inherit_graph.begin(); iter != inherit_graph.end(); ++iter)
  {
    visited_map[iter->first] = 0;
    for (iter2 = iter->second.begin(); iter2 != iter->second.end(); ++iter2)
      visited_map[*iter2] = 0;
  }

  for (iter = inherit_graph.begin(); iter != inherit_graph.end(); ++iter)
  {
    DFS_has_cycle(visited_map, iter->first);
    if (cycle_found) 
      break;    
  }
}

void ClassTable::DFS_has_cycle(std::map<Symbol, int> visited_map, Symbol c)
{
  
  visited_map[c] = -1;
  //cout<<"  visiting "<<c<<endl;
  for (std::set<Symbol>::iterator iter = inherit_graph[c].begin(); iter != inherit_graph[c].end(); ++iter)
  {
    if(visited_map[*iter] == -1)
      cycle_found = true;
    else if (visited_map[*iter] == 0)
      DFS_has_cycle(visited_map, *iter);
  }
  visited_map[c] = 1;

}


Symbol ClassTable::least_upper_bound(Symbol c1, Symbol c2)
{                                                             
  bool is_upper_bound = true;
  Symbol head = Object;
  std::set<Symbol>::iterator iter;
  while (is_upper_bound == true)
  {
    is_upper_bound = false;
    for (iter = inherit_graph[head].begin(); iter != inherit_graph[head].end(); ++iter)
    {
      if ( is_child(c1, *iter) && is_child(c2, *iter))
      {
        is_upper_bound = true;
        head = *iter;
        break;
      }
    }
  }
  return head;
}

method_class * ClassTable::get_method(Symbol class_name, Symbol method_name)
{

}

std::vector<Symbol> ClassTable::get_signature(Symbol class_name, Symbol method_name)
{

}


void ClassTable::print_inherit_map()
{
  std::map<Symbol, std::set<Symbol> > ::iterator iter1;
  std::set<Symbol>::iterator iter2;
  for (iter1=inherit_graph.begin(); iter1!=inherit_graph.end(); ++iter1)
  {
    cout<<"Parent: "<<iter1->first<<" -> ";
    for (iter2=iter1->second.begin(); iter2!=iter1->second.end(); ++iter2)
    {
      cout<<(*iter2)<<", " ;
    }
    cout<<endl;

  }
}

void ClassTable::print_class_map()
{
  cout<<endl<<"printing the class_map"<<endl;
  std::map<Symbol, class__class *>::iterator iter;
  for( iter = class_map.begin(); iter != class_map.end(); ++iter )
    cout<<iter->first<<endl;
  cout<<endl;
}

////////////////////////////////////////////////////////////////////
//
// semant_error is an overloaded function for reporting errors
// during semantic analysis.  There are three versions:
//
//    ostream& ClassTable::semant_error()
//
//    ostream& ClassTable::semant_error(Class_ c)
//       print line number and filename for `c'
//
//    ostream& ClassTable::semant_error(Symbol filename, tree_node *t)
//       print a line number and filename
//
///////////////////////////////////////////////////////////////////

ostream& ClassTable::semant_error(Class_ c)
{
  return semant_error(c->get_filename(),c);
}

ostream& ClassTable::semant_error(Symbol filename, tree_node *t)
{
  error_stream << filename << ":" << t->get_line_number() << ": ";
  return semant_error();
}

ostream& ClassTable::semant_error()
{
  semant_errors++;
  return error_stream;
}

void ClassTable::fatal()
{
  cerr<<"Compilation halted due to static semantic errors."<<endl;
  exit(1);
}








/*   This is the entry point to the semantic checker.

     Your checker should do the following two things:

     1) Check that the program is semantically correct
     2) Decorate the abstract syntax tree with type information
        by setting the `type' field in each Expression node.
        (see `tree.h')

     You are free to first do 1), make sure you catch all semantic
     errors. Part 2) can be done in a second stage, when you want
     to build mycoolc.
 */
void program_class::semant()
{
    initialize_constants();

    /* ClassTable constructor may do some semantic analysis */
    ClassTable *classtable = new ClassTable(classes);

    /* some semantic analysis code may go here */

    if (classtable->errors()) {
	    cerr << "Compilation halted due to static semantic errors." << endl;
	    exit(1);
    }
}






