--redefinination
class X { };
class X { };
class Object {};
class Int {};
class Bool {};
class String {};
class IO {};

--cycle in inheritance map
class D1 inherits D2 { };
class D2 inherits D3 { };
class D3 inherits D4 { };
class D3 inherits D1 { };

--inherits from basic class
class C1 inherits IO { };
class C2 inherits Int { };
class C3 inherits Bool { };
class C4 inherits String { };

class AttributeRedef { x : Int; };
class AttributeRedef1 inherits AttributeRedef { x : Int; };
class AttributeConflict {x : Int; x : String;};

class ForMethodReturnNotComp1 {};
class ForMethodReturnNotComp2 inherits ForMethodReturnNotComp1 {};

class InheritMethodCompatible {
    call1(x : Int) : Bool { true };
    call2(x : Int) : Bool { true };
    call3(x : Int) : Bool { true };
};

class InheritMethodCompatible1 inherits InheritMethodCompatible {
    call1(x : Int) : String { "true" };
    call2(x : IO) : Bool { true };
    call3(x : Int, y : IO) : Bool { true };
};

class A {
   x : A;
   x : B;

   a() : Bool { true };
   a() : Int { 2 };
   b() : Int { 2 };
   c(xx:Int) : Int { xx + 3 };
   d(xx:Int) : Int { 5 };
   e(x:Int, y:Int) : Int { 6 };
   f(x:Int, y:Int, z:Int) : Int { 7 };
};

class B inherits A{
   varA : A;
   y : Int;
   y : Int;
   w : Bool <- z;

   a() : Int { 1 };
   b() : Int { 22 };
   c(yy:Bool) : Int { 33 };
   d(xx:Bool) : Bool { 6 };
   e(x:Bool) : Int { 7 };
   f(x:Bool, y:Int, z:String) : Int { 8 };
   g(x:Int, x:Bool, xx:Bool, xx:Bool) : Int { 8 };
   h(varA : A) : Bool { true };
};

class C {
	a : Int;
	b : Bool;
	init(x : Int, y : Bool) : C {
           {
		a <- x;
		b <- y;
		c <- x;
		self;
           }
	};
};


class BadComparison {
    test() : Bool {
      {
          1 <= "2";
          true;
      }
    };
};

class UndefinedAttribute {
    var : NotPossibleToHaveThisTypeName;
};

class UndefinedFormal {
    test(var:NotPossibleToHaveThisTypeName) : Bool { false };
};

class InvalidSelf {
    self : A;
    test() : Bool {
        {
            self <- new InvalidSelf;
            true;
        }
    };
};

class MethodConflict {
    y() : Int { 1 };
    -- Error : method y multiply defined
    y() : Bool { true };
};

class FormalParamMultipleDefine {
    -- Error : Formal x is multiply defined
    m(x : Int, x : String) : Int { 0 };
};

class MethodReturnNotCompatible {
    m1() : SELF_TYPE { new MethodReturnNotCompatible };
    m2() : ForMethodReturnNotComp2 { new ForMethodReturnNotComp1 };
};

class AttrTypeUndefined {
    var : NotPossibleToHaveThisTypeName;
    var1 : Int <- new IO;
};

class FormalTypeUndefined {
    m(x:NotPossibleToHaveThisTypeName) : Bool { true };
};

class CaseBranchWithSELF {
    var : Int;
    m() : Bool {
        {
            case var of
            b1 : Object => b1;
            b2 : SELF_TYPE => b2;
            esac;
            true;
        }
    };
};



-- Wrong actual parameters     
Class Main {
	main():C {
	 {
	  (new C).init(1,1);
	  (new C).init(1,true,3);
	  (new C).iinit(1,true);
	  (new C);
	 }
	};
};
