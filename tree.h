/* Movileanu Raluca - 311CB */
#ifndef TEMA3SD_TREE_H
#define TEMA3SD_TREE_H
#define MAXLENDIR 50 //lungime nume director
#define MAXLENFILE 50 //lungime nume fisier
#define MAXLENLINE 60 // lungime maxima linie citita
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Dir {
    char * name; // nume director
    struct Dir * parent; // pointer catre directorul parinte
    struct File * head_children_files; // pointer catre radacina arborelui de fisiere
    struct Dir * head_children_dirs; // pointer catre radacina arborelui de directoare
    struct Dir * left; // pointer catre directorul mai mic lexicografic
    struct Dir * right; // pointer catre directorul mai mare lexicografic
} Dir;

typedef struct File {
    char * name; // nume fisier
    struct Dir * parent; // pointer catre radacina arborelui parinte de directoare
    struct File * left; // pointer catre fisierul mai mic lexicografic
    struct File * right; // pointer catre fisierul mai mare lexicografic
} File;

/* Functie care cauta numele in arborele de directoare dintr-un director */
bool searchNameInDirs (Dir *dir, char *name) ;

/* Functie care cauta numele in arborele de fisiere dintr-un director */
bool searchNameInFiles (File *file, char *name) ;

/* Functie care compara doua stringuri, ca referinta avand prima valoare */
bool isGreater (char *a, char *b);

/* Functie care aloca memorie pentru un obiect de tip File */
File *alocHeadFile (Dir *parent, char *name);

/* Functei care aloca memorie pentru un obiect de tip Dir */
Dir *alocHeadDir (Dir *parent, char *name);

/* Functie care creeaza un fisier in directorul curent */
void touch (Dir *parent, char *name);

/* Functie care creaza un director in directorul curent */
void mkdir (Dir *parent, char *name);

/* Parcurgere inOrder / stanga vf dreapta pentru fisiere */
void inOrderForDir (Dir *parent);

/* Parcurgere inOrder / stanga vf dreapta pentru directoare */
void inOrderForFile (File * file);

/* Functie care afiseaza directoarele si fisierele din directorul curent */
void ls(Dir *parent);

/* Functie care elimina un fisier din directorul curent */
File* rm (Dir *parent, char *name);

/* Functie care distruge recursiv un arbore de fisiere */
void destroyFileTree (File *file);

/* Functie care distruge recursiv un arbore de directoare */
void rmAll (Dir *parent);

/* Functie care elimina un director, cu tot ce contine el */
Dir* rmDir (Dir *parent, char *name);

/* Functie care muta utilizatorul din directorul corect in directorul name */
void cd(Dir **target, char *name);

/* Functie care arata calea de la root la directorul curent */
void pwd(Dir *current);

/* Functie care cauta un fisier in toata ierarhia de directoare si fisiere */
void findFile (Dir *parent, char *name, bool *found);

/* Functie care cauta un director in toata ierarhia de directoare si fisiere */
void findDir (Dir *parent, char *name, bool *found);

/* Functie care primeste ca parametru un tip de fisier
 * adica -d pentru director si -f pentru file, si il cauta */
void find (Dir *parent, char *type, char *name, bool *found);

#endif //TEMA3SD_TREE_H