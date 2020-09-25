#lang racket


;; procedury "wykładowe"
(define (inc x) (+ x 1))
(define (dec x) (- x 1))
(define (dist x y)
  (abs (- x y)))
(define (close-enough? x y)
  (< (dist x y) 0.000000001))
;; złożenie f(g(x))
(define (compose f g)
  (lambda (x) (f (g x))))
;; n-krotne złożenie
(define (repeated p n)
  (cond [(= n 0) identity]
        [(= n 1) p]
        [else (compose p (repeated p (- n 1)))] ))
;; obliczanie (przybliżonego) punktu stałego funkcji f przez iterację
(define (fix-point f x0)
  (let ((x1 (f x0)))
    (if (close-enough? x0 x1)
        x0
        (fix-point f x1))))
;; próba obliczania pierwiastka kwadratowego z x jako punktu stałego funkcji y ↦ x / y zapętla się
;; stosujemy tłumienie z uśrednieniem: procedurę wyższego rzędu zwracającą procedurę jako wynik
(define (average-damp f)
  (lambda (x) (/ (+ x (f x)) 2)))



;; ROZWIĄZANIE
(define (nth-root x n)
  (define (how-many n)
    (cond [(= n 1) 0]
          [else (floor (log x n))]))
  (let ([k (how-many n)])
       (fix-point  ((repeated average-damp k) (lambda (y) (/ x (expt y (dec n))))) 1.0)))



;; Do testów
(define (nth-root-test x n k)
  (fix-point  ((repeated average-damp k) (lambda (y) (/ x (expt y (dec n))))) 1.0))



;; ------TESTY------
(display "--- TESTY DLA POTĘG DWÓJKI ---\n")
(display "\nn=1, 0 tłumień OK\n")
(nth-root-test 2 1 0) 
(display "n=2, 1 tłumienie OK\n")
(nth-root-test 4 2 1) 
(display "n=3, 1 tłumienie OK\n")
(nth-root-test 8 3 1) 
(display "n=4, 2 tłumienia OK\n")
(nth-root-test 16 4 2) 
(display "n=5, 2 tłumienia OK\n")
(nth-root-test 32 5 2) 
(display "n=6, 2 tłumienia OK\n")
(nth-root-test 64 6 2) 
(display "n=7, 2 tłumienia OK\n")
(nth-root-test 128 7 2) 
(display "n=8, 3 tłumienia OK\n")
(nth-root-test 256 8 3)
(display "\nNa tym etapie zauważamy że wymagana ilość złożeń odpowiada 2^c,\n")
(display "czyli uogólniając - to wyszło przy testach liczb innych niż 2 -\n") 
(display "należy dla pierwiastka o podstawie x ")
(display "używać liczby złożeń \nrównej podzłodze z ")
(display "logarytmu o podstawie x z n (floor (log x n))\n\n")
(display "...n od 8 do 15, 3 złożenia OK\n")
(display "n=16, 4 tłumienia OK\n")
(nth-root-test (expt 2 16) 16 4)
(display "...n od 16 do 31, 4 złożenia OK\n")
(display "n=32, 5 tłumień OK\n")
(nth-root-test (expt 2 32) 32 5)
(display "...n od 32 do 63, 5 złożeń OK\n")
(display "n=64, 6 tłumień OK\n")
(nth-root-test (expt 2 64) 64 6)
(display "n od 64 do 127, 6 złożeń OK\n")
(display "n=128, 7 tłumień OK\n")
(nth-root-test (expt 2 128) 128 7)
(display "...i tak dalej\n")


(display "\n\n--- TESTY POPRAWNOŚCI DLA POTĘG TRÓJKI --- \n(nth-root (expt 3 i) i)\n")
(for  ([i '(1 2 3 4 5 6 7 8 9 15 16 20 32)])
  (display "\n(i=")
  (display i)
  (display ")   ")
  (display (nth-root (expt 3 i) i)))


(display "\n\n\n--- TESTY POPRAWNOŚCI DLA POTĘG CZWÓRKI --- \n(nth-root (expt 4 i) i)\n")
(for  ([i '(1 2 3 4 5 6 7 8 9 15 16 20 32)])
  (display "\n(i=")
  (display i)
  (display ")   ")
  (display (nth-root (expt 4 i) i)))


(display "\n\n\n--- TESTY DLA RÓŻNYCH PIERWIASTKÓW k-stopnia --- \n")
(display "tu: (testy 5) - dla stopnia 5\n\n")
(define (testy k)
  (define (test x)
    (fprintf (current-output-port)
             "Pierwiastek stopnia ~a z ~a\n-biblioteczny: ~a\n-nth-root:    ~a\n\n"
             k
             x
             (cond [(>= x 0) (expt x (/ 1 2))]
                   [else (- (expt (- x) (/ 1 2)))])             
             (nth-root x 2)))
  (for  ([i '(1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 25)]) (test i)))
(testy 5)
