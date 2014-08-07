(* Jake Austin, Comp 105 HW4: ML1 *)

(* compound: recursively applies binary operator f to x N times *)
fun compound (op f, N, x) = if N>=1 then op f(x, compound(op f, N-1, x)) 
				    else x;

(* exp: Using compound with multiplication, exp calculates x^y *)
fun exp x y = if y=0 then 1 else compound(op *, y-1, x);

(* fib: recursively calculates fibonacci number of input, defined for n>=0 *)
fun fib 0 = 0
  | fib 1 = 1
  | fib n = fib(n-1)+fib(n-2);

(* rev: Using foldl, rev takes a list and returns the reversed list *)
fun rev nil = nil
  | rev x = foldl op:: nil x;

(* minlist: Using foldl, minlist returns the smallest value in an int list *)
fun minlist (x::xs) = foldl (fn(a, b)=> if a<=b then a else b) x xs
  | minlist [] = raise Empty;

(* myfoldl: Revursive implementation of foldl *)
fun myfoldl f x [] = x
  | myfoldl f x (y::ys) = myfoldl f (f(y, x)) ys;

(* myfoldr: Recursive implementation of foldr *)
fun myfoldr f x [] = x
  | myfoldr f x (y::ys) = f(y, (myfoldr f x ys));

(* zip: Given 2 lists of even length, recursively makes list of tuples  *)
(*      returns nil in any case where the lists are not equal in length *)
fun zip (x::xs) (y::ys) = (x, y)::(zip xs ys)
  | zip _ _ = [];

(* unzip: Given list of pair tuples, recursively splits tuples into 2 lists *)
fun unzip [] = ([], [])
  | unzip ((x, y)::zs) = let val (xs, ys) = unzip zs in (x::xs, y::ys) end;

(* flatten: Given a list of lists, recursively generates 1d list with all  *)
(*          elements.                                                      *)
fun flatten [] = []
  | flatten (x::xs) = x @ flatten xs;


(* mynth: Given a non-negative integer and a list, recursively iterates *)
(*        through list and returns nth element.                         *)
fun mynth x (y::[]) = if x=0 then y else raise Domain
  | mynth x (y::ys) = if x<0 then raise Domain 
                      else if x=0 then y else mynth (x-1) ys
  | mynth x [] = raise Empty;


(* environment type *)
type 'a env = (string * 'a) list

(* empty environment *)
val emptyEnv = [];

(* bindVar: Takes tuple, cons tuple (key, value) onto environment *)
fun bindVar (x:string, y, env) = (x, y)::env;

(* isBound: takes string and environment, returns bool if string is bound in *)
(* environment                                                               *)
fun isBound (x:string, []) = false
  | isBound (x:string, ((y , z)::zs)) = if x=y then true
			                else isBound (x, zs); 

exception NotFound;

(* lookup: takes string and environment, returns associated value or raises *)
(* exception                                                                *)
fun lookup (x:string, []) = raise NotFound
  | lookup (x:string, ((y, z)::zs)) = if x=y then z
				      else lookup (x, zs);
(* extendEnv takes a list of keys and list of values and environment        *)
(* using pairfold, bindings mapping the keys to the values are added to env *) 
fun extendEnv (xs, ys, env) = 
let fun pairfold f z ([], []) = z
      | pairfold f z (x::xs, y::ys) = f (x, y, pairfold f z (xs, ys))
      | pairfold _ _ _ = raise Match;
in
pairfold bindVar env (xs, ys) end;

(* env2 type *)
type 'a env2 = string -> 'a

(* emptyEnv2 raises the exception that no string will be found *)
fun emptyEnv2 (x:string) = raise NotFound;

fun lookup2 (x:string, env2) = env2 x;

(* is bound 2 *)
fun isBound2 (x:string, env2) = let val y = lookup2 (x, env2) in true end
                                handle NotFound => false;

(* bindVar2: Takes a key, value and environment, creates and returns a      *)
(* function that takes a string, maps string x to y, otherwise looks up the *)
(* string within the environment, ultimately reaching NotFound              *) 
fun bindVar2 (x:string, y, env2) = 
             (fn z:string => if z=x then y else lookup2 (x, env2)); 

(* seq datatype *)
datatype 'a seq = EMPTY
                | SINGLETON of ('a)
                | SEQ of ('a seq * 'a seq);

(* scons: adds singleton of x to fron of sequence *)
fun scons (x, sq) = SEQ(SINGLETON(x) , sq); 

(* ssnoc: adds singleton of x to end of sequence *)
fun ssnoc (x, sq) = SEQ(sq, SINGLETON(x));

(* sappend: takes two sequences, returns sequence containing both *)
fun sappend (sq1, sq2) = (SEQ(sq1, sq2));

(* listOfSeq: Given sequence, generates list *)
fun listOfSeq (EMPTY) = []
  | listOfSeq (SINGLETON(x)) = [x]
  | listOfSeq (SEQ(sq1, sq2)) = listOfSeq(sq1)@listOfSeq(sq2);

(* seqOfList: given list, uses foldr to generate sequence *)
fun seqOfList (x) = foldr scons EMPTY x;


(* flist is a tuple of a list (LEFT), an element (FINGER), and a list (RIGHT)*)
(* LEFT is represented in reverse in order to access in constant time, and   *)
(* must be reversed to access the list in order                              *)
type 'a flist = ('a list * 'a * 'a list);

fun singletonOf (x) = ([], x, []);

(* atFinger returns the value y in a flist *)
fun atFinger(xs, y, zs) = y;

(* goRight moves the finger one element to the right, or raises an exception *)
(* if the finger is already at the far right                                 *)
fun goRight(xs, y, []) = raise Subscript
  | goRight(xs, y, z::zs) = (y::xs, z, zs);

(* goLeft moves the finger one element to the left, or raises an exception *)
(* if the finger is already at the far left                                *)
fun goLeft([], y, zs) = raise Subscript 
  | goLeft(x::xs, y, zs) = (xs, x, y::zs);

(* insertLeft takes an element and inserts it to the left of the finger *)
fun insertLeft(a, (xs, y, zs)) = (a::xs, y, zs);

(* insertRight takes an element and inserts it to the right of the finger *)
fun insertRight(a, (xs, y, zs)) = (xs, y, a::zs);

(* deleteLeft deletes the element to the left of the finger or raises an *)
(* exception if the finger is at the far left                            *)
fun deleteLeft([], y, zs) = raise Subscript
  | deleteLeft(x::xs, y, zs) = (xs, y, zs);

(* deleteRight deletes the element to the right of the finger or raises an *)
(* exception if the finger is at the far right                             *)
fun deleteRight(xs, y, []) = raise Subscript
  | deleteRight(xs, y, z::zs) = (xs, y, zs);

(* Using pattern matching, ffoldl make an flist into a list and calls foldl *)
fun ffoldl (f, a, ([], y, [])) = foldl f a [y]
  | ffoldl (f, a, (xs, y, [])) = foldl f a (rev(y::xs))
  | ffoldl (f, a, ([], y, zs)) = foldl f a (y::zs)
  | ffoldl (f, a, (x::xs, y, zs)) = foldl f a (rev(x::xs) @ (y::zs));

(* Using pattern matching, ffoldr make an flist into a list and calls foldr *)
fun ffoldr (f, a, ([], y, [])) = foldr f a [y]
  | ffoldr (f, a, (xs, y, [])) = foldr f a (rev(y::xs))
  | ffoldr (f, a, ([], y, zs)) = foldr f a (y::zs)
  | ffoldr (f, a, (x::xs, y, zs)) = foldr f a (rev(x::xs) @ (y::zs));


