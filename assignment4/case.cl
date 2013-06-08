class A {};
class B inherits A {};
class C inherits A {};
class D inherits B {};
class E inherits B {};
class F inherits D {};
class G inherits E {};

class Main inherits IO {
  docase(x : Object) : SELF_TYPE {
    case x of
    a : A => out_string(a.type_name()).out_string(" <= A\n");
    z : Object => out_string(z.type_name()).out_string(" <= Object\n");
    z : C => out_string(z.type_name()).out_string(" <= C\n");
    z : E => out_string(z.type_name()).out_string(" <= E\n");
    z : F => out_string(z.type_name()).out_string(" <= F\n");
    esac
  };
  main() : Object { {
    docase(new A);
    docase(new B);
    docase(new C);
    docase(new D);
    docase(new E);
    docase(new F);
    docase(new G);
    docase(self);
  } };
};
