#ifndef __TRAITEMENTF_H__
#define __TRAITEMENTF_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Utilisateur Utilisateur;
struct Utilisateur
{
    char *nom;
    char *prenom;
    char *email;
    char *tel;
    char *identifiant;
    char *mdp;
    int numeroUtilisateur;
};

#include "traitementFichier.h"




////CREATION
int ajouterUtilisateur(Utilisateur nouveau);

int creerDossierUtilisateur(char *numeroUtilisateur);

//creer un fichier 'perm', 'mesContact.an'
int creerFichiersUtilisateur(char *numeroUtilisateur);

void initUser(Utilisateur *user);



void freeUser(Utilisateur *user);

//SALVAGNIAC LOUIS
int verifierConnexion(char *identifiant,char *mdp);

//SALVAGNIAC LOUIS
Utilisateur fabriquerUtilisateur(char *donnee);

int estMDPExistant(char *identifiant);

int supprimerUtilisateur(char *identifiant);

int supprimerLigneFichierUser(int numeroUtilisateur);

int chercherUtilisateur(char *numeroUtilisateur);


//ALEXANDRE SALIOU
int ajouterLigneFichierUser(Utilisateur nouveau);


//ALEXANDRE SALIOU
int supprimerLigneFichierUser(int numeroUtilisateur);


//ALEXANDRE SALIOU
int supprimerDossierUtilisateur(char *numeroUtilisateur);


//ALEXANDRE SALIOU
int creerFichiersUtilisateur(char *numeroUtilisateur);


//ALEXANDRE SALIOU
int ajouterLigneFichierUser(Utilisateur nouveau);

#endif
