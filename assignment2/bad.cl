
(* no error *)
class A {
};

(* error:  b is not a type identifier *)
Class b inherits A {
};

(* error:  a is not a type identifier *)
Class C inherits a {
};

(* error:  keyword inherits is misspelled *)
Class D inherts A {
};

(* error:  closing brace is missing *)
Class E inherits A {
;

(* error:  int is not a type id *)
class F {
    a : int;
	b : Int;
    c : Bool;
};


(* error:  error propagation in let *)
class H {
    testLet() : Bool {
        {
            let a:Int <- 1, b:aouble in let c:Int in a + b + c;
        }
    };
};

(* error:  error in block, should recover *)
class I {
    testBlockRecover() : Bool {
        {
            (* this is an error *)
            a = b = c;
            (* then this is valid, we should recover *)
            a = b;
            b = c;
			c = d;
            let d:int in d*~2;
        }
    };
};


(* error:  comparisons are non-associative *)
class G {
    testNonAssoc() : Bool {
        {
            a = b = c;
            a < b < 3;
			a > b = c;
            a = b;
        }
    };
};

