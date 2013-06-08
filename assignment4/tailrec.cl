class Main inherits IO {
  fact(n : Int) : Int { fact_helper(n, 1) };
  fact_helper(n : Int, c : Int) : Int { if n < 2 then c else fact_helper(n - 1, c * n) fi };
  main() : Object { {
    out_int(fact(1)); out_string("\n");
    out_int(fact(3)); out_string("\n");
    out_int(fact(10)); out_string("\n");
    out_int(fact(12)); out_string("\n");
  } };
};
