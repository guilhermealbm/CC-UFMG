class A {
};

Class BB__ inherits A {
};

class Count {
    i : Int <- 0;   
    inc () : SELF_TYPE {
        {
            i <- i + 1;
            self;
        }
    };
};

(* For now on, we got some correct code from class examples *)


(* atoi.cl *)

(*
   c2i   Converts a 1-character string to an integer.  Aborts
         if the string is not "0" through "9"
*)
class A2I {

     c2i(char : String) : Int {
	if char = "0" then 0 else
	if char = "1" then 1 else
	if char = "2" then 2 else
        if char = "3" then 3 else
        if char = "4" then 4 else
        if char = "5" then 5 else
        if char = "6" then 6 else
        if char = "7" then 7 else
        if char = "8" then 8 else
        if char = "9" then 9 else
        { abort(); 0; }  -- the 0 is needed to satisfy the typchecker
        fi fi fi fi fi fi fi fi fi fi
     };

(*
   i2c is the inverse of c2i.
*)
     i2c(i : Int) : String {
	if i = 0 then "0" else
	if i = 1 then "1" else
	if i = 2 then "2" else
	if i = 3 then "3" else
	if i = 4 then "4" else
	if i = 5 then "5" else
	if i = 6 then "6" else
	if i = 7 then "7" else
	if i = 8 then "8" else
	if i = 9 then "9" else
	{ abort(); ""; }  -- the "" is needed to satisfy the typchecker
        fi fi fi fi fi fi fi fi fi fi
     };

(*
   a2i converts an ASCII string into an integer.  The empty string
is converted to 0.  Signed and unsigned strings are handled.  The
method aborts if the string does not represent an integer.  Very
long strings of digits produce strange answers because of arithmetic 
overflow.

*)
     a2i(s : String) : Int {
        if s.length() = 0 then 0 else
	if s.substr(0,1) = "-" then ~a2i_aux(s.substr(1,s.length()-1)) else
        if s.substr(0,1) = "+" then a2i_aux(s.substr(1,s.length()-1)) else
           a2i_aux(s)
        fi fi fi
     };

(*
  a2i_aux converts the usigned portion of the string.  As a programming
example, this method is written iteratively.
*)
     a2i_aux(s : String) : Int {
	(let int : Int <- 0 in	
           {	
               (let j : Int <- s.length() in
	          (let i : Int <- 0 in
		    while i < j loop
			{
			    int <- int * 10 + c2i(s.substr(i,1));
			    i <- i + 1;
			}
		    pool
		  )
	       );
              int;
	    }
        )
     };

(*
    i2a converts an integer to a string.  Positive and negative 
numbers are handled correctly.  
*)
    i2a(i : Int) : String {
	if i = 0 then "0" else 
        if 0 < i then i2a_aux(i) else
          "-".concat(i2a_aux(i * ~1)) 
        fi fi
    };
	
(*
    i2a_aux is an example using recursion.
*)		
    i2a_aux(i : Int) : String {
        if i = 0 then "" else 
	    (let next : Int <- i / 10 in
		i2a_aux(next).concat(i2c(i - next * 10))
	    )
        fi
    };

};

(* graph.cl *)


class Graph {

   vertices : VList <- new VList;
   edges    : EList <- new EList;

   add_vertice(v : Vertice) : Object { {
      edges <- v.outgoing().append(edges);
      vertices <- vertices.cons(v);
   } };

   print_E() : Object { edges.print() };
   print_V() : Object { vertices.print() };

};

class Vertice inherits IO { 

   num  : Int;
   out  : EList <- new EList;

   outgoing() : EList { out };

   number() : Int { num };

   init(n : Int) : SELF_TYPE {
      {
         num <- n;
         self;
      }
   };


   add_out(s : Edge) : SELF_TYPE {
      {
	 out <- out.cons(s);
         self;
      }
   };

   print() : Object {
      {
         out_int(num);
	 out.print();
      }
   };

};

class Edge inherits IO {

   from   : Int;
   to     : Int;
   weight : Int;

   init(f : Int, t : Int, w : Int) : SELF_TYPE {
      {
         from <- f;
	 to <- t;
	 weight <- w;
	 self;
      }
   };

   print() : Object {
      {
         out_string(" (");
	 out_int(from);
	 out_string(",");
	 out_int(to);
	 out_string(")");
	 out_int(weight);
      }
   };

};



class EList inherits IO {
   -- Define operations on empty lists of Edges.

   car : Edge;

   isNil() : Bool { true };

   head()  : Edge { { abort(); car; } };

   tail()  : EList { { abort(); self; } };

   -- When we cons and element onto the empty list we get a non-empty
   -- list. The (new Cons) expression creates a new list cell of class
   -- Cons, which is initialized by a dispatch to init().
   -- The result of init() is an element of class Cons, but it
   -- conforms to the return type List, because Cons is a subclass of
   -- List.

   cons(e : Edge) : EList {
      (new ECons).init(e, self)
   };

   append(l : EList) : EList {
     if self.isNil() then l
     else tail().append(l).cons(head())
     fi
   };

   print() : Object {
     out_string("\n")
   };

};


(*
 *  Cons inherits all operations from List. We can reuse only the cons
 *  method though, because adding an element to the front of an emtpy
 *  list is the same as adding it to the front of a non empty
 *  list. All other methods have to be redefined, since the behaviour
 *  for them is different from the empty list.
 *
 *  Cons needs an extra attribute to hold the rest of the list.
 *
 *  The init() method is used by the cons() method to initialize the
 *  cell.
 *)

class ECons inherits EList {

   cdr : EList;	-- The rest of the list

   isNil() : Bool { false };

   head()  : Edge { car };

   tail()  : EList { cdr };

   init(e : Edge, rest : EList) : EList {
      {
	 car <- e;
	 cdr <- rest;
	 self;
      }
   };

   print() : Object {
     {
       car.print();
       cdr.print();
     } 
   };

};




class VList inherits IO {
   -- Define operations on empty lists of vertices.

   car : Vertice;

   isNil() : Bool { true };

   head()  : Vertice { { abort(); car; } };

   tail()  : VList { { abort(); self; } };

   -- When we cons and element onto the empty list we get a non-empty
   -- list. The (new Cons) expression creates a new list cell of class
   -- ECons, which is initialized by a dispatch to init().
   -- The result of init() is an element of class Cons, but it
   -- conforms to the return type List, because Cons is a subclass of
   -- List.

   cons(v : Vertice) : VList {
      (new VCons).init(v, self)
   };

   print() : Object { out_string("\n") };

};


class VCons inherits VList {

   cdr : VList;	-- The rest of the list

   isNil() : Bool { false };

   head()  : Vertice { car };

   tail()  : VList { cdr };

   init(v : Vertice, rest : VList) : VList {
      {
	 car <- v;
	 cdr <- rest;
	 self;
      }
   };

   print() : Object {
     {
       car.print();
       cdr.print();
     } 
   };

};


class Parse inherits IO {


   boolop : BoolOp <- new BoolOp;

   -- Reads the input and parses the fields

   read_input() : Graph {

      (let g : Graph <- new Graph in {
         (let line : String <- in_string() in
            while (boolop.and(not line="\n", not line="")) loop {
		-- out_string(line);
		-- out_string("\n");
		g.add_vertice(parse_line(line));
		line <- in_string();
	    } pool
         );
	 g;
      } )
   };


   parse_line(s : String) : Vertice {
      (let v : Vertice <- (new Vertice).init(a2i(s)) in {
	 while (not rest.length() = 0) loop {
	       -- out_string(rest);
	       -- out_string("\n");
	       (let succ : Int <- a2i(rest) in (let
	           weight : Int <- a2i(rest)
               in
	          v.add_out(new Edge.init(v.number(), 
                                          succ,
					  weight))
	       ) );
	 } pool;
	 v;
         }
      )
   };

     c2i(char : String) : Int {
	if char = "0" then 0 else
	if char = "1" then 1 else
	if char = "2" then 2 else
        if char = "3" then 3 else
        if char = "4" then 4 else
        if char = "5" then 5 else
        if char = "6" then 6 else
        if char = "7" then 7 else
        if char = "8" then 8 else
        if char = "9" then 9 else
        { abort(); 0; }  -- the 0 is needed to satisfy the typchecker
        fi fi fi fi fi fi fi fi fi fi
     };

     rest : String;

     a2i(s : String) : Int {
        if s.length() = 0 then 0 else
	if s.substr(0,1) = "-" then ~a2i_aux(s.substr(1,s.length()-1)) else
        if s.substr(0,1) = " " then a2i(s.substr(1,s.length()-1)) else
           a2i_aux(s)
        fi fi fi
     };

(*
  a2i_aux converts the usigned portion of the string.  As a programming
example, this method is written iteratively.
  The conversion stops at a space or comma.
  As a side effect, r is set to the remaining string (without the comma).
*)
     a2i_aux(s : String) : Int {
	(let int : Int <- 0 in	
           {	
               (let j : Int <- s.length() in
	          (let i : Int <- 0 in
		    while i < j loop
			(let c : String <- s.substr(i,1) in
			    if (c = " ") then
			       {
				  rest <- s.substr(i+1,s.length()-i-1);
				  i <- j;
			       }
			    else if (c = ",") then
		               {
				  rest <- s.substr(i+1, s.length()-i-1);
				  i <- j;
		               }
			    else
			       {
				 int <- int * 10 + c2i(s.substr(i,1));
				 i <- i + 1;
				 if i=j then rest <- "" else "" fi;
			       }
			    fi fi
			)
		    pool
		  )
	       );
              int;
	    }
        )
     };

};

class BoolOp {

  and(b1 : Bool, b2 : Bool) : Bool {
     if b1 then b2 else false fi
  };


  or(b1 : Bool, b2 : Bool) : Bool {
     if b1 then true else b2 fi
  };

};
