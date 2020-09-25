#lang racket

(require racket/contract)

;; ZAD1
;; -------------------------------------------------------

(define/contract (suffixes lista)
  (let ([a (new-∀/c 'a)])
    (-> (listof a) (listof (listof a))))
  
  (if (null? lista) (list '())
                     (cons lista (suffixes (cdr lista)))))

(suffixes '())
(suffixes '(1 2))
(suffixes '(1 2 3))

;; ZAD2
;; -------------------------------------------------------

(define/contract (sqrt x)
  (->i ([x number?])
       [result number?]
       #:post (result x)
       (and/c (number? x) (positive? x)))
  (* x x))

;; ZAD3
;; -------------------------------------------------------
;; A)
(define/contract (filter pred xs)
    (let ([a (new-∀/c 'a)])
    (-> (-> a boolean?) (listof a) (listof a)))
  (cond [(null? xs)
         null]
        [(pred (car xs))
         (cons (car xs) (filter pred (cdr xs)))]
        [else
         (filter pred (cdr xs))]
      ))
;; B)
(define/contract (filter2 pred xs)
  (let ([a (new-∀/c 'a)])
    (->i ([pred (-> a boolean?)]
          [xs (listof a)])
         [result (listof a)]
         #:post (result pred xs)
         (listof a)
                 ))
  
  (cond [(null? xs)
         null]
        [(pred (car xs))
         (cons (car xs) (filter2 pred (cdr xs)))]
        [else
         (filter2 pred (cdr xs))]
      ))