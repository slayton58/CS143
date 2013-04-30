(*
 *  execute "coolc bad.cl" to see the error messages that the coolc parser
 *  generates
 *
 *  execute "parsetest < bad.cl" to see the error messages that your parser
 *  generates
 *)

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
    mint : int;
    mbool : Bool;
};

(* error:  comparisons are non-associative *)
class G {
    testNonAssoc() : Bool {
        {
            a = b = c;
            a < b < 3;
            a <= b = c <= d;
            -- this is valid
            a = b;
        }
    };
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
            let d:int in d*~2;
        }
    };
};


(* below are some example codes, we randomly break somewhere and check *)

(*
 *  A contribution from Anne Sheets (sheets@cory)
 *
 *  Tests the arithmetic operations and various other things
 *)

class A {

   var : Int <- 0;

   value() : Int { var };

   set_var(num : Int) : SELF_TYPE {
      {
         var <- num;
         self;
      }
   };

   method1(num : Int) : SELF_TYPE {  -- same
      self
   };

   (* error:  bad formal list *)
   method2(num1 : Int, num2 : ) : B {  -- plus
      (let x : Int
	 {
            x <- num1 + num2;
	    (new B).set_var(x);
	 }
      )
   };

   method3(num : Int) : C {  -- negate
      (let x : Int in
	 {
            x <- ~num;
            (* error:  bad expression in block *)
            a = b = c;
	    (new C).set_var(x);
	 }
      )
   };

   (* error:  bad formal list *)
   method4(num1 : Int, num2 : Int) : D {  -- diff
            if num2 < num1 then
               (let x : Int in
		  {
                     x <- num1 - num2;
                     x = y = z;
                     (* error:  bad dispatch expression *)
	             (new D).set_var(x : Int);
	          }
               )
            else
               (let x : Int in
		  {
	             x <- num2 - num1;
	             (new D).set_var(x);
		  }
               )
            fi
   };

   method5(num : Int) : E {  -- factorial
       (* not error: a long integer, not error by parser's standard *)
      (let x : Int <- 12345678901234567890123456789012345678901234567890 in
	 {
	    (let y : Int <- 1 in
	       while y <= num loop
	          {
                  (* error:  bad expression *)
                     x <- x ** y;
	             y <- y + 1;
	          }
	       pool
	    );
	    (new E).set_var(x);
	 }
      )
   };

};

(* error: missing parent class in class decalaration *)
class B inherits {  -- B is a number squared

   method5(num : Int) : E { -- square
      (let x : Int in
	 {
            x <- num * num;
        (* error: bad dispatch format *)
	    (new E).set_var(x);
	 }
     )
   };

};

(* error: wrong type identifier, c should be upper case *)
class c inherits B {

   method6(num : Int) : A { -- negate
      (let x : Int in
         {
            x <- ~num;
            (* error: non-assoc, to illustrate error recovery from last error *)
            a = b = c;
	    (new A).set_var(x);
         }
      )
   };

   method5(num : Int) : E {  -- cube
      (let x : Int in
	 {
            x <- num * num * num;
	    (new E).set_var(x);
	 }
      )
   };
};

class D inherits B {  
		
   method7(num : Int) : Bool {  -- divisible by 3
      (let x : Int <- num in
            (* error: extra "if" at beginning *)
            if if x < 0 then method7(~x) else
            if 0 = x then true else
            if 1 = x then false else
	    if 2 = x then false else
	       method7(x - 3)
	    fi fi fi fi
      )
   };

};

