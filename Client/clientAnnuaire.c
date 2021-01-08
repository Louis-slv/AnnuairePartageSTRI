#include "clientAnnuaire.h"

const size_t TAILLE_MAX = 150;


char* traiterReponse(char *reponseStr){
    
	const char *separateur = "\r\n";
    Ligne reponse[15];
    
    char *ligne = strtok(reponseStr,separateur);
    unsigned int i = 0; //représente le nombre de ligne de la requete
    
    while(ligne != NULL){
        reponse[i] = traiterLigneReponse(ligne);
        ligne = strtok(NULL,separateur);
        //printf("%s:%s\n",reponse[i].libelle,reponse[i].donnee);
        i++;
    }

    if(chercherDonnee(reponse,i,"Message") != NULL){
        printf("%s\n",chercherDonnee(reponse,i,"Message"));
    } 

    return reponse[0].donnee; //retourne le codeErreur

    
    //traiterEtat1(requete);
    
    //free(requete);

}


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


char* chercherDonnee(Ligne reponse[],unsigned int tailleRep,const char *libelle){

    for(int i = 0 ; i < tailleRep ; i++){
        if(strcmp(reponse[i].libelle,libelle) == 0){
            return reponse[i].donnee;  
       }
    }

	return NULL;
}


int envoyerRequete(char *methode, char* codeEtat,char *donnee){
    char *requete = (char *) calloc(sizeof(char),TAILLE_MAX);

    strcat(requete,methode);
    strcat(requete,":");
    strcat(requete,codeEtat);
    strcat(requete,"\r\n");//Fin de ligne
    if(donnee != NULL && donnee != ""){

        strcat(requete,"Data-lenght:");
        char *dataLenght = (char *) calloc(TAILLE_MAX,sizeof(char));
	    sprintf(dataLenght,"%ld",strlen(donnee));
        strcat(requete, dataLenght);
        free(dataLenght);
        strcat(requete,"\r\n");//Fin de ligne

        strcat(requete,"Data:");
        strcat(requete,donnee);
        strcat(requete,"\r\n");//Fin de ligne
    }
    
    strcat(requete,"\r\n");//Fin de requête

    printf("Emission:\n%s", requete);
    
    if(Emission(requete)!=1) {
        printf("Erreur d'emission");
        return 1;
    }

    free(requete);

}


char* entrerDonnee(char* message,char caractereFin){
    char *donnee = (char *) calloc(sizeof(char),100);
    printf("%s", message);
    scanf("%s",donnee);
    if (caractereFin != NULL){
        donnee[strlen(donnee)] = caractereFin;
    }else{
        donnee[strlen(donnee)] = '\0';
    }

    return donnee;
}


int ajouterUtilsateur(){

    char *donnee = (char *) calloc(sizeof(char),400);

    char *courant = entrerDonnee("Prenom :",' ');
    strcat(donnee,courant);
    free(courant);

    courant = entrerDonnee("Nom :",' ');
    strcat(donnee,courant);
    free(courant);

    courant = entrerDonnee("Email :",' ');
    strcat(donnee,courant);
    free(courant);

    courant = entrerDonnee("Tel :",' ');
    strcat(donnee,courant);
    free(courant);

    courant = entrerDonnee("Identifiant :",' ');
    strcat(donnee,courant);
    free(courant);

    courant = entrerDonnee("Mot de passe :",' ');
    strcat(donnee,courant);
    free(courant);

    envoyerRequete("GODATA","31",donnee);

    system("clear");

    free(donnee);

}


int supprimerUtilisateur(){
    
    char *numUser = entrerDonnee("Entrez le numero de l'utilisateur : ",NULL);
    envoyerRequete("GODATA","32",numUser);

    free(numUser);
}



int modifierUtilisateur(){

    char *donnee = (char *) calloc(sizeof(char),400);

    char *courant = entrerDonnee("Entrez le numero de l'utilisateur : ",' ');
    strcat(donnee,courant);
    free(courant);


    courant = entrerDonnee("Prenom :",' ');
    strcat(donnee,courant);
    free(courant);

    courant = entrerDonnee("Nom :",' ');
    strcat(donnee,courant);
    free(courant);

    courant = entrerDonnee("Email :",' ');
    strcat(donnee,courant);
    free(courant);

    courant = entrerDonnee("Tel :",' ');
    strcat(donnee,courant);
    free(courant);

    courant = entrerDonnee("Identifiant :",' ');
    strcat(donnee,courant);
    free(courant);

    courant = entrerDonnee("Mot de passe :",NULL);
    strcat(donnee,courant);
    free(courant);

    envoyerRequete("GODATA","33",donnee);

}