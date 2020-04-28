#voi citi lambda prin simbolul "$"
#voi citi datele din fisierul "proiect2.in"
#voi afisa rezultatul in fisierul "proiect2.out"
#voi afisa dfa-ul minimal intr-o forma asmenatoare citirii: pe prima linie N numarul de noduri, pe a doua linie M numarul de trazitii
# pe a treia linie K numarul de stari finale, pe urmatoarea linie starea initiala S, pe urmatoarea vectorul de stari finale
# pe urmatoarea linie dictionarul cu muchii
def Minimizare(automat):
    DFAminim = DFA()
    matriceEchivalenta = [[True for i in range (automat.nrNoduri)] for j in range (automat.nrNoduri)]
    for i in range (automat.nrNoduri):
        for j in range (i+1, automat.nrNoduri):
            if (automat.end[i] == 1 and automat.end[j]==0) or (automat.end[i] == 0 and automat.end[j]==1):
                matriceEchivalenta[i][j] = False
    changed = 1
    while changed == 1:
        changed = 0
        for i in range (automat.nrNoduri):
            for j in range (i+1, automat.nrNoduri):
                    for c in automat.multimeInput:
                        if matriceEchivalenta[i][j] == True:
                            x = -1
                            y = -1
                            for pereche in automat.tranzitii[i]:
                                if pereche[1] == c:
                                    x = pereche[0]
                            for pereche in automat.tranzitii[j]:
                                if pereche[1] == c:
                                    y = pereche[0]
                            if x != -1 and y != -1:
                                if x < y:
                                    if matriceEchivalenta[x][y] == False:
                                        matriceEchivalenta[i][j] = False
                                        changed = 1
                                else:
                                    if matriceEchivalenta[y][x] == False:
                                        matriceEchivalenta[i][j] = False
                                        changed = 1
    listOfNewNodes = []
    for i in range(automat.nrNoduri):
        gasit = 0
        for Set in listOfNewNodes:
            if i in Set:
                gasit = 1
        if gasit == 0:
            newset = set()
            newset.add(i)
            listOfNewNodes.append(newset)
        for j in range(i + 1, automat.nrNoduri):
            if matriceEchivalenta[i][j] == True:
                for Set in listOfNewNodes:
                    if i in Set:
                        Set.add(j)
    #print (listOfNewNodes)
    DFAminim.nrNoduri = len(listOfNewNodes)
    DFAminim.end = [0] * DFAminim.nrNoduri
    for i in range(len(listOfNewNodes)): #fiecare set devine un nod si gasesc muchiile
        for c in automat.multimeInput:
            for j in range(len(listOfNewNodes)):
                gasit = 0
                for element in listOfNewNodes[i]:
                    if gasit == 0:
                        for pereche in automat.tranzitii[element]:
                            if pereche[1] == c and pereche[0] in listOfNewNodes[j]:
                                gasit = 1
                                DFAminim.adaugaMuchie(i, j, c)
    for i in range(len(listOfNewNodes)): #determin starea initiala si starile finale ale noului automat
        final = 0
        for element in listOfNewNodes[i]:
            if element == automat.stareInitiala: #verific daca in set se afla starea initiala din vechiul dfa
                DFAminim.stareInitiala = i
            if automat.end[element] == 1: #verific daca in set se afla o stari finale din vechiul dfa
                final = 1
        if final == 1:
            DFAminim.nrStariFinale +=1
            DFAminim.end[i] = 1
    return DFAminim

def eliminare_stari_inaccesibile_si_nefinale(automat):
    DFAm1 = DFA(automat.stareInitiala)
    nod = automat.stareInitiala
    vizitat = [0] * automat.nrNoduri
    finale = [0] * automat.nrNoduri
    def DFS(nodcurent):
        vizitat[nodcurent] = 1
        for pereche in automat.tranzitii[nodcurent]:
            if vizitat[pereche[0]] == 0:
                DFS(pereche[0])
            if automat.end[nodcurent] == 1 or finale[pereche[0]] == 1:
                finale[nodcurent] = 1
    DFS(nod)
    for i in range (automat.nrNoduri):
        if vizitat[i] == 1 and finale[i] == 1:
            for pereche in automat.tranzitii[i]:
                if vizitat[pereche[0]] == 1 and finale[pereche[0]] == 1:
                    DFAm1.adaugaMuchie(i, pereche[0], pereche[1])
    DFAm1.end = [0] * automat.nrNoduri
    for i in range(automat.nrNoduri):
        if vizitat[i] == 1 and finale[i]==1:
            DFAm1.nrNoduri += 1
            if automat.end[i] == 1:
                DFAm1.nrStariFinale += 1
                DFAm1.end[i] = 1
        else:
            DFAm1.end[i] = - 1
    return DFAm1

def lambdaNFA_to_NFA(automat):
    automat.LambdaInchidere()
    automatNFA = NFA(automat.nrNoduri, 0, 0, automat.stareInitiala)
    for i in range(automat.nrNoduri):
        for c in automat.multimeInput:
            noduriVecine = set ()
            cVecini = set()
            for nod in automat.lambdaInchidere[i]:
                for pereche in automat.tranzitii[nod]:
                    if pereche[1] == c:
                        cVecini.add(pereche[0])
                if automat.end[nod] == 1:
                    automatNFA.end[i] = 1
            for nod in cVecini:
                noduriVecine = noduriVecine.union(automat.lambdaInchidere[nod])
            for nod in noduriVecine:
                automatNFA.adaugaMuchie(i, nod, c)
    automatNFA.setNrStariFinale()
    return automatNFA

def NFA_to_DFA(automat):
    coada = []
    l = [automat.stareInitiala]
    coada.append(l)
    p = 0
    u = 0
    automatDFA = DFA(automat.stareInitiala)
    if automat.end[automat.stareInitiala] == 1:
        automatDFA.end.append(1)
        automatDFA.nrStariFinale = 1
    else:
        automatDFA.end.append(0)
    while p <= u:
        for c in automat.multimeInput:
            noduriVecine = set()
            starefinala = 0
            for nod in coada[p]:
                if c in automat.tranzitii[nod].keys():
                    for vecin in automat.tranzitii[nod][c]:
                        noduriVecine.add(vecin)
                        if automat.end[vecin] == 1:
                            starefinala = 1
            newNode = list(noduriVecine)
            index = -1
            for i in range(u+1):
                if newNode == coada[i]:
                    index = i
            if index == -1:
                coada.append(newNode)
                u+=1
                automatDFA.adaugaMuchie(p, u, c)
                if starefinala == 1:
                    automatDFA.nrStariFinale += 1
                    automatDFA.end.append(1)
                else:
                    automatDFA.end.append(0)
            else:
                automatDFA.adaugaMuchie(p, index, c)
        p+=1
    automatDFA.nrNoduri = u + 1
    return automatDFA

def DFA_to_minimalDFA(automat):
    DFA1 = Minimizare(automat)
    #afisare(DFA1)
    return eliminare_stari_inaccesibile_si_nefinale(DFA1)

class lambdaNFA:
    def __init__(self, nrNoduri, nrMuchii, nrStariFinale, stareInitiala):
        self.nrNoduri = nrNoduri
        self.nrMuchii = nrMuchii
        self.nrStariFinale = nrStariFinale
        self.stareInitiala = stareInitiala
        self.end = [0] * nrNoduri  # seminifica daca un nod este stare finala sau nu
        self.tranzitii = {i: [] for i in range(nrNoduri)}  # dictionar, cheile sunt noduri, iar elementele nodurile vecine si caracterele
        self.multimeInput = set() #retin caractere de pe toate muchiile intr-o multime
    def setEnd (self, l):
        for i in range(self.nrStariFinale):
            l[i] = int(l[i])
            self.end[l[i]] = 1

    def adaugaMuchie(self, q1, q2, c):
        self.tranzitii[q1].append([q2, c])
        if c != '$':
            self.multimeInput.add(c)

    def LambdaInchidere(self):
        self.lambdaInchidere = {i: [i] for i in range(self.nrNoduri)} #initializez nodurile din care pot ajunge din i cu lambda
        vizitat = [0] * self.nrNoduri #verific daca am mai fost intr-un nod

        def lambdaParcurgere(nod, l):
            vizitat[nod] = 1 #marcam nodul ca vizitat
            for pereche in self.tranzitii[nod]:
                if pereche[1] == '$': #daca nodul nu a fost vizitat si are muchie lambda
                    if vizitat[pereche[0]] == 0:
                        lambdaParcurgere(pereche[0], l)
                    else:
                        l = self.lambdaInchidere[pereche[0]].copy()
            self.lambdaInchidere[nod].extend(l)  #updatez inchiderea nodului
            l.append(nod) #adaug nodul la lista partiala
        for i in range (self.nrNoduri):
            if vizitat[i] == 0:
                l = [] # retin nodurile in care am ajus pentru a le putea updata prin 'lambda'DFS
                lambdaParcurgere(i, l)

class NFA:
    def __init__(self, nrNoduri, nrMuchii, nrStariFinale, stareInitiala):
        self.nrNoduri = nrNoduri
        self.nrMuchii = nrMuchii
        self.nrStariFinale = nrStariFinale
        self.stareInitiala = stareInitiala
        self.end = [0] * nrNoduri  # seminifica daca un nod este stare finala sau nu
        self.tranzitii = [ {} for i in range (nrNoduri) ] # dictionar, cheile sunt noduri, iar elementele nodurile vecine si caracterele
        self.multimeInput = set()  # retin caractere de pe toate muchiile intr-o multime

    def adaugaMuchie(self, q1, q2, c):
        gasit = 0
        if c in self.tranzitii[q1].keys():
            self.tranzitii[q1][c].append(q2)
        else:
            self.tranzitii[q1].update({c: [q2]})
        self.multimeInput.add(c)
        self.nrMuchii += 1
    def setNrStariFinale(self):
        for i in range (self.nrNoduri):
            if self.end[i]:
                self.nrStariFinale += 1

class DFA:
    def __init__(self, stareInitiala = 0):
        self.nrNoduri = 0
        self.nrMuchii = 0
        self.nrStariFinale = 0
        self.stareInitiala = stareInitiala
        self.tranzitii = {}  # dictionar, cheile sunt noduri, iar elementele nodurile vecine si caracterele
        self.multimeInput = set()  # retin caractere de pe toate muchiile intr-o multime
        self.end = []
    def adaugaMuchie(self, q1, q2, c):
        if q1 not in self.tranzitii.keys():
            self.tranzitii.update({q1: []})
        self.tranzitii[q1].append([q2, c])
        self.multimeInput.add(c)
        self.nrMuchii += 1

def afisare(self):
    g.write(str(self.nrNoduri))
    g.write('\n')
    g.write(str(self.nrMuchii))
    g.write('\n')
    g.write(str(self.nrStariFinale))
    g.write('\n')
    g.write(str(self.stareInitiala))
    g.write('\n')
    g.write(str(self.end))
    g.write('\n')
    g.write(str(self.tranzitii))
    g.write('\n')

def main():

    N = int(f.readline())   # numar noduri
    M = int(f.readline())   # numar muchii
    K = int(f.readline())   #numar stari finale
    S = int(f.readline())   #starea initiala

    automat = lambdaNFA(N, M, K, S)

    l = f.readline().split()  # stari finale
    automat.setEnd(l)

    for i in range(M):
        l = f.readline().split()
        q1 = int(l[0])
        q2 = int(l[1])
        c = l[2]
        automat.adaugaMuchie(q1, q2, c)

    automatNFA = lambdaNFA_to_NFA(automat)
    automatDFA = NFA_to_DFA(automatNFA)
    #afisare(automatNFA)
    #afisare(automatDFA)
    automatDFAminimal = DFA_to_minimalDFA(automatDFA)
    afisare(automatDFAminimal)

f = open("proiect2.in", "r")
g = open("proiect2.out", "w")
main()