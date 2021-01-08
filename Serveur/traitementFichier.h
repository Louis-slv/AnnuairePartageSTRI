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





//creer un fichier 'perm', 'mesContact.an'
int creerFichiersUtilisateur(char *numeroUtilisateur);


//LOUIS SALVAGNIAC
//Initilise un Utilisateur en mémoir
void initUser(Utilisateur *user);


//LOUIS SALVAGNIAC
//Libère l'espace mémoir de l'utilisateur 'user'
void freeUser(Utilisateur *user);



//SALVAGNIAC LOUIS
//Retourne 1 si l'identifiant est le mot de passe sont correct, sinon 0
int verifierConnexion(char *identifiant,char *mdp);

//SALVAGNIAC LOUIS
//Fabrique un utilisateur a partir des données d'une requête (chaine de caractère)
Utilisateur fabriquerUtilisateur(char *donnee);


//ALEXANDRE SALIOU
//Supprimer la ligne contenant les informations de l'utilisateur 
//Identifier par son numeroUtilisateur
int supprimerLigneFichierUser(int numeroUtilisateur);


////////A TOI DE COMMENTER CA/////////

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
