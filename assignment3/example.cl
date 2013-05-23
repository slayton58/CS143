
(*  Example cool program testing as many aspects of the code generator
    as possible.
 *)

class Main {
  main():Int { 
	{
	  a <- 111*222; 
	  a <- add(8, 9);
	}
  
  };
  add(a:Int, b:Int):Int {
	{
		a+b;
	}
  };
  a:Int <- 999;
};

