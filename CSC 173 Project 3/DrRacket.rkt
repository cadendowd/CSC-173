#lang slideshow
(require math)

;append function
(define (appendList lst1 lst2)
  (if (empty? lst1)
      lst2
      (cons (first lst1) (appendList (rest lst1) lst2))))

(printf "Append function answer: ")
(appendList '(1 3 x a) '(4 2 b))

;list reverse function
(define (reverseList lst)
  (if (null? lst)
     '()
     (append (reverseList (rest lst)) (list (first lst)))
  )
)

(printf "Reverse function answer: ")
(reverseList '(a b c d))

;remove duplicates from a list function
(define (removeDuplicates lst)
  (hash-keys (for/hash ([x (in-list lst)]) (values x #t))))

(printf "Remove duplicates from a list function answer:")
(removeDuplicates '(1 1 2 4 1 2 5))

;set membership function
(define (member x set)
  (cond
    [(empty? set) #f]
    [(equal? x (first set)) #t]
    [else (member x (rest set))]))

 
(printf "Set membership function answer: ")
(member 1 (list 1 2 3 4))

;set insert function
(define (insert x set)
  (cond
    [(empty? set) (cons x empty)]
    [(member x set) set]
    [else (cons (first set) (insert x (rest set)))]))

(printf "Set insert function answer: ")
(insert 5 (list 1 2 3))

;set union function
(define (union set1 set2)
    (if (empty? set1)
      set2
      (cons (first set1) (union (rest set1) set2))))

(printf "Set union function answer: ")
(union '(a b c) '(a c d))
  
;absolute value function
(define (abs x)
  (if (>= x 0)
      x
      (* -1 x)))

(printf "Absolute value function answer for 7: ")
(abs 7)
(printf "Absolute value function answer for -7: ")
(abs -7)


;factorial function
(define (fact x)
  (if (= x 0)
      1
      (* (fact (- x 1)) x)))

(printf "Factorial function answer: ")
(fact 5)

;GCD function
(define (gcd a b)
  (if (= b 0)
      a
      (gcd b (modulo a b))))

(printf "GCD function answer: ")
(gcd 8 12)

;fibonacci sequence function
(define (fib x)
  (if(= x 0)
     0
  (if (= x 1)
      1
      (+ (fib(- x 1)) (fib(- x 2))))))

(printf "Fibonacci sequence function answer for 6: ")
(fib 6)
(printf "Fibonacci sequence function answer for 10: ")
(fib 10)

;prime number function
(define (prime? p)
  (define (nonDivisible n d)
    (cond
     ((= d 1) #t)
     (else (if(= (remainder n d) 0)
          #f
          (nonDivisible n (- d 1))))))
  (if (= p 1)
      #t
      (nonDivisible p (- p 1))))

(printf "Prime number function answer for 5: ")
(prime? 5)
(printf "Prime number function answer for 6: ")
(prime? 6)

;perfect number function
(define (perfect? n)
  
  (= 
   (* n 2)
   (sum (divisors n))))

(printf "Perfect number function answer for 5: ")
(perfect? 5)
(printf "Perfect number function answer for 6: ")
(perfect? 6)

;abundant number function
(define (abundant? n)
   (<
    (* n 2)
    (sum (divisors n))))

(printf "Abundant number function answer for 5: ")
(abundant? 5)
(printf "Abundant number function answer for 12: ")
(abundant? 12)

;deficient number function
(define (deficient? n)
  (>
   (* n 2)
   (sum (divisors n))))

(printf "Deficient number function answer for 5: ")
(deficient? 5)
(printf "Deficient number function answer for 12: ")
(deficient? 12)