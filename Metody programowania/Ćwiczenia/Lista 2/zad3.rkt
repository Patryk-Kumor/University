#lang racket

(define (square a) (* a a))

(define (inc b) (+ b 1))

(define (compose f g)
  (lambda (x) (f (g x))))

;--------------------------------------;

(define (repeated p n)
  (cond [(= n 0) identity]
        [(= n 1) p]
        [else (compose p (repeated p (- n 1)))] ))

((repeated inc 0) 4)
((repeated inc 0) 1)

((repeated inc 1) 4)
((repeated inc 1) 1)

((repeated inc 2) 4)
((repeated inc 2) 1)