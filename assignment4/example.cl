
class AAA {
    a:Int <- 111+222+333;
	b:String <- "lalala";
    test() : Object {
        {
            if 1 + 3 = 5 then
                (new IO).out_string("!!!case1\n")
            else
                (new IO).out_string("!!!case2\n")
            fi;
            1 = 2;
            "abc" = "abc";
            true = false;
        }
    };
};
class Main inherits AAA{
  main():Int { 
  {
    a <- 111*222; 
    a <- add(8, 9);
    test();
	5;
  }
  
  };
  add(a:Int, b:Int):Int {
  {
    a+b;
  }
  };
  c:Bool <- true;

};
