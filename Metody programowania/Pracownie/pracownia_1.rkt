#lang racket


;; funkcja główna
(define (cube-root x)
  ;; lokalne definicje pomocnicze
  (define (distance x y)
    (abs (- x y)))
  (define (square x)
    (* x x))
  (define (cube x)
    (* x x x))
  ;; poprawienie przybliżenia pierwiastka trzeciego stopnia z x
  (define (improve approx)
    (/ (+ (/ x (square approx)) (* 2 approx)) 3))
  ;; sprawdzanie dokładności 
  (define (good-enough? approx)
    (< (distance x (cube approx)) 0.000001))
  ;; główna procedura znajdująca rozwiązanie
  (define (iterate approx)
    (cond
      [(good-enough? approx) approx]
      [else (iterate (improve approx))]))
  ;; właściwe wywołanie
  ;;(iterate 1.0))
  (cond
    [(>= x 0) (iterate 1.0)]
    [(< x 0) (iterate -1.0)]))


;; testy
;; adnotacja do testów: zwykła funkcja biblioteczna pierwiastka trzeciego
;; stopnia dla liczby ujemnej zwraca jedynie liczby zespolone,
;; więc wynik biblioteczny wyliczany jest za pomocą podwójnej zmiany znaku
(define (testy)
  (define (test x)
    (fprintf (current-output-port)
             "Pierwiastek trzeciego stopnia z ~a\n-biblioteczny: ~a\n-cube-root:    ~a\n\n"
             x
             (cond [(>= x 0) (expt x (/ 1 3))]
                   [else (- (expt (- x) (/ 1 3)))])             
             (cube-root x)))
  (for  ([i '(-2147483648 -1000 -125 -64 -27 -10 -9 -8 -7 -6 -5 -4 -3 -2 -1.5 -1 -0.5 -0.008
              0 0.008 0.5 1 1.5 2 3 4 5 6 7 8 9 10 27 64 125 1000 2147483647)]) (test i)))


;; testowanie
(testy)