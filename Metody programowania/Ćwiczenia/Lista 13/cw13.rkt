#lang racket

(require racklog)

;; predykat unarny %male reprezentuje zbiór mężczyzn
(define %male
  (%rel ()
        [('adam)]
        [('john)]
        [('joshua)]
        [('mark)]
        [('david)]))

;; predykat unarny %female reprezentuje zbiór kobiet
(define %female
  (%rel ()
        [('eve)]
        [('helen)]
        [('ivonne)]
        [('anna)]))

(define %is-kain-or-abel
  (%rel (x)
     [(x)
      (%parent 'adam x)
      (%parent 'eve  x)
      (%= x 'kain)]
     [('abel)]
     ))


;; predykat binarny %parent reprezentuje relację bycia rodzicem
(define %parent
  (%rel ()
        [('adam 'helen)]
        [('adam 'abel)]
        [('adam 'anna)]
        [('eve 'helen)]
        [('eve 'ivonne)]
        [('eve 'anna)]
        [('john 'joshua)]
        [('helen 'joshua)]
        [('ivonne 'david)]
        [('mark 'david)]))

;; predykat binarny %sibling reprezentuje relację bycia rodzeństwem
(define %sibling
  (%rel (a b c)
        [(a b)
         (%parent c a)
         (%parent c b)]))

;; predykat binarny %sister reprezentuje relację bycia siostrą
(define %sister
  (%rel (a b)
        [(a b)
         (%sibling a b)
         (%female a)]))

;; predykat binarny %ancestor reprezentuje relację bycia przodkiem
(define %ancestor
  (%rel (a b c)
        [(a b)
         (%parent a b)]
        [(a b)
         (%parent a c)
         (%ancestor c b)]))

;; ZADANIE 1

(define %ismother
  (%rel (a b)
        ([a]
         [%female a]
         [%parent a b])))

(define %isfather
  (%rel (a b)
        ([a]
         [%male a]
         [%parent a b])))

(define %grandson
  (%rel (a b c)
        ([a b]
         [%parent a c]
         [%parent c b])))

(define %cousin
  (%rel (a b c)
        ([a b]
         [%grandson c a]
         [%grandson c b])))

;; ZADANIE 2

(%find-all () (%ancestor 'mark 'john))

(%find-all (x) (%ancestor 'adam x))

(%find-all (x) (%sister 'ivonne x))

(%find-all (x y) (%cousin x y))

(display "\n\n")

;;------------------------------------------------------------------

;; ZADANIE 5

(%which (x y z) (%= (list 'a (list x x) (list y y))
                (list x y z)
                ))

;(list ’f (’g x) x) i (list ’f y ’a)
(%which (x y) (%= (list 'f '('g x) x) (list 'f y 'a)))

;(%which (x) (%= (list 'f x) x)) pętla

(%which (x y) (%= x (list 'g y)))

(%which (x) (%= (list 'a) (list 'a x)))

(%which (x) (%= (list 'a) (cons 'a x)))

(%which (x y z) (%= (list 'a (list x x) (list y y))  (list x y z)))

(display "\n\n")
;;------------------------------------------------------------------
;; ZADANIE 6

(define %sublist
  (%rel (a b c d)
        [('() a)]
        [((cons a b) (cons a c))
         (%sublist b c)]
        [((cons a b) (cons c d))
         (%sublist (cons a b) d)])
  )

;(%which (x) (%sublist x '(1 2 3) ))

;; ZADANIE 7

(define %select
  (%rel (x xs y ys)
        [(x (cons x xs) xs)]
        [(y (cons x xs) (cons x ys))
         (%select y xs ys)]))

(define %perm
  (%rel (x xs zs ys)
        [(null null )]
        [((cons x xs) ys)
         (%select x ys zs)
         (%perm xs zs)]))

;(%which (x) (%perm x '(1 2 3) ))

;; ZADANIE 8

(define (list->num list)
  (define (help list acc)
    (if (null? (cdr list)) (car list)
                         (+ (* acc (car list)) (help (cdr list) (/ acc 10)))))
  (help list (expt 10 (- (length list) 1)))
  )
