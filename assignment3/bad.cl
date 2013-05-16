class A {
   call() : Bool { true };

   -- Error : Formal parameter x cannot have type SELF_TYPE.
   talk(x:SELF_TYPE) : Bool { false };

   -- Error : Attribute x is multiply defined in class.
   x : A;
   x : B;

   -- Test : method and attribute sharing the same name
   x() : Bool { false };

   y : Int;
   z : Bool;

   -- Error : Method a is multiply defined.
   a() : Int { 0 };
   a() : Bool { false };

   b() : Int { 2 };
   c(xx:Int) : Int { xx + 3 };
   d(xx:Int) : Int { 5 };
   e(x:Int, y:Int) : Int { 6 };
   f(x:Int, y:Int, z:Int) : Int { 7 };
};

(*
   -- Error : Class A was previously defined.
class A { };


   -- Error : Redefinition of basic class Object.
class Object {
};

*)
class B inherits A{
   varA : A;

   -- Error : Attribute y is an attribute of an inherited class.
   y : Int;
   -- Error : Attribute y is an attribute of an inherited class.
   y : Int;

   -- Error : In redefined method x, return type Int is different from original return type Bool.
   x() : Int { 1 };

   -- Test : use attribute of the parent
   w : Bool <- z;

   -- Test : redefined inherited method
   b() : Int { 22 };

   -- Error : In redefined method c, parameter type Bool is different from original type Int
   c(yy:Bool) : Int { 33 };

   -- Error : In redefined method d, return type Bool is different from original return type Int.
   -- Error : Inferred return type Int of method d does not conform to declared return type Bool.
   d(xx:Bool) : Bool { 6 };

   -- Error : Incompatible number of formal parameters in redefined method e.
   e(x:Bool) : Int { 7 };

   -- Error : In redefined method f, parameter type Bool is different from original type Int 
   f(x:Bool, y:Int, z:String) : Int { 8 };

   -- Error : Formal parameter x is multiply defined.
   -- Error : Formal parameter xx is multiply defined.
   ff(x:Int, x:Bool, xx:Bool, xx:Bool) : Int { 8 };

   -- Test : formals can share the same name with attribute
   fff(varA : A) : Bool { true };

   test() : Bool { varA.call() };
};

(*
-- Error : redefinition of basic class
class IO {};
*)

(*
-- Error : cycle in inheritance graph
class D inherits DDD { };
class DD inherits D { };
class DDD inherits DD { };

class E inherits EEE { };
class EE inherits E { };
class EEE inherits EE { };


-- Error : class re-definition
class F {};
class F {};


-- Error : inherit from basic classes
class InheritBasic1 inherits IO { };
class InheritBasic2 inherits Int { };
class InheritBasic3 inherits Bool { };
class InheritBasic4 inherits String { };
*)

class BadComparison {
    test() : Bool {
      {
          -- Error : bad comparison
          1 <= "2";
          true;
      }
    };
};

class UndefinedAttributeType {
    -- Error : undefined attribute type ...
    var : NotPossibleToHaveThisTypeName;
};

class UndefinedFormalType {
    -- Error : undefined formal type ...
    test(var:NotPossibleToHaveThisTypeName) : Bool { false };
};

class InvalidSelf {
    -- Error : self cannot be attribute
    self : A;
    test() : Bool {
        {
            -- Error : assignment to self
            self <- new InvalidSelf;
            true;
        }
    };
};

class AttributeRedef { x : Int; };
-- Error : Attribute x redefined
class AttributeRedef1 inherits AttributeRedef { x : Int; };

class AttributeConflict {
    x : Int;
    -- Error : attribute multiply defined
    x : Int;
    x : String;
};

class MethodConflict {
    y() : Int { 1 };
    -- Error : method y multiply defined
    y() : Bool { true };
};

class InheritMethodCompatible {
    call1(x : Int) : Bool { true };
    call2(x : Int) : Bool { true };
    call3(x : Int) : Bool { true };
};
class InheritMethodCompatible1 inherits InheritMethodCompatible {
    -- Error : return type not compatible
    call1(x : Int) : String { "true" };
    -- Error : formal parameter type not compatible
    call2(x : IO) : Bool { true };
    -- Error : formal list length not compatible
    call3(x : Int, y : IO) : Bool { true };
};

class FormalParamMultipleDefine {
    -- Error : Formal x is multiply defined
    m(x : Int, x : String) : Int { 0 };
};

class ForMethodReturnNotComp1 {};
class ForMethodReturnNotComp2 inherits ForMethodReturnNotComp1 {};
class MethodReturnNotCompatible {
    -- Error : return type not compatible
    m1() : SELF_TYPE { new MethodReturnNotCompatible };
    -- Error : return type not compatible
    m2() : ForMethodReturnNotComp2 { new ForMethodReturnNotComp1 };
};

class AttrTypeUndefined {
    -- Error : attribute type ... not defined
    var : NotPossibleToHaveThisTypeName;
    -- Error : init not type compatible
    var1 : Int <- new IO;
};

class FormalTypeUndefined {
    -- Error : formal type ... not defined
    m(x:NotPossibleToHaveThisTypeName) : Bool { true };
};

class CaseBranchWithSELF {
    var : Int;
    m() : Bool {
        {
            case var of
            b1 : Object => b1;
            -- Error : case branch with SELF_TYPE
            b2 : SELF_TYPE => b2;
            esac;
            true;
        }
    };
};


class C {
	a : Int;
	b : Bool;
	init(x : Int, y : Bool) : C {
           {
		a <- x;
		b <- y;
        -- Error : assignment to undeclared identifier c
		c <- x;
		self;
           }
	};
};

Class Main {
	main():C {
	 {
      -- Error : wrong actual parameter type
	  (new C).init(1,1);
      -- Error : wrong number of parameters
	  (new C).init(1,true,3);
	  (new C).iinit(1,true);
	  (new C);
	 }
	};
};
