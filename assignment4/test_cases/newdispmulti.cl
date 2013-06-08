class Main {
  main(): Object {
    {
    (new A).a();
    }
  };
};

class A inherits IO{
  a() : Object {
    (new B).b()
  };

  a_out() : Object {
    {
    out_string("finally...\n");
    }
  };
};

class B {
  b() : Object {
    (new C).c()
  };

  b_out() : Object {
    {
    (new A).a_out();
    }
  };
};

class C {
  c() : Object {
    (new D).d()
  };

  c_out() : Object {
    (new B).b_out()
  };
};

class D {
  d() : Object {
    (new E).e()
  };

  d_out() : Object {
    (new C).c_out()
  };
};

class E {
  e() : Object {
    (new F).f()
  };

  e_out() : Object {
    (new D).d_out()
  };
};

class F {
  f() : Object {
    (new E).e_out()
  };
};