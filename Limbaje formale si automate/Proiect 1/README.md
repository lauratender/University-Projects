*Cerințele temei*

a) AFD: Se da un automat finit determinist apoi o lista de cuvinte și pentru fiecare dintre cuvinte trebuie sa spuneți dacă este acceptat de automat;

b) AFN: Aceeasi cerinta aplicata unui un automat nedeterminist;

c) Generarea celor mai mici 100 de cuvinte acceptate de automat.

De asemenea cerinta subpunctului b) poate fi verificata pe platforma Infoarena, problema nfa: www.infoarena.ro/problema/nfa.

*Despre rezolvare*

Am implementat cerințele problemei atât în C++, cât și în Python. Inițial am scris programul în Python, apoi am scris o versiune îmbunătățită în C++. 

În implementarea din C++, citirea datelor se face precum în problema nfa/infoarena.
În Python, din fișierul "automat.in", citesc pe prima linie un număr n de noduri, pe următoarea linie un număr m de de muchii, pe următoarele m linii, câte două numere reprezentând noduri și un caracter de pe muchia dintre acestea. Pe următoarea linie, cites numărul q0, starea inițială. Pe o altă linie un număr t, reprezentând numărul de stări finale, iar pe ultima linie t numere reprezentând stările finale. Din fișierul "cuvinte.in" citesc pe prima linie numărul de cuvinte și de pe următoarele linii cuvintele, fiecare cuvânt este pe o linie. În fișierul "starecuvinte.out" precizez pentru fiecare cuvânt dacă este acceptat de automat. În fișierul "limbaj.out" afișez cele mai mici 100 de cuvinte (sau toate în cazul în care sunt mai puține) acceptate de automat.

*C++*

Am reținut vecinii unui nod și caracterul dintre acesta și vecini printr-un vector de o structură ce conține vecinul și caracterul.
Pentru subpunctele b) și c) am folosit două structuri de coadă sub forma unor liste simplu inlănțuite, operațiile de pop realizându-se într-o complexitate O(1) și eliberând memoria. Cozile rețin și pentru b) numărul de litere parcurse până la acel nod, respectiv pentru c) literele parcurse pănă la acel nod printr-un string. 
La b) cu ajutorul unei matrici rețin dacă am mai trecut deja printr-un nod cu același număr de litere parcurs pentru a nu face pași inutili.
Adaug toate cuvintele generate într-un vector de stringuri. Cu ajutorul lui verific că nu am generat un cuvânt de mai multe ori.

*Python*

Am reținut vecinii unui nod și caracterul dintre acesta și vecini printr-un dicționar, cheia este un întreg ce reprezintă numărul nodului, iar valorile sunt liste de liste ce conțin perechi nod, valoare.
Cerințele b) și c) sunt implementate cu ajutorul unor cozi statice, soluția aceasta fiind mai ineficientă din punct de vedere al memoriei. 
