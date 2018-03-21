/*

    Zelda Oni Link Begins

    Copyright (C) 2006-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include "Listable.h"

Listable::Listable() : suivant(0), id(0) {
}

Listable::~Listable() {
    if (suivant) {
        delete suivant;
    }
    suivant = 0;
}

int Listable::size() {
    if (suivant == 0) return 0;
    return (suivant->size() + 1);
}
        
void Listable::ajout(Listable* l) {
    if (suivant == 0) {
        suivant = l;
        suivant->id = id + 1;
    }
    else suivant->ajout(l);
}

Listable* Listable::enleve(Listable* l) {
    if (suivant == 0) return 0;
    if (l == suivant) {
        Listable* tmp = suivant->suivant;
        suivant->suivant = 0; //pour éviter suppressions récursives
        Listable* ret = suivant;
        suivant = tmp;
        return ret;
    }
    return suivant->enleve(l);
}

void Listable::setSuivant(Listable* l) {
    suivant = l;
}

bool Listable::operator==(const Listable* l) {
    return (id == l->id);
}

int Listable::getListId() {return id;}
