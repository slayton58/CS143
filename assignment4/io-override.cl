class IO2 inherits IO {
  out_string(s : String) : SELF_TYPE { self@IO.out_int(s.length()) };
  out_int(i : Int) : SELF_TYPE { self@IO.out_string("an int") };
};

class Main inherits IO2 {
  main() : Object { {
    out_string("my string");
    out_int(42);
  } };
};
