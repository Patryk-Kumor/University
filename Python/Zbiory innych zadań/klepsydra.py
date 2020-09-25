def klepsydra(N):   #2N+1
    for i in range(2*N+1):
        if i<=N:
            print(i*' '+(2*N-2*i+1)*'*')
        else:
            print((2*N-i)*' '+(2*i+1-2*N)*'*')

klepsydra(3)
print()
klepsydra(4)
