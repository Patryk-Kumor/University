#lang racket


(define product
  (lambda (term next s e)
    (if (> s e)
        1
        (* (term s) (product term next (next s) e)) )))

(define (product2 term next s e w)
    (if (> s e)
        w
        (product2 term next (next s) e (* (term s) w))))
     
 
(define (inc x) (+ x 1))

(define (duble x) (+ x 2))

(define (square x) (* x x))

(define (help x) (/ (* x (duble x))
                    (* (square (inc x)))))



(define pi
  (* 4 (product help duble 2.0 10000) ) )

(define mypi
  (* 4 (product2 help duble 2.0 10000 1) ) )

mypi

















