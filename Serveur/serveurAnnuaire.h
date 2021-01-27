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

//Etat dans lequel se trouve le serveur
char *etatCourant;

//Booleen pour savoir si l'utilisteur est identifier ou non
int estIdentifier;

//LOUIS SALVAGNIAC
//Effectue le traitement en fonction de la requête envoyé
int traiterRequete(char *requete);


//LOUIS SALVAGNIAC
//Transforme une ligne de requete en strcuture Ligne
Ligne traiterLigneRequete(char *ligneStr);

//LOUIS SALVAGNIAC
//Recherche une donnee dans la requete à un champ dans certain libelle
char* chercherDonnee(Ligne requete[],unsigned int taille,const char *libelle);

//LOUIS SALVAGNIAC
//Recupere le codeEtat dans la requete
char* getEtat(Ligne requete[]);


//LOUIS SALVAGNIAC
//Recupere la methode de la requete
char* getMethode(Ligne requete[]);


//LOUIS SALVAGNIAC
//Envoi d'une reponse client 
int envoyerReponse(char *etat, char* codeErreur,char *donnee,char *message);


//LOUIS SALVAGNIAC
//Traitement de l'état 1 : 'Acceuil'
int traiterEtat1(Ligne requete[]);


//LOUIS SALVAGNIAC
//Traitement de l'état 2 (utilisateur) et 3 (admin) : 'Menu d'action'
//Pour rentrer dans ces état il faut que l'utilisateur est rentré un id et 
//mot de passe valide
int traiterEtat2et3(Ligne requete[],unsigned int taille);


//LOUIS SALVAGNIAC
//Traitement de l'état 31 : 'Ajout utilisateur'
int traiterEtat31(Ligne requete[],unsigned int taille);


//LOUIS SALVAGNIAC
//Traitement de l'état 31 : 'Supprimer utilisateur'
int traiterEtat32(Ligne requete[],unsigned int taille);


//LOUIS SALVAGNIAC
//Traitement de l'état 31 : 'Modifier utilisateur'
int traiterEtat33(Ligne requete[],unsigned int taille);

#endif
