#include <assert.h>
#include <stdio.h>
#include "emit.h"
#include "cool-tree.h"
#include "symtab.h"
#include <map>
#include <stack>
#include <vector>

enum Basicness     {Basic, NotBasic};
#define TRUE 1
#define FALSE 0

class CgenClassTable;
typedef CgenClassTable *CgenClassTableP;

class CgenNode;
typedef CgenNode *CgenNodeP;

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
   void set_class_tag();

public:
   CgenClassTable(Classes, ostream& str);
   void code();
   CgenNodeP root();
   void print_inheritance_tree();
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
            CgenClassTableP class_table, int tag_);

   void add_child(CgenNodeP child);
   std::vector<CgenNodeP> get_children() { return children; }
   void set_parentnd(CgenNodeP p);
   CgenNodeP get_parentnd() { return parentnd; }
   int basic() { return (basic_status == Basic); }
   int get_tag() {return tag;}
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

