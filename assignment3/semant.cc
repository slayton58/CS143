

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "semant.h"
#include "utilities.h"
#include "typeinfo"

#include <queue>
#include <vector>


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

bool ClassTable::class_exist(Symbol c)
{
  return (class_map.count(c) > 0);
}

std::vector<Symbol> ClassTable::get_signature(Symbol class_name, Symbol method_name)
{
  std::vector<Symbol> sig;
  if (method_map.count(class_name)==0)
    semant_error()<<" No class_name found"<<endl;
  else if (method_map[class_name].count(method_name)==0)
    semant_error()<<" No method_name found"<<endl;
  else
  {
    method_class* m = method_map[class_name][method_name];
    Formals formals = m->get_formals();
    //add formals' types:
    for(int i = formals->first(); formals->more(i); i = formals->next(i))
    {
      formal_class *fm = (formal_class *)formals->nth(i);
      sig.push_back(fm->get_type_decl());//TODO
    }
    // add return type:
    sig.push_back(m->get_return_type()); //TODO

  }
  return sig;
}

void ClassTable::verify_signature( class__class* cls, method_class* m )
{
  Formals formals = m->get_formals();
  // iterater through the formal list to check each can't be self or SELF_TYPE
  for (int i = formals->first(); formals->more(i); i = formals->next(i))
  {
    formal_class* fm = (formal_class *) formals->nth(i);

    //formal list shouldn't have self
    if(fm->get_name() == self)
      semant_error((cls->get_filename()), m)<<"formal list shouldn't have self "<<endl;

    //formal list shouldn't have SELF_TYPE
    if(fm->get_name() == SELF_TYPE)
      semant_error((cls->get_filename()), m)<<"formal list shouldn't have SELF_TYPE "<<endl;
  }
  //check the return type should be an already defined class
  if (class_map[m->get_return_type()] == NULL && m->get_return_type() != SELF_TYPE)
    semant_error((cls->get_filename()), m)<<" return type not defined in method "<< m->get_name()<<endl;


}

bool ClassTable::method_exist(Symbol class_name, Symbol method_name)
{
  bool exist=true;
  if (method_map.count(class_name)==0)
    exist = false;    
  else if (method_map[class_name].count(method_name)==0)
    exist = false;

  return exist;
}

method_class* ClassTable::get_method(Symbol class_name, Symbol method_name)
{
  return method_map[class_name][method_name];
}
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
  bool main_found = false;
  bool main_has_formal = false;
  std::queue<Symbol> q;
  q.push(Object);
  Symbol c;  
  // BFS all the classes 
  while ( !q.empty() )
  {
    c = q.front();

    q.pop();
    // for each class, get the features
    Features features = class_map[c]->get_features();
    for(int i = features->first(); features->more(i); i = features->next(i))
    {
      Feature f = features->nth(i);

      if (f->get_is_method())  
      {
        method_class* m = (method_class*)f;
        verify_signature(class_map[c], m);
        method_map[c][m->get_name()]=m;  
        if (c==Main && m->get_name()==main_meth)
        {
          main_found = true;
          if (m->get_formals()->len()>0)
            main_has_formal = true;          
        }
      }
    } 

    //also add features from parent class:
    std::map<Symbol, method_class*> parent_methods = 
      method_map[class_map[c]->get_parent()]; //TODO
    std::map<Symbol, method_class*>::iterator iter;
    for (iter=parent_methods.begin(); iter!=parent_methods.end(); ++iter)
    {
      if (method_map[c].count(iter->first) == 0 )
        method_map[c][iter->first]= iter->second;
    }

    std::set<Symbol> child_class = inherit_graph[c];
    std::set<Symbol>::iterator iter2;
    for(iter2= child_class.begin(); iter2!= child_class.end(); ++iter2)
    {
      q.push(*iter2) ;
    }


  }

  if (!main_found)
    semant_error(class_map[c]->get_filename(), class_map[c])<<" No main method found"<<endl;
  if (main_has_formal)
    semant_error(class_map[c]->get_filename(), class_map[c])<<" main method shouldn't have formals"<<endl;
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
    /* some semantic analysis code may go here */

	     ClassTable *classTable = new ClassTable(classes);
       
	     OcurredExpection = false;
	     sv = new semanVisitor(classTable);
       
	     this->accept(sv);
       
	     if(classTable->errors()) {
	    	 cerr << "compilation halted due to static semantic errors." << endl;
	         }
}

void semanVisitor::visit(Program e) {
	cerr << "public void visit (program e) should never be called." << endl;
}

void semanVisitor::visit(Class_ e) {
	cerr << "public void visit (Class_ e) should never be called." << endl;
}

void semanVisitor::visit(Feature e) {
	cerr << "public void visit (Feature e) should never be called." << endl;
}

void semanVisitor::visit(Formal e) {
	cerr << "public void visit (Formal e) should never be called." << endl;
}


void semanVisitor::visit(Case e) {
	cerr << "public void visit (Case e) should never be called." << endl;
}


void semanVisitor::visit(Expression e) {
  cout << "come to visit Expression" << endl;
  cout << typeid(*e).name()<<endl;
	if (typeid(*e)==typeid(assign_class)) {
		assign_class* node=(assign_class *) (e);   cout<<"before visit assign"<<endl;
		visit(node); cout<<" after visit assign"<<endl;
	 }
	else if(typeid(*e) == typeid(static_dispatch_class)) {
		static_dispatch_class* node = (static_dispatch_class*) (e);
		visit(node);
	}
	else if(typeid(*e) == typeid(dispatch_class)) {
        dispatch_class* node = (dispatch_class*) (e);
        visit(node);
	}
	else if(typeid(*e) == typeid(cond_class)) {
		cond_class* node = (cond_class*) (e);
		visit(node);
	}
	else if(typeid(*e) == typeid(loop_class)) {
		loop_class* node = (loop_class*) (e);
		visit(node);
	}
	else if(typeid(*e) == typeid(typcase_class) ){
		typcase_class* node = (typcase_class*) (e);
		visit(node);
	}
	else if(typeid(*e) == typeid(block_class)) {
		block_class* node = (block_class*) (e);
		visit(node);
	}
	else if(typeid(*e) == typeid(let_class)) {
		let_class* node = (let_class*) (e);
		visit(node);
	}
	else if(typeid(*e) == typeid(plus_class) ){
		plus_class* node = (plus_class*) (e);
		visit(node);
	}
	else if(typeid(*e) == typeid(sub_class)) {
		sub_class* node = (sub_class*) e;
		visit(node);
	}
	else if(typeid(*e) == typeid(mul_class)) {
		mul_class* node = (mul_class*) e;
		visit(node);
	}
	else if(typeid(*e) == typeid(divide_class)) {
		divide_class* node = (divide_class*) e;
		visit(node);
	}
	else if(typeid(*e) == typeid(neg_class)) {
		neg_class* node = (neg_class*) e;
		visit(node);
	}
	else if(typeid(*e) == typeid(lt_class)) {
		lt_class* node = (lt_class*) e;
		visit(node);
	}
	else if( typeid(*e) == typeid(eq_class)) {
		eq_class* node = (eq_class*) e;
		visit(node);
	}
	else if(typeid(*e) == typeid(leq_class)) {
		leq_class* node = (leq_class*) e;
		visit(node);
	}
	else if(typeid(*e) == typeid(comp_class)) {
		comp_class* node = (comp_class*) e;
		visit(node);
	}
	else if(typeid(*e) == typeid(int_const_class)) {
		int_const_class* node = (int_const_class*) e;
		visit(node); cout<<"after visit int const " << node->get_token()<<endl;
	}
	else if(typeid(*e)== typeid(bool_const_class)){
		bool_const_class* node = (bool_const_class*) e;
		visit(node);
	}
	else if(typeid(*e) == typeid(string_const_class)) {
		string_const_class* node = (string_const_class*) e;
		visit(node);
	}
	else if(typeid(*e)== typeid(new__class)) {
		new__class* node = (new__class*) e;
		visit(node);
	}
	else if(typeid(*e)== typeid(isvoid_class)) {
		isvoid_class* node = (isvoid_class*) e;
		visit(node);
	}
	else if(typeid(*e)== typeid(no_expr_class)) {
		no_expr_class* node = (no_expr_class*) e;
		visit(node);
	}
	else if(typeid(*e) == typeid(object_class)) {
		object_class* node = (object_class*) e;
		visit(node);
	}
}

void semanVisitor::visit(program_class* prg) {
	Classes classes = prg->getClasses();
	for(int i =classes->first(); classes->more(i); i=classes->next(i) ){
		class__class* cl = (class__class*) classes->nth(i);
	}  
}

void semanVisitor::visit(class__class* cl) 
{
	currentClass = cl;
	Features features = cl->get_features();
	Features parent_feature_list = cl->parent_feature_list;
   cout << "wrong in visit" << endl;
	for(int i=0; i < features->len(); i++) 
  {
		Feature ft1 = (Feature) features->nth(i);
		bool conflictWithParents = false;
      cout << "wrong in outter loop" << endl;
      cout<< parent_feature_list->len()<<endl;
		for(int j=0; j < parent_feature_list->len(); j++) 
    {     
      cout << "wrong in inner loop" << endl;
			Feature ft2 = (Feature) parent_feature_list->nth(j);
      if((!(ft1->get_is_method()) && !(ft2->get_is_method()))
				&& (((attr_class*)ft1)->get_name() == ((attr_class*)ft2)->get_name()))
      {            cout << "wrong in if" << endl;
				conflictWithParents = true;
				classTable->semant_error(currentClass->get_filename(), ft1)<<"arribute "<<((attr_class*)ft1)->get_name()<<"is an attribute of inherited class"<<endl;
				break;
			}
      else if((ft1->get_is_method() && ft2->get_is_method())
					&& ((method_class*)ft1)->get_name()->get_string() == ((method_class*)ft2)->get_name()->get_string())
      {      cout << "wrong in else if" << endl;
				method_class* mt1 =((method_class*)ft1);
				method_class* mt2 =((method_class*)ft2);

				//check return_type
				if(mt1->get_return_type()->get_string()!=mt2->get_return_type()->get_string())
        {
					classTable->semant_error(currentClass->get_filename(), ft1)<<"return type is different from inherited type"<<endl;
					break;
				}

				bool sameFormalsLength = false;
				Formals fms1 = mt1->get_formals();
				Formals fms2 = mt2->get_formals();
				if(fms1->len() == fms2->len()) {
					sameFormalsLength = true;
				}
				else {
					classTable->semant_error(currentClass->get_filename(), ft1)<<"different number of formals from parent"<<endl;
				}

				//check formal type
				if(sameFormalsLength ) 
        {
					for(int q =0; q< fms1->len(); q++) 
          {
						formal_class* fm1 = (formal_class*)fms1->nth(q);
						formal_class* fm2 = (formal_class*)fms2->nth(q);

						if(fm1->get_type_decl()->get_string() != fm2->get_type_decl()->get_string()) 
            {
							classTable->semant_error(currentClass->get_filename(), ft1)<<"formal length is differnt from parent"<<endl;
						    break;
						}
					}
				}
			}
		}
    cout<< " pass outter loop " << endl;
		if(conflictWithParents == false) 
    {    cout<< "wrong in conflict with parents" << endl;
         cout << i << endl;
		    //	check feature defined conflicts within the current class
			for(int k=0; k< i; k++) 
      {   cout<< "wrong in conflict inner loop"<<endl;
				Feature ft3 = (Feature) features->nth(k);

				if((!(ft1->get_is_method()) && !(ft3->get_is_method()))
						&& ((attr_class*)ft1)->get_name()->get_string()== ((attr_class*)ft3)->get_name()->get_string()) 
        {
					classTable->semant_error(currentClass->get_filename(), ft1)<<"attribute is multiply defined"<<endl;
					break;
				}
				else if ((ft1->get_is_method() && ft3->get_is_method())
						&& ((method_class*)ft1)->get_name()->get_string()== ((method_class*)ft3)->get_name()->get_string()) 
        {
					classTable->semant_error(currentClass->get_filename(), ft1)<<"method is multiply defined"<<endl;
					break;
				}
			}
		}
	}
}

void semanVisitor::visit(method_class *mt) 
{
  Formals formals = mt->get_formals(); 
  cout<< "before visit method outter loop " << endl;
  for(int i =formals->first(); formals->more(i); i=formals->next(i) ) 
  {
    formal_class* fm = (formal_class*) formals->nth(i);   cout<< "formal name: " << fm->get_name()<<endl;
    if(typeid(probeObject(fm->get_name()))==typeid(formal_class)) 
    {
      classTable->semant_error(currentClass->get_filename(), fm)<<"formal multiply defined"<<endl;
    }
    else
      addId(fm->get_name(),fm, 0);
  } 
  cout<< "after visit method outter loop " << endl;
  
  this->visit(mt->get_expr());     cout<< "after visit get expr " << endl;
  // get method signature
  std::vector<Symbol> signature = classTable->get_signature(currentClass->get_name(), mt->get_name());
  
  //check whether return type is compatible
  Symbol return_from_method = mt->get_return_type();
  Symbol return_from_expr = mt->get_expr()->get_type();

  Symbol return_from_expr_infer = return_from_expr;
  if(return_from_expr_infer == SELF_TYPE) {
    return_from_expr_infer = this->currentClass->get_name();
  }

  bool case_1 = (return_from_method == SELF_TYPE) &&
    (return_from_expr != SELF_TYPE);
  bool case_2 = (return_from_method != SELF_TYPE) &&
    (!classTable->is_child(return_from_expr_infer,return_from_method));
  if(case_1 || case_2) {
    classTable->semant_error(currentClass->get_filename(),mt)<<"return type does not match!"<<endl;
  }
}

void semanVisitor::visit(attr_class *at) {
    // check self is not the name
     if(at->get_name() == self) {
       classTable->semant_error(currentClass->get_filename(), at)
         << "cannot use \'self\' as the name of an attribute.\n" <<endl;
     }
     // check whether type decl is valid
     if(at->get_type_decl() != SELF_TYPE &&
       !classTable->class_exist(at->get_type_decl())) {
        classTable->semant_error(currentClass->get_filename(), at)
          << "class " << at->get_type_decl()->get_string()
          << " of attribute "  << at->get_name()->get_string()
          << " is undefined.\n" <<endl;
     }

     this->visit(at->get_init());

     if(at->get_init()->get_type()==NULL)
       return;

     //verif whether type decl is compatible
     Symbol type_decl = at->get_type_decl();
     Symbol type_init = at->get_init()->get_type();
     if(type_init == SELF_TYPE) {
          type_init = this->currentClass->get_name();
     }
     if(!this->classTable->is_child(type_init,type_decl)) {
        classTable->semant_error(currentClass->get_filename(),at)
          << "Initialized type "  << type_init->get_string()
          << " of attribute " << at->get_name()->get_string()
          << " does not conform to the declared type "
          << type_decl->get_string() << ".\n" << endl;        
     }
}

void semanVisitor::visit(formal_class* fm) {
  //check whether type_decl is valid
  if(fm->get_type_decl() != SELF_TYPE &&
    !classTable->class_exist(fm->get_type_decl())) {
     classTable->semant_error(currentClass->get_filename(), fm)
       << "class " << fm->get_type_decl()->get_string()
       << " of formal " << fm->get_name()->get_string()
       << " is undefined.\n" << endl;
  }    
}

void semanVisitor::visit(branch_class *br) {
  // no need to check object redefinition 
  addId(br->get_name(), br, 0);
    
    if(!classTable->class_exist(br->get_type_decl())){
      classTable->semant_error(currentClass->get_filename(), br)
        << "Class " << br->get_type_decl()
        << " in case branch is undefined.\n" << endl;
    }
   //SELF_TYPE is not allowed in case branch
    if((br->get_type_decl()) == SELF_TYPE) {
    classTable->semant_error(currentClass->get_filename(), br)
      << "Identifier " << br->get_name()->get_string()
      << " declared with SELF_TYPE in case. \n" << endl;
  }
  this->visit(br->get_expr());
}

void semanVisitor::visit(assign_class *as) {
  if(symtable_o->lookup(as->get_name())==NULL) 
  {
     classTable->semant_error(currentClass->get_filename(),as) 
       << "Assigned variable "<< as->get_name()->get_string()
       <<" is undeclared.\n" <<endl;
    as->set_type(Object);
    return;
  }         
  if(as->get_name() == self) {
     classTable->semant_error(currentClass->get_filename(), as)
       << "\'self\' cannot be assigned.\n" <<endl;
     as->set_type(Object);
     return;
  }    

  Symbol type =NULL;
  tree_node *node =  symtable_o->lookup(as->get_name());

   //check type of ID
  if(typeid(node) == typeid(attr_class)) {
    type = ((attr_class*) node )->get_type_decl();
  }
  else if(typeid(node) == typeid(formal_class)) {
    type = ((formal_class*) node)->get_type_decl();
  }
  else if(typeid(node) == typeid(let_class)) {
    type = ((let_class*) node)->get_type_decl();
  }
  else if(typeid(node) == typeid(branch_class)) {
    type = ((branch_class*)node)->get_type_decl();
  }

  //cout<<"type is "<<type<<endl;

  this->visit(as->get_expr());
  Symbol type1 = as->get_expr()->get_type();

  //error is type1 >= type
  Symbol type_cur = type;
  Symbol type1_cur = type1;
  if(type_cur == SELF_TYPE) {
     type_cur = currentClass->get_name();
  }
  if(type1_cur == SELF_TYPE) {
    type1_cur = currentClass->get_name();
  } 

  if(!this->classTable->is_child(type1_cur,type_cur)) {
    classTable->semant_error(currentClass->get_filename(),as)
      << "Type of assigned expression is " << type1_cur->get_string()
      << " which does not conform to the declared type "
      << type->get_string() << " of " << as->get_name()->get_string()<< endl;
    as->set_type(Object);
    return;
  }
  as->set_type(type1_cur);
}

void semanVisitor::visit( static_dispatch_class *e )
{
    this->visit(e->get_expr());
    Expressions actual = e->get_actual();
    for(int i =actual->first(); actual->more(i); i=actual->next(i) ){
      Expression_class* ex = (Expression_class*) actual->nth(i);
      this->visit(ex);
    } 

    Symbol static_type = e->get_type_name();

    if(!classTable->method_exist(static_type, e->get_name())) {
      classTable->semant_error(currentClass->get_filename(), e)
        << "Cannot dispatch to undefined method "
        <<e->get_name()->get_string() << ". \n" << endl;
      e->set_type(Object);
      return;
    }

    Symbol type_caller = e->get_expr()->get_type();
    Symbol type_caller_cur = type_caller;
    if(type_caller_cur == SELF_TYPE) {
      type_caller_cur = this->currentClass->get_name();
    }

    if(!classTable->is_child(type_caller_cur, static_type)) {
      classTable->semant_error(currentClass->get_filename(),e)
        << "Expression type is " << type_caller_cur->get_string()
        << " which does not conform to the declared static type "
        << static_type->get_string() << ".\n" << endl;
      e->set_type(Object);
      return; 
    }

    std::vector<Symbol> sig = classTable->get_signature(static_type, e->get_name());
    if(sig.size()-1 != actual->len()) {
      classTable->semant_error(currentClass->get_filename(),e)
        << "Number of arguments is imcompatible of the called method "
        << e->get_name() << ".\n" << endl;
      e->set_type(Object);
      return;
    }

    for(int i=0; i<sig.size()-1; i++) {
      Symbol type_formal = sig[i];
      Symbol type_act = actual->nth(i)->get_type();

      Symbol type_act_cur = type_act;
      if(type_act == SELF_TYPE) {
        type_act_cur = currentClass->get_name();
      }
      if(!classTable->is_child(type_act_cur, type_formal)) {
        method_class* m = classTable->get_method(type_caller_cur, e->get_name());
        formal_class* f = (formal_class*) m->get_formals()->nth(i);

        classTable->semant_error(currentClass->get_filename(),e)
          << "Type of parameter " << f->get_name()
          << " in called method " << e->get_name()
          << " is " << type_act_cur->get_string()
          << " which does not conform to declared type "
          << f->get_type_decl() << ".\n" << endl;
        e->set_type(Object);
        return;
      }
    }

    Symbol return_type = sig[sig.size()-1];
    if(return_type == SELF_TYPE) {
      return_type = type_caller;
    }
    e->set_type(return_type);
}

void semanVisitor::visit( dispatch_class *e )
{
  this->visit(e->get_expr());
  Expressions actual = e->get_actual();
  for(int i =actual->first(); actual->more(i); i=actual->next(i) ){
    Expression_class* ex = (Expression_class*) actual->nth(i);
    this->visit(ex);
  } 

  Symbol type_caller = e->get_expr()->get_type();
  Symbol type_caller_cur = type_caller;
  if(type_caller_cur == SELF_TYPE) {
    type_caller_cur = this->currentClass->get_name();
  }

  if(!classTable->method_exist(type_caller_cur, e->get_name())) {
    classTable->semant_error(currentClass->get_filename(), e)
      << "Cannot dispatch to undefined method "
      <<e->get_name()->get_string() << ". \n" << endl;
    e->set_type(Object);
    return;
  }


  std::vector<Symbol> sig = classTable->get_signature(type_caller_cur, e->get_name());
  if(sig.size()-1 != actual->len()) {
    classTable->semant_error(currentClass->get_filename(),e)
      << "Number of arguments is imcompatible of the called method "
      << e->get_name() << ".\n" << endl;
    e->set_type(Object);
    return;
  }

  for(int i=0; i<sig.size()-1; i++) {
    Symbol type_formal = sig[i];
    Symbol type_act = actual->nth(i)->get_type();

    Symbol type_act_cur = type_act;
    if(type_act == SELF_TYPE) {
      type_act_cur = currentClass->get_name();
    }
    if(!classTable->is_child(type_act_cur, type_formal)) {
      method_class* m = classTable->get_method(type_caller_cur, e->get_name());
      formal_class* f = (formal_class*) m->get_formals()->nth(i);

      classTable->semant_error(currentClass->get_filename(),e)
        << "Type of parameter " << f->get_name()
        << " in called method " << e->get_name()
        << " is " << type_act_cur->get_string()
        << " which does not conform to declared type "
        << f->get_type_decl() << ".\n" << endl;
      e->set_type(Object);
      return;
    }
  }

  Symbol return_type = sig[sig.size()-1];
  if(return_type == SELF_TYPE) {
    return_type = type_caller;
  }
  e->set_type(return_type);
}

void semanVisitor::visit( cond_class *e )
{
  this->visit(e->get_pred());
  this->visit(e->get_then_exp());
  this->visit(e->get_else_exp());

  if(Bool != e->get_pred()->get_type()) {
    classTable->semant_error(currentClass->get_filename(),e)
      << "Type of \'if\' predication is not Bool.\n" << endl;
    e->set_type(Object);
    return;
  }
  else {
    Symbol type_then = e-> get_then_exp()->get_type();
    Symbol type_else = e-> get_else_exp()->get_type();

    if((type_then == SELF_TYPE) && (type_else == SELF_TYPE))  {
       e->set_type(SELF_TYPE);
       return;
    }
    else if(type_then == SELF_TYPE) {
      type_then = currentClass->get_name();
    }
    else if(type_else == SELF_TYPE) {
      type_else = currentClass->get_name();
    }

    Symbol lub = classTable->least_upper_bound(type_else, type_then);
    e->set_type(lub);
  }
}

void semanVisitor::visit( loop_class *e )
{
   this->visit(e->get_pred());
   this->visit(e->get_body());

   if(e->get_pred()->get_type() != Bool) {
     classTable->semant_error(currentClass->get_filename(),e) 
       << "Type of loop conditon is not Bool.\n" << endl;
     e->set_type(Object);
     return;
   }
   e->set_type(Object);
}

void semanVisitor::visit( typcase_class *e )
{
   this->visit(e->get_expr());
   Cases cases = e->get_cases();
   if(cases->len() == 0) {
     e->set_type(Object);
     return;
   }
   else {     
     for(int i =cases->first(); cases->more(i); i=cases->next(i) ){
       branch_class* ty = (branch_class*) cases->nth(i);
       this->visit(ty);
     }

     for(int j=0; j< cases->len(); j++) {
       for(int k =j+1; k < cases->len(); k++) {
          branch_class* bj = (branch_class*) cases->nth(j);
          branch_class* bk = (branch_class*) cases->nth(k);
          if(bj->get_type_decl() == bk->get_type_decl()) {
            classTable->semant_error(currentClass->get_filename(),bj)
              << "Branch " << bj->get_type_decl()->get_string()
              << " is duplicated in case statement.\n" << endl;
            e->set_type(Object);
            return;
          }
       }
   }
     Symbol type = ((branch_class*)cases->nth(0))->get_expr()->get_type();
     if(type == SELF_TYPE) {
       type = currentClass->get_name();
     }
     for(int i =cases->first(); cases->more(i); i=cases->next(i) ){
       branch_class* b = (branch_class*) cases->nth(i);

       Symbol type_b = b->get_expr()->get_type();
       if(type_b == SELF_TYPE)  type_b = currentClass->get_name();
        type = classTable->least_upper_bound(type, type_b);
     }

     bool all_self = true;
     for(int i =cases->first(); cases->more(i); i=cases->next(i) ){
       branch_class* b = (branch_class*) cases->nth(i);
       if(b->get_expr()->get_type() != SELF_TYPE) {
          all_self = false;   break;
       }
     } 
     if(all_self) e->set_type(SELF_TYPE);
     else e->set_type(type);
  }
}

void semanVisitor::visit( block_class *e )
{
   Expressions body = e->get_body();
   Symbol type = NULL;

   for(int i =body->first(); body->more(i); i=body->next(i) ){
     Expression_class* ex = (Expression_class*) body->nth(i); 
     cout<<"block visit start"<<endl;
     this->visit(ex);
     cout<<"block visit finish"<<endl;
     type = ex->get_type();
   }
   e->set_type(type);
}

void semanVisitor::visit( let_class *e )
{  
  Symbol type_id = e->get_type_decl();

   if(e->get_identifier() == self) {
      classTable->semant_error(currentClass->get_filename(), e)
        << "Cannot bind \'self in a \'let\' expression.\n" << endl;
      e->set_type(Object);
      return;
   }

   this->visit(e->get_init());

   if(type_id == SELF_TYPE) {
     type_id = currentClass->get_name();
   }
   if(typeid((e->get_init()))!=typeid(no_expr_class)) //TODO
   {
     type_id=e->get_init()->get_type();
     if(type_id != NULL && !classTable->is_child(type_id,e->get_type_decl())) 
     {
         classTable->semant_error(currentClass->get_filename(), e)
           << "Inferred type of initialization of " << e->get_identifier()->get_string()
           << " is " << type_id->get_string() 
           << " which does not conform to the declared type "
           << e->get_type_decl()->get_string() << endl;
         e->set_type(Object);
         return;
     }
   }
   // we need this enter and exit scope since not all "let" processing is 
   //invoked from let.accept(v) 
   enterscope();
   addId(e->get_identifier(), e, 0);
   this->visit(e->get_body());
   exitscope();
   e->set_type(e->get_body()->get_type());
}

void semanVisitor::visit( plus_class *e )
{
  this->visit(e->get_e1());
  this->visit(e->get_e2());

  Symbol type1 = e->get_e1()->get_type();
  Symbol type2 = e->get_e2()->get_type();

  if(type1 == Int && type2 == Int){
    e->set_type(Int);
    cout<<"plus finish"<<endl;

  }

  else {
    classTable->semant_error(currentClass->get_filename(),e) 
      << "Non-Int arguments for" << type1->get_string()
      << " + " << type2->get_string() << ".\n" << endl;
    e->set_type(Object);
    return;
  }
}

void semanVisitor::visit( sub_class *e )
{
  this->visit(e->get_e1());
  this->visit(e->get_e2());
  
  Symbol type1 = e->get_e1()->get_type();
  Symbol type2 = e->get_e2()->get_type();
  
  if(type1 == Int && type2 == Int)   e->set_type(Int);
  else {
    classTable->semant_error(currentClass->get_filename(),e) 
      << "Non-Int arguments for" << type1->get_string()
      << " - " << type2->get_string() << ".\n" << endl;
    e->set_type(Object);
    return;
  }
}

void semanVisitor::visit( mul_class *e )
{

  this->visit(e->get_e1());
  this->visit(e->get_e2());

  Symbol type1 = e->get_e1()->get_type();
  Symbol type2 = e->get_e2()->get_type();


  if(type1 == Int && type2 == Int)   e->set_type(Int);
  else {
    classTable->semant_error(currentClass->get_filename(),e) 
      << "Non-Int arguments for" << type1->get_string()
      << " * " << type2->get_string() << ".\n" << endl;
    e->set_type(Object);
    return;
  }
}

void semanVisitor::visit( divide_class *e )
{

  this->visit(e->get_e1());
  this->visit(e->get_e2());
  Symbol type1 = e->get_e1()->get_type();
  Symbol type2 = e->get_e2()->get_type();


  if(type1 == Int && type2 == Int)   e->set_type(Int);
  else {
    classTable->semant_error(currentClass->get_filename(),e) 
      << "Non-Int arguments for" << type1->get_string()
      << " / " << type2->get_string() << ".\n" << endl;
    e->set_type(Object);
    return;
  }
}

void semanVisitor::visit( neg_class *e )
{
  this->visit(e->get_e1());

  if(e->get_e1()->get_type()==Int)  e->set_type(Int);
  else {
    classTable->semant_error(currentClass->get_filename(),e)
      << "Argument has type " << e->get_e1()->get_type()->get_string()
      << ".\n" << endl;
    e->set_type(Object);
    return;
  }
}

void semanVisitor::visit( lt_class *e )
{

  this->visit(e->get_e1());
  this->visit(e->get_e2());
  Symbol type1 = e->get_e1()->get_type();
  Symbol type2 = e->get_e2()->get_type();


  if(type1 == Int && type2 == Int)   e->set_type(Bool);
  else {
    classTable->semant_error(currentClass->get_filename(),e) 
      << "Non-Int arguments for" << type1->get_string()
      << " < " << type2->get_string() << ".\n" << endl;
    e->set_type(Object);
    return;
  }
}

void semanVisitor::visit( eq_class *e )
{

  this->visit(e->get_e1());
  this->visit(e->get_e2());
  Symbol type1 = e->get_e1()->get_type();
  Symbol type2 = e->get_e2()->get_type();


  bool base_type1 = (type1 == Int)||(type1 == Bool)||(type1 == Str);
  bool base_type2 = (type2 == Int)||(type2 == Bool)||(type2 == Str);

  bool incompatible_base_type = (base_type1 && base_type2 && type1!=type2);
  bool not_all_base_type = (base_type1 != base_type2);

  if(incompatible_base_type || not_all_base_type) {
    classTable->semant_error(currentClass->get_filename(),e) 
      << "Illegal comparison with basic types" << endl;
    e->set_type(Object);
    return;
  }
  else e->set_type(Bool);
}

void semanVisitor::visit( leq_class *e )
{
  this->visit(e->get_e1());
  this->visit(e->get_e2());
  Symbol type1 = e->get_e1()->get_type();
  Symbol type2 = e->get_e2()->get_type();



  if(type1 == Int && type2 == Int)   e->set_type(Bool);
  else {
    classTable->semant_error(currentClass->get_filename(),e) 
      << "Non-Int arguments for" << type1->get_string()
      << " <= " << type2->get_string() << ".\n" << endl;
    e->set_type(Object);
    return;
  }
}

void semanVisitor::visit( comp_class *e )
{
  this->visit(e->get_e1());

  if(e->get_e1()->get_type()==Bool)  e->set_type(Bool);
  else {
    classTable->semant_error(currentClass->get_filename(),e)
      << "Argument has type " << e->get_e1()->get_type()->get_string()
      << ".\n" << endl;
    e->set_type(Object);
    return;
  }
}

void semanVisitor::visit( int_const_class *e )
{
  inttable.add_int(atoi(e->get_token()->get_string()));
  e->set_type(Int);
}

void semanVisitor::visit( bool_const_class *e )
{
  e->set_type(Bool);
}

void semanVisitor::visit( string_const_class *e )
{
  stringtable.add_string(e->get_token()->get_string());
  e->set_type(Str);
}

void semanVisitor::visit( new__class *e )
{  
   Symbol type = e->get_type_name();

   if(e->get_type_name() != SELF_TYPE && 
     !classTable->class_exist(type)) {
       classTable->semant_error(currentClass->get_filename(),e)
         << "Cannot use \'new\' with undefined class "
         << type->get_string()
         <<".\n" << endl;
       e->set_type(Object);
       return;
   }

   if(type == SELF_TYPE)    e->set_type(SELF_TYPE);
   else e->set_type(type);
}

void semanVisitor::visit( isvoid_class *e )
{
   this->visit(e->get_e1());
   e->set_type(Bool);
}

void semanVisitor::visit( no_expr_class *e )
{
   // do nothing
}

void semanVisitor::visit( object_class *e )
{ 
  Symbol type = NULL;

  if(e->get_name() == self)   {e->set_type(SELF_TYPE); return;}
  if(symtable_o->lookup(e->get_name())==NULL) {
    classTable->semant_error(currentClass->get_filename(),e)
      << "Undeclared identifier" << e->get_name()->get_string()
      <<".\n" << endl;
    e->set_type(Object);
    return;
  }
 
  tree_node* node = symtable_o->lookup(e->get_name());
  if(typeid(node) == typeid(attr_class)) {
    type = ((attr_class*) node)->get_type_decl();
  }
  else if(typeid(node) == typeid(formal_class)) {
    type = ((formal_class*) node)->get_type_decl();
  }
  else if(typeid(node) == typeid(let_class)) {
    type = ((let_class*) node)->get_type_decl();
  }
  else if(typeid(node) == typeid(branch_class)) {
    type = ((branch_class*) node)->get_type_decl();
  }
  e->set_type(type);
}

/**************************************************************/
/*                   Accept function                          */
/**************************************************************/

void program_class::accept(Visitor *v) {
	v->enterscope();
	v->visit(this);
	for(int i =classes->first(); classes->more(i); i=classes->next(i)) {
		class__class* cl = (class__class*)classes->nth(i);
				cl->accept(v);
	}
	v->exitscope();
}

void class__class::accept(Visitor *v) {
	v->enterscope();
	semanVisitor* sv = (semanVisitor*) v;
	if( parent != No_class) {
		// how to print out symbol table?
		class__class* parentClass__class = sv->classTable->get_parent(this->get_name());
		if(parentClass__class != NULL) 
    {
			parentClass__class->add_parentMembers(v, parent_feature_list);
		}
		 //how to print out symbol table?
	}

	v->visit(this);
      cout << "correct after visit this " << this->get_name()<< endl;
      cout << "feature length "<<features->len() << endl;
	for (int i=0; i < features->len(); i++) {
		Feature ft = (Feature) features->nth(i);
    if(ft->get_is_method())
    {   
      cout << "is method " << endl;
			method_class* mt = (method_class*) ft;
     /* Feature f = (Feature)sv->probeMethod(mt->get_name())  ;    
			if( !f->get_is_method() )*/
      {
				sv->addId(mt->get_name(), mt, 1);
        cout<< "!!!!!!!!!!!!!!!!!!!!!!!!add method " << mt->get_name()<<endl; 
      }
		}
    else if(!(ft->get_is_method()) )
    {     
      cout << "is object " << endl;
			attr_class* at = (attr_class*) ft;
      /*Feature f = (Feature)sv->probeMethod(at->get_name())   ;
			if( f->get_is_method() )*/
      {
					sv->addId(at->get_name(), at, 0); 
          cout<< "add object@@@@@@@@@@@@@@@@@ " <<at->get_name()<< endl; 
      }
		}
	}
     cout<< "parent feature list length: "<<parent_feature_list->len()<< endl;
	for(int i=0; i < parent_feature_list->len(); i++) 
  {
		Feature ft = (Feature) features->nth(i);
    if(ft->get_is_method())
    {
			method_class* mt = (method_class*) ft;
			//if(typeid((sv->probeMethod(mt->get_name())))!=typeid(method_class))
				sv->addId(mt->get_name(), mt, 1);
		}
    else if (!(ft->get_is_method()))
    {
			attr_class* at = (attr_class*) ft;
			//if(typeid((sv->probeObject(at->get_name())))!=typeid(attr_class))
				sv->addId(at->get_name(), at, 0);
		}
	}

	for(int i=0; i < features->len(); i++) {
		Feature ft = (Feature) features->nth(i);
		if (ft->get_is_method()){
			method_class* mt = (method_class*) ft;
      cout<<"correct before get is method"<<endl;
			mt->accept(v);  cout<<"correct after get is method"<<endl;
		}
		else if (!(ft->get_is_method())){
			attr_class *at = (attr_class*) ft;
      cout<<"correct before get is attr"<<endl;
			at->accept(v); cout <<"correct after get is attr " << endl; 
		}
	}   cout<< "before exit scope" << endl;
	v->exitscope();  cout<< " exit scope" << endl;
}


void class__class::add_parentMembers(Visitor *v, Features parent_feature_list) 
{
  
  semanVisitor* sv = (semanVisitor*) v;
  cout<<"adding parent members for "<<this->get_name()<<endl;
  cout<<features->len()<<endl;
  for(int i=0; i < features->len(); i++) 
  {
    Feature ft = (Feature) features->nth(i);
    if (ft->get_is_method())
    {
      method_class* mt = (method_class*) ft;
      parent_feature_list = append_Features(single_Features(mt), parent_feature_list);
    }
    else if (!(ft->get_is_method()))
    {
      attr_class* at = (attr_class*) ft;
      parent_feature_list = append_Features(single_Features(at), parent_feature_list);
    }
    cout<<parent_feature_list->len()<<endl;
    for(int i = parent_feature_list->first(); parent_feature_list->more(i); i = parent_feature_list->next(i))
      cout<<i<<endl;
      /*if (features->nth(i)->get_is_method())
        method_class *m =(method_class *)features->nth(i)->get_is_method();*/
      

  }
  if(parent != No_class) {
   // cout<<"adding parent members for in class"<<sv->classTable->get_parent(this->get_name())->get_name()<<endl;
    class__class* parentClass__class  = sv->classTable->get_parent(this->get_name());
    // printf something?
    parentClass__class->add_parentMembers(v, parent_feature_list);
  }
}

void method_class::accept(Visitor *v) {
  v->enterscope();  cout << "before visit " << this->get_name() << endl;
  v->visit(this);
   cout << "after visit " << this->get_name() << endl;
  for(int i =formals->first(); formals->more(i); i=formals->next(i)) {
    formal_class* fm = (formal_class*)formals->nth(i);
    fm->accept(v);   
  }
  v->exitscope();
}

void attr_class::accept(Visitor *v) {
  v->enterscope();
  v->visit(this);
  v->exitscope();
}

void formal_class::accept(Visitor *v) {
  v->visit(this);
}

void Expression_class::accept( Visitor *v )
{
  v->enterscope();
  v->visit(this);                 
  v->exitscope();
}
void branch_class::accept(Visitor *v) {
  v->enterscope();
  v->visit(this);
  expr->accept(v);
  v->exitscope();
}

void assign_class::accept(Visitor *v) {
  v->enterscope();
  v->visit(this);
  expr->accept(v);
  v->exitscope();
}

void static_dispatch_class::accept(Visitor *v) {
  v->enterscope();

  expr->accept(v);
  v->visit(this);
  for(int i =actual->first(); actual->more(i); i=actual->next(i)) {
    Expression_class* ac = (Expression_class*)actual->nth(i);
    ac->accept(v);   
  }
  v->exitscope();
}

void dispatch_class::accept(Visitor *v) {
  v->enterscope();

  expr->accept(v);
  v->visit(this);
  for(int i =actual->first(); actual->more(i); i=actual->next(i)) {
    Expression_class* ac = (Expression_class*)actual->nth(i);
    ac->accept(v);   
  }
  v->exitscope();
}

void cond_class::accept(Visitor *v) {
  v->enterscope();
  v->visit(this);
  pred->accept(v);
  then_exp->accept(v);
  else_exp->accept(v);
  v->exitscope();
}

void loop_class ::accept(Visitor *v) {
  v->visit(this);
}

void typcase_class::accept(Visitor *v) {
  v->enterscope();
  v->visit(this);
  expr->accept(v);

  for(int i =cases->first(); cases->more(i); i=cases->next(i)) {
    branch_class* cs = (branch_class*)cases->nth(i);
    cs->accept(v);   
  }
  v->exitscope();
}

void block_class::accept(Visitor *v) {
  v->enterscope();
  v->visit(this);
  v->exitscope();
}

void let_class::accept(Visitor *v) {
  v->enterscope();
  v->visit(this);
  v->exitscope();
}

void plus_class::accept(Visitor *v) {
  v->enterscope();
  v->visit(this);
  e1->accept(v);
  e2->accept(v);
  v->exitscope();
}

void sub_class::accept(Visitor *v) {
  v->enterscope();
  v->visit(this);
  e1->accept(v);
  e2->accept(v);
  v->exitscope();
}

void mul_class::accept(Visitor *v) {
  v->enterscope();
  v->visit(this);
  e1->accept(v);
  e2->accept(v);
  v->exitscope();
}

void divide_class::accept(Visitor *v) {
  v->enterscope();
  v->visit(this);
  e1->accept(v);
  e2->accept(v);
  v->exitscope();
}

void neg_class::accept(Visitor *v) {
  v->enterscope();
  v->visit(this);
  e1->accept(v);
  v->exitscope();
}

void lt_class::accept(Visitor *v) {
  v->enterscope();
  v->visit(this);
  e1->accept(v);
  e2->accept(v);
  v->exitscope();
}

void eq_class::accept(Visitor *v) {
  v->enterscope();
  v->visit(this);
  e1->accept(v);
  e2->accept(v);
  v->exitscope();
}

void leq_class::accept(Visitor *v) {
  v->enterscope();
  v->visit(this);
  e1->accept(v);
  e2->accept(v);
  v->exitscope();
}

void comp_class::accept(Visitor *v) {
  v->enterscope();
  v->visit(this);
  e1->accept(v);
  v->exitscope();
}

void int_const_class::accept(Visitor *v) {
  v->enterscope();
  v->visit(this);
  v->exitscope();
}

void bool_const_class::accept(Visitor *v) {
  v->enterscope();
  v->visit(this);
  v->exitscope();
}

void string_const_class::accept(Visitor *v) {
  v->enterscope();
  v->visit(this);
  v->exitscope();
}

void new__class::accept(Visitor *v) {
  v->enterscope();
  v->visit(this);
  v->exitscope();
}

void isvoid_class::accept(Visitor *v) {
  v->enterscope();
  v->visit(this);
  e1->accept(v);
  v->exitscope();
}

void no_expr_class::accept(Visitor *v) {
  v->enterscope();
  v->visit(this);
  v->exitscope();
}

void object_class::accept(Visitor *v) {
  v->enterscope();
  v->visit(this);
  v->exitscope();
}
