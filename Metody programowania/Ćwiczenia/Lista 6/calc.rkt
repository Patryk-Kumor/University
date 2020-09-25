#lang racket

;; arithmetic expressions

(define (const? t)
  (number? t))

(define (binop? t)
  (and (list? t)
       (member (car t) '(+ - * /))))

(define (binop-op e)
  (car e))

(define (binop-left e)
  (cadr e))

(define (binop-right e)
  (caddr e))

(define (binop-cons op l r)
  (list op l r))

(define (arith-expr? t)
  (or (const? t)
      (and (binop? t)
           (arith-expr? (binop-left  t))
           (arith-expr? (binop-right t)))))

;; calculator

(define (op->proc op)
  (cond [(eq? op '+) +]
        [(eq? op '*) *]
        [(eq? op '-) -]
        [(eq? op '/) /]))

(define (eval-arith e)
  (cond [(const? e) e]
        [(binop? e)
         (apply
          (op->proc (binop-op e))
            (car e))]))

;; let expressions

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

;;;;;;;;;;;;;

(define (let-defs? t)
  (and (list? t)
       (= (length t) 3)
       (and (symbol? (car t)) (eq? (car t) 'let-defs))
       (list? (second t))
       ))

(define (let-defs t)
  (second t))


;;;;;;;;;;;;;

(define (var? t)
  (symbol? t))

(define (var-var e)
  e)

(define (var-cons x)
  x)

(define (arith/let-expr? t)
  (or (const? t)
      (and (binop? t)
           (arith/let-expr? (binop-left  t))
           (arith/let-expr? (binop-right t)))
      (and (let? t)
           (arith/let-expr? (let-expr t))
           (arith/let-expr? (let-def (let-def-expr t))))
      (var? t)))

;; evalation via substitution

(define (subst e x f)
  (cond [(const? e) e]
        [(binop? e)
         (binop-cons
           (binop-op e)
           (subst (binop-left  e) x f)
           (subst (binop-right e) x f))]
        [(let? e)
         (let-cons
           (let-def-cons
             (let-def-var (let-def e))
             (subst (let-def-expr (let-def e)) x f))
           (if (eq? x (let-def-var (let-def e)))
               (let-expr e)
               (subst (let-expr e) x f)))]
        [(var? e)
         (if (eq? x (var-var e))
             f
             (var-var e))]))

(define (eval-subst e)
  (cond [(const? e) e]
        [(binop? e)
         ((op->proc (binop-op e))
            (eval-subst (binop-left  e))
            (eval-subst (binop-right e)))]
        [(let? e)
         (eval-subst
           (subst
             (let-expr e)
             (let-def-var (let-def e))
             (eval-subst (let-def-expr (let-def e)))))]
        [(var? e)
         (error "undefined variable" (var-var e))]))

;; evaluation via environments

(define empty-env
  null)

(define (add-to-env x v env)
  (cons (list x v) env))

(define (find-in-env x env)
  (cond [(null? env) (error "undefined variable" x)]
        [(eq? x (caar env)) (cadar env)]
        [else (find-in-env x (cdr env))]))

(define (eval-env e env)
  (define (let-helper lista-par env)
    (if (null? lista-par)
        env
        (let-helper (cdr lista-par) (add-to-env (car (car lista-par))
                                                (eval-env (second (car lista-par)) env)
                                                     env))))
  (cond [(const? e) e]
        [(binop? e)
         (apply
          (op->proc (binop-op e))
          (map (lambda (x) (eval-env x env)) (cdr  e)) )]
        [(if-zero? e)
         (if (= (eval-env (if-cond e) env) 0)
             (eval-env (if-nastepnik e) env)
             (eval-env (if-alternatywa e) env))]
        [(let? e)
         (eval-env
           (let-expr e)
           (env-for-let (let-def e) env))]
        
        [(let-defs? e)

         (eval-env (third e) (let-helper (second e) env))]

         

        
        [(var? e) (find-in-env (var-var e) env)]))

(define (env-for-let def env)
  (add-to-env
    (let-def-var def)
    (eval-env (let-def-expr def) env)
    env))

(define (eval e)
  (eval-env e empty-env))


;; ZAD 1 - NIEUZYTKI
;; flatten tworzy nową listę, a nie korzysta z dostępnych już "pudełek"

(define (anth-rpn2 lista)
  (if (number? lista) lista
      (flatten (list (anth-rpn (cadr lista))
                     (anth-rpn (caddr lista))
                     (car lista)))))
                               
;; ZAD 1 - dobre

(define (anth-rpn lista)
  (define (onp xs acc)
    (cond [(number? xs) (cons xs acc)]
           [else (onp (cadr xs) (onp (caddr xs) (cons (car xs) acc)))]))
  (onp lista null))


;; ZAD 2

(define (stack? s)
  (list? s))

(define (push arg stack)
  (cons arg stack))

(define (pop stack)
  (cons (car stack) (cdr stack)))

;; ZAD 3

(define (eval-onp stack)
  (display stack)
  (let ([up (car (pop stack))])

    (cond [(symbol? up) ((op->proc up)  (eval-onp (cdr stack))   )])
    
    )
)



;; ZAD 5=-

(define (if-zero? t)
  (and (list? t)
       (eq? (car t) 'if-zero)
       (= (length t) 4 )))

(define (if-cond t)
  (cadr t))

(define (if-nastepnik t)
  (third t))

(define (if-alternatywa t)
  (fourth t))

  