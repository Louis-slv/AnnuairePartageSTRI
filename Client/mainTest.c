#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "client.h"



const size_t TAILLE_MAX = 150;

//Strcuture de donnees représentant une ligne de la requete
typedef struct Ligne Ligne;
struct Ligne
{
    char *libelle;
    char *donnee;
};


int envoyerRequete(char *methode, char* codeEtat,char *donnee);
int traiterReponse(char *requete);
Ligne traiterLigneReponse(char *ligneStr);
char* chercherDonnee(Ligne *requete,unsigned int tailleReq,const char *libelle);
int traiterEtat1(Ligne requete[]);
int envoyerReponse(char *etat, char* codeErreur,char *donnee);


int main() {

    
}

//LOUIS SALVAGNIAC
//Permet d'envoyer un requête au serveur avec une certaine methode et pour un état codeEtat
//En transmettant des donnees
int envoyerRequete(char *methode, char* codeEtat,char *donnee){
    char *requete = (char *) calloc(sizeof(char),TAILLE_MAX);

    strcat(requete,methode);
    strcat(requete," ");
    strcat(requete,codeEtat);
    strcat(requete,"\r\n");//Fin de ligne
    if(donnee != NULL && donnee != ""){

        strcat(requete,"Data-lenght : ");
        char *dataLenght = (char *) calloc(TAILLE_MAX,sizeof(char));
	    sprintf(dataLenght,"%ld",strlen(donnee));
        strcat(requete, dataLenght);
        free(dataLenght);
        strcat(requete,"\r\n");//Fin de ligne

        strcat(requete,"Data : ");
        strcat(requete,donnee);
        strcat(requete,"\r\n");//Fin de ligne
    }
    
    strcat(requete,"\r\n");//Fin de requête

    printf("Emission : %s", requete);
    /*
    if(Emission(requete)!=1) {
        printf("Erreur d'emission");
        return 1;
    }
    */
    free(requete);
}



//LOUIS SALVAGNIAC
//Permet de traiter une réponse du serveur
int traiterReponse(char *requeteStr){
    
	const char *separateur = "\r\n";
    Ligne requete[15];
    
    char *ligne = strtok(requeteStr,separateur);
    unsigned int i = 0; //représente le nombre de ligne de la requete
    
    while(ligne != NULL){
        requete[i] = traiterLigneReponse(ligne);
        ligne = strtok(NULL,separateur);
        printf("%s:%s\n",requete[i].libelle,requete[i].donnee);
        i++;
    }

    printf("%s\n",chercherDonnee(requete,i,"GO"));
    //traiterEtat1(requete);
    
    //free(requete);

}



//LOUIS SALVAGNIAC
//Permet recuperer chaque champ d'une ligne de ma requete dans une
//strcture de donnée Ligne 
Ligne traiterLigneReponse(char *ligneStr){
    
    int parti = 0;
    int i = 0;
    Ligne ligne;
    
    ligne.libelle = (char *) calloc(TAILLE_MAX,sizeof(char));
    ligne.donnee = (char *) calloc(1000,sizeof(char));

    for(i ; i < strlen(ligneStr) ; i++){

        //Passage du libelle aux donnees
        if(ligneStr[i] == ':'){
            parti = 1;
            i++;
        }
        
        //Libelle de la ligne 
        if(parti == 0){
            ligne.libelle[strlen(ligne.libelle)] = ligneStr[i];
        }

        //Donnees de la lignes
        if(parti == 1){
            ligne.donnee[strlen(ligne.donnee)] = ligneStr[i];
        }
        
        
    }

    return ligne;
    
}




char* chercherDonnee(Ligne requete[],unsigned int taille,const char *libelle){


    for(int i = 0 ; i < taille ; i++){
        if(strcmp(requete[i].libelle,libelle) == 0){
            return requete[i].donnee;  
       }
    }

	return NULL;
}

int traiterEtat1(Ligne requete[]){

	envoyerReponse("1","200","Connectez-vous");
    
}


int envoyerReponse(char *etat, char* codeErreur,char *donnee){
    char *reponse = (char *) calloc(sizeof(char),TAILLE_MAX);

    strcat(reponse,etat);
    strcat(reponse,":");
    strcat(reponse,codeErreur);
    strcat(reponse,"\r\n");//Fin de ligne

    if(donnee != NULL && donnee != ""){

        strcat(reponse,"Data-lenght:");
        char *dataLenght = (char *) calloc(TAILLE_MAX,sizeof(char));
	    sprintf(dataLenght,"%ld",strlen(donnee));
        strcat(reponse, dataLenght);
        free(dataLenght);
        strcat(reponse,"\r\n");//Fin de ligne

        strcat(reponse,"Data:");
        strcat(reponse,donnee);
        strcat(reponse,"\r\n");//Fin de ligne
    }
    
    strcat(reponse,"\r\n");//Fin de requête

    printf("Emission:\n%s", reponse);
    
    /*
    if(Emission(reponse)!=1) {
        printf("Erreur d'emission");
        return 1;
    }*/

}