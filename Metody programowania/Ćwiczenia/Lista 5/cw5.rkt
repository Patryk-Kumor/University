#lang racket

;;; ZAD 1, 2

(define (var? t)
  (symbol? t))

(define (neg x)
  (list 'neg x))

(define (neg? t)
   (and (list? t)
        (= 2 ( length t))
        (eq? 'neg (car t))))

(define (neg-subf t) (second t))

(define (conj x y)
  (list 'conj x y))

(define (conj-left t) (second t))

(define (conj-rght t) (third t))

(define  (conj? t)
  (and (list? t)
       (= 3 (length t))
       (eq? 'conj (car t))))

(define (disj x y)
  (list 'disj x y))

(define (disj-left t) (second t))

(define (disj-rght t) (third t))

(define (disj? t)
  (and (list? t)
       (= 3 (length t) )
       (eq? 'disj (car t))))

(define ( prop? f)
  (or (var? f )
      (and (neg? f)
           (prop? (neg-subf f ) ) )
      (and (disj? f )
           (prop? (disj-left f ) )
           (prop? (disj-rght f ) ) )
      (and (conj? f)
           (prop? (conj-left f) )
           (prop? (conj-rght f) ) ) ) )

(define (free-vars f)
    (cond [(var? f)  (list f)]
          [(neg? f)  (free-vars  (neg-subf f))]
          [(conj? f) (append  (free-vars (conj-left f)) (free-vars (conj-rght f)))]
          [(disj? f) (append  (free-vars (disj-left f)) (free-vars (disj-rght f)))] ))
      
(remove-duplicates
 (free-vars (conj (neg 'x) (disj 'x 'x)))) 

;;; ZAD 3

;; to do
(define (find-var t vars) #t)
(define (gen-vals t vars) #t)

(define (eval-formula t vars)
  (cond [(var? t) (find-var t vars)]
        [(neg? t) (not (eval-formula (neg-subf t) vars))]
        [(conj? t) (and (eval-formula (conj-left t) vars) (eval-formula (conj-rght t) vars))]
        [(disj? t) (or (eval-formula (disj-left t) vars) (eval-formula (disj-rght t) vars))]
        ))

(define (falsifiable-eval? t)
  (define (falsifiable t vals)
    (if (null? vals)
        false
        (if (eval-formula t (car vals))
                          (falsifiable t (cdr vals))
                          (car vals))))
  (falsifiable t (gen-vals (free-vars t))))

;;; ZAD 4

(define (literal isNeg v)
  (if (eq? isNeg 'neg)
      (list isNeg v)
      (list '() v)))
(define (lit-neg f) (first f))
(define (lit-val f) (second f))
  

(define (literal? f)
  (or (var? f)
      (and (neg? f) (var? (neg-subf f)))))

(define (nnf? f)
  (cond [(literal? f) #t]
        [(conj? f) (and (nnf? (conj-left f)) (nnf? (conj-rght f)))]
        [(disj? f) (and (nnf? (disj-left f)) (nnf? (disj-rght f)))]
        [else #f]))

(define (conv-to-nnf f)
  (define (conf-to-nnf-neg t)
    (cond [(var? t) (neg t)]
          [(neg? t) (conv-to-nnf (neg-subf t))]
          [(disj? t) (conj (conf-to-nnf-neg (disj-left t))
                                (conf-to-nnf-neg (disj-rght t)))]
          [(conj? t) (conj (conf-to-nnf-neg (conj-left t))
                                (conf-to-nnf-neg (conj-rght t)))]))
  (cond [(var? f) f]
        [(neg? f) (conf-to-nnf-neg f)]
        [(conj? f) (conj (conv-to-nnf (conj-left f) (conv-to-nnf (conv-to-nnf (conj-rght f)))))]))



