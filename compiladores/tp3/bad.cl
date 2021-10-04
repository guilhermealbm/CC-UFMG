
(*
 *  execute "coolc bad.cl" to see the error messages that the coolc parser
 *  generates
 *
 *  execute "myparser bad.cl" to see the error messages that your parser
 *  generates
 *)

(* no error *)
class A {
};

(* error:  b is not a type identifier *)
Class b inherits A {
};

(* error:  a is not a type identifier *)
Class C inherits a {
};

(* error:  keyword inherits is misspelled *)
Class D inherts A {
};

(* error:  closing brace is missing *)
Class E inherits A {
;

(* new test cases *)

(* error: feature starting with uppercase *)
Class F {
	N : Int;
};

(* error: feature starting with uppercase *)
Class F {
	num : Int;
	NUM : Int;
};

(* error: feature starting with uppercase and without defined type *)
Class F inherits A {
  NUM
};

(* error: trying to assign a bool to a int variable *)
Class F {
	n : Int;
	m : Int <- BOOL;
};

(* error: trying to assign a bool to a int variable *)
Class F inherits A {
    m : Int <- BOOL;
    n : Int;
};

(* error: missing semicolon *)
Class F inherits A {
    n : Int <- 10
};

(* error: block error *)
Class G inherits A {
 	b(num1 : Int) : Int {
    { num1 <- 1; 
    Error; }
  };
};

(* error: case error *)
Class H {
   n : Int;
   m : Int <- n case of s:String => 3 esac;
}

(* error: wrong method call *)
Class I {
   c() : Object {
      out_string(Error);
   };
};
