def palindrome?(our_string)
  our_string = our_string.downcase.gsub(/[^a-zA-Z0-9\-]/,"").delete("- _")
  our_string == our_string.reverse
end

def mini_test_palindrome?(our_string, result)
  raise "This is wrong" unless palindrome?(our_string)==result
end

def test_palindrome?()
  mini_test_palindrome?("A man, a plan, a canal -- Panama", true)
  mini_test_palindrome?("Madam, I'm Adam!",true)
  mini_test_palindrome?("Abracadabra",false)
  mini_test_palindrome?("",true)
  mini_test_palindrome?(",./\;'[]<>?|:{}!@#$%^&*()",true)
  mini_test_palindrome?("AaAa$#@aa@#$A@aaa!aa@AA!A!)!a!A!A!a!",true)
  mini_test_palindrome?("BbbaaabBABABbbbab",false)
  mini_test_palindrome?(")k-a!j%a@k%",true)
  mini_test_palindrome?("O, ty z Katowic, Iwo? Tak, Zyto.",true)
  mini_test_palindrome?("Ile Roman ladny dyndal na moreli?",true)
  mini_test_palindrome?("Sum summus mus. ",true)
  mini_test_palindrome?("Co mi dal duch – cud, lad i moc.",true)
end

test_palindrome?()

#############################################################################

def count_words(our_string)
  words = Hash.new(0)
  our_string = our_string.downcase.gsub(/[^a-zA-Z0-9_']/, " ") 
  our_string.split(/\s/).each do |word|
    if word != ""
      words[word] += 1
    end
  end
  words
end

def mini_test_count_words(our_string, result)
  raise "This is wrong" unless count_words(our_string)==result
end

def test_count_words()
  mini_test_count_words("A man, a plan, a canal -- Panama",
  {'a' => 3, 'man' => 1, 'canal' => 1, 'panama' => 1, 'plan' => 1})
  mini_test_count_words("One Ring to rule them all, One Ring to find them,",
  {"one"=>2, "ring"=>2, "to"=>2, "rule"=>1, "them"=>2, "all"=>1, "find"=>1})
  mini_test_count_words("One Ring to bring them all and in the darkness bind them.",
  {"one"=>1, "ring"=>1, "to"=>1, "bring"=>1, "them"=>2, "all"=>1, "and"=>1, "in"=>1, "the"=>1, "darkness"=>1, "bind"=>1})
  mini_test_count_words("a b c d e f", {"a"=>1, "b"=>1, "c"=>1, "d"=>1, "e"=>1, "f"=>1})
  mini_test_count_words("a b c d e f a a a", {"a"=>4, "b"=>1, "c"=>1, "d"=>1, "e"=>1, "f"=>1})
end

test_count_words()

#############################################################################

def same23?(arr)
  a = arr.count("a")
  b = arr.count("b")
  c = arr.count("c")
  if (a==3)
    return (b==2 or c==2)
  elsif (b==3)
    return (a==2 or c==2)
  elsif (c==3)
    return (a==2 or b==2)
  else
    return false
  end
 #return (((a==3 and (b==2 or c==2)) or (b==3 and (a==2 or c==2))) or (c==3 and (a==2 or b==2)))
end

def mini_test_same23?(arr, result)
  raise "This is wrong" unless same23?(arr)==result
end

def test_same23()
  mini_test_same23?(["a", "a", "a", "b", "b"], true)
  mini_test_same23?(["a", "b", "c", "b", "c"], false)
  mini_test_same23?(["a", "a", "a", "a", "a"], false)
  mini_test_same23?(["a", "c", "a", "c", "a"], true)
  mini_test_same23?(["a", "c", "a", "b", "a"], false)
end

test_same23()