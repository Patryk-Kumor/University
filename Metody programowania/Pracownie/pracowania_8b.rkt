#lang racket

;; pomocnicza funkcja dla list tagowanych o określonej długości

(define (tagged-tuple? tag len p)
  (and (list? p)
       (= (length p) len)
       (eq? (car p) tag)))

(define (tagged-list? tag p)
  (and (pair? p)
       (eq? (car p) tag)
       (list? (cdr p))))

;; self-evaluating expressions

(define (const? t)
  (or (number? t)
      (my-symbol? t)
      (eq? t 'true)
      (eq? t 'false)))

;; arithmetic expressions

(define (op? t)
  (and (list? t)
       (member (car t) '(+ - * / = > >= < <= eq?))))

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
        [(eq? op '/) /]
        [(eq? op '=)  (compose bool->val =)]
        [(eq? op '>)  (compose bool->val >)]
        [(eq? op '>=) (compose bool->val >=)]
        [(eq? op '<)  (compose bool->val <)]
        [(eq? op '<=) (compose bool->val <=)]
        [(eq? op 'eq?) (lambda (x y)
                         (bool->val (eq? (symbol-symbol x)
                                         (symbol-symbol y))))]))

;; symbols

(define (my-symbol? e)
  (and (tagged-tuple? 'quote 2 e)
       (symbol? (second e))))

(define (symbol-symbol e)
  (second e))

(define (symbol-cons s)
  (list 'quote s))

;; lets

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
  (and (tagged-tuple? 'let 3 t)
       (let-def? (cadr t))))

(define (let-def e)
  (cadr e))

(define (let-expr e)
  (caddr e))

(define (let-cons def e)
  (list 'let def e))

;; DODAJEMY LAZY-LET
;; -----------------

(define (lazy-let-def? t)
  (and (list? t)
       (= (length t) 2)
       (symbol? (car t))))

(define (lazy-let-def-var e)
  (car e))

(define (lazy-let-def-expr e)
  (cadr e))

(define (lazy-let-def-cons x e)
  (list x e))

(define (lazy-let? t)
  (and (tagged-tuple? 'lazy-let 3 t)
       (lazy-let-def? (cadr t))))

(define (lazy-let-def e)
  (cadr e))

(define (lazy-let-expr e)
  (caddr e))

(define (lazy-let-cons def e)
  (list 'lazy-let def e))

;; -----------------

;; variables

(define (var? t)
  (symbol? t))

(define (var-var e)
  e)

(define (var-cons x)
  x)

;; pairs

(define (cons? t)
  (tagged-tuple? 'cons 3 t))

(define (cons-fst e)
  (second e))

(define (cons-snd e)
  (third e))

(define (cons-cons e1 e2)
  (list 'cons e1 e2))

(define (car? t)
  (tagged-tuple? 'car 2 t))

(define (car-expr e)
  (second e))

(define (cdr? t)
  (tagged-tuple? 'cdr 2 t))

(define (cdr-expr e)
  (second e))

(define (pair?? t)
  (tagged-tuple? 'pair? 2 t))

(define (pair?-expr e)
  (second e))

(define (pair?-cons e)
  (list 'pair? e))


;; if

(define (if? t)
  (tagged-tuple? 'if 4 t))

(define (if-cons b t f)
  (list 'if b t f))

(define (if-cond e)
  (second e))

(define (if-then e)
  (third e))

(define (if-else e)
  (fourth e))

;; cond

(define (cond-clause? t)
  (and (list? t)
       (= (length t) 2)))

(define (cond-clause-cond c)
  (first c))

(define (cond-clause-expr c)
  (second c))

(define (cond-claue-cons b e)
  (list b e))

(define (cond? t)
  (and (tagged-list? 'cond t)
       (andmap cond-clause? (cdr t))))

(define (cond-clauses e)
  (cdr e))

(define (cond-cons cs)
  (cons 'cond cs))

;; lists

(define (my-null? t)
  (eq? t 'null))

(define (null?? t)
  (tagged-tuple? 'null? 2 t))

(define (null?-expr e)
  (second e))

(define (null?-cons e)
  (list 'null? e))

;; lambdas

(define (lambda? t)
  (and (tagged-tuple? 'lambda 3 t)
       (list? (cadr t))
       (andmap symbol? (cadr t))))

(define (lambda-no-args? t)
  (and (tagged-tuple? 'lambda 3 t)
       (eq? (lambda-vars t) '())
       (list? (cadr t))
       (andmap symbol? (cadr t))))

(define (lambda-cons vars e)
  (list 'lambda vars e))

(define (lambda-vars e)
  (cadr e))

(define (lambda-expr e)
  (caddr e))

;; lambda-rec

(define (lambda-rec? t)
  (and (tagged-tuple? 'lambda-rec 3 t)
       (list? (cadr t))
       (>= (length (cadr t)) 1)
       (andmap symbol? (cadr t))))

(define (lambda-rec-no-args? t)
  (and (tagged-tuple? 'lambda-rec 3 t)
       (eq? (lambda-rec-vars t) '())
       (list? (cadr t))
       (>= (length (cadr t)) 1)
       (andmap symbol? (cadr t))))

(define (lambda-rec-cons vars e)
  (list 'lambda-rec vars e))

(define (lambda-rec-expr e)
  (third e))

(define (lambda-rec-name e)
  (car (second e)))

(define (lambda-rec-vars e)
  (cdr (second e)))

;; applications

(define (app? t)
  (and (list? t)
       (> (length t) 0)))

(define (app-cons proc args)
  (cons proc args))

(define (app-proc e)
  (car e))

(define (app-args e)
  (cdr e))

;; expressions

(define (expr? t)
  (or (const? t)
      (and (op? t)
           (andmap expr? (op-args t)))
      (and (let? t)
           (expr? (let-expr t))
           (expr? (let-def-expr (let-def t))))
      ;; DODAJEMY LAZY-LET
      ;; -----------------
      (and (lazy-let? t)
           (expr? (lazy-let-expr t))
           (expr? (lazy-let-def-expr (lazy-let-def t))))
      ;; -----------------
      (and (cons? t)
           (expr? (cons-fst t))
           (expr? (cons-snd t)))
      (and (car? t)
           (expr? (car-expr t)))
      (and (cdr? t)
           (expr? (cdr-expr t)))
      (and (pair?? t)
           (expr? (pair?-expr t)))
      (my-null? t)
      (and (null?? t)
           (expr? (null?-expr t)))
      (and (if? t)
           (expr? (if-cond t))
           (expr? (if-then t))
           (expr? (if-else t)))
      (and (cond? t)
           (andmap (lambda (c)
                      (and (expr? (cond-clause-cond c))
                           (expr? (cond-clause-expr c))))
                   (cond-clauses t)))
      (and (lambda? t)
           (expr? (lambda-expr t)))
      (and (lambda-rec? t)
           (expr? (lambda-rec-expr t)))
      (var? t)
      (and (app? t)
           (expr? (app-proc t))
           (andmap expr? (app-args t)))))

;; environments

(define empty-env
  null)

(define (add-to-env x v env)
  (cons (list x v) env))

;; DODAJEMY LAZY-LET

(define (add-to-env-lambda var-name lambda old-env env)
  (cons (list var-name lambda old-env) env))

(define (find-in-env x env)
  (cond [(null? env) (error "undefined variable" x)]
        [(eq? x (caar env)) ;(cadar env)
         ;(display "Found var: ") (display (cadar env)) (display "\n") 
         (cond
           [(lambda-no-args?  (cadar env)) (eval-env (list (cadar env))
                                                     (caddar env))]
           ;[(lambda-rec-no-args?  (cadar env)) (eval-env (list (cadar env))
           ;                                              (caddar env))]
           [else (cadar env)])]
        [else (find-in-env x (cdr env))]))

;; closures

(define (closure-cons xs expr env)
  (list 'closure xs expr env))

(define (closure? c)
  (and (list? c)
       (= (length c) 4)
       (eq? (car c) 'closure)))

(define (closure-vars c)
  (cadr c))

(define (closure-expr c)
  (caddr c))

(define (closure-env c)
  (cadddr c))

;; closure-rec

(define (closure-rec? t)
  (tagged-tuple? 'closure-rec 5 t))

(define (closure-rec-name e)
  (second e))

(define (closure-rec-vars e)
  (third e))

(define (closure-rec-expr e)
  (fourth e))

(define (closure-rec-env e)
  (fifth e))

(define (closure-rec-cons f xs e env)
  (list 'closure-rec f xs e env))

;; evaluator

(define (bool->val b)
  (if b 'true 'false))

(define (val->bool s)
  (cond [(eq? s 'true)  true]
        [(eq? s 'false) false]
        [else (error "could not convert symbol to bool")]))

(define (eval-env e env)
  (cond [(const? e)
         e]
        [(op? e)
         (apply (op->proc (op-op e))
                (map (lambda (a) (eval-env a env))
                     (op-args e)))]
        [(let? e)
         (eval-env (let-expr e)
                   (env-for-let (let-def e) env))]
        ;; DODAJEMY LAZY-LET
        [(lazy-let? e)
         (eval-env (lazy-let-expr e)
                   (env-for-lazy-let (lazy-let-def e) env))]
        ;; -----------------
        [(my-null? e)
         null]
        [(cons? e)
         (cons (eval-env (cons-fst e) env)
               (eval-env (cons-snd e) env))]
        [(car? e)
         (car (eval-env (car-expr e) env))]
        [(cdr? e)
         (cdr (eval-env (cdr-expr e) env))]
        [(pair?? e)
         (bool->val (pair? (eval-env (pair?-expr e) env)))]
        [(null?? e)
         (bool->val (null? (eval-env (null?-expr e) env)))]
        [(if? e)
         (if (val->bool (eval-env (if-cond e) env))
             (eval-env (if-then e) env)
             (eval-env (if-else e) env))]
        [(cond? e)
         (eval-cond-clauses (cond-clauses e) env)]
        [(var? e)
         (find-in-env (var-var e) env)]
        [(lambda? e)
         (closure-cons (lambda-vars e) (lambda-expr e) env)]
        [(lambda-rec? e)
         (closure-rec-cons (lambda-rec-name e)
                           (lambda-rec-vars e)
                           (lambda-rec-expr e)
                           env)]
        [(app? e)
         (apply-closure
           (eval-env (app-proc e) env)
           (map (lambda (a) (eval-env a env))
                (app-args e)))]))

(define (eval-cond-clauses cs env)
  (if (null? cs)
      (error "no true clause in cond")
      (let ([cond (cond-clause-cond (car cs))]
            [expr (cond-clause-expr (car cs))])
           (if (val->bool (eval-env cond env))
               (eval-env expr env)
               (eval-cond-clauses (cdr cs) env)))))

(define (apply-closure c args)
  (cond [(closure? c)
         (eval-env
            (closure-expr c)
            (env-for-closure
              (closure-vars c)
              args
              (closure-env c)))]
        [(closure-rec? c)
         (eval-env
           (closure-rec-expr c)
           (add-to-env
            (closure-rec-name c)
            c
            (env-for-closure
              (closure-rec-vars c)
              args
              (closure-rec-env c))))]))

(define (env-for-closure xs vs env)
  (cond [(and (null? xs) (null? vs)) env]
        [(and (not (null? xs)) (not (null? vs)))
         (add-to-env
           (car xs)
           (car vs)
           (env-for-closure (cdr xs) (cdr vs) env))]
        [else (error "arity mismatch")]))

(define (env-for-let def env)
  (add-to-env
    (let-def-var def)
    (eval-env (let-def-expr def) env)
    env))

;; DODAJEMY LAZY-LET
(define (env-for-lazy-let def env)
  ;; dodanie pary do env
  (add-to-env-lambda
    ;; zmienna
    (lazy-let-def-var def)
       ;; ciało które obliczamy z zadanym środowiskiem
       ;; (eval-env (lazy-let-def-expr def) env)
    ;; ciało => zamiana na lambdę-rec
    ;(lambda-rec-cons '() (lazy-let-def-expr def))
    (lambda-cons '() (lazy-let-def-expr def))
    env
    ;;pozostałe środowisko
    env))

;; (define (add-to-env x v env)
;;  (cons (list x v) env))
;; -----------------

(define (eval e)
  (eval-env e empty-env))

;; -----------
;; ---TESTY---
;; -----------

(display "Zwykłe lambdy - działanie\n\n\n")
'(lambda (x) (+ x x x))
(eval '(lambda (x) (+ x x x)))
(display "\n\n")

'((lambda (x) (+ x x)) 1)
(eval '((lambda (x) (+ x x)) 1))
(display "\n\n")

'(lambda (x) (/ x 0))
(eval '(lambda (x) (/ x 0)))
(display "\n\n")

'((lambda (x) (/ x 0)) 0)
;(eval '((lambda (x) (/ x 0)) 0))
(display "/: division by zero\n")
(display "\n\n")

'(lambda (x) (/ x (lambda (x) (/ x 0))))
(eval '(lambda (x) (/ x (lambda (x) (/ x 0)))))
(display "\n\n")

'((lambda (x) (/ x ((lambda (x) (/ x 0)) 1))) 1)
;(eval '((lambda (x) (/ x ((lambda (x) (/ x 0)) 1))) 1))
(display "/: division by zero")
(display "\n\n")

'(lazy-let (x 0) ( lazy-let (y (/ 1 x)) y ))
;(eval '(lazy-let (x 0) ( lazy-let (y (/ 1 x)) y )))
(display "/: division by zero")

;; ---

(display "\n\n\n----------------------------------------------\n")
(display "Leniwe let - bez środowiska na górnym poziomie\n\n\n")
'(lazy-let (x 1) (+ 1 2))
(eval '(lazy-let (x 1) (+ 1 2)))
(display "\n\n")

'(lazy-let (x (/ 1 0)) (+ 1 2))
(eval '(lazy-let (x 1) (+ 1 2)))
(display "\n\n")

'(lazy-let (x 1) (+ x (/ 1 0)))
;(eval '(lazy-let (x 1) (+ x (/ 1 0))))
(display "/: division by zero\n")
(display "\n\n")

'(lazy-let (x (/ 1 0)) x)
;(eval '(lazy-let (x (/ 1 0)) x))
(display "/: division by zero\n")
(display "\n\n")

'(lazy-let (x '(lazy-let (x (/ 1 0)) x)) 1)
(eval '(lazy-let (x (lazy-let (x (/ 1 0)) x)) 1))
(display "\n\n")

'(lazy-let (x '(lazy-let (x (/ 1 0)) x)) x)
;(eval '(lazy-let (x (lazy-let (x (/ 1 0)) x)) x))
(display "/: division by zero\n")

;; ---

(display "\n\n------------------------------------------------\n")
(display "Leniwe let - ze środowiskiem na wyższym poziomie\n\n\n")
'(let (y 1) (let (y 2) (lazy-let (y (/ y 0)) (+ 1 y))))
;(eval '(let (y 1) (let (y 2) (lazy-let (y (/ y 0)) (+ 1 y)))))
(display "/: division by zero\n")
(display "\n\n")

'(lazy-let (y 1) (lazy-let (y 2) (lazy-let (y (/ y 0)) (+ 1 y))))
;(eval '(lay-let (y 1) (lazy-let (y 2) (lazy-let (y (/ y 0)) (+ 1 y)))))
(display "/: division by zero\n")
(display "\n\n")

'(lazy-let (x (/ 0 0)) (lazy-let (y (/ 0 0)) (lazy-let (y (/ x (/ y x))) (+ 1 2))))
(eval '(lazy-let (x (/ 0 0)) (lazy-let (y (/ 0 0)) (lazy-let (y (/ x (/ y x))) (+ 1 2)))))
(display "\n\n")

'(let [x 4] (lazy-let [y (+ x 1)] (let [x 10] y)))
(eval '(let [x 4] (lazy-let [y (+ x 1)] (let [x 10] y))))
(display "\n\n")

'(let [x 4] (lazy-let [y (+ x 1)] (let [x 10] y)))
(display "start env: ") (display '((x 11) (y 10101))) (display "\n")
(eval-env '(let [x 4] (lazy-let [y (+ x 1)] (let [x 10] y)))
          '((x 11) (y 10101)))

;; ---

(display "\n\n---------------\n")
(display "Dodatkowe testy\n\n\n")

(define silnia '((lambda-rec (fact n)
                   (lazy-let [t 1]
                     (lazy-let [f (* n ( fact (- n 1)))]
                       (if (= n 0) t f )))) 5))
silnia
(eval silnia)
(display "\n\n")

(define silnia-bez-lazy '((lambda-rec (fact n)
                            (let [t 1]
                              (let [f (* n ( fact (- n 1)))]
                                (if (= n 0) t f )))) 5))
silnia-bez-lazy
;(eval silnia-bez-lazy)
(display "/: zgodnie z oczekiwaniem: \n")
(display "/: śmiercionośna pętla bez leniwości\n")