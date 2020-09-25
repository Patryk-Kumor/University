#lang racket


(define (cont-frac num den k)
  (define (cont-frac2 iterator)
    (cond [(= iterator k) 0]
          [else (/ (num iterator)
                   (+ (den iterator) (cont-frac2 (+ iterator 1))))]))
  (cont-frac2 0))


(define (cont-frac-iter num den k)
  (define (cont-frac2 acc w)
    (cond [(= acc 0) w ]
          [else (cont-frac2 (- acc 1) (/ (num acc) (+ (den acc) w)))]))
  (cont-frac2 k 0))


(cont-frac (lambda (i) 1.0) (lambda (i) 1.0) 0)
(cont-frac (lambda (i) 1.0) (lambda (i) 1.0) 1)
(cont-frac (lambda (i) 1.0) (lambda (i) 1.0) 2)
(cont-frac (lambda (i) 1.0) (lambda (i) 1.0) 3)
(cont-frac (lambda (i) 1.0) (lambda (i) 1.0) 4)
(cont-frac (lambda (i) 1.0) (lambda (i) 1.0) 5)


(cont-frac-iter (lambda (i) 1.0) (lambda (i) 1.0) 0)
(cont-frac-iter (lambda (i) 1.0) (lambda (i) 1.0) 1)
(cont-frac-iter (lambda (i) 1.0) (lambda (i) 1.0) 2)
(cont-frac-iter (lambda (i) 1.0) (lambda (i) 1.0) 3)
(cont-frac-iter (lambda (i) 1.0) (lambda (i) 1.0) 4)
(cont-frac-iter (lambda (i) 1.0) (lambda (i) 1.0) 5)

(define (square x) (* x x))

(+ 3 (cont-frac (lambda (x) (if (= x 1) 3.0 6.0)) (lambda (x) (if (= x 1) 1 (* (square (+ x 1))))) 200))
