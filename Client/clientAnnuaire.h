#ifndef __CLIENTANNUAIRE_H__
#define __CLIENTANNUAIRE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"




//Strcuture de donnees représentant une ligne de la requete
typedef struct Ligne Ligne;
struct Ligne
{
    char *libelle;
    char *donnee;
};



//LOUIS SALVAGNIAC
//Permet de traiter une réponse du serveur
char* traiterReponse(char *reponse);


//LOUIS SALVAGNIAC
//Permet recuperer chaque champ d'une ligne de ma requete dans une
//strcture de donnée Ligne 
Ligne traiterLigneReponse(char *ligneStr);


//LOUIS SALVAGNIAC
//Permet de cherhcher une donnee en particulier dans une reponse
//a partir du libelle de la ligne contenant cette donnee
char* chercherDonnee(Ligne *reponse,unsigned int tailleRep,const char *libelle);


//LOUIS SALVAGNIAC
//Permet d'envoyer un requête au serveur avec une certaine methode et pour un état codeEtat
//En transmettant des donnees
int envoyerRequete(char *methode, char* codeEtat,char *donnee);



//LOUIS SALVAGNIAC
//Fournis l'interface de saisie d'un nouvelle utlisateurs et envoi la requete correspondante
int ajouterUtilsateur();


//LOUIS SALVAGNIAC
//Fournis l'interface de supression d'un utilisateur et envoi la requete correspondante
int supprimerUtilisateur();


//LOUIS SALVAGNIAC
//Fournis l'interface de modification d'un utilisateur et envoi la requete correspondante
int modifierUtilisateur();

//LOUIS SALVAGNIAC
//Permet la saisie d'une chaine de caractere et positionne le caractereFin a la fin de cette chaine 
//Elle affiche un message d'information avant la saisie
char* entrerDonnee(char* message,char caractereFin);

#endif