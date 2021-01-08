#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <regex.h>
#include "serveur.h"
#include "serveurAnnuaire.h"

const size_t TAILLE_REQUETE = 150;


int main() {
	
	char *message = NULL;
	char *requete = NULL;


	Initialisation();

	while(1) {

		int fini = 0;
		AttenteClient();
		requete =  (char *) calloc(TAILLE_REQUETE,sizeof(char));
		etatCourant = (char *) calloc(5,sizeof(char));
		while(!fini) {
			message = Reception();
			int compte = 0;
			if(message != NULL) {

				
				//printf("%s\n", message);

				if(strlen(requete)+strlen(message) > strlen(requete)){
					requete = realloc(requete,strlen(requete) + TAILLE_REQUETE);
				}
				
				strcat(requete,message);

				
				//Si c'est la fin de la requete 
				if(message[strlen(message)-1] == '\n' &&
					message[strlen(message)-2] == '\r' && 
					strlen(message) == 2){
					
					traiterRequete(requete);
					free(requete);
				}

				free(message);

			} else {
				fini = 1;
			}

		}

		free(requete);
		TerminaisonClient();
	}

	return 0;

}


