class Main {
  main(): Object {
    {
    (new A).a();
    }
  };
};

class A inherits B{
  a() : Object {
    self.a_fun().a_fun().a_fun().a_fun().a_fun().a_fun().a_fun().a_fun().a_fun().a_fun().a_fun().a_fun().a_fun().b()
  };

  a_fun() : SELF_TYPE {
    {
      out_string("a_fun\n");
      self;
    }
  };

};

class B inherits IO{
  b() : Object {
    self.b_fun().b_fun().b_fun().b_fun().b_fun().b_fun().b_fun().b_fun().b_fun().b_fun().b_fun().b_fun().b_fun().b_out()
  };

  b_fun() : SELF_TYPE {
    {
      out_string("b_fun\n");
      self;
    }
  };

  b_out() : Object {
    {
    out_string("finally...\n");
    }
  };
};
