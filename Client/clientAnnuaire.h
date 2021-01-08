#ifndef __CLIENTANNUAIRE_H__
#define __CLIENTANNUAIRE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"





typedef struct Ligne Ligne;
struct Ligne
{
    char *libelle;
    char *donnee;
};


char* traiterReponse(char *reponse);


Ligne traiterLigneReponse(char *ligneStr);


char* chercherDonnee(Ligne *reponse,unsigned int tailleRep,const char *libelle);


int envoyerRequete(char *methode, char* codeEtat,char *donnee);

int ajouterUtilsateur();

int supprimerUtilisateur();

char* entrerDonnee(char* message);

#endif