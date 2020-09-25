#lang racket

(define (lcons x f)
  (cons x f))

(define (lhead l)
  (car l))

(define (ltail l)
  ((cdr l)))

(define (nats-from m)
  (lcons
   m
   (lambda () (nats-from (+ m 1)))))

(define nats
  (nats-from 0))

(define (take n l)
  (if (or (null? l) (= n 0))
      null
      (cons (lhead l)
            (take (- n 1) (ltail l)))))

(define (filter p l)
  (cond [(null? l) null]
        [(p (lhead l))
         (lcons (lhead l)
                (lambda ()
                  (filter p (ltail l))))]
        [else (filter p (ltail l))]))

(define (prime? n)
  (define (div-by m)
    (cond [(= m n) true]
          [(= (modulo n m) 0) false]
          [else (div-by (+ m 1))]))
  (if (< n 2)
      false
      (div-by 2)))


;; PRZED ZAJ.

(define (fibs-from m n)
  (lcons
   n
   (lambda () (fibs-from n (+ m n)) )))

(define fibs
  (fibs-from 0 1))

(take 10 fibs)

;;

(define (complete-from m)
  (lcons
   m
   (lambda () (complete-from (if (>= m 0) (- (+ m 1)) (- m) )))))

(define complete
  (complete-from 0))

(take 10 complete)




(define (lnat n)
  (cons
   n
   (lambda () (lnat (+ n 1)))))






