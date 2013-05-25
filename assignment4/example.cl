
(*  Example cool program testing as many aspects of the code generator
    as possible.
 *)

class Main {
  main() : Object {
      {
          (new BB).test(1, (new AA).test(3, 4+4));
          (new IO).out_int((new BB).testtest());
          (new IO).out_int(~(1+(new AA).test(2,3)));

          (new AA).test(123, 432);
          (new AA).testtest();
          (new BB).test(123, 432);
          (new BB).testtest();

          (new TestIfElse).test();
          (new TestLoop).test(1, 5);
          (new TestAssign).test(1);
          (new TestComp).test(1 = 2);
          (new TestEqual).test();
          (new TestNew).test();
          (new TestArith).test();
          (new TestComparison).test();
          (new TestIsVoid).test();
          (new TestStaticDispatch).test();
          (new TestInit).test();
          (new TestCaseLet).test();
      }
  };
};

class AA {
    var : Int <- 234;

    test(x : Int, y : Int) : Int {
        x + y
    };

    testtest() : Int {
        3 + test(1, 2) + 4
    };


};

class BB inherits AA {
    foo : Int;
    bar : Int <- 567;
    abc : Int <- 10 - 11;
};


class TestIfElse {
    test() : Object {
        {
            if 1 <= 3 then 1 else
            if 3 <= 1 then 1 else 2 fi
            fi;
        }
    };
};

class TestLoop {
    test(begin:Int, end:Int) : Object {
        while begin <= end loop
        {
            (new IO).out_int(begin);
            begin <- begin + 1;
        }
        pool
    };
};

class TestAssign {
    test(i : Int) : Int {
        i <- i + 1
    };
};

class TestComp {
    test(b : Bool) : Bool {
        not b
    };
};

class TestEqual {
    test() : Object {
        {
            if 1 + 3 = 5 then
                (new IO).out_int(1)
            else
                (new IO).out_int(2)
            fi;
            1 = 2;
            "abc" = "abc";
            true = false;
            new A = new A;
        }
    };
};

class ForTestNew {
    v1 : Int <- 123;
    v2 : String <- "abc\n";
    v3 : Bool <- true;
    m() : Object { {
        (new IO).out_int(v1);
        (new IO).out_string(v2);
    } };
};
class TestNew {
    var : ForTestNew <- new ForTestNew;
    test() : Object { { var.m(); } };
};

class TestArith {
    test() : Int {
        1 + 2 * 3 * (4 - 5 * 6) / (7 - 3) + 9
    };
};

class TestComparison {
    test() : Object {
        {
        if 2 <= 3 then
            (new IO).out_string("lower than or equal to\n")
        else
            (new IO).out_string("greater than\n")
        fi;
        if 2 < 3 then
            (new IO).out_string("lower than\n")
        else
            (new IO).out_string("greater than or equal to\n")
        fi;
        }
    };
};

class ForTestIsVoid {};
class TestIsVoid {
    a : ForTestIsVoid;
    b : ForTestIsVoid <- new ForTestIsVoid;
    test() : Object{
        {
            if isvoid a then
                (new IO).out_string("a is void\n")
            else
                (new IO).out_string("a is not void\n")
            fi;
            if isvoid b then
                (new IO).out_string("b is void\n")
            else
                (new IO).out_string("b is not void\n")
            fi;
            if isvoid while false loop true pool then
                (new IO).out_string("while is void\n")
            else
                (new IO).out_string("while is not void\n")
            fi;
        }
    };
};


class ForTestStaticDispatch1 {
    f() : IO { (new IO).out_int(1) };
};
class ForTestStaticDispatch2 inherits ForTestStaticDispatch1 {
    f() : IO { (new IO).out_int(2) };
};
class TestStaticDispatch {
    v1 : ForTestStaticDispatch1 <- new ForTestStaticDispatch1;
    v2 : ForTestStaticDispatch2 <- new ForTestStaticDispatch2;
    test() : Object {
        {
        v1.f();
        v2.f();
        }
    };
};

class ForTestInit1 { a : Int; };
class ForTestInit2 inherits ForTestInit1 { b : Int <- a + 1; };
class TestInit {
    foo : ForTestInit1 <- new ForTestInit1;
    bar : ForTestInit2 <- new ForTestInit2;
    foobar : ForTestInit1 <- new ForTestInit2;
    test() : Object { 1 };
};

class A {
  a():Int{
    10
  };
};

class B inherits A {
  b():Int{
    20
  };
};

class C inherits B {
  c():Int{
    30
  };
};

class D inherits A {
  d():Int{
    40
  };
};

class E {
  e():Int{
    50
  };
  f():Int{
    {
      (New IO).out_int(6000);
      (New IO).out_string(" in E.f() \n");
      6000;
    }
  };
};

class F inherits E{
  f : Int <- 60;
  setf(ff:Int):Int { f <-ff };
  f():Int{
    {
      (New IO).out_int(f);
      (New IO).out_string(" in F.f() \n");
      f;
    }
  };
};

class TestCaseLet {
  x : F <- new F;
  i : Int <- 10;
  test():Object {
    {
     let y:F <- new F, z:F <- new F in 
        let w:Int <- 600 in 
          {
            z.setf(y.f()+6); 
            x.setf(z.f()+w);
          };
     while 0 < i loop {
       case x of
         x1 : E => x1.e();
         x2 : F => {
                          let a:F <- new F in 
                            let a:A <- new A in
                              let a:E in {
                                a <- new E;
                                x.setf(x2.f() + a.f());
                                case x2.f() of
                                  y1 : E => y1.e();
                                  y2 : F => x2.f();
                                  y3 : Int => x2.setf(x2.f() + 60000);
                                esac;
                              };
                           };
         x3 : A => x3.a();
         x4 : B => x4.b();
         x5 : C => x5.c();
         x6 : D => x6.d();
         x7 : Int => 7;
       esac;
       i <- i - 1;
     }pool;
    }
  };
};

