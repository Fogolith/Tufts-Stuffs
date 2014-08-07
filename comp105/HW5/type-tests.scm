‘(#t #f)

; (#t #f) : (tuple bool (tuple bool (list ‘a)))

‘(3 2)

; (3 2) : (tuple int (tuple int (list ‘a)))

‘()

; () : (list ‘a)

‘(3)

; (3) : (tuple int (list ‘a))

‘(2 (2 #t))

; (2 (2 #t)) : (tuple int (tuple (tuple int (tuple bool (list ‘a))) (list ‘a)))

(+ 1 2)

; 3 : int

(< 1 0)

; #f : bool

(let (x 2)(y 4)) (+ x y))
; 6 : int



