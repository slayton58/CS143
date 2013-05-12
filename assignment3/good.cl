class C {
	a : Int;
	b : Bool;
	init(x : Int, y : Bool) : C {
           {
		a <- x;
		b <- y;
		self;
           }
	};
};

class D inherits C {
    d : Int;
    methodD() : Bool { true };
};


class E inherits D {

    test(bar:String, foobar:C) : Int {
        {
            foo;
            foobar;
        }
    };

    methodE() : Bool { false };
    var : Int;
    foo : Bool;
};

class B inherits IO {
    otherMethod() : IO {
        {
            1 + 2;
            {
            1 + 2;
            };
            new B;
        }
    };
};

class TestAssign inherits IO {
    a : Int;
    c : IO;
    cC : TestAssign;
    test() : TestAssign {
        {
        a <- 123;
        c <- cC;
        }
    };
};

Class Main {
	main():C {
	  (new C).init(1,true)
	};
};
