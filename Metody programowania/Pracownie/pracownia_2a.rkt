#lang racket



;; definicje "wykładowe"
(define (identity x) x)
(define (inc x) (+ x 1))
(define (dec x) (- x 1))
(define (dist x y)
    (abs (- x y)))
(define (close-enough? x y)
    (< (dist x y) 0.000001))
(define (square x) (* x x))



; rozwiązanie
(define (cont-frac N D)
  (define (newA An-2 An-1 n) (+ (* (D n) An-1)
                                (* (N n) An-2)))
  (define (newB Bn-2 Bn-1 n) (+ (* (D n) Bn-1)
                                (* (N n) Bn-2)))
  (define (newF An Bn n) (/ An Bn))
  (define (iterate An-2 An-1 Bn-2 Bn-1 Fn-1 n)
    (let ([An (newA An-2 An-1 n)]
          [Bn (newB Bn-2 Bn-1 n)])
      (let ([Fn (newF An Bn n)])
         (if (close-enough? Fn-1 Fn) Fn
             (iterate An-1 An Bn-1 Bn Fn (inc n))))))
  (iterate 1 0 0 1  0  1.0))



;; ---- TESTY ----
;; ---------------

;; złoty środek +- 0.618
(display "Złoty środek +- 0.618\n")
(cont-frac (lambda (x) 1.0) (lambda (x) 1.0))

;; pierwiastek sqrt
;; zgodnie z zasadą sqrt( a^2 + b) = a + x ; x = b/(2a + x)
;;  ---
;; pierwiastek z 13 = 3.60555127546
(display "\nPierwiastek z 13 = 3.60555127546\n")
(+ 3 (cont-frac (lambda (x) 4.0) (lambda (x) 6.0)))
;; pierwiastek z 18 = 4.24264068712
(display "\nPierwiastek z 18 = 4.24264068712\n")
(+ 4 (cont-frac (lambda (x) 2.0) (lambda (x) 8.0)))
;; uogólnienie pierwiastków kwadratowych
(define (sqrt x)
  (let ([a x])
    (+ 1 (cont-frac (lambda (y) (- a 1)) (lambda (y) 2.0) ))))
;; pierwiastek z 2 = 1.41421356237
(display "\nPierwiastek z 2 = 1.41421356237\n")
(sqrt 2)
;; pierwiastek z 3 = 1.41421356237
(display "\nPierwiastek z 3 = 1.73205080756\n")
(sqrt 3)
;; pierwiastek z 4 = 2
(display "\nPierwiastek z 4 = 2\n")
(sqrt 4)

;; pi z zadania 7
(display "\nPi\n")
(+ 3 (cont-frac (lambda (x) (square (- (* 2 x) 1))) (lambda (x) 6.0)))

;; powinno wyjść +-0.58
(display "\n1/(1 + 2/(2 + 3/(3 + ...))) = +- 0.58\n")
(cont-frac ( lambda (x) x) ( lambda (x) x))

;; tangens
(define pi/4 (/ 3.14159265359 4))
(define (tangens x)
  (let ([a x])
    (cont-frac (lambda (y) (if (= y 1) a (-(square a)))) (lambda (y)  (- (* 2 y) 1)))))
;; tanges pi/6
(display "\nTangens pi/6 = sqrt(3)/3\n")
(tangens (/ pi 6))
;; tanges pi/4
(display "\nTangens pi/4 = 1\n")
(tangens (/ pi 4))
;; tanges pi/3
(display "\nTangens pi/3 = sqrt(3)\n")
(tangens (/ pi 3))
;; tanges pi/3
(display "\nTangens pi/3 = sqrt(3)\n")
(tangens (/ pi 3))
;; tanges 1
(display "\nTangens 1 = ")
(tan 1)
(tangens 1)
;; tanges 1/2
(display "\nTangens 1/2 = ")
(tan 0.5)
(tangens 0.5)

;; arctan x
(define (arctan x)
  (let ([a x])
    (cont-frac (lambda (y) (if (= y 1) a (square (* (dec y) a)))) (lambda (y)  (- (* 2 y) 1)))))
;; arctan pi/6)
(display "\nArctan pi/6 = ")
(atan (/ pi 6))
(arctan (/ pi 6))
;; arctan pi/4)
(display "\nArctan pi/4 = ")
(atan (/ pi 4))
(arctan (/ pi 4))
;; arctan pi/3)
(display "\nArctan pi/3 = ")
(atan (/ pi 3))
(arctan (/ pi 3))
;; arctan pi/2)
(display "\nArctan pi/2 = ")
(atan (/ pi 2))
(arctan (/ pi 2))
;; arctan 1)
(display "\nArctan 1 = ")
(atan 1)
(arctan 1)
;; arctan 1/2)
(display "\nArctan 1/2 = ")
(atan 0.5)
(arctan 0.5)