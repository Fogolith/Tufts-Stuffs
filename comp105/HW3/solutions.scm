;Jake Austin, Comp 105 a3 Scheme I

;2A, count takes an atom and a list and returns the number of occurances of x
;in y at the top level
(define count (x y) (if (< 0 (length y)) (if (atom? (car y)) (if (= x (car y)) 
							(+ 1 (count x (cdr y)))
							(count x (cdr y)))
				    (count x (cdr y)))
			0))

;2B, countall, takes in an atom and list and returns the number of occurances 
;of x at any depth of y
(define countall (x y) (if(< 0 (length y)) (if(atom? (car y)) (if(= x (car y))
                                                     (+ 1 (countall x (cdr y)))
						     (countall x (cdr y)))
 					   (+ (countall x (car y))
				              (countall x (cdr y))))
			0))



;check_reverse is used to see if an element of x is an atom or list
;lists are reversed, atoms are returned
(define check_reverse (x) (if(atom? x) x (reverse x)))
;2C, mirror, takes in a list of s-exp and recursively mirrors members
(define mirror (x) (reverse (map check_reverse x)))


;2D, flatten, takes in a list of s-exp and returns one dimensional list with all
;elements
(define flatten (x) (if(< 0 (length x))
                      (if(atom?(car x))
		       (if(= (car x) '()) 
			 (append '() (flatten(cdr x)))			
		       (cons(car x)(flatten(cdr x))))
                     (append(flatten(car x))(flatten(cdr x))))
                   '()))

;2E,helper, after contig-sublist finds a member of x in y, checks if the 
;remainder of x follows within y
(define match? (x y) (if(< 0 (length x)) 
                       (if(< 0 (length y))   
                        (if(=(car x)(car y)) 
                           (match? (cdr x)(cdr y))
                        #f)
                       #f)
                      #t))
;2E, contig-sublist? determines if x is a continuous sublist of y
(define contig-sublist? (x y) (if(< (length x) (length y)) 
                                (if(=(car x)(car y))
                                   (if(match? (cdr x)(cdr y)) #t  
	       					   (contig-sublist? x (cdr y)))
                                (contig-sublist? x (cdr y)))
                              #f))

;2F, sublist? determines if x is a sublist of y (not neccessarily continuous)
(define sublist? (x y) (if(< 0 (length x)) 
                           #t
                       (if(< (length x)(length y)) 
                          (if(=(car x)(car y)) 
                            (sublist? (cdr x)(cdr y))
                          (sublist? x (cdr y)))
                        #f)))
                        
;9a, cdr*, takes a list of lists and returns a list of the cdrs of sublists
(define cdr* (x) (map cdr x))

;9b, max*, takes a list of integers and returns max value
(define max* (x) (foldl max (car x)(cdr x)))

;9g, append, takes 2 lists and returns the concatenation
(define append (x y) (foldr cons y x))

;9i, reverse, takes a list and returns the reversed list
(define reverse (x) (foldl cons '() x))

;drop, takes an integer n and a list and drops the first n elements
;if n is greater than the number of elements in the list, return empty list
(define drop (n x) (if(<= n (length x)) (if(= n 0) x (drop (- n 1)(cdr x)))
		      '()))
;take, takes an integer n and a list and returns a list of the first n 
;elements. If asked to take more elements than are in the list, the whole
;list is returned
(define take (n x) (if(< n (length x)) (if(= n 0) '()
					   (cons (car x)(take (- n 1)(cdr x))))
		      x))


;zip, takes 2 lists and returns an association list mapping values in x to
;values in y. Behavior for lists of unequal length is undefined
(define zip (x y) (if(< 0 (length x)) (if(< 0 (length y)) (cons
							  (list2(car x)(car y))
							  (zip(cdr x)(cdr y)))
					 '())
		     '()))
;unzip, takes an association list and returns a list with 2 sublists consisting
;of keys and values. Behavior for non-association lists is undefined.
(define unzip (x) (list2(map car x)(map cadr x)))

;arg max, takes a function and a non-empty list of integers and returns the 
;integer for which f(x) is the largest
(define arg-max (f x) (if(=(f (car x))(max*(map f x))) (car x) 
			 (arg-max f (cdr x))))

;merge, takes 2 sorted lists and returns a single sorted list containing 
;all elements of both lists
(define merge (x y) (if(< 0 (length x))
		       (if(< 0 (length y))
			  (if(<(car x)(car y))
			     (if(< 1 (length x))
				(if(<(cadr x)(car y))
				   (append(list2(car x)(cadr x))
					  (merge (cddr x) y))
				   (append(list2(car x)(car y))
					  (merge (cdr x)(cdr y))))
				(append(list2(car x)(car y))
				       (merge (cdr x)(cdr y))))
			     (if(< 1 (length y))
				(if(< (cadr y)(car x))
				   (append(list2(car y)(cadr y))
					  (merge x (cddr y)))
				   (append(list2(car y)(car x))
					  (merge (cdr x)(cdr y))))
				(append(list2(car y)(car x))
				       (merge (cdr x)(cdr y)))))
			  (cons (car x) (merge (cdr x) y)))
		       (if(< 0 (length y)) (cons(car y)(merge x (cdr y)))
			  '())))

;interleave, takes 2 lists and creates a new list by alternating members from
;each
(define interleave (x y) (if(< 0 (length x)) 
			    (if(< 0 (length y))
			       (append(list2(car x)(car y))
				      (interleave (cdr x)(cdr y)))
			       x)
			    (if(< 0 (length y)) y '())))

