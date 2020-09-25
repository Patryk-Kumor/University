#lang racket

(define (make-cycle-helper or-first list)
  (if (null? (mcdr list))
      (set-mcdr! list or-first)
      (make-cycle-helper or-first (mcdr list))))

(define (make-cycle list)
  (if (null? list)
      null
      (make-cycle-helper list list)))

(define x (mcons 1 (mcons 2 null)))
(make-cycle x)

;
;

(define (has-cycle? list)
  (define (contains? list elem)
    (if (null? list)
        false
        (if (eq? (mcar list) elem)
                 true
                 (contains? (mcdr list) elem))))
  (define (has-cycle-helper visited list)
    (if (null? list)
        false
        (if (contains? visited list)
            true
            (has-cycle-helper (mcons list visited) (mcdr list)))))
  (has-cycle-helper '() list))