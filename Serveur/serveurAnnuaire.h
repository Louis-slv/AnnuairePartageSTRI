#ifndef __SERVEURANNUAIRE_H__
#define __SERVEURANNUAIRE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serveur.h"



typedef struct Ligne Ligne;
struct Ligne
{
    char *libelle;
    char *donnee;
};

char *etatCourant;

int estIdentifier;

//LOUIS SALVAGNIAC
//Effectue le traitement en fonction de la requête envoyé
int traiterRequete(char *requete);

Ligne traiterLigneRequete(char *ligneStr);

char* chercherDonnee(Ligne requete[],unsigned int taille,const char *libelle);

char* getEtat(Ligne requete[]);

char* getMethode(Ligne requete[]);

int envoyerReponse(char *etat, char* codeErreur,char *donnee,char *message);

int traiterEtat1(Ligne requete[]);

int traiterEtat2et3(Ligne requete[],unsigned int taille);

int traiterEtat31(Ligne requete[],unsigned int taille);

int traiterEtat32(Ligne requete[],unsigned int taille);


#endif
