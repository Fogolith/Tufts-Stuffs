;Jake Austin, Andrew Jang, and Ian Mcconnel. HW5 part C, function in tuscheme
(val-rec (forall ('a) (function ((function ('a) bool) (list 'a)) bool))
  exists?
  (type-lambda ('a)
    (lambda (((function ('a) bool) f) ((list 'a) xs))
     
       (if ((@ null? 'a) xs) #f
           (if (f ((@ car 'a) xs)) #t
               ((@ exists? 'a) f ((@ cdr 'a) xs))
           )
       ) 
    
    ) 
  )
)

(val-rec
  (forall ('a) (function ((function ('a) bool) (list 'a)) bool))
  all?
  (type-lambda ('a)
    (lambda (((function ('a) bool) f) ((list 'a) xs))
    (if ((@ null? 'a) xs) #t
     (and ((@ exists? 'a) f (list1 ((@ car 'a) xs))) 
          ((@ all? 'a) f ((@ cdr 'a) xs)))
    )
    )
  )
)
; type of exists? and all? is ----- 'a list x (function ('a) bool) --> bool



