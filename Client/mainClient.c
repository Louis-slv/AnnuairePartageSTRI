#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "client.h"
#include "clientAnnuaire.h"


int main() {

	char *message;

	//Etablissement d'une connection TCP au serveur d'adresse 'host' et sur son port 'port'
	if(InitialisationAvecService("localhost","13214") != 1) {
		printf("Erreur d'initialisation\n");
		return 1;
	}


	envoyerRequete("GO","1",NULL);

	char *codeErreur = (char *) malloc(sizeof(char)*3);

	message = Reception();
	if(message != NULL) {
		//printf("J'ai recu: %s\n", message);
		codeErreur = traiterReponse(message);
		printf("%s\n",codeErreur);
		free(message);
	} else {
		printf("Erreur de reception\n");
		return 1;
	}

	//Tant que la connexion n'est pas valide
	int deconnexion = 0;
	while(deconnexion == 0){

		//Authentification
		while(strcmp(codeErreur,"100") != 0 && strcmp(codeErreur,"101") != 0){

			char *donnee = (char *) calloc(sizeof(char),201);
			char *id =  (char *) malloc(sizeof(char)*100);
			char *mdp =  (char *) malloc(sizeof(char)*100);

			//Saisie id et mdp
			printf("Identifiant :");		
			scanf("%s", id);
			printf("Mot de passe :");
			scanf("%s", mdp);

			strcat(donnee,id);
			strcat(donnee," ");
			strcat(donnee,mdp);

			free(mdp);
			free(id);
			envoyerRequete("GODATA","2",donnee);

			free(donnee);

			message = Reception();
			if(message != NULL) {
				//printf("J'ai recu: %s\n", message);
				system("clear");
				codeErreur = traiterReponse(message);
				printf("%s\n",codeErreur);
				free(message);
			} else {
				printf("Erreur de reception\n");
				return 1;
			}		
		}
		

		//Action de l'utilisateur
		if(strcmp(codeErreur,"101") == 0){
			char choix[50];
			printf("Entrez votre choix :");
			scanf("%s",choix);	
			if(strcmp(choix,"31") == 0){
				ajouterUtilsateur();		
			}else if(strcmp(choix,"32") == 0){
				supprimerUtilisateur();
			}else if(strcmp(choix,"33") == 0){
				modifierUtilisateur();
			}else{
				printf("Ce choix n'existe pas !");
			}
			//free(choix);
		}else if(strcmp(codeErreur,"100") == 0){
			//traiter les fonction d'un user normale
		}

		message = Reception();
		if(message != NULL) {
			//printf("J'ai recu: %s\n", message);
			codeErreur = traiterReponse(message);
			printf("%s\n",codeErreur);
			free(message);
		} else {
			printf("Erreur de reception\n");
			return 1;
		}	

	}
	
	

	//Fermeture de la connection avec le serveur 
	Terminaison();

	return 0;
}




