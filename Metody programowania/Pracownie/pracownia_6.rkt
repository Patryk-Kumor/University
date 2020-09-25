#lang racket

(define (const? t)
  (number? t))

(define (binop? t)
  (and (list? t)
       (= (length t) 3)
       (member (car t) '(+ - * /))))

(define (binop-op e)
  (car e))

(define (binop-left e)
  (cadr e))

(define (binop-right e)
  (caddr e))

(define (binop-cons op l r)
  (list op l r))

(define (op->proc op)
  (cond [(eq? op '+) +]
        [(eq? op '*) *]
        [(eq? op '-) -]
        [(eq? op '/) /]))

(define (let-def? t)
  (and (list? t)
       (= (length t) 2)
       (symbol? (car t))))

(define (let-def-var e)
  (car e))

(define (let-def-expr e)
  (cadr e))

(define (let-def-cons x e)
  (list x e))

(define (let? t)
  (and (list? t)
       (= (length t) 3)
       (eq? (car t) 'let)
       (let-def? (cadr t))))

(define (let-def e)
  (cadr e))

(define (let-expr e)
  (caddr e))

(define (let-cons def e)
  (list 'let def e))

(define (var? t)
  (symbol? t))

(define (var-var e)
  e)

(define (var-cons x)
  x)

(define (hole? t)
  (eq? t 'hole))

(define (arith/let/holes? t)
  (or (hole? t)
      (const? t)
      (and (binop? t)
           (arith/let/holes? (binop-left  t))
           (arith/let/holes? (binop-right t)))
      (and (let? t)
           (arith/let/holes? (let-expr t))
           (arith/let/holes? (let-def-expr (let-def t))))
      (var? t)))

(define (num-of-holes t)
  (cond [(hole? t) 1]
        [(const? t) 0]
        [(binop? t)
         (+ (num-of-holes (binop-left  t))
            (num-of-holes (binop-right t)))]
        [(let? t)
         (+ (num-of-holes (let-expr t))
            (num-of-holes (let-def-expr (let-def t))))]
        [(var? t) 0]))

(define (arith/let/hole-expr? t)
  (and (arith/let/holes? t)
       (= (num-of-holes t) 1)))

(define (hole-context e)
  ;; pomocniczo
  ;;(display e) (display "\n")
  (define (hole e)
    (cond
      [(hole? e) '()]
      [(const? e) #f]
      [(var? e) #f]
      [(binop? e)
       (let ([left (hole (binop-left e))]
             [right (hole (binop-right e))])
         (cond [left left]
               [right right]
               [else #f]))]
      [(let? e)
       (let ([def-var (let-def-var (let-def e))]
             [def-expr (hole (let-def-expr (let-def e)))]
             [expr (hole (let-expr e))])
         (cond [def-expr def-expr]
               [expr (cons (var-cons def-var) expr)]
               [else #f]))]))
  ;; główne wywołanie + sprawdzanie poprawności
  (if (and (arith/let/holes? e)
           (arith/let/hole-expr? e))
      (remove-duplicates (hole e))      
      #f)) ;; niepoprawna ilość dziur / niepoprawna struktura danych

;; Druga wersja -> z kosmiczną złożonością
#|
(define (hole-context2 e)
  ;; funkcje pomocnicze -> dodatkowe
  (define (insert el lst)
    (if (member el lst)
        lst
        (cons (var-cons el) lst)))    
  ;; funkcje pomocnicze -> akumulator
  (define (hole-context-acc e acc)
    (cond
      [(hole? e) acc]
      [(let? e)
       (let ([new-acc (insert (let-def-var (let-def e)) acc)])
         (if (arith/let/hole-expr? (let-def-expr (let-def e)))
             (hole-context-acc (let-def-expr (let-def e)) acc)
             (hole-context-acc (let-expr e) new-acc)))]
      [(binop? e)
       (cond    
             [(arith/let/hole-expr? (binop-left e))
              (hole-context-acc (binop-left e) acc)]
             [(arith/let/hole-expr? (binop-right e))
              (hole-context-acc (binop-right e) acc)])]
      [else '()]))
  ;; główne wywołanie
  (if (and (arith/let/holes? e)
           (arith/let/hole-expr? e))
      (hole-context-acc e '())
      #f)) ;; niepoprawna ilość dziur
|#

(define (test)
  ;; pomocniczo
  (define (var<? x y)
    (symbol<? x y))
  (define (is-ok? list1 list2)
    (if list1
        (equal? (sort list1 var<?) (sort list2 var<?))
        #f)) 
  ;; z polecenia:
  (and (is-ok?  (hole-context '(+ 3 hole ))
                '())
       (is-ok?  (hole-context '(let (x 3) (let (y 7) (+ x hole ))))
                '(y x))
       (is-ok?  (hole-context '(let (x 3) (let (y hole ) (+ x 3)))) 
                '(x))
       (is-ok?  (hole-context '(let (x hole) (let (y 7) (+ x 3)))) 
                '())
       (is-ok?  (hole-context '(let (piesek 1) (let (kotek 7) (let (piesek 9) (let (chomik 5) hole )))))
                '(chomik piesek kotek)) 
       (is-ok?  (hole-context '(+ (let (x 4) 5) hole )) 
                '())
  ;; własne:
       (is-ok?  (hole-context 'hole )
                '())
       (is-ok?  (hole-context '(+ (* 1 (- 1 hole)) (/ 1 1)) )
                '())
       (is-ok?  (hole-context '(let (x x) (+ x hole)))
                '(x))
       (is-ok?  (hole-context '(let (x hole) (+ x x)))
                '())
       (is-ok?  (hole-context '(let (x (let (x x) hole)) (+ x x)))
                '(x))
       (is-ok?  (hole-context '(let (x (let (x x) hole)) (+ x x)))
                '(x))
       (is-ok?  (hole-context '(let (x (let (y x) hole)) (+ x x)))
                '(y))
       (is-ok?  (hole-context '(let (x (let (y x) 1)) (+ x (let (y x) hole))))
                '(x y))       
       (is-ok?  (hole-context '(let (a 1) (let (a 2) (let (a 3) (let (a 4) (let (a 5) (let (a 6) (let (a 7) (let (a 8) (let (a 9) (let (a 10) hole)))))))))))
                '(a))
       (is-ok?  (hole-context '(let (a 1) (let (b 2) (let (c 3) (let (d 4) (let (e 5) (let (f 6) (let (g 7) (let (h 8) (let (i 9) (let (j 10) hole)))))))))))
                '(j i h g f e d c b a))
       (is-ok?  (hole-context '(let (a 1) (let (b 2) (let (a 3) (let (b 4) (let (a 5) (let (b 6) (let (a 7) (let (b 8) (let (a 9) (let (b 10) hole)))))))))))
                '(b a))
       (is-ok?  (hole-context '(let (a 1) (let (a 2) (let (a 3) (let (a 4) (let (a 5) (let (a 6) (let (a 7) (let (a 8) (let (a 9) (let (b hole) a)))))))))))
                '(a))
       (is-ok?  (hole-context '(+ 1 (let (a 1) (let (a 2) (let (a 3) (let (a 4) (let (a 5) (let (a 6) (let (a 7) (let (a 8) (let (a 9) (let (b hole) a))))))))))))
                '(a))
       (is-ok?  (hole-context '(+ (let (a 1) (let (a 2) (let (a 3) (let (a 4) (let (a 5) (let (a 6) (let (a 7) (let (a 8) (let (a 9) (let (a a) a)))))))))) hole))
                '())
       ))