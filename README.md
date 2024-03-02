# File-System-Data-Structures

Am definit structurile Dir si File astfel:
*pentru Dir:
        -nume director
        -pointer catre directorul parinte
        -pointer catre radacina arborelui de fisiere
        -pointer catre radacina arborelui de directoare
        -pointer catre directorul mai mic lexicografic
        -pointer catre directorul mai mare lexicografic
*pentru File:
        -nume fisier
        -pointer catre radacina arborelui parinte de directoare
        -pointer catre fisierul mai mic lexicografic
        -pointer catre fisierul mai mare lexicografic

Functiile definite de mine sunt:
-searchNameInDirs si searchNameInFiles, care cauta nume de director/fisier in
arborii de directoare/fisiere din directorul curent

-isGreater, care imi compara doua stringuri, fiind true daca primul e mai mare

-alocHeadFile, care imi initializeaza campurile pentru un fisier

-alocHeadDir, care imi initializeaza campurile pentru un director

-touch, o functie care imi adauga un fisier in arborele de fisiere, fie la inceput
daca arborele e vid, fie pe stanga sau dreapta, in functie de compararea numelui
pe care doresc sa il inserez cu cele deja existente

-mkdir, face acelasi lucru ca si touch, doar ca este pentru directoare

-inOrderForDir/inOrderForFile, functii care realizeaza o parcurgere inOrder pe arbore

-ls, functia de afisare a elementelor din arborele de directoare, urmat de elementele
din arborele de fisiere. Pentru asta, am parcurs inorder ambii arbori, pentru a le afisa
in ordine lexicografica

-rm, functie care sterge un fisier din arborele de fisiere din directorul curent. Daca
arborele este gol, nu avem ce sterge, altfel parcurg arborele pana cand acesta e gol sau
gasesc elementul de eliminat, iar in cel din urma caz, verific daca are fie doar un fiu, fie
ambii fii, si in functie de aceste doua cazuri, elimin fisierul cautat

-destroyFileTree, o functie care imi distruge arborele de fisiere dintr-un director curent;
distrugerea se realizeaza recursiv

-rmAll, functie recursiva, care parcurge arborele de directoare, si elimin
tot ce se poate din directoarele si fisierele prezente acolo

-rmdir, functie care are ca scop eliminarea unui director, impreuna cu arborii de directoare
si ai celor din interiorul directoarelor. Aceasta functie se bazeaza pe rmAll si destroyFiletree.
procedeul este identic cu cel al lui rm, adica parcurgerile si cazurile de eliminare

-cd, este o functie care ma muta din directorul curent in cel cautat, sau inapoi.
parcurgerea este iterativa, si folosesc functia isGreater pentru a afla daca merg pe stanga
sau pe dreapta. In cazul in care variabila temporara ajunge pe NULL, nu exista directorul

-pwd, functie recursiva care imi afiseaza calea pana la directorul curent de la root

-findFile, o functie recursiva care cauta un fisier in toti arborii de fisiere din toti arborii
de directoare, astfel ca ma folosesc e functia searchNameInFiles pentru a cauta in arborele din
directorul curent, iar daca nu se gaseste, caut in continuare in toate directoarele.

-findDir, face acelasi lucru, dar pentru nume de director, si foloseste functia searchNameInDirs

-find, functie care primeste parametru tipul cautat, adica -f sau -d, iar in functie de asta
cauta folosind findFile sau findDir

-quit, care nu este de fapt o functie, ci doar un caz tratat in main, in care apelez rmAll pe root,
pentru memory leaks.

In main, am citit de la stdin comanda pe care trebuie sa o execut, alaturi de parametrii care puteau
sa existe sau nu, si am apelat functiile definite mai sus.

