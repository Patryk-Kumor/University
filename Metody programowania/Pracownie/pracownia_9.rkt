#lang racket

;; pomocnicza funkcja dla list tagowanych o określonej długości

(define (tagged-tuple? tag len p)
  (and (list? p)
       (= (length p) len)
       (eq? (car p) tag)))

(define (tagged-list? tag p)
  (and (pair? p)
       (eq? (car p) tag)
       (list? (cdr p))))

;;
;; WHILE
;;

; memory

(define empty-mem
  null)

(define (set-mem x v m)
  (cond [(null? m)
         (list (cons x v))]
        [(eq? x (caar m))
         (cons (cons x v) (cdr m))]
        [else
         (cons (car m) (set-mem x v (cdr m)))]))

(define (get-mem x m)
  (cond [(null? m) 0]
        [(eq? x (caar m)) (cdar m)]
        [else (get-mem x (cdr m))]))

; arith and bool expressions: syntax and semantics

(define (const? t)
  (number? t))

(define (true? t)
  (eq? t 'true))

(define (false? t)
  (eq? t 'false))

(define (op? t)
  (and (list? t)
       (member (car t) '(+ - * / = > >= < <= not and or mod rand))))

(define (op-op e)
  (car e))

(define (op-args e)
  (cdr e))

(define (op->proc op)
  (cond [(eq? op '+) +]
        [(eq? op '*) *]
        [(eq? op '-) -]
        [(eq? op '/) /]
        [(eq? op '=) =]
        [(eq? op '>) >]
        [(eq? op '>=) >=]
        [(eq? op '<)  <]
        [(eq? op '<=) <=]
        [(eq? op 'not) not]
        [(eq? op 'and) (lambda x (andmap identity x))]
        [(eq? op 'or) (lambda x (ormap identity x))]
        [(eq? op 'mod) modulo]
        [(eq? op 'rand) (lambda (max) (min max 4))])) ; chosen by fair dice roll.
                                                      ; guaranteed to be random.

(define (var? t)
  (symbol? t))

(define (eval-arith e m)
  (cond [(true? e) true]
        [(false? e) false]
        [(var? e) (get-mem e m)]
        [(op? e)
         (apply
          (op->proc (op-op e))
          (map (lambda (x) (eval-arith x m))
               (op-args e)))]
        [(const? e) e]))

;; syntax of commands

(define (assign? t)
  (and (list? t)
       (= (length t) 3)
       (eq? (second t) ':=)))

(define (assign-var e)
  (first e))

(define (assign-expr e)
  (third e))

(define (if? t)
  (tagged-tuple? 'if 4 t))

(define (if-cond e)
  (second e))

(define (if-then e)
  (third e))

(define (if-else e)
  (fourth e))

(define (while? t)
  (tagged-tuple? 'while 3 t))

(define (while-cond t)
  (second t))

(define (while-expr t)
  (third t))

(define (block? t)
  (list? t))

;; state

(define (res v s)
  (cons v s))

(define (res-val r)
  (car r))

(define (res-state r)
  (cdr r))

;; psedo-random generator

(define initial-seed
  123456789)

(define (rand max)
  (lambda (i)
    (let ([v (modulo (+ (* 1103515245 i) 12345) (expt 2 32))])
      (res (modulo v max) v))))

;; WHILE interpreter

(define (old-eval e m)
  (cond [(assign? e)
         (set-mem
          (assign-var e)
          (eval-arith (assign-expr e) m)
          m)]
        [(if? e)
         (if (eval-arith (if-cond e) m)
             (old-eval (if-then e) m)
             (old-eval (if-else e) m))]
        [(while? e)
         (if (eval-arith (while-cond e) m)
             (old-eval e (old-eval (while-expr e) m))
             m)]
        [(block? e)
         (if (null? e)
             m
             (old-eval (cdr e) (old-eval (car e) m)))]))

(define (eval e m seed)
  ;; TODO : ZAD B: Zaimplementuj procedurę eval tak, by
  ;;        działała sensownie dla wyrażeń używających
  ;;        konstrukcji "rand".
  (old-eval e m))

(define (run e)
  (eval e empty-mem initial-seed))

;;

(define fermat-test
      ;; TODO : ZAD A: Zdefiniuj reprezentację programu w jęzku
  '((composite := false)
    (while (> k 0)
           (
            (a := (rand (- n 2)))
            (temp := 1)
            (pow-iter := (- n 1))
            (while (> pow-iter 0)
                   ((temp := (* temp a))
                    (pow-iter := (- pow-iter 1))))   
            (if (= (mod temp n) 1)
                (composite := false)
                (composite := true))
            (if (eq? composite true)
                (k := 0)
                (k := k))                  
            (k := (- k 1))))
  ))

(define (probably-prime? n k) ; check if a number n is prime using
                              ; k iterations of Fermat's primality
                              ; test
  (let ([memory (set-mem 'k k
                (set-mem 'n n empty-mem))])
    (not (get-mem
           'composite
           (eval fermat-test memory initial-seed)))))


;; TESTY pseudo-generatora

(old-eval '( x := (rand -33)) '())
(old-eval '( x := (rand -32)) '())
(old-eval '( x := (rand -16)) '())
(old-eval '( x := (rand -8)) '())
(old-eval '( x := (rand -5)) '())
(old-eval '( x := (rand -4)) '())
(old-eval '( x := (rand -3)) '())
(old-eval '( x := (rand -2)) '())
(old-eval '( x := (rand -1)) '())
(old-eval '( x := (rand 0)) '())
(old-eval '( x := (rand 1)) '())
(old-eval '( x := (rand 2)) '())
(old-eval '( x := (rand 3)) '())
(old-eval '( x := (rand 4)) '())
(old-eval '( x := (rand 5)) '())
(old-eval '( x := (rand 8)) '())
(old-eval '( x := (rand 16)) '())
(old-eval '( x := (rand 32)) '())
(old-eval '( x := (rand 33)) '())

;; TESTY "dla przypomnienia składni"

(display "\n\n")
(old-eval '( (x := (rand 1)) ((x := (rand 2))) ) '())
(old-eval '( (x := (rand 1)) ((x := (rand 2))) ) '( (n . 1) (k . 1)))
(old-eval '(while (> k 0) (k := (- k 1))) '( (n . 1) (k . 10)))
;; 2^2, wynik = temp
(old-eval '(while (> pow-iter 0) ( (temp := (* temp a)) (pow-iter := (- pow-iter 1)))) '( (pow-iter . 2) (a . 2) (temp . 1)))
;; 3^3
(old-eval '(while (> pow-iter 0) ( (temp := (* temp a)) (pow-iter := (- pow-iter 1)))) '( (pow-iter . 3) (a . 3) (temp . 1)))
;; 3^4
(old-eval '(while (> pow-iter 0) ( (temp := (* temp a)) (pow-iter := (- pow-iter 1)))) '( (pow-iter . 4) (a . 3) (temp . 1)))                  

;; TESTY fermat-test - zwracanie

(display "\n\nLICZBY ZŁOŻONE (composite = t): \n")
(old-eval fermat-test '( (n . 2) (k . 25)))
(old-eval fermat-test '( (n . 4) (k . 25)))
(old-eval fermat-test '( (n . 6) (k . 25)))
(old-eval fermat-test '( (n . 8) (k . 25)))
(old-eval fermat-test '( (n . 10) (k . 25)))
(old-eval fermat-test '( (n . 20) (k . 25)))
(old-eval fermat-test '( (n . 200) (k . 25)))
(old-eval fermat-test '( (n . 1000) (k . 25)))

(display "\n\nLICZBY PIERWSZE (composite = f): \n")
(old-eval fermat-test '( (n . 3) (k . 25)))
(old-eval fermat-test '( (n . 5) (k . 25)))
(old-eval fermat-test '( (n . 7) (k . 25)))
(old-eval fermat-test '( (n . 11) (k . 25)))
(old-eval fermat-test '( (n . 13) (k . 25)))
(old-eval fermat-test '( (n . 97) (k . 25)))
(old-eval fermat-test '( (n . 1619) (k . 1)))

;; TESTY fermat-test

(display "\n\nLICZBY ZŁOŻONE (f): \n")
(probably-prime? 2 5)
(probably-prime? 8 5)
(probably-prime? 32 5)
(probably-prime? 1562 5)
(probably-prime? 2222 5)

(display "\n\nLICZBY ZŁOŻONE (t): \n")
(probably-prime? 3 5)
(probably-prime? 5 5)
(probably-prime? 7 5)
(probably-prime? 11 5)
(probably-prime? 13 5)
(probably-prime? 97 5)