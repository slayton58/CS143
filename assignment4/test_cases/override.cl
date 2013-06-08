class A inherits IO {
  a() : SELF_TYPE {
    out_string("A_a\n")
  };
  b() : SELF_TYPE {
    out_string("A_b\n")
  };
  c() : SELF_TYPE {
    out_string("A_c\n")
  };
  s() : SELF_TYPE {
    self
  };
};
class B inherits A {
  b() : SELF_TYPE {
    out_string("B_b\n")
  };
  c() : SELF_TYPE {
    out_string("B_c\n")
  };
  d() : SELF_TYPE {
    out_string("B_d\n")
  };
};
class C inherits B {
  c() : SELF_TYPE {
    out_string("C_c\n")
  };
  e() : SELF_TYPE {
    out_string("C_e\n")
  };
};
class Main {
  main():Object {
    {
      let x : C <- new C.s() in {x.a(); x.b(); x.c(); x.d(); x.e();};
      let x : B <- new B.s() in {x.a(); x.b(); x.c(); x.d();};
      let x : A <- new A.s() in {x.a(); x.b(); x.c();};
      let x : C <- new C.s().s().s().s().s() in {x.a(); x.b(); x.c();};
      let x : B <- new B.s().s().s().s().s() in {x.a(); x.b(); x.c();};
      let x : A <- new A.s().s().s().s().s() in {x.a(); x.b(); x.c();};
    }
  };
};
