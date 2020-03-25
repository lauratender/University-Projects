import time
import random
def afisare(l):
    global n
    for i in range(n):
        g.write(str(l[i]))
        g.write(' ')
    g.write('\n')
def verificare (v, sortat):
    if v == sortat:
        g.write('sortat\n')
    else:
        g.write('nesortat\n')
def sortare_nativa(l):
    l.sort()
    return l
def bubble_sort(l):
    global n
    if n > 10000:
        return l
    ok = 1
    while ok == 1:
        ok = 0
        for i in range (n-1):
            if l[i] > l[i+1]:
                l[i], l[i+1] = l[i+1], l[i]
                ok = 1
    return l
def count_sort(l):
    global n, M, new
    if M > 100000:
        return l
    else:
        f = [0]*(M+1)
        for i in range (n):
            f[l[i]]+=1
        new = []
        for i in range(M+1):
            if f[i]>0:
                for j in range (f[i]):
                    new.append(i)
        return new
def merge_sort(l):
    n=len(l)
    if n>1:
        mij = n//2
        a = l[:mij]
        b = l[mij:]
        merge_sort(a)
        merge_sort(b)
        i = j = k = 0
        m = n- mij
        while i < mij and j<m:
            if a[i] < b[j]:
                l[k]=a[i]
                i+=1
            else:
                l[k]=b[j]
                j+=1
            k+=1
        while i<mij:
            l[k] = a[i]
            i += 1
            k+=1
        while j<m:
            l[k] = b[j]
            j += 1
            k+=1
        return v

def quicksort_random(st, dr):
    global v
    pivot = random.choice(v[st:(dr+1)])
    i = st
    j = dr
    while i <= j:
        while v[i] < pivot:
            i+=1
        while v[j] > pivot:
            j-=1
        if i <= j:
            v[i], v[j] = v[j], v[i]
            i+=1
            j-=1
    if st < j:
        quicksort_random(st, j)
    if i < dr:
        quicksort_random (i, dr)

def quicksort_mediana(st, dr): #daca vectorul este deja sortat programul nu mai functioneaza chiar daca in anumite cazuri este mai eficienta
    global v
    if dr - st > 3:
        A = v[st: (st+3)]
        A.sort()
        pivot = A[1]
    else:
        pivot = v[st]
    i = st
    j = dr
    while i <= j:
        while v[i] < pivot:
            i+=1
        while v[j] > pivot:
            j-=1
        if i <= j:
            v[i], v[j] = v[j], v[i]
            i+=1
            j-=1
    if st < j:
        quicksort_mediana(st, j)
    if i < dr:
        quicksort_mediana (i, dr)

def RadixSort10(l, p):
    global ar
    List = [[]for i in range(10)]
    lg = len (l)
    for i in range(lg):
        List[(l[i]//p)%10].append(l[i])
    for i in range(10):
        if len(List[i])>1 and p!=1:
            RadixSort10(List[i], p//10)
        if len(List[i])==1 or p == 1:
            ar.extend(List[i])
def RadixSort2(l, p):
    global ar
    List = [[]for i in range(2)]
    lg = len (l)
    for i in range(lg):
        List[(l[i]>>p)%2].append(l[i])
    for i in range(2):
        if len(List[i])>1 and p>0:
            RadixSort2(List[i], p-1)
        if len(List[i])==1 or p == 0:
            ar.extend(List[i])
f = open("date.in", "r")
g = open ("date.out", "w")
x = int(f.readline())
for j in range (x):
    v = f.readline().split(', ')
    n = len(v)

    g.write("test ")
    g.write( str(j+1))
    g.write(": ")
    g.write(str(n))
    g.write (" numere mai mici decat ")
    for i in range(n):
        v[i]=int(v[i])
    M = max(v)
    g.write(str(M+1))
    g.write('\n')

    cv=v[:]
    sortat = v[:]

    inceput = time.time()
    sortare_nativa(sortat)
    sfarsit = time.time()
    g.write ('Sortare nativa - timp: ')
    g.write(str(sfarsit-inceput))
    g.write('\n')

    v = cv[:]
    inceput = time.time()
    bubble_sort(v)
    sfarsit = time.time()
    g.write('Bubble sort - timp: ')
    g.write(str(sfarsit - inceput))
    g.write(', status: ')
    verificare(v, sortat)

    v = cv [:]
    inceput = time.time()
    new = count_sort(v)
    sfarsit = time.time()
    g.write('Count sort - timp: ')
    g.write(str(sfarsit - inceput))
    g.write(', status: ')
    verificare(new, sortat)

    v = cv [:]
    inceput=time.time()
    merge_sort(v)
    sfarsit=time.time()
    g.write('Merge sort - timp: ')
    g.write(str(sfarsit-inceput))
    g.write(', status: ')
    verificare(v, sortat)

    v = cv[:]
    inceput = time.time()
    quicksort_random(0, n - 1)
    sfarsit = time.time()
    g.write('Quick sort cu pivot ales random - timp: ')
    g.write(str(sfarsit - inceput))
    g.write(', status: ')
    verificare(v, sortat)

    v = cv[:]
    cM=M
    p=1
    while cM>0:
        cM//=10
        p*=10
    p//=10
    ar = []
    inceput = time.time()
    RadixSort10(v, p)
    sfarsit = time.time()
    g.write('Radix sort in baza 10 - timp: ')
    g.write(str(sfarsit - inceput))
    g.write(', status: ')
    verificare(ar, sortat)

    v = cv[:]
    cM = M
    p = 0
    while cM > 0:
        cM>>=1
        p +=1
    p -= 1
    ar = []
    inceput = time.time()
    RadixSort2(v, p)
    sfarsit = time.time()
    g.write('Radix sort in baza 2 - timp: ')
    g.write(str(sfarsit - inceput))
    g.write(', status: ')
    verificare(ar, sortat)
    g.write("\n")

f.close()
g.close()


