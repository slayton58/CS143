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
            bar;
            foobar;
            var;
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
            1 - 2;
            1 * 2;
            1 / 2;
            ~2;
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

class ForTestNew inherits TestNew {};
class TestNew inherits IO {
    var : TestNew;
    test() : ForTestNew {
        {
            var <- new SELF_TYPE;
            var <- new ForTestNew;
        }
    };
};

class ForTestCond1 inherits IO {};
class ForTestCond2 inherits ForTestCond1 {};
class ForTestCond3 inherits ForTestCond1 {};
class ForTestCond4 inherits ForTestCond3 {};
class TestCond {
    var : Int <- 5;

    test() : IO {
        if var <= 10/2 then
            new ForTestCond2
        else
            new ForTestCond4
        fi
    };
};

class ForTestAttr inherits TestAttr {};
class TestAttr {
    varInt : Int <- 123;
    varBool : Bool;
    varStr : String <- "123";
    varSelf1 : TestAttr <- new SELF_TYPE;
    --varTest1 : ForTestAttr <- new TestAttr;
    varTest : TestAttr <- new ForTestAttr;
};

class ForTestMethod1 inherits IO {};
class ForTestMethod2 inherits ForTestMethod1 {};
class TestMethod {
    --test1(i:Int) : Bool { 123 };

    test2(varIO:IO) : ForTestMethod1 {
        new ForTestMethod2
    };

    test3() : IO {
        new ForTestMethod2
    };
};

class TestIsvoid {
    test() : Bool {
        isvoid 123
    };
};

class TestComp {
    test() : Bool {
        {
        --not 123;
        not 123 < 123;
        }
    };
};

class TestLoop {
    test() : Object {
        while 1 < 5 loop
            new TestLoop
        pool
    };
};

class ForTestCase1 {};
class ForTestCase2 inherits ForTestCase1 {};
class ForTestCase3 inherits ForTestCase1 {};
class ForTestCase4 inherits ForTestCase3 {};
class TestCase {
    test() : ForTestCase1 {
        case new ForTestCase3 of
        a1 : ForTestCase1 => new ForTestCase2;
        a2 : ForTestCase2 => a2;
        a3 : ForTestCase3 => new ForTestCase4;
        a4 : ForTestCase4 => new ForTestCase4;
        esac
    };
};

class ForTestLet inherits TestLet {};
class TestLet {
    test() : Bool {
        {
        let x : Int in x < 100;
        }
    };

    test1() : TestLet {
        let y : SELF_TYPE in y
    };

    test2() : Int {
        let z : Int <- 10 in {5;z;}
    };

    test3() : Bool {
        {
            --let w : TestLet <- new IO in w;
            let w : TestLet <- new ForTestLet in w;
            true;
        }
    };
};

class ForTestDispatch1 inherits IO {
    call(i:IO) : Bool { true };
};
class TestDispatch inherits ForTestDispatch1 {
    var : ForTestDispatch1 <- new ForTestDispatch1;
    test() : Bool {
        var.call(var)
    };

    test1() : Bool {
        {
            var.call(new IO);
            self.test();
            true;
        }
    };
};


Class Main {
	main():C {
	  (new C).init(1,true)
	};
};

