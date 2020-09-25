#lang racket

;; expressions

(define (const? t)
  (number? t))

(define (op? t)
  (and (list? t)
       (member (car t) '(+ - * /))))

(define (op-op e)
  (car e))

(define (op-args e)
  (cdr e))

(define (op-cons op args)
  (cons op args))

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

(define (arith/let-expr? t)
  (or (const? t)
      (and (op? t)
           (andmap arith/let-expr? (op-args t)))
      (and (let? t)
           (arith/let-expr? (let-expr t))
           (arith/let-expr? (let-def-expr (let-def t))))
      (var? t)))

;; let-lifted expressions

(define (arith-expr? t)
  (or (const? t)
      (and (op? t)
           (andmap arith-expr? (op-args t)))
      (var? t)))

(define (let-lifted-expr? t)
  (or (and (let? t)
           (let-lifted-expr? (let-expr t))
           (arith-expr? (let-def-expr (let-def t))))
      (arith-expr? t)))

;; generating a symbol using a counter

(define (number->symbol i)
  (string->symbol (string-append "x" (number->string i))))

;; environments (could be useful for something)

(define empty-env
  null)

(define (add-to-env x v env)
  (cons (list x v) env))

(define (find-in-env x env)
  (cond [(null? env) (error "undefined variable" x)]
        [(eq? x (caar env)) (cadar env)]
        [else (find-in-env x (cdr env))]))

;; the let-lift procedure

(define (let-lift e)
  ;; pomocniczo - zamiana wszystkich wystąpień z x na x2
  (define (rename x x2 e)
    (cond      
      [(const? e) e]
      [(var? e)
       (if (eq? e x) x2 e)]
      [(op? e) (cons (op-op e)
               (map (lambda (a) (rename x x2 a)) (op-args e)))]
      [(let? e)
       (let* ([def-var (rename x x2 (let-def-var (let-def e)))]
              [def-expr (rename x x2 (let-def-expr (let-def e)))]
              [expr (rename x x2 (let-expr e))])
         (let-cons (let-def-cons def-var def-expr) expr))]))
  ;; pomocniczo - aplikacja let-lift-help (zamiana zmiennych przy letach) dla elementów list przy op
  (define (op-helper args env acc)
    (cond [(null? args) null]
          [else
           (let* ([e (car args)]
                  [new-e (car (let-lift-help e env acc))]
                  [new-acc (cdr (let-lift-help e env acc))])
             (cons (cons new-e new-acc) (op-helper (cdr args) env new-acc)))]))    
  ;; pomocniczo - zmiana nazw zmiennych związanych w lecie
  (define (let-lift-help e env acc)
    (cond      
      [(const? e) (cons e acc)]
      [(var? e) (cons e acc)]
      [(op? e)
       (let* ([op (op-op e)]
              [args (op-args e)]
              [new-list (op-helper args env acc)]
              [acc (cdr (car (reverse new-list)))])
         (cons (cons op new-list) acc))]
      [(let? e)
       (let* ([def-expr (let-def-expr (let-def e))]
              [def-expr2 (let-lift-help def-expr env acc)]
              [new-acc (cdr def-expr2)]              
              [def-var (let-def-var (let-def e))]
              [new-var (number->symbol new-acc)]          
              [expr (rename def-var new-var (let-expr e))]
              [expr2 (let-lift-help expr env (+ new-acc 1))]
              [new-acc2 (cdr expr2)])
         (cons (let-cons (let-def-cons new-var def-expr2) expr2) new-acc2))]))
  ;; pomocniczo - powrót do normalnego stanu (bez par (e . acc))
  (define (transform-list args)
    (cond [(null? args) null]
          [else
           (let* ([e (car args)]
                  [wyr (let-lift-form e)])
             (cons wyr (transform-list (cdr args))))]))
  (define (let-lift-form e)
    (cond      
      [(const? (car e)) (car e)]
      [(var? (car e)) (car e)]
      [(op? (car e))
       (cons (op-op (car e))  (transform-list (op-args (car e))))]                      
      [(let? (car e))
         (let* ([e (car e)]
                [var (car (second e))]
                [def-expr (let-lift-form (second (second e)))]
                [expr (let-lift-form (third e))])
           (let-cons (let-def-cons var def-expr) expr))]))
  ;;  merge par -> '( '(a . b) '(a . b) ) = '( '(a a) '(b b))
  (define (merge op pairs defs ar)   
    (cond [(null? pairs) (list   defs (cons op  ar))]
          [else
           (let ([e (let-lift-transform (car pairs))])
           (merge op
                  (cdr pairs)
                  (append defs (car e))
                  (append ar (cdr e)))   )]))
  ;; główny transform  
  (define (let-lift-transform e)
    (cond      
      [(const? e) (cons '() (list e) )]
      [(var? e) (cons '() (list e) )]
      [(op? e)
       (merge (op-op e) (op-args e) '() '())]
      [(let? e) 
       (let* ([def-var (let-def-var (let-def e))]
              [def-expr (let-lift-transform (let-def-expr (let-def e)))]
              [expr (let-lift-transform (let-expr e))])
         ;; ważna jest tu kolejność !! (Później lety są budowane od początku do końca listy defs)
         (cons
          (append
           (car def-expr)
           (list (cons def-var (cdr def-expr)))
           (car expr))
          (cdr expr)))]))
  ;; zamiana na let
  (define (let-lift-transform-2 defs ar)
    (cond [(null? defs) (car ar)]
          [else
           (let-cons
                 (let-def-cons (car (car defs))
                               (car (cdr (car defs))))
                 (let-lift-transform-2 (cdr defs) ar)) ]))
  ;; główne wywołanie
  (let*
      ([before (let-lift-transform (let-lift-form (let-lift-help e null 0)))] ; ze zmianą zmiennych 
      ;([before (let-lift-transform e)] ; bez zmiany zmiennych
       [after (let-lift-transform-2 (car before) (cdr before))]) after))

;; testy
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; z polecenia

(define test1 '(+ 10 (* (let (x 7) (+ x 2)) 2))) 

(define test2 '(let (x (- 2 (let (z 3) z))) (+ x 2)))

(define test3 '(+ (let (x 5) x) (let (x 1) x)))

;; własne

(define test4 '(let (x 1) 2))

(define test5 '(+ (let (x 1) x)
                  (let (y (let (y2 22) y2)) (let (y3 222) y3))
                  (let (x 3) x)
                  (let (x 4) x)
                  (let (x 5) x)))
                                 
(define test6 '(+ 1 2 3 4 5))

(define test7 '(+ (let (a 1) x)
                  (let (b 2) (let (b2 22) y))
                  (let (c 3) (let (c2 33) (let (c3 333) z)))))

(define test8 '(+ (let (a 1) x)
                  (let (b 2) (let (b b) y))
                  (let (c 3) (let (c 33) (let (c 333) z)))))

(define test9 '(let (x 1)
                 (let (y 1) 2)))

(define test10 '(let (x (let (y 1) 2))
                 0))

(define test11 '(let (x (let (y 2) y))
                  (let (z 3) z)))

(define test12 '(let (x (let (y 2) y))
                  (let (z (let (a 3) a)) z)))

(define test13 '(let (x (let (x 1) x))
                  (let (y x) x) ))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


(display "Let-lift\n\n")

test1
(let-lift test1)
(display "is let-lifted-expr? ") (let-lifted-expr? (let-lift test1))
(display "\n\n")

test2
(let-lift test2)
(display "is let-lifted-expr? ") (let-lifted-expr? (let-lift test2))
(display "\n\n")

test3
(let-lift test3)
(display "is let-lifted-expr? ") (let-lifted-expr? (let-lift test3))
(display "\n\n")

test4
(let-lift test4)
(display "is let-lifted-expr? ") (let-lifted-expr? (let-lift test4))
(display "\n\n")

test5
(let-lift test5)
(display "is let-lifted-expr? ") (let-lifted-expr? (let-lift test5))
(display "\n\n")

test6
(let-lift test6)
(display "is let-lifted-expr? ") (let-lifted-expr? (let-lift test6))
(display "\n\n")

test7
(let-lift test7)
(display "is let-lifted-expr? ") (let-lifted-expr? (let-lift test7))
(display "\n\n")

test8
(let-lift test8)
(display "is let-lifted-expr? ") (let-lifted-expr? (let-lift test8))
(display "\n\n")

test9
(let-lift test9)
(display "is let-lifted-expr? ") (let-lifted-expr? (let-lift test9))
(display "\n\n")

test10
(let-lift test10)
(display "is let-lifted-expr? ") (let-lifted-expr? (let-lift test10))
(display "\n\n")

test11
(let-lift test11)
(display "is let-lifted-expr? ") (let-lifted-expr? (let-lift test11))
(display "\n\n")

test12
(let-lift test12)
(display "is let-lifted-expr? ") (let-lifted-expr? (let-lift test12))
(display "\n\n")

test13
(let-lift test13)
(display "is let-lifted-expr? ") (let-lifted-expr? (let-lift test13))
(display "\n\n")