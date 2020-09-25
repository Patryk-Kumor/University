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

;; reprezentacja danych wejściowych (z ćwiczeń)
(define (var? x)
  (symbol? x))

(define (var x)
  x)

(define (var-name x)
  x)

;; przydatne predykaty na zmiennych
(define (var<? x y)
  (symbol<? x y))

(define (var=? x y)
  (eq? x y))

(define (literal? x)
  (and (tagged-tuple? 'literal 3 x)
       (boolean? (cadr x))
       (var? (caddr x))))

(define (literal pol x)
  (list 'literal pol x))

(define (literal-pol x)
  (cadr x))

(define (literal-var x)
  (caddr x))

(define (clause? x)
  (and (tagged-list? 'clause x)
       (andmap literal? (cdr x))))

(define (clause . lits)
  (cons 'clause lits))

(define (clause-lits c)
  (cdr c))

(define (cnf? x)
  (and (tagged-list? 'cnf x)
       (andmap clause? (cdr x))))

(define (cnf . cs)
    (cons 'cnf cs))

(define (cnf-clauses x)
  (cdr x))

;; oblicza wartość formuły w CNF z częściowym wartościowaniem. jeśli zmienna nie jest
;; zwartościowana, literał jest uznawany za fałszywy.
(define (valuate-partial val form)
  (define (val-lit l)
    (let ((r (assoc (literal-var l) val)))
      (cond
       [(not r)  false]
       [(cadr r) (literal-pol l)]
       [else     (not (literal-pol l))])))
  (define (val-clause c)
    (ormap val-lit (clause-lits c)))
  (andmap val-clause (cnf-clauses form)))

;; reprezentacja dowodów sprzeczności

(define (axiom? p)
  (tagged-tuple? 'axiom 2 p))

(define (proof-axiom c)
  (list 'axiom c))

(define (axiom-clause p)
  (cadr p))

(define (res? p)
  (tagged-tuple? 'resolve 4 p))

(define (proof-res x pp pn)
  (list 'resolve x pp pn))

(define (res-var p)
  (cadr p))

(define (res-proof-pos p)
  (caddr p))

(define (res-proof-neg p)
  (cadddr p))

;; sprawdza strukturę, ale nie poprawność dowodu
(define (proof? p)
  (or (and (axiom? p)
           (clause? (axiom-clause p)))
      (and (res? p)
           (var? (res-var p))
           (proof? (res-proof-pos p))
           (proof? (res-proof-neg p)))))

;; procedura sprawdzająca poprawność dowodu
(define (check-proof pf form)
  (define (run-axiom c)
    (displayln (list 'checking 'axiom c))
    (and (member c (cnf-clauses form))
         (clause-lits c)))
  (define (run-res x cpos cneg)
    (displayln (list 'checking 'resolution 'of x 'for cpos 'and cneg))
    (and (findf (lambda (l) (and (literal-pol l)
                                 (eq? x (literal-var l))))
                cpos)
         (findf (lambda (l) (and (not (literal-pol l))
                                 (eq? x (literal-var l))))
                cneg)
         (append (remove* (list (literal true x))  cpos)
                 (remove* (list (literal false x)) cneg))))
  (define (run-proof pf)
    (cond
     [(axiom? pf) (run-axiom (axiom-clause pf))]
     [(res? pf)   (run-res (res-var pf)
                           (run-proof (res-proof-pos pf))
                           (run-proof (res-proof-neg pf)))]
     [else        false]))
  (null? (run-proof pf)))


;; reprezentacja wewnętrzna

;; sprawdza posortowanie w porządku ściśle rosnącym, bez duplikatów
(define (sorted? vs)
  (or (null? vs)
      (null? (cdr vs))
      (and (var<? (car vs) (cadr vs))
           (sorted? (cdr vs)))))

(define (sorted-varlist? x)
  (and (list? x)
       (andmap var? x) ;; BYŁO : (andmap (var? x))
       (sorted? x)))

;; klauzulę reprezentujemy jako parę list — osobno wystąpienia pozytywne i negatywne. Dodatkowo
;; pamiętamy wyprowadzenie tej klauzuli (dowód) i jej rozmiar.
(define (res-clause? x)
  (and (tagged-tuple? 'res-int 5 x)
       (sorted-varlist? (second x))
       (sorted-varlist? (third x))
       (= (fourth x) (+ (length (second x)) (length (third x))))
       (proof? (fifth x))))

(define (res-clause pos neg proof)
  (list 'res-int pos neg (+ (length pos) (length neg)) proof))

(define (res-clause-pos c)
  (second c))

(define (res-clause-neg c)
  (third c))

(define (res-clause-size c)
  (fourth c))

(define (res-clause-proof c)
  (fifth c))

;; przedstawia klauzulę jako parę list zmiennych występujących odpowiednio pozytywnie i negatywnie
(define (print-res-clause c)
  (list (res-clause-pos c) (res-clause-neg c)))

;; sprawdzanie klauzuli sprzecznej
(define (clause-false? c)
  (and (null? (res-clause-pos c))
       (null? (res-clause-neg c))))

;; pomocnicze procedury: scalanie i usuwanie duplikatów z list posortowanych
(define (merge-vars xs ys)
  (cond [(null? xs) ys]
        [(null? ys) xs]
        [(var<? (car xs) (car ys))
         (cons (car xs) (merge-vars (cdr xs) ys))]
        [(var<? (car ys) (car xs))
         (cons (car ys) (merge-vars xs (cdr ys)))]
        [else (cons (car xs) (merge-vars (cdr xs) (cdr ys)))]))

(define (remove-duplicates-vars xs)
  (cond [(null? xs) xs]
        [(null? (cdr xs)) xs]
        [(var=? (car xs) (cadr xs)) (remove-duplicates-vars (cdr xs))]
        [else (cons (car xs) (remove-duplicates-vars (cdr xs)))]))

(define (rev-append xs ys)
  (if (null? xs) ys
      (rev-append (cdr xs) (cons (car xs) ys))))

;; TODO: miejsce na uzupełnienie własnych funkcji pomocniczych

;; zwraca posortowane wspólne elementy
(define (union list1 list2)
  (define (helper list1 list2 res)
    (cond [(null? list1) res]
          [(member (car list1) list2) (helper (cdr list1) list2 (cons (car list1) res))]
          [else (helper (cdr list1) list2 res)]))
  (sort (helper list1 list2 '() ) var<?))

;; funkcje pomocnicze do optymalizacji

;; sprawdza czy cała lista znajduje się w drugiej
(define (is-in? list1 list2)
  (cond [(null? list1) #t]
        [(member (car list1) list2) (is-in? (cdr list1) list2)]
        [else #f]))

;; sprawdza czy klauzula jest łatwiejsza wobec innej
(define (easier? new clause)
  (define (helper new-pos new-neg clause-pos clause-neg)
    (and (is-in? clause-pos new-pos)
         (is-in? clause-neg new-neg)))
  (helper (res-clause-pos new) (res-clause-neg new) (res-clause-pos clause) (res-clause-neg clause)))

;; sprawda i ewentualnie podmienia klauzlę jeśli łatwiejsza
(define (sub clauses new res)
  (cond [(null? clauses) res]
        [(easier? new (car clauses)) (cons (car res) #t)]
        [else (sub (cdr clauses) new (cons (cons (car clauses)
                                                 ( car res))
                                           (cdr res)))]))

(define (clause-trivial? c)
  ;; TODO: zaimplementuj!
  ;; funkcja pomocnicza -> zwraca #t na pierwszym wspólnym elemencie
  ;; podobna do union ale zatrzymuje się na pierwszym lepszym znalezionym
  (define (find-in-lists list1 list2)
    (cond [(null? list1) #f]
          [(member (car list1) list2) #t]
          [else (find-in-lists (cdr list1) list2)]))
  ;; właściwe wywołanie
  (find-in-lists (res-clause-pos c) (res-clause-neg c)))

(define (resolve c1 c2)
  ;; TODO: zaimplementuj! 
  (define (merge x list1 list2) (remove-duplicates-vars (merge-vars (remove x list1) (remove x list2))))
  ;; część właściwa
  (let ([c1-pos (res-clause-pos c1)]
        [c1-neg (res-clause-neg c1)]
        [c2-pos (res-clause-pos c2)]
        [c2-neg (res-clause-neg c2)])
    (let ([un (union c1-pos c2-neg)])
      ;; jeśli niepusty przekrój -> tworzymy res
      ;; jeśli pusty -> sprawdzamy drugą opcję 
      (cond [(empty? un) (let ([un (union c2-pos c1-neg)])
                          (cond [(empty? un) #f]
                                [else (res-clause (merge (car un) c1-pos c2-pos)
                                                  (merge (car un) c1-neg c2-neg)
                                                  (proof-res (car un) (res-clause-proof c2) (res-clause-proof c1)))]))]
            [else (res-clause (merge (car un) c1-pos c2-pos)
                              (merge (car un) c1-neg c2-neg)
                              (proof-res (car un) (res-clause-proof c1) (res-clause-proof c2)))]))))

(define (resolve-single-prove s-clause checked pending)
  ;; TODO: zaimplementuj!
  ;; jeśli istnieje rezolwenta -> podmieniamy ją
  (define (remove-from-single s-clause clause)
    (let ([resolvent (resolve s-clause clause)])
               (if (eq? resolvent #f)
                   clause
                   resolvent)))
  ;; funkcja podmieniająca na całej liście
  (define (remove-from s-clause clauses)
    (if (null? clauses) null
        (cons (remove-from-single s-clause (car clauses))
              (cdr clauses))))
  ;; część główna
  ;; sort raczej nie jest potrzebny skoro checked i pending już są posortowane
  (let* ((checked2 (sort (remove-from s-clause checked) < #:key res-clause-size))
         (pending2 (sort (remove-from s-clause pending) < #:key res-clause-size))
         (resolvents   (filter-map (lambda (c) (resolve c s-clause))
                                     checked))
         (sorted-rs    (sort resolvents < #:key res-clause-size)))
    (subsume-add-prove (cons s-clause checked2) pending2 sorted-rs)))

;; wstawianie klauzuli w posortowaną względem rozmiaru listę klauzul
(define (insert nc ncs)
  (cond
   [(null? ncs)                     (list nc)]
   [(< (res-clause-size nc)
       (res-clause-size (car ncs))) (cons nc ncs)]
   [else                            (cons (car ncs) (insert nc (cdr ncs)))]))

;; sortowanie klauzul względem rozmiaru (funkcja biblioteczna sort)
(define (sort-clauses cs)
  (sort cs < #:key res-clause-size))

;; główna procedura szukająca dowodu sprzeczności
;; zakładamy że w checked i pending nigdy nie ma klauzuli sprzecznej
(define (resolve-prove checked pending)
  (cond
   ;; jeśli lista pending jest pusta, to checked jest zamknięta na rezolucję czyli spełnialna
   [(null? pending) (generate-valuation (sort-clauses checked))]
   ;; jeśli klauzula ma jeden literał, to możemy traktować łatwo i efektywnie ją przetworzyć
   [(= 1 (res-clause-size (car pending)))
    (resolve-single-prove (car pending) checked (cdr pending))]
   ;; w przeciwnym wypadku wykonujemy rezolucję z wszystkimi klauzulami już sprawdzonymi, a
   ;; następnie dodajemy otrzymane klauzule do zbioru i kontynuujemy obliczenia
   [else
    (let* ((next-clause  (car pending))
           (rest-pending (cdr pending))
           (resolvents   (filter-map (lambda (c) (resolve c next-clause))
                                     checked))
           (sorted-rs    (sort-clauses resolvents)))
      (subsume-add-prove (cons next-clause checked) rest-pending sorted-rs))]))

;; procedura upraszczająca stan obliczeń biorąc pod uwagę świeżo wygenerowane klauzule i
;; kontynuująca obliczenia. Do uzupełnienia.
(define (subsume-add-prove checked pending new)
  (cond
   [(null? new)                 (resolve-prove checked pending)]
   ;; jeśli klauzula do przetworzenia jest sprzeczna to jej wyprowadzenie jest dowodem sprzeczności
   ;; początkowej formuły
   [(clause-false? (car new))   (list 'unsat (res-clause-proof (car new)))]
   ;; jeśli klauzula jest trywialna to nie ma potrzeby jej przetwarzać
   [(clause-trivial? (car new)) (subsume-add-prove checked pending (cdr new))]
   [else
    ;; TODO: zaimplementuj!
    ;; w tym etapie pomagałem Andrzejowi Milczarkowi, więc może mieć podobnie pewne elementy
    (let ([new-checked (sub checked (car new) (list '() #f))]
          [new-pending (sub pending (car new) (list '() #f))])
      (if (or (eq? (cdr new-checked) #t)
              (eq? (cdr new-pending) #t))
          ;; true oznacza że gdzieś nowa klauzula była łatwiejsza
          (subsume-add-prove checked pending (cdr new))
          (subsume-add-prove (car new-checked) (insert (car new) (car new-pending)) (cdr new))))]))                 
    ;(subsume-add-prove checked (insert (car new) pending) (cdr new))]))

(define (generate-valuation resolved)
  ;; TODO: zaimplementuj!
  ;; pomocniczo -> tworzenie wartosciowania (zawsze z pierwszego elementu)
  (define (create clause)
    (if (null? (res-clause-pos clause) ) (list  (car (res-clause-neg clause)) #f)
                                         (list  (car (res-clause-pos clause)) #t)))
  ;; pomocniczo -> uproszczenie jednej klauzuli
  ;; jeśli dane wartościowanie sprawia że jakaś klauzula jest spełniona : to można ją pominąć
  ;; jeśli nie : to tylko możemy usunąć wystąpienie tej zmiennej
  (define (simplyfy-clause val clause)
    (cond [(member (first val) (res-clause-pos clause))
           (if (eq? (second val) #t)
               (res-clause '()
                           '()
                           (res-clause-proof clause))
               (res-clause (remove (car val) (res-clause-pos clause))
                           (res-clause-neg clause)
                           (res-clause-proof clause))) ]
          [(member (first val) (res-clause-neg clause))
           (if (eq? (second val) #f)
               (res-clause '()
                           '()
                           (res-clause-proof clause))
               (res-clause (res-clause-pos clause)
                           (remove (car val) (res-clause-neg clause)  )                                                                    
                           (res-clause-proof clause))) ]
          [else clause]))
  ;; uproszczenie na całej liście
  (define (simplify x rest)
    (cond [(null? rest) null]
          [else (let ([smpled (simplyfy-clause x (car rest))])
                  (if (= (res-clause-size smpled) 0)
                         (simplify x (cdr rest))
                         (cons smpled (simplify x (cdr rest)) )))]))
  ;; pomocniczo -> generowanie
  (define (generate list vals) 
      (cond [(null? list) vals]
            [(= (res-clause-size (car list))
                0) (generate (cdr list) ; zabezpieczenie gdyby coś się usunęło => gdy klauzula już spełniona
                             vals)]
            [(= (res-clause-size (car list))
                1) (generate (simplify (create (car list))
                                       (cdr list))
                             (cons (create (car list))
                                   vals))]
            [(>= (res-clause-size (car list))
                 2) (generate (simplify (create (car list))
                                        (cdr list))
                              (cons (create (car list))
                                    vals))] ))
  ;; właścwiwe wywołanie
  (list 'sat (generate resolved '() )))

;; procedura przetwarzające wejściowy CNF na wewnętrzną reprezentację klauzul
(define (form->clauses f)
  (define (conv-clause c)
    (define (aux ls pos neg)
      (cond
       [(null? ls)
        (res-clause (remove-duplicates-vars (sort pos var<?))
                    (remove-duplicates-vars (sort neg var<?))
                    (proof-axiom c))]
       [(literal-pol (car ls))
        (aux (cdr ls)
             (cons (literal-var (car ls)) pos)
             neg)]
       [else
        (aux (cdr ls)
             pos
             (cons (literal-var (car ls)) neg))]))
    (aux (clause-lits c) null null))
  (map conv-clause (cnf-clauses f)))

(define (prove form)
  (let* ((clauses (form->clauses form)))
    (subsume-add-prove '() '() clauses)))

;; procedura testująca: próbuje dowieść sprzeczność formuły i sprawdza czy wygenerowany
;; dowód/waluacja są poprawne. Uwaga: żeby działała dla formuł spełnialnych trzeba umieć wygenerować
;; poprawną waluację.
(define (prove-and-check form)
  (let* ((res (prove form))
         (sat (car res))
         (pf-val (cadr res)))
    (if (eq? sat 'sat)
        (valuate-partial pf-val form)
        (check-proof pf-val form))))

;;; TODO: poniżej wpisz swoje testy
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;; test części wspólnej
(union '() '())
(union '(a b c) '(d e f))
(union '(a c d) '(d c a))
(display "\n")


;; testy sprawdzenia istnienia wspólnego elementu w listach
(define (find-in-lists list1 list2)
    (cond [(null? list1) #f]
          [(member (car list1) list2) #t]
          [else (find-in-lists (cdr list1) list2)]))
(find-in-lists '(1 2 3) '(3 4 5 2))
(find-in-lists '() '(3 4 5))
(find-in-lists '() '())
(find-in-lists '(1 2 3 4 5 6 7 8 9 10 ) '(10))
(find-in-lists '(1 3 5 7) '(2 4 6 9))


;; testy tworzenia i resolve
;; p v ~q 
(define tester (form->clauses
                (cnf (clause (literal true 'p) (literal false 'q)))))
;; p v ~p
(define tester2 (form->clauses
                 (cnf (clause (literal true 'p) (literal false 'p)))))
;; r v ~p
(define tester3 (form->clauses
                 (cnf (clause (literal true 'r) (literal false 'p)))))


;; p v ~q 
(define not-changed-cnf  (cnf (clause (literal true 'p) (literal false 'q))))
;; (p v ~q) ^ (p v ~p)
(define not-changed-cnf2 (cnf (clause (literal true 'p) (literal false 'q))
                              (clause (literal true 'p) (literal false 'p))))
;; (p v r) ^ (~p v ~r)
(define not-changed-cnf3 (cnf (clause (literal true 'p) (literal true 'r))
                              (clause (literal false 'p) (literal false 'r))))
;; (p) ^ (~p) - sprzeczne
(define not-changed-cnf4 (cnf (list (literal true 'p))
                              (list (literal false 'p))))  
;; (p v r) ^ (~r v ~s) ^ (q v s) ^ (q v r) ^ (~p v ~q) ^ (s v p) - sprzeczne
(define not-changed-cnf5 (cnf (clause (literal true 'p) (literal true 'r))
                              (clause (literal false 'r) (literal false 's))
                              (clause (literal true 'q) (literal true 's))
                              (clause (literal true 'q) (literal true 'r))
                              (clause (literal false 'p) (literal false 'q))
                              (clause (literal true 's) (literal true 'p)) ))
;; (p) ^ (~p) ^ (r) ^ (~r) - sprzeczne
(define not-changed-cnf6 (cnf  (list (literal true 'p))
                               (list (literal false 'p))
                               (list (literal true 'r))
                               (list (literal false 'r))) )
;; (~p v q) ^ (~p v ~r v s) ^ (~q v r) ^ p ^ ~s - sprzeczne
(define not-changed-cnf7 (cnf (clause (literal false 'p) (literal true 'q))
                              (clause (literal false 'p) (literal false 'r) (literal true 's))
                              (clause (literal false 'q) (literal true 'r))
                              (clause (literal true 'p))
                              (clause (literal false 's))))


;; czy na pewno cnf ( p v ~q )?
(display "\nTest na pewno cnf?\n")
(cnf? not-changed-cnf)
(cnf? not-changed-cnf2)


;; testowe wypisywanie
(display "\nTest wypisywania:\n")
tester
tester2


;; UWAGA: w andmap w sorted-varlist? w res-clause?
;; było (andmap (var? x)), a powinno być (andmap var? x)
(display "\nTest czy na pewno spełniają res-clause?:\n")
(res-clause? (car tester))
(res-clause? (car tester2))
(res-clause? (car tester3))


;; test trywialności i resolve
(display "\nTest trywialności i resolve (true, false, rezolwenta):\n")
(clause-trivial? (car tester)) ; nie jest trywialne
(clause-trivial? (car tester2)) ; jest trywialne
;; resolve( p v ~q , r v ~p ) = ~q v r
(resolve (car tester) (car tester3))


;; testy ogólnego prove
;; te z wartościowaniem:
(display "\nTesty prove:\n")
(prove not-changed-cnf)
(prove not-changed-cnf2)
(prove not-changed-cnf3)
;; te sprzeczne:
(prove not-changed-cnf4) 
(prove not-changed-cnf5) 
(prove not-changed-cnf6)
(prove not-changed-cnf7) 


;; mini test sprawdania dowodu
(display "\nTesty prove-and-check:\n")
(prove-and-check not-changed-cnf)
(prove-and-check not-changed-cnf2)
(prove-and-check not-changed-cnf3)
(prove-and-check not-changed-cnf4)
(prove-and-check not-changed-cnf5)
(prove-and-check not-changed-cnf6)
(prove-and-check not-changed-cnf7)


;; test od A. Milczarka: bez optymalizacji - pętla
(display "\nReszta:\n")
(prove-and-check (cnf (clause (literal #t 'a) (literal #f 'c)) (clause (literal #f 'a) (literal #t 'b)) (clause (literal #t 'c) (literal #f 'b))))