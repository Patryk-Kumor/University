#lang racket


(define (prefixes xs)
  (define (helper xs acc)
    (cond [(null? xs) acc]
          [else
             (helper (cdr xs) (cons (append (first acc) (list (car xs))) acc))]))
  (helper (cdr xs) (list (list  (car xs))) ))