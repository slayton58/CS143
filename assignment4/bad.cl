(* check error dispatch-on-void *)

class Main {
    var : A;
    main() : Object {
        var.m()
    };
};

class A {
    m() : Int { 1 };
};
