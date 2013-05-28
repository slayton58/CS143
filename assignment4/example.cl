class AAA {    
    a:Int <- 111+222+333;
    test(a:Int, b:Int) : Object {
        {
           
            if (1 + 3 = 4) then
                (new IO).out_string("!!!case1\n")
            else
                (new IO).out_string("!!!case2\n")
            fi;
			3+4;
            1 = 2;
			
			a = a+b;
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
    test(a, c);
	5;
  }
  
  };
  add(a:Int, b:Int):Int {
  {
    a+b;
  }
  };

  b:Bool <- true;
  c:Int <- 3+4;
  
};

