#include <fstream>
#include <vector>
using namespace std;

ifstream in ("nfa.in");
ofstream out ("nfa.out");
#define MAXN 300
#define MAXLEN 150
int stare_finala[MAXN+1]; //folosesc acest array pentru a retine daca un nod este stare finala
int inq[1 + MAXN][1 + MAXLEN];
//folosesc inq pentru a verifica daca am mai trecut prin acel nod la acelasi pas din cuvant

struct vecin //folosesc structura pentru a retine numarului nodului vecin, cat si caracterul care se afla pe muchia dintre vecini
{
    int nrnod;
    char valmuchie;
};
struct el_coada //folosesc structura pentru elementele cozii pe care o voi folosi in rezolvarea subpunctului b
{
    int nrnod; //numarul nodului din coada
    int parcurs; //cate caractere din cuvantul de analizat am parcurs in automat
    el_coada* urm; //adresa urmatorului nod din coada
};
struct el_coada1 //folosesc structura pentru elementele cozii pe care o voi folosi in rezolvarea subpunctului c
{
    int nrnod; //numarul nodului din coada
    string cuv; //partea de cuvant parcursa pana la nodul curent
    el_coada1* urm; //adresa urmatorului nod din coada
};

int main()
{
    int N, M, K, x, i, q1, q2, Q, S;
    char c;
    string cuvant;

    in>>N>>M>>K>>S; //variabilele au aceeasi semnificatie ca in problema de pe infoarena mentionata
    for (i=0; i<K; i++)
    {
        in>>x;
        stare_finala[x]=1; //marchez nodurile finale
    }

    vector <vecin> liste_vecini[N+1]; //prin acest vector retin vecinii  unui nod si caracterul de pe muchia dintre nod si vecinul sau
    for (i=0; i<M; i++)
    {
        in>>q1>>q2>>c;
        vecin pereche;
        pereche.nrnod = q2;
        pereche.valmuchie = c;
        liste_vecini[q1].push_back(pereche);
    }
    in>>Q;
    //subpunctul a al proiectului - DFA
    /*
    for (i=0; i<Q; i++)
    {
        in>>cuvant; //citirea cuvintelor
        int lungime {static_cast<int>(cuvant.length())}; //lungimea cuvantului citit
        int acceptat = 0, nodcurent = S, parcurs=0;
        // acceptat este variablia in care vom retine daca cuvantul este sau nu acceptat
        // parcurs este variabila prin care retin cate caractere din cuvant au fost parcurse
        while (parcurs<=lungime)
        {
            if (parcurs == lungime) //daca am parcurs tot cuvantul
            {
                if (stare_finala[nodcurent]==1) //verific daca nodul in care ne aflam este stare finala
                    acceptat = 1; //cuvantul este acceptat
                parcurs++;

            }
            else
            {
                bool gasit = 0; //variabila semnifica daca am gasit o muchie pe care parcurgerea cuvantului poate continua
                for (vecin x : liste_vecini[nodcurent]) //pentru vecinii nodului curent
                {
                    if (x.valmuchie == cuvant[parcurs])//daca litera curenta este egala cu caracterul de pe muchie
                    {
                        nodcurent = x.nrnod; //mergem la nodul vecin
                        parcurs++; //am mai parcurs un caracter
                        gasit = 1; //am gasit o muchie pe care sa continuam parcurgerea
                        break; //intrucat automatul este determinist nu putem gasi mai multe muchii cu acelasi caracter
                    }
                }
                if (gasit==0) //nu am putut parcurge intreg cuvantul
                    break;
            }
        }
        out<<acceptat<<"\n";
    } */
    // subpunctul b al proiectului - NFA
    for (i=0; i<Q; i++)
    {
        in>>cuvant; //citirea cuvintelor
        int lungime {static_cast<int>(cuvant.length())}; //lungimea cuvantului citit
        int acceptat = 0, nodcurent;
        // acceptat este variablia in care vom retine daca cuvantul este sau nu acceptat
        for (int j=0; j<=MAXN; j++)
            for(int k=0; k<=MAXLEN; k++)
                inq[j][k]=0; //resetez matricea cu valoarea 0
        el_coada *prim = new el_coada; //creez primul element din coada
        prim->nrnod = S; //il initializez cu nodul de start
        prim->parcurs = 0; //->parcurs semnifica cate litere din cuvant au fost parcurse
        prim->urm = nullptr; //nodul urmatorul este null
        el_coada* ultim = prim; //initial ultimul nod este egal cu primul
        inq[S][0] = 1; //marchez pozitia de start si 0 litere
        while (prim != nullptr) //cat timp coada este nevida
        {
            nodcurent = prim->nrnod;
            if (prim->parcurs == lungime) //daca am parcurs tot cuvantul
            {
                if (stare_finala[nodcurent]==1) //daca nodul curent este stare finala
                {
                    acceptat = 1; //cuvantul este acceptat
                    break; //putem parasi while-ul
                }
            }
            else
            {
                for (vecin x : liste_vecini[nodcurent]) //pentru vecinii nodului curent
                {
                    if (x.valmuchie == cuvant[prim->parcurs] && inq[x.nrnod][prim->parcurs + 1]!=1)
                        //daca litera curenta este egala cu caracterul de pe muchie si nu am mai fost acolo cu aceeasi pozitie din cuvant
                    {
                        el_coada* aux = new el_coada; //creez ul element auxiliar pe care il adaug la final
                        aux->nrnod = x.nrnod;
                        aux->parcurs = prim->parcurs + 1;
                        aux->urm = nullptr; //urmatorul nod este null
                        ultim->urm = aux;
                        ultim = aux; //aux devine ultimul nod
                        inq[x.nrnod][prim->parcurs + 1] = 1; //il marchez ca parcurs
                    }
                }
            }
            el_coada* temp = prim;
            prim = prim -> urm; //resetez primul element pentru a-l putea sterge
            delete(temp); //sterg un element din coada
        }
        out<<acceptat<<"\n";
        while (prim != nullptr) //daca a ramas memorie dezalocata, o dezaloc
        {
            el_coada* temp = prim;
            prim = prim -> urm;
            delete(temp);
        }
    }

    // subpunctul c al proiectului - generarea celor mai mici 100 de cuvinte acceptate de automat
    vector <string> cuvinte[1]; //retin cuvintele generate pentru a nu obtine de mai multe ori acelasi cuvant
    int nr_generate = 0; //numarul de cuvinte generate
    el_coada1 *first = new el_coada1; //creez primul element din coada
    first->nrnod = S; //il initializez cu nodul de start
    first->cuv = ""; //->parcurs semnifica cate litere din cuvant au fost parcurse
    first->urm = nullptr; //nodul urmatorul este null
    el_coada1* last = first; //initial ultimul nod este egal cu primul
    while (nr_generate < 100 && first != nullptr) //daca nu am generat 100 de cuvinte, iar coada este nevida
    {
        int nodcurent = first->nrnod;
        if (stare_finala[nodcurent]==1) //daca nodul curent este stare finala, afisam cuvantul
        {

            bool distinct = true;
            for (string word: cuvinte[0]) //verific daca cuvantul nu este deja generat
                if ( first->cuv == word)
                    distinct = false;
            if (distinct == true) //daca cuvantul nu este deja generat
            {
                out<<first->cuv<<"\n";
                nr_generate++;
                cuvinte[0].push_back(first->cuv); //adaug cuvantul la vectorul de cuvinte generate
            }
        }
        for (vecin x : liste_vecini[nodcurent]) //pentru vecinii nodului curent
        {
            el_coada1* oth = new el_coada1; //creez ul element auxiliar pe care il adaug la final
            oth->nrnod = x.nrnod;
            oth->cuv = first->cuv + x.valmuchie;
            oth->urm = nullptr; //urmatorul nod este null
            last->urm = oth;
            last = oth; //aux devine ultimul nod
        }
        el_coada1* tmp = first;
        first = first -> urm; //resetez primul element pentru a-l putea sterge
        delete(tmp); //sterg un element din coada
    }
    while (first != nullptr) //daca a ramas memorie dezalocata, o dezaloc
    {
        el_coada1* tmp = first;
        first = first -> urm;
        delete(tmp);
    }
    return 0;
}
