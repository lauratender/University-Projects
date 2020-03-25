def AFD():
    global dch, q0, end, cuv, lng
    parcurs = 0
    acceptat = 0
    nodcurent = q0
    while parcurs <=  lng:
        if parcurs == lng:
            parcurs+=1
            if end[nodcurent]==1:
                acceptat = 1

        else:
            gasit=0
            for L in dch[nodcurent]:
                if L[1]==cuv[parcurs]:
                    gasit=1
                    nodcurent = L[0]
                    parcurs+=1
                    break
            if gasit == 0:
                break
    if acceptat == 1:
        g.write('1 ')
        g.write(cuv)
        g.write (" este acceptat de limbaj\n")
    else:
        g.write('0 ')
        g.write(cuv)
        g.write (" nu este acceptat de limbaj\n")
def AFN():
    global dch, q0, end, cuv, lng
    acceptat = 0
    coada = [[q0, 0]]
    p = 0
    u = 0
    parcurs = 0
    while parcurs<=lng and p<= u:
        nodcurent = coada[p][0]
        parcurs = coada[p][1]
        if parcurs == lng:
            if end[nodcurent]==1:
                acceptat = 1
                parcurs+=1
        else:
            for L in dch[nodcurent]:
                if L[1]==cuv[parcurs]:
                    coada.append([L[0], parcurs+1])
                    u+=1
        p+=1
    if acceptat == 1:
        g.write('1 ')
        g.write(cuv)
        g.write (" este acceptat de limbaj\n")
    else:
        g.write('0 ')
        g.write(cuv)
        g.write (" nu este acceptat de limbaj\n")
def generare():
    global dch, q0, end, cuv, lng
    generate = 0
    coada = [[q0,'']]
    p = 0
    u = 0
    while generate <=100 and p<=u:
        nodcurent = coada[p][0]
        if end[nodcurent]==1:
            g1.write(coada[p][1])
            g1.write('\n')
            generate+=1
        for L in dch[nodcurent]:
            coada.append([L[0], coada[p][1]+L[1]])
            u+=1
        p+=1
#main
f=open("automat.in", "r")
f1=open("cuvinte.in", "r")
g=open("starecuvinte.out", "w")
g1=open("limbaj.out", "w")
n = int(f.readline()) #numar noduri
m = int(f.readline()) #numar muchii
dch = {i:[] for i in range(n)} #dictionar, cheile sunt noduri, iar elementele nodurile vecine si caracterele
for i in range(m): #creare Lvec si c
    l = f.readline().split()
    q1 = int(l[0])
    q2 = int(l[1])
    c = l[2]
    dch[q1].append([q2, c])

q0 = int(f.readline()) #stare initala
t = int(f.readline()) #numar de stari finale
end = [0]*n # seminifica daca un nod este stare finala sau nu
l = f.readline().split() #stari finale
for i in range(t):
    l[i] = int(l[i])
    end[l[i]]=1
nrcuv=int(f1.readline())
for i in range(nrcuv):
   cuv = f1.readline().split()
   cuv = cuv[0]
   lng = len(cuv)
   #a)
   #AFD()
   #b)
   AFN()
   #c
   generare()
