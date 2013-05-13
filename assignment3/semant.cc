

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "semant.h"
#include "utilities.h"
#include "typeinfo"


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

    /* Fill this in */

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
	try {
	     ClassTable *classTable = new ClassTable(classes);
	     OcurredExpection = false;
	     sv = new semanVisitor(classTable);
	     this->accept(sv);

	     if(classTable->errors()) {
	    	 cerr << "compilation halted due to static semantic errors." << endl;
	         throw 20;
	     }
	}
	catch (int e){
		OcurredExpection = true;
	}
	if(OcurredExpection) {
		cerr << "compilation halted due to static semantic errors." << endl;
		exit(1);
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
	if (typeid(*e)==typeid(assign_class)) {
		assign_class* node=(assign_class *) (e);
		visit(node);
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
	else if(typeid(e) == typeid(sub_class)) {
		sub_class* node = (sub_class*) e;
		visit(node);
	}
	else if(typeid(e) == typeid(mul_class)) {
		mul_class* node = (mul_class*) e;
		visit(node);
	}
	else if(typeid(e) == typeid(divide_class)) {
		divide_class* node = (divide_class*) e;
		visit(node);
	}
	else if(typeid(e) == typeid(neg_class)) {
		neg_class* node = (neg_class*) e;
		visit(node);
	}
	else if(typeid(e) == typeid(lt_class)) {
		lt_class* node = (lt_class*) e;
		visit(node);
	}
	else if( typeid(e) == typeid(eq_class)) {
		eq_class* node = (eq_class*) e;
		visit(node);
	}
	else if(typeid(e) == typeid(leq_class)) {
		leq_class* node = (leq_class*) e;
		visit(node);
	}
	else if(typeid(e) == typeid(comp_class)) {
		comp_class* node = (comp_class*) e;
		visit(node);
	}
	else if(typeid(e) == typeid(int_const_class)) {
		int_const_class* node = (int_const_class*) e;
		visit(node);
	}
	else if(typeid(e)== typeid(bool_const_class)){
		bool_const_class* node = (bool_const_class*) e;
		visit(node);
	}
	else if(typeid(e) == typeid(string_const_class)) {
		string_const_class* node = (string_const_class*) e;
		visit(node);
	}
	else if(typeid(e)== typeid(new__class)) {
		new__class* node = (new__class*) e;
		visit(node);
	}
	else if(typeid(e)== typeid(isvoid_class)) {
		isvoid_class* node = (isvoid_class*) e;
		visit(node);
	}
	else if(typeid(e)== typeid(no_expr_class)) {
		no_expr_class* node = (no_expr_class*) e;
		visit(node);
	}
	else if(typeid(e) == typeid(object_class)) {
		object_class* node = (object_class*) e;
		visit(node);
	}
}

void semanVisitor::visit(program_class* prg) {
	Classes classes = prg->getClasses();
	for(int i =classes->first(); classes->more(i); i=classes->next(i) ){
		class__class* cl = (class__class*) classes->nth(i);
	}  // shall I use next(i) or just i?
}

void semanVisitor::visit(class__class* cl) {
	currentClass = cl;
	Features features = cl->getFeatures();
	Features parent_feature_list = cl->parent_feature_list;

	for(int i=0; i < features->len(); i++) {
		Feature ft1 = (Feature) features->nth(i);
		bool conflictWithParents = false;

		for(int j=0; j < parent_feature_list->len(); j++) {
			Feature ft2 = (Feature) parent_feature_list->nth(j);
			if(typeid(*ft1)==typeid(attr_class) && typeid(*ft2)==typeid(attr_class) //do I need * ?
				&& (((attr_class*)ft1)->getName()->get_string() == ((attr_class*)ft2)->getName()->get_string())){
				conflictWithParents = true;

				classTable->semant_error(currentClass->get_filename(), ft1); //how about the error information?
				break;
			}
			else if(typeid(*ft1)==typeid(method_class) && typeid(*ft2)==typeid(method_class)
					&& ((method_class*)ft1)->getName()->get_string() == ((method_class*)ft2)->getName()->get_string()){
				method_class* mt1 =((method_class*)ft1);
				method_class* mt2 =((method_class*)ft2);

				//check return_type
				if(mt1->getReturn_type()->get_string()!=mt2->getReturn_type()->get_string()){
					classTable->semant_error(currentClass->get_filename(), ft1);
					break;
				}

				bool sameFormalsLength = false;
				Formals fms1 = mt1->getFormals();
				Formals fms2 = mt2->getFormals();
				if(fms1->len() == fms2->len()) {
					sameFormalsLength = true;
				}
				else {
					classTable->semant_error(currentClass->get_filename(), ft1);
				}

				//check formal type
				if(sameFormalsLength ) {
					for(int i =0; i< fms1->len(); i++) {
						formal_class* fm1 = (formal_class*)fms1->nth(i);
						formal_class* fm2 = (formal_class*)fms2->nth(i);

						if(fm1->getType_decl()->get_string() != fm2->getType_decl()->get_string()) {
							classTable->semant_error(currentClass->get_filename(), ft1);
						    break;
						}
					}
				}
			}
		}
		if(conflictWithParents == false) {
		    //	check feature defined conflicts within the current class
			for(int k=0; k< i; k++) {
				Feature ft3 = (Feature) features->nth(k);

				if(typeid(*ft1)==typeid(attr_class) && typeid(*ft3)==typeid(attr_class)
						&& ((attr_class*)ft1)->getName()->get_string()== ((attr_class*)ft3)->getName()->get_string()) {
					classTable->semant_error(currentClass->get_filename(), ft1);
					break;
				}
				else if(typeid(*ft1)==typeid(method_class) && typeid(*ft3)==typeid(method_class)
						&& ((method_class*)ft1)->getName()->get_string()== ((method_class*)ft3)->getName()->get_string()) {
					classTable->semant_error(currentClass->get_filename(), ft1);
					break;
				}
			}
		}
	}
}

/*void program_class::semant() {
	try {
	     ClassTable classTable = new ClassTable(classes);
	     OcurredExpection = false;
	     sv = new semanVisitor(classTable);
	     this->accept(&sv);

	     if(classTable.errors()) {
	    	 cerr << "compilation halted due to static semantic errors." << endl;
	         throw 20;
	     }
	}
	catch (int e){
		OcurredExpection = true;
	}
	if(OcurredExpection) {
		cerr << "compilation halted due to static semantic errors." << endl;
	}

}*/

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

	//parent_feature_list = new Features();
	if( parent != No_class) {
		//class__class* parentClass__class = sv.classTable->getParent(this->getName());
	}

	v->visit(this);
	v->exitscope();
}
