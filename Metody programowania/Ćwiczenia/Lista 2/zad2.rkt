#lang racket


(define (square a) (* a a))

(define (inc b) (+ b 1))

(define (compose f g)
  (lambda (x) (f (g x))))


;--------------------------------------;


((compose square inc) 5)
; ((compose square inc) 5)
; (lambda (5) (square (inc x))) 
; (lambda (5) (square (+ x 1))) 
; (lambda (5) (* (+ x 1) (+ x 1))) 
; (* (+ 5 1) (+ 5 1) )
; (* 6 6)
; 36
; debuggerowo:
; ((compose square inc) 5)
; (lambda (5) (square (inc x)))
; (square (inc 5)))
; (square (+ 5 1))
; (square 6)
; (* 6 6)
; 36


((compose inc square) 5)
; ((compose inc square) 5)
; (lambda (5) (inc (square x)))
; (lambda (5) (inc (* x x)))
; (lambda (5) (+ (* x x) 1))
; (+ (* 5 5) 1)
; (+ 25 1)
; 26
; debuggerowo:
; ((compose inc square) 5)
; (lambda (5) (inc (square x)))
; (inc (square 5))
; (inc (* 5 5))
; (inc 25)
; (+ 25 1)
; 26