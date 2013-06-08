class Main inherits IO {
  c : Int;
  x(s : String, i : Int) : SELF_TYPE { { c <- c + i; out_string(s); } };
  y() : SELF_TYPE { out_int(c) };
  main() : Object { if c < 1 then x("then",2) else x("else",3) fi.y() };
};
