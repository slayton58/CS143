#include <assert.h>
#include <stdio.h>
#include "emit.h"
#include "cool-tree.h"
#include "symtab.h"
#include <map>
#include <stack>
#include <vector>
#include <string>

enum Basicness     {Basic, NotBasic};
#define TRUE 1
#define FALSE 0

class CgenClassTable;
typedef CgenClassTable *CgenClassTableP;

class CgenNode;
typedef CgenNode *CgenNodeP;
class method_sign
{
public:
  Symbol class_name;
  method_class* method_name;
  method_sign(Symbol c, method_class* m) {
    class_name = c;
    method_name = m;
  }
};



//maps the class name (a symbol) to its CgenNode
class CgenClassTable : public SymbolTable<Symbol,CgenNode> {
private:
   std::vector<CgenNodeP> nds; //this is the meat: a list of nodes
   ostream& str;
   int stringclasstag;
   int intclasstag;
   int boolclasstag;
   int cur_tag;


// The following methods emit code for
// constants and global declarations.

   void code_global_data();
   void code_global_text();
   void code_bools(int);
   void code_select_gc();
   void code_constants();
   void code_class_nameTab();
   void code_class_objTab();
   void code_dispatch_table();
   void code_prototype_objects();
   void code_init();

// The following creates an inheritance graph from
// a list of classes.  The graph is implemented as
// a tree of `CgenNode', and class names are placed
// in the base class symbol table.

   void install_basic_classes();
   void install_class(CgenNodeP nd);
   void install_classes(Classes cs);
   void build_inheritance_tree();
   void set_relations(CgenNodeP nd);
   void build_features_map();
   void set_tags();

public:
   Environment* env;
   CgenClassTable(Classes, ostream& str, Environment* env);
   void code();
   CgenNodeP root();
   void print_inheritance_tree();
   int get_attr_ofs(Symbol, Symbol);
   int get_method_ofs(Symbol, Symbol);
   CgenNodeP get_node_by_name (Symbol);
};

// Each class corresponds to a CgenNode, records the children, the parent
class CgenNode : public class__class 
{
 private: 
   CgenNodeP parentnd;                        // Parent of class
   Basicness basic_status;                    // `Basic' if class is basic
                                             // `NotBasic' otherwise
   int tag;                                   // tag for the class(unique number)
   
public:

  std::vector<CgenNodeP> children;                  // Children of class 
  CgenNode(Class_ c,
            Basicness bstatus,
            CgenClassTableP class_table);

  /** mapping for class attributes */
  std::vector<attr_class*> attr_list;

  /** mapping for class methods */
  std::vector<method_sign*> method_list;

   void add_child(CgenNodeP child);
   void set_parentnd(CgenNodeP p);
   CgenNodeP get_parentnd() { return parentnd; }
   int basic() { return (basic_status == Basic); }
   int get_tag() {return tag;}
   void set_tag(int t) {tag = t;}
};

class BoolConst 
{
 private: 
  int val;
 public:
  BoolConst(int);
  void code_def(ostream&, int boolclasstag);
  void code_ref(ostream&) const;
};

class Environment
{
private:
  int label_cnt;
public:
  class__class* cur_class;
  CgenClassTable* cgen_table;
  SymbolTable<Symbol, std::string> sym_table;
  int cur_exp_oft;
  ostream& str;

  Environment(Classes classes, ostream & s ):str(s)
  {
    cur_class = NULL;
    cgen_table = new CgenClassTable(classes, s, this);
    label_cnt = 0;
  }

  int get_label_cnt()
  {
    return label_cnt++;
  }

};
