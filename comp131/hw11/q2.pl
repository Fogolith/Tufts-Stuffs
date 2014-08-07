p(Y) :- q(X, Y), r(Y).
p(X) :- q(X, X).
q(X, X) :- s(X).
r(b).
s(a).
s(b).
