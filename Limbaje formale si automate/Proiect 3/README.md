# Proiectul al III-lea
## Transformarea unei gramatici regulate intr-un DFA minimal

Acest proiect este un update la proiectul al II-lea. Am adaugat functia de transformare a unei gramatici regulate intr-un lambda NFA.

O gramatica regulata are tranzitii de forma:

1. stare neterminala -> stare terminala stare neterminala

sau

2. stare neterminala -> stare terminala

Un rezumat al implementarii este acesta: 

Pentru starile neterminale am creat noduri, la care am adaugat un unic nod stare finala. 
Pentru tranzitiile de tip 1 am construit o muchie intre cele doua noduri asociate starilor neterminale ce are ca simbol starea terminala. Pentru tranzitiile de tip 2 am construit o muchie ce are ca simbol starea terminala de la starea neterminala catre unica stare finala. 
