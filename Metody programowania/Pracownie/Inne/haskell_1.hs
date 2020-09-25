-- Wymagamy, by moduł zawierał tylko bezpieczne funkcje
{-# LANGUAGE Safe #-}
-- Definiujemy moduł zawierający rozwiązanie.
-- Należy zmienić nazwę modułu na {Imie}{Nazwisko} gdzie za {Imie}
-- i {Nazwisko} należy podstawić odpowiednio swoje imię i nazwisko
-- zaczynające się wielką literą oraz bez znaków diakrytycznych.
module PatrykKumor (typecheck, eval) where

-- Importujemy moduły z definicją języka oraz typami potrzebnymi w zadaniu
import AST
import DataTypes
import Data.Typeable
import Data.List
import Data.Maybe

-- Funkcja sprawdzająca typy
-- Dla wywołania typecheck vars e zakładamy, że zmienne występujące
-- w vars są już zdefiniowane i mają typ int, i oczekujemy by wyrażenia e
-- miało typ int
-- UWAGA: to nie jest jeszcze rozwiązanie; należy zmienić jej definicję.
--------------------------------------------------------------------------------------------------------

typecheck :: [Var] -> Expr p -> TypeCheckResult p
typecheck vars e = typecheck2 vars [] e
typecheck2 vars bools e = case e of
  EVar p var -> if elem var vars then Ok
                                 else Error (getData e) "Error: no var in vars"
  ENum    p integer -> Ok
  EBool   p bool ->  Error p "Error: bool return" 
                     where p = (getData (EBool p bool))
  EUnary p unaryOperator e1 -> case unaryOperator of
                               UNot -> Error (getData e) "Error: bool operator in return"
                               UNeg -> if typecheck2int vars bools e1 then Ok
                                                           else Error (getData e) "Error: types do not match"
  EBinary p binaryOperator e1 e2 -> case elem binaryOperator binaryInt of
                                    True -> if ((typecheck2int vars bools e1) && (typecheck2int vars bools e2)) then Ok
                                                                                          else Error (getData e) "Error: types do not match"
                                    False -> Error (getData e) "Error: bool operator in return"
                                    where binaryInt = [BAdd, BSub, BMul, BDiv, BMod]
  EIf p eBool e1 e2 -> if (typecheck2bool vars bools eBool) then if ((typecheck2int vars bools e1) && (typecheck2int vars bools e2)) then Ok
                                                                                                    else  Error (getData e) "Error: types do not match in If"
                                                 else Error (getData e) "Error: not bool in IF"
  ELet p var e1 e2 -> if ((typecheck2int vars bools e1) && (typecheck2int (var:vars) bools e2)) then Ok
                                                                     else if ((typecheck2bool vars bools e1) && (typecheck2int vars (var:bools) e2)) then Ok
                                                                                                                        else Error (getData e) "Error: types do not match in Let"
--------------------------------------------------------------------------------------------------------

typecheck2int vars bools (ENum _ _) = True
typecheck2int vars bools (EUnary _ UNeg e) = typecheck2int vars bools e
typecheck2int vars bools (EVar _ var) = elem var vars
typecheck2int vars bools (EBinary _ operator e1 e2) = case elem operator op_list of
                                           True -> (typecheck2int vars bools e1) && (typecheck2int vars bools e2)
                                           False -> False
                                           where op_list = [BAdd, BSub, BMul, BDiv, BMod]
typecheck2int vars bools (ELet _ var e1 e2) = if (typecheck2int vars bools e1) then (typecheck2int (var:vars) bools e2)
                                              else if (typecheck2bool vars bools e1) then (typecheck2int vars (var:bools) e2)
                                                   else False
typecheck2int vars bools (EIf _ eBool e1 e2) = (typecheck2bool vars bools eBool) && (typecheck2int vars bools e1) && (typecheck2int vars bools e2)
typecheck2int vars bools _ = False
--------------------------------------------------------------------------------------------------------

typecheck2bool vars bools (EVar _ var) = elem var bools
typecheck2bool vars bools (EBool _ _) = True
typecheck2bool vars bools (EUnary _ UNot e) = typecheck2bool vars bools e
typecheck2bool vars bools (EBinary _ op e1 e2) = case elem op op_list1 of
                                      True -> (typecheck2bool vars bools e1) && (typecheck2bool vars bools e2)
                                      False -> case elem op op_list2 of
                                               True -> (typecheck2int vars bools e1) && (typecheck2int vars bools e2)
                                               False -> False
                                      where op_list1 = [BAnd, BOr]
                                            op_list2 = [BEq, BNeq, BLt, BGt, BLe, BGe]
typecheck2bool vars bools (EIf _ eBool e1 e2) = (typecheck2bool vars bools e1) && (typecheck2bool vars bools eBool) && (typecheck2bool vars bools e2)
typecheck2bool vars bools (ELet _ var e1 e2) = if (typecheck2int vars bools e1) then (typecheck2bool (var:vars) bools e2)
                                              else if (typecheck2bool vars bools e1) then (typecheck2bool vars (var:bools) e2)
                                                   else False
typecheck2bool vars bools _ = False

--------------------------------------------------------------------------------------------------------
-- Funkcja obliczająca wyrażenia
-- Dla wywołania eval input e przyjmujemy, że dla każdej pary (x, v)
-- znajdującej się w input, wartość zmiennej x wynosi v.
-- Możemy założyć, że wyrażenie e jest dobrze typowane, tzn.
-- typecheck (map fst input) e = Ok
-- UWAGA: to nie jest jeszcze rozwiązanie; należy zmienić jej definicję.
--------------------------------------------------------------------------------------------------------

eval :: [(Var,Integer)] -> Expr p -> EvalResult
eval vars e = eval2 vars [] e

eval2 vars bools e = case e of
  EVar p var -> Value $ (snd lst)!!(fromJust $ elemIndex var $ fst lst)
                where lst = unzip vars
  ENum p integer -> Value integer
  EBool p bools ->  RuntimeError
  EUnary p unaryOperator e1 -> case unaryOperator of
                               UNeg -> Value (-(licz vars bools e1))
                               otherwise -> RuntimeError
  EBinary p binaryOperator e1 e2 -> case elem binaryOperator binaryInt of
                                    True -> case binaryOperator of
                                            BAdd -> Value ((licz vars bools e1) + (licz vars bools e2))
                                            BSub -> Value ((licz vars bools e1) - (licz vars bools e2))
                                            BMul -> Value ((licz vars bools e1) * (licz vars bools e2))
                                            BDiv -> if ((licz vars bools e2) == 0) then RuntimeError
                                                    else Value ((licz vars bools e1) `div` (licz vars bools e2))
                                            BMod -> if ((licz vars bools e2) == 0) then RuntimeError
                                                    else Value ((licz vars bools e1) `mod` (licz vars bools e2))
                                    False -> RuntimeError
                                    where binaryInt = [BAdd, BSub, BMul, BDiv, BMod]
  EIf p eBool e1 e2 -> case (licz_bool vars bools eBool) of
                        True -> Value (licz vars bools e1)
                        False -> Value (licz vars bools e2)
  ELet p var e1 e2 -> if (typecheck2int (lista vars) (lista bools) e1) then Value (licz ((var,n):vars) bools e2)
                      else if (typecheck2bool (lista vars) (lista bools) e1) then Value (licz vars ((var,m):bools) e2)
                           else RuntimeError
                      where n = licz vars bools e1
                            m = licz_bool vars bools e1
--------------------------------------------------------------------------------------------------------


licz vars bools (EVar p var) = (snd lst)!!(fromJust $ elemIndex var $ fst lst)
                              where lst = unzip vars
licz vars bools (ENum p integer) = integer
licz vars bools (EUnary p unaryOperator e1) = case unaryOperator of
                                               UNeg ->  (-(licz vars bools e1))
licz vars bools (EBinary p binaryOperator e1 e2) = case elem binaryOperator binaryInt of
                                                   True -> case binaryOperator of
                                                      BAdd ->  ((licz vars bools e1) + (licz vars bools e2))
                                                      BSub ->  ((licz vars bools e1) - (licz vars bools e2))
                                                      BMul ->  ((licz vars bools e1) * (licz vars bools e2))
                                                      BDiv -> if ((licz vars bools e2) == 0) then 0
                                                              else  ((licz vars bools e1) `div` (licz vars bools e2))
                                                      BMod -> if ((licz vars bools e2) == 0) then 0
                                                              else  ((licz vars bools e1) `mod` (licz vars bools e2))
                                                   where binaryInt = [BAdd, BSub, BMul, BDiv, BMod]
licz vars bools (EIf p eBool e1 e2) = case (licz_bool vars bools eBool) of
                                      True -> (licz vars bools e1)
                                      False -> (licz vars bools e2)
licz vars bools (ELet p var e1 e2) = if (typecheck2int (lista vars) (lista bools) e1) then  (licz ((var,n):vars) bools e2)
                                     else if (typecheck2bool (lista vars) (lista bools) e1) then  (licz vars ((var,m):bools) e2)
                                              else 0
                                     where n = licz vars bools e1
                                           m = licz_bool vars bools e1
--------------------------------------------------------------------------------------------------------


licz_bool vars bools (EVar p var) = (snd lst)!!(fromJust $ elemIndex var $ fst lst)
                                    where lst = unzip bools
licz_bool vars bools (EBool   p bool) = bool
licz_bool vars bools (EUnary p unaryOperator e1) = case unaryOperator of
                                                   UNot ->  if ((licz_bool vars bools e1)==True) then False else True 
licz_bool vars bools (EBinary p binaryOperator e1 e2) = case binaryOperator of
                                                        BAnd -> (licz_bool vars bools e1) && (licz_bool vars bools e2)
                                                        BOr -> (licz_bool vars bools e1) || (licz_bool vars bools e2)
                                                        BEq -> (licz vars bools e1) == (licz vars bools e2)
                                                        BNeq -> (licz vars bools e1) /= (licz vars bools e2)
                                                        BLt -> (licz vars bools e1) < (licz vars bools e2)
                                                        BGt -> (licz vars bools e1) > (licz vars bools e2)
                                                        BLe -> (licz vars bools e1) <= (licz vars bools e2)
                                                        BGe -> (licz vars bools e1) >= (licz vars bools e2)
licz_bool vars bools (EIf p eBool e1 e2) = case (licz_bool vars bools eBool) of
                                           True -> (licz_bool vars bools e1)
                                           False -> (licz_bool vars bools e2)
licz_bool vars bools (ELet p var e1 e2) = if (typecheck2int (lista vars) (lista bools) e1) then  (licz_bool ((var,n):vars) bools e2)
                                          else if (typecheck2bool (lista vars) (lista bools) e1) then  (licz_bool vars ((var,m):bools) e2)
                                                     else False
                                          where n = licz vars bools e1
                                                m = licz_bool vars bools e1


lista xs = fst l
 where l = unzip xs

 