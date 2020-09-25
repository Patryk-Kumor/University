#lang racket



;; ĆW 1
;; własności z wykładu:
;; (car (cons x y)) = x 
;; (cdr (cons x y)) = y 
;; (pair? (cons x y)) = true 
;; (pair? x) = false , wpp

(define (make-rat n d)
  (if (= d 0) #f
        (let ([x (gcd n d)])
          (list (/ n x) (/ d x)))))
          ;(cons (/ n x) (cons (/ d x) null)))))

(define (rat-num l)
  (car l))

(define (rat-den l)
  (car (cdr l)))

(define (rat? l)
 (and (list? l) (list? (cdr l)) (null? (cdr (cdr l))) (not (= (rat-den l) 0))) )

;; testy ĆW1

(define x (make-rat 1 2))
(rat-num x)
(rat-den x)
(rat? x)


(list 1 2 3 null 4 5 6)


;; ĆW 2

;; punkty
(define (make-point x y)
  (cons x y))

(define (point? p)
  (and (pair? p)))

(define (point-x p)
  (car p))

(define (point-y p)
  (cdr p))

;; wektory
(define (make-vect x1 y1 x2 y2)
  (cons (make-point x1 y1) (make-point x1 y2)))

(define (vect? v)
  (and (pair? v) (pair? (car v)) (pair? (cdr v))))

(define (vect-begin v)
  (car v))

(define (vect-end v)
  (cdr v))

;; reszta

(define (display-point p )
  (display "(")
  (display ( point-x p ))
  (display ", ")
  (display ( point-y p ))
  (display ")"))

(define (display-vect v )
  (display "[")
  (display-point (vect-begin v ))
  (display ", ")
  (display-point (vect-end v ))
  (display "]"))

(define (square x) (* x x))
(define (vect-lenght v)
  (sqrt (+ (square (- (point-x (car v))
                (point-x (cdr v))))
     (square (- (point-y (car v))
                (point-y (cdr v)))))))

(define (vect-scale v k)
  (let ([x0 (point-x (vect-begin v))]
        [y0 (point-y(vect-begin v))]
        [x (- (point-x (vect-begin v))
              (point-x (vect-end v)))]
        [y (- (point-y (vect-begin v))
              (point-y (vect-end v)))])
    (make-vect x0 y0 (+ x0 (* x k)) (+ y0 (* y k)))))

(define (vect-translate v p)
  (let ([x (- (point-x (vect-begin v))
              (point-x (vect-end v)))]
        [y (- (point-y (vect-begin v))
              (point-y (vect-end v)))])
    (make-vect (point-x p) (point-y p) (+ (point-x p) x) (+ (point-y p) y))))

;; testy ĆW2

(define a (make-point 1 2))

(define b (make-point 2 3))

(define v (make-vect 1 2 3 4))

(define len (vect-lenght v))
len



;; kartkówka
(define (f x)
  (+ x
     ((lambda (x) (* (f x)
                    (sin x))
       ) x)))



;; ĆW 6
(define (permi xs)
  (define (insert el xs acc)
    (if (= acc 0) (cons el xs)
                  (insert el (cdr xs) (+ acc 1))))
  (define (permi3 xs L3 acc)
    (if (> acc (length L3))
        null
        (cons (insert L3 xs acc) (permi3 xs L3 (+ acc 1)))))
  (define (permi2 xs ys)
    (if (null? ys)
        null
        (append (permi3 xs (car ys) 0) (permi2 xs (cdr ys))) ))
  (if (null? xs)
      (cons xs null)
      (permi2 (car xs) (permi (cdr xs)))))

(define xs (list 1 2 3))
(define permixs (permi xs))
permixs