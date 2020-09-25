#lang typed/racket

(: prefixes (All (A) (-> (Listof A) (Listof (Listof A)))))
(define (prefixes xs)
  (: helper (-> (Listof A) (Listof (Listof A)) (Listof (Listof A))))
  (define (helper xs acc)
    (cond [(null? xs) acc]
          [else
             (helper (cdr xs) (cons (append (first acc) (list (car xs))) acc))]))
  (reverse (helper (cdr xs) (list (list  (car xs))) )))