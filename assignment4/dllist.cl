class Node {
        next : Node;
        prev : Node;
        n : Int <- 1;
        setPrev(node : Node) : Node{
                prev <- node
        };
        setNext(node : Node) : Node{
                next <- node
        };
        getNext() : Node {
                next
        };
        getN() : Int {
                n
        };
        setN(x : Int) : Int {
                n <- x
        };
};

class List {
        head : Node;
        tail : Node;
        add(node : Node) : Node {
                if isvoid head then {
                        head <- node;
                        tail <- node;
                } else {
                        tail.setNext(node);
                        node.setPrev(tail);
                        tail <- node;
                }
                fi
        };
        print (out : IO) : Node {
                let l : Node <- head in {
                        while not isvoid l loop {
                          out.out_int(l.getN());
                          out.out_string(" ");
                          l <- l.getNext();
                        } pool;
                        l;
                }
        };
};

class Main inherits IO {
        main() : IO {
        {
           let i : Int <- 0 in
             while i < 3 loop {
                let i : Int <- 0,
                    list : List <- new List in {
                    list.add(new Node);
                    while i < 100 loop {
                      let a : Node <- new Node in {
                        a.setN(i);
                        list.add(a);
                      };
                      i <- i + 1;
                    } pool;
                    list.print(self);
                    self.out_string("\n");
                };
                i <- i + 1;
             } pool;
        self;
        }
        };
};

