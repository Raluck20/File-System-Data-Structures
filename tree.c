/* Movileanu Raluca - 311CB */
#include "tree.h"

/* Functie care cauta numele in arborele de directoare dintr-un director */
bool searchNameInDirs (Dir *dir, char *name) {
    if (dir == NULL) // conditie stop
        return false;
    if (strcmp(dir->name, name) == 0){ //daca sunt egale, numele exista
        return true;
    }
    else if (isGreater(name, dir->name))    //altfel, apeluri recursive
        return searchNameInDirs(dir->right, name);
    else
        return searchNameInDirs(dir->left, name);
}

/* Functie care cauta numele in arborele de fisiere dintr-un director */
bool searchNameInFiles (File *file, char *name) {
    if (file == NULL)
        return false;
    if (strcmp(file->name, name) == 0) { //daca sunt egale, numele exista
    return true;
    }
    if (isGreater(name, file->name)) //altfel, apeluri recursive
        return searchNameInFiles(file->right, name);
    else
        return searchNameInFiles(file->left, name);
}
/* Functie care compara doua stringuri, ca referinta avand prima valoare */
bool isGreater (char *a, char *b) {
    if (strcmp(a, b) > 0) {
        return true;
    }
    return false;
}
/* Functie care aloca memorie pentru un obiect de tip File */
File *alocHeadFile (Dir *parent, char *name) {
    File *file = (File*)malloc(sizeof(File));
    if (!file) {
        printf("Allocation error\n"); //eroare la alocare
        return NULL;
    }
    file->name = (char*)malloc(MAXLENFILE * sizeof(char));
    if (!file->name) {
        printf("Allocation error\n");
        free(file);
        return NULL;
    }
    strcpy(file->name, name); // copiez numele
    file->parent = parent; // atribuim campului parent pe parent dat ca parametru
    file->left = NULL;
    file->right = NULL;

    return file;
}

/* Functie care aloca memorie pentru un obiect de tip Dir */
Dir *alocHeadDir (Dir *parent, char *name) {
    Dir *dir = (Dir*)malloc(sizeof(Dir));
    if (!dir) {
        printf("Allocation error\n"); // eroare la alocare
        return NULL;
    }

    dir->name = (char*)malloc(MAXLENDIR * sizeof (char));
    if (!dir->name) {
        printf("Allocation error\n");
        free(dir);
        return NULL;
    }

    strcpy(dir->name, name); // copiez numele
    dir->parent = parent; // atribuim campului parent pe parent dat ca parametru
    dir->left = NULL;
    dir->right = NULL;
    dir->head_children_dirs = NULL;
    dir->head_children_files = NULL;

    return dir;
}

/* Functie care creeaza un fisier in directorul curent */
void touch (Dir *parent, char *name) {
    //caut in lista de directoare din directorul curent, nu pot exista fisier si director
    //cu acelasi nume
    if (parent->head_children_dirs != NULL &&
        (searchNameInDirs(parent->head_children_dirs, name) == true)) {
        printf("Directory %s already exists!\n", name);
        return;
    }

    //cazul pentru lista goala, cream un nou fisier fiind cap de lista
    if (parent->head_children_files == NULL) {
        parent->head_children_files = alocHeadFile(parent, name);
        return;
    }

    //parcurgem arborele de fisiere
    File **temp = &(parent->head_children_files);
    while (*temp != NULL) {
        if (strcmp ((*temp)->name, name) == 0) {
            printf("File %s already exists!\n",name);
            return;
        }
        if (isGreater(name, (*temp)->name)) { //daca numele e mai mare, merg dreapta
            temp = &(*temp)->right;
        }
        else {
            temp = &(*temp)->left; // altfel stanga
        }
    }
    *temp = alocHeadFile(parent, name); //am gasit locul unde creez fisierul
}

/* Functie care creaza un director in directorul curent */
void mkdir (Dir *parent, char *name) {
    //caut in lista de fisiere din directorul curent, nu pot exista fisier si director
    //cu acelasi nume
    if (parent->head_children_files != NULL &&
        searchNameInFiles(parent->head_children_files, name) == true) {
        printf("File %s already exists!\n",name);
        return;
    }

    //cazul pentru primul director, arborele de directoare este gol
    if (parent->head_children_dirs == NULL) {
        parent->head_children_dirs = alocHeadDir(parent,name);
        return;
    }

    //parcurg arborele de directoare
    Dir **temp = &(parent->head_children_dirs);
    while (*temp != NULL) {
        if (strcmp ((*temp)->name, name) == 0) {
            printf("Directory %s already exists!\n",name);
            return;
        }
        if (isGreater(name, (*temp)->name)) { // daca name e mai mare, merg dreapta
            temp = &(*temp)->right;
        }
        else {
            temp = &(*temp)->left; // altfel merg stanga
        }
    }
    *temp = alocHeadDir(parent, name); // am gasit locul in care creez directorul
}

/* Parcurgere inOrder / stanga vf dreapta pentru fisiere */
void inOrderForFile (File *file) {
    if (file == NULL)
        return;
    inOrderForFile(file->left);
    printf("%s ", file->name);
    inOrderForFile(file->right);
}

/* Parcurgere inOrder / stanga vf dreapta pentru directoare */
void inOrderForDir (Dir *parent) {
    if (parent == NULL)
        return;
    inOrderForDir(parent->left);
    printf("%s ", parent->name);
    inOrderForDir(parent->right);
}

/* Functie care afiseaza directoarele si fisierele din directorul curent */
void ls(Dir *parent) {

    inOrderForDir(parent->head_children_dirs);
    inOrderForFile(parent->head_children_files);
    printf("\n");
}

/* Functie care elimina un fisier din directorul curent */
File* rm (Dir *parent, char *name) {
    if (parent->head_children_files == NULL) { // daca arborele de fisiere e gol
                                              // nu am ce elimina, fisierul nu exista
        printf("File %s doesn't exist!\n", name);
        return parent->head_children_files;
    }
    File *temp = parent->head_children_files;
    File *prev = NULL;

    //parcurg arborele
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        if (isGreater(name, temp->name)) {
            temp = temp->right;
        }
        else {
            temp = temp->left;
        }
    }
    // daca e NULL, nu exista
    if (temp == NULL) {
        printf("File %s doesn't exist!\n", name);
        return parent->head_children_files;
    }
    //cazul in care exista cheia cautata
    //verific daca are doar copil stanga sau doar copil dreapta
    if (temp->left == NULL || temp->right == NULL) {
        File *newTemp;
        //vf daca are doar copil dreapta
        if (temp->left == NULL) {
            newTemp = temp->right;
        }
        else {
            //doar copil stanga
            newTemp = temp->left;
        }
        //daca elementul de eliminat este radacina
        if (prev == NULL) {
            free(temp->name);
            free(temp);
            return newTemp;
        }
        if (temp == prev->left) {
            prev->left = newTemp;
        }
        else {
            prev->right = newTemp;
        }
        free(temp->name);
        free(temp);
    }
    // caul in care are ambii fii, stang si drept
    else {
        File *p = NULL, *temp2;

        //succesor din parcurgere inordrer
        temp2 = temp->right;
        while (temp2->left != NULL) {
            p = temp2;
            temp2 = temp2->left;
        }
        //vf daca parintele succesorului
        //este elementul temp cu cheia cautata
        //daca nu, copilul stang va deveni
        //succesorul drept
        if (p != NULL) {
            p->left = temp2->right;
        }
        //altfel, fac nodul drept sa fie sters
        else {
            temp->right= temp2->right;
        }
        strcpy(temp->name, temp2->name);
        free(temp2->name);
        free(temp2);
    }
    return parent->head_children_files;
}

/* Functie care distruge recursiv un arbore de fisiere */
void destroyFileTree (File *file) {
    if (file == NULL) {
        return; //stop condition
    }
    destroyFileTree(file->left);
    destroyFileTree(file->right);
    free(file->name);
    free(file);
    file = NULL;
}

/* Functie care distruge recursiv un arbore de directoare */
void rmAll (Dir *parent) {
    if (parent == NULL) {
        return; //stop condition;
    }
    rmAll(parent->left);
    rmAll(parent->right);
    destroyFileTree(parent->head_children_files);
    free(parent->name);
    rmAll(parent->head_children_dirs);
    free(parent);

}
/* Functie care elimina un director, cu tot ce contine el */
Dir* rmDir (Dir *parent, char *name) {
    if (parent->head_children_dirs == NULL) { // daca arborele de directoare e gol, nu elimin
        printf("Directory %s doesn't exist!\n", name);
        return parent;
    }
    Dir *temp = parent->head_children_dirs;
    Dir *prev = NULL;

    //parcurg arborele
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        if (isGreater(name, temp->name)) {
            temp = temp->right;
        }
        else {
            temp = temp->left;
        }
    }
    //daca ajung pe NULL, nu exista directorul de eliminat
    if (temp == NULL) {
        printf("Directory %s doesn't exist!\n", name);
        return parent;
    }
    //cazul in care exista cheia cautata
    //verfic daca are doar copil stanga sau doar copil dreapta
    if (temp->left == NULL || temp->right == NULL) {
        Dir *newTemp;
        //vf daca are doar copil dreapta
        if (temp->left == NULL) {
            newTemp = temp->right;
        }
        else {
            //doar copil stanga
            newTemp = temp->left;
        }
        //daca elementul de eliminat este radacina
        if (prev == NULL) {
            rmAll(temp->head_children_dirs);
            destroyFileTree(temp->head_children_files);
            free(temp->name);
            free(temp);
            parent->head_children_dirs = newTemp;
            return parent;
        }
        else {
            if (temp == prev->left) {
                prev->left = newTemp;
            } else {
                prev->right = newTemp;
            }
        }
        rmAll(temp->head_children_dirs);
        destroyFileTree(temp->head_children_files);
        free(temp->name);
        free(temp);
    }
        //cazul in care are ambii fii, stanga si dreapta
    else {
        Dir *p = NULL, *temp2;

        //succesor din parcurgere inorder
        temp2 = temp->right;
        while (temp2->left != NULL) {
            p = temp2;
            temp2 = temp2->left;
        }
        //vf daca parintele succesorului
        //este elementul temp cu cheia cautata
        //daca nu, copilul stang va deveni
        //succesorul drept
        if (p != NULL) {
            p->left = temp2->right;
        }
            //altfel, fac nodul drept sa fie sters
        else {
            temp->right= temp2->right;
        }
        strcpy(temp->name, temp2->name);
        rmAll(temp2->head_children_dirs);
        destroyFileTree(temp2->head_children_files);
        free(temp2->name);
        free(temp2);
    }
    return parent;
}

/* Functie care muta utilizatorul din directorul corect in directorul name */
void cd(Dir **target, char *name) {
    if (strcmp (name, "..") == 0) { //verific daca merg inapoi
        if ((*target)->parent) { //daca ma pot intoarce, adica nu sunt pe root
            (*target) = (*target)->parent;
            return;
        }
        else
            return;
    }
    Dir *temp = (*target)->head_children_dirs;
    //parcurg arborele de directoare
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        if (isGreater(name, temp->name)) {
            temp = temp -> right;
        }
        else {
            temp = temp->left;
        }
    }
    //daca ajung pe null, nu exista directorul cautat
    if (temp == NULL) {
        printf("Directory not found!\n");
        return;
    }
    (*target)= temp; //am ajuns pe directorul cautat
}

/* Functie care arata calea de la root la directorul curent */
void pwd(Dir *current) {
    if (current->parent == NULL) {
        printf("/%s", current->name);
        return;
    }
    pwd(current->parent);
    printf("/%s", current->name);
}

/* Functie care cauta un fisier in toata ierarhia de directoare si fisiere */
void findFile (Dir *parent, char *name, bool *found) {
    if (parent == NULL || *found == true) { //conditie stop, apel recursiv
        return;
    }
    //daca gasesc fisierul in arborele curent de fisiere
    if (searchNameInFiles(parent->head_children_files, name) == true) {
        *found = true;
        printf("File %s found!\n", name);
        pwd(parent);
        printf("\n");
        return;
    }
    //caut in toata ierarhia de directoare
    findFile(parent->head_children_dirs, name, found);
    findFile(parent->left, name, found);
    findFile(parent->right, name, found);
}

/* Functie care cauta un director in toata ierarhia de directoare si fisiere */
void findDir (Dir *parent, char *name, bool *found) {
    if (parent == NULL || *found == true) { //conditie stop, apel recursiv
        return;
    }
    //daca gasesc directorul in arborele curent de directoare
    if (searchNameInDirs(parent->head_children_dirs, name)) {
        *found = true;
        printf("Directory %s found!\n", name);
        pwd(parent);
        printf("/%s\n", name);
        return;
    }
    //caut in toata ierarhia de directoare
    findDir(parent->head_children_dirs, name, found);
    findDir(parent->left, name, found);
    findDir(parent->right, name, found);
}

/* Functie care primeste ca parametru un tip de fisier
 * adica -d pentru director si -f pentru file, si il cauta */
void find (Dir *parent, char *type, char *name, bool *found) {
    if (strcmp(type, "-f") == 0) { // find the file
        findFile(parent, name, found);
    }
    if (strcmp(type, "-d") == 0) {
        findDir(parent, name, found);
    }
}