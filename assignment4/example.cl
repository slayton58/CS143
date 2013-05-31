

class Main {
  main() : Object {
      {
          (new Dog).test(1, (new Cat).test(3, 5+8));
          (new IO).out_int((new Dog).test_test());
          (new IO).out_int(~(1+(new Cat).test(1,3)));

          (new Cat).test(126, 332);
          (new Cat).test_test();
          (new Dog).test(126, 332);
          (new Dog).test_test();
		  
		  (new Test_code_init).test();
          (new Test_code_let_tycase).test();
		  (new Test_code_static_dispatch).test();
		  (new Test_code_assign).test(1);
		  (new Test_code_loop).test(2, 6);
          (new Test_code_cond).test();
          (new Test_code_loop).test(2, 6);
          (new Test_code_assign).test(1);
          (new Test_code_comp).test(2 = 3);
          (new Test_code_eq).test();
          (new Test_code_arith).test();
          (new Test_code_compare).test();
          (new Test_code_isvoid).test();
          (new Test_code_new).test();
         
      }
  };
};

class Cat {
    var : Int <- 789;

    test(m : Int, n : Int) : Int {
        m + n
    };

    test_test() : Int {
        3 + test(5, 2) + 8
    };


};

class Dog inherits Cat {
    one : Int;
    two : Int <- 567;
    three : Int <- 10 - 11;
};

class Test_static_dispatch_parent {
    f() : IO { (new IO).out_int(123) };
};
class Test_static_dispatch_child inherits Test_static_dispatch_parent {
    f() : IO { (new IO).out_int(456) };
};
class Test_code_static_dispatch {
    v1 : Test_static_dispatch_parent <- new Test_static_dispatch_parent;
    v2 : Test_static_dispatch_child <- new Test_static_dispatch_child;
    test() : Object {
        {
        v1.f();
        v2.f();
        }
    };
};

class Test_code_cond {
    test() : Object {
        {
            if 4 <= 5 then 1 else
            if 5 <= 4 then 1 else 2 fi
            fi;
        }
    };
};

class Test_code_loop {
    test(start:Int, end:Int) : Object {
        while start <= end loop
        {
            end <- end -1;
			(new IO).out_int(start);
            start <- start + 1;
        }
        pool
    };
};

class Apple {
  a():Int{
    123
  };
};

class Banana inherits Apple {
  b():Int{
    234
  };
};

class Cut inherits Banana {
  c():Bool{
    true
  };
};

class Double inherits Apple {
  d():String{
    "lala"
  };
};

class Ella {
  e():Int{
    789
  };
  f():Int{
    {
      (New IO).out_int(6);
      (New IO).out_string(" in Ella.f() \n");
      6;
    }
  };
};

class Fun inherits Ella{
  f : Int <- 60;
  change(ff:Int):Int { f <-ff };
  f():Int{
    {
      (New IO).out_int(f);
      (New IO).out_string(" in Fun.f() \n");
      f;
    }
  };
};

class Test_code_let_tycase {
  x : Fun <- new Fun;
  i : Int <- 10;
  test():Object {
    {
     let y:Fun <- new Fun, z:Fun <- new Fun in 
        let w:Int <- 600 in 
          {
            z.change(y.f()+6); 
            x.change(z.f()+w);
          };
     while 0 < i loop {
       case x of
         x1 : Ella => x1.e();
         x2 : Fun => {
                          let a:Fun <- new Fun in 
                            let a:Apple <- new Apple in
                              let a:Ella in {
                                a <- new Ella;
                                x.change(x2.f() + a.f());
                                case x2.f() of
                                  y1 : Ella => y1.e();
                                  y2 : Fun => x2.f();
                                  y3 : Int => x2.change(x2.f() + 60000);
                                esac;
                              };
                           };
         x3 : Apple => x3.a();
         x4 : Banana => x4.b();
         x5 : Cut => x5.c();
         x6 : Double => x6.d();
         x7 : Int => 7;
       esac;
       i <- i - 1;
     }pool;
    }
  };
};


class Test_code_assign {
    test(i : Int) : Int {
        i <- i + 1000
    };
};

class Test_code_comp {
    test(b : Bool) : Bool {
        not b
    };
};

class Test_code_eq {
    test() : Object {
        {
            if 1 + 3 = 5 then
                (new IO).out_int(1)
            else
                (new IO).out_int(2)
            fi;
            1 = 2;
            "three" = "three";
            true = false;
            new Apple = new Apple;
        }
    };
};

class Test_code_arith {
    test() : Int {
        3 + 2 * 5 * (4 - 10 * 6) / (8 - 2) + 4
    };
};

class Test_code_compare {
    test() : Object {
        {
        if 4 <= 5 then
            (new IO).out_string("lower or equal \n")
        else
            (new IO).out_string("greater \n")
        fi;
        if 123 < 456 then
            (new IO).out_string("lower\n")
        else
            (new IO).out_string("greateror equal\n")
        fi;
        }
    };
};

class Test_is_void {};
class Test_code_isvoid {
    p : Test_is_void;
    q : Test_is_void <- new Test_is_void;
    test() : Object{
        {
		    if isvoid q then
                (new IO).out_string("q: void\n")
            else
                (new IO).out_string("q: not void\n")
            fi;
            if isvoid p then
                (new IO).out_string("p: void\n")
            else
                (new IO).out_string("p: not void\n")
            fi;
        }
    };
};

class Test_new {
    c1 : Int <- 789;
    c2 : String <- "lala\n";
    c3 : Bool <- false;
    f() : Object { {
        (new IO).out_int(c1);
        (new IO).out_string(c2);
    } };
};

class Test_code_new {
    var : Test_new <- new Test_new;
    test() : Object { { var.f(); } };
};

class Test_init_parent { apple : Int; };
class Test_init_child inherits Test_init_parent { banana : Int <- apple * 2; };
class Test_code_init {
    foo : Test_init_parent <- new Test_init_parent;
    bar : Test_init_child <- new Test_init_child;
    onetwo : Test_init_parent <- new Test_init_child;
    test() : Object { "lala" };
};


