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

class Main {
  x : F <- new F;
  i : Int <- 10;
  main():Object {
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

