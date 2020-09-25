#lang racket

(define (inc x) (+ x 1))
(define (identity x)  x )


(define accumulate
  (lambda (combiner null-value term a next b)
    (if (> a b)
        null-value
        (combiner (term a) (accumulate combiner null-value term (next a) next b) ))))


(define (accumulate-iter combiner null-value term a next b)
  (define (accumulate-iterate a acc)
    (if (> a b)
        acc
        (accumulate-iterate (next a) (combiner acc (term a)))))
  (accumulate-iterate a null-value))


(define (sum beg end)
  (accumulate + 0 identity beg inc end))
(define (sum2 beg end)
  (accumulate-iter + 0 identity beg inc end))
(sum 0 10)
(sum2 0 10)