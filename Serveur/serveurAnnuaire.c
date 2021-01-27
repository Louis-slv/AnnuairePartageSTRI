
#include "serveurAnnuaire.h"
#include "traitementFichier.h"

const size_t TAILLE_MAX = 150;

int traiterRequete(char *requeteStr){
    
	const char *separateur = "\r\n";
    Ligne requete[15];
    
    char *ligne = strtok(requeteStr,separateur);
    unsigned int i = 0; //représente le nombre de ligne de la requete
    

    //Transforme chaque ligne en strcture Ligne
    while(ligne != NULL){
        requete[i] = traiterLigneRequete(ligne);
        ligne = strtok(NULL,separateur);
        printf("%s:%s\n",requete[i].libelle,requete[i].donnee);
        i++;
    }

    //Choisi le traitement adéquat en fonction du codeEtat de la requete
    if(strcmp(getEtat(requete),"1") == 0){
        traiterEtat1(requete);
    }else if(strcmp(getEtat(requete),"2") == 0 || strcmp(getEtat(requete),"3") == 0){
        traiterEtat2et3(requete,i);
    }else if(strcmp(getEtat(requete),"31") == 0 ){
        traiterEtat31(requete,i);
    }else if(strcmp(getEtat(requete),"32") == 0 ){
        traiterEtat32(requete,i);
    }else if(strcmp(getEtat(requete),"33") == 0 ){
        traiterEtat33(requete,i);
    }


}


Ligne traiterLigneRequete(char *ligneStr){
    
    int parti = 0;
    int i = 0;

    //Création d'une nouvelle strcture ligne
    Ligne ligne;   
    ligne.libelle = (char *) calloc(TAILLE_MAX,sizeof(char));
    ligne.donnee = (char *) calloc(1000,sizeof(char));

    //Pour chaque caractère de la ligne...
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

    //Pour chaque ligne de la requete...
    for(int i = 0 ; i < taille ; i++){
        if(strcmp(requete[i].libelle,libelle) == 0){
            
            return requete[i].donnee;  //Renvoi la donnée correspondante
       }
    }

	return NULL;
}


char* getEtat(Ligne requete[]){
    return requete[0].donnee;
}


char* getMethode(Ligne requete[]){
    return requete[0].libelle;
}


int envoyerReponse(char *etat, char* codeErreur,char *donnee,char *message){

    char *reponse = (char *) calloc(sizeof(char),TAILLE_MAX);


    //AJout des différents champs de la réponse
    strcat(reponse,etat);
    strcat(reponse,":");
    strcat(reponse,codeErreur);
    strcat(reponse,"\r\n");//Fin de ligne

    if(message != NULL && message != ""){

        strcat(reponse,"Message:");
  
        strcat(reponse,message);
        strcat(reponse,"\r\n");//Fin de ligne
    }

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
    
    //Envoi de la réponse
    if(Emission(reponse)!=1) {
        printf("Erreur d'emission");
        return 1;
    }

}


//Etat dans lequel on s'authentifie
int traiterEtat1(Ligne requete[]){

    //Vérifier si un utilisateur n'est pas déjà log
	envoyerReponse("1","200",NULL,"Connectez-vous");
    
}


//Etat d'accès à l'affichage des menu, il faut un login et mdp correct soit  en admin(3) soit en user normale (2)
int traiterEtat2et3(Ligne requete[],unsigned int taille){

    if(strcmp(getMethode(requete),"GODATA") != 0){
        envoyerReponse(getEtat(requete),"300",NULL,"Acces refuse");
    }else{
        
        //Recupération de l'id et du mdp dans la requete
        char *id = strtok(chercherDonnee(requete,taille,"Data")," ");
        char *mdp = strtok(NULL," ");

        //Vérification des infos d'authentification et envoi de la réponse avec le menus correspondant
        if(verifierConnexion(id,mdp) == 0){
            if(strcmp(id,"admin") == 0){
                envoyerReponse("3","101",NULL,"31 -> AJouter | 32 -> Supprimer | 33 -> Modifier | 1 -> Deconnexion");
            }else{
                envoyerReponse("2","100",NULL,"21 -> Mon annuaire | 22 -> Mes infos | 23 -> Mes Annuaire | 1 -> Deconnexion");
            }
            
            
        }else{
            envoyerReponse(getEtat(requete),"102",NULL,"Idenfiant ou mot de passe incorrect !");
        }
    }
    
}


//Etat d'ajout d'un utilisateur par l'admin
int traiterEtat31(Ligne requete[],unsigned int taille){

    if(strcmp(getMethode(requete),"GODATA") == 0){

        char *donnee = chercherDonnee(requete,taille,"Data");


        //AJout du nouveau user dans le fichier
        int numUtil =  ajouterLigneFichierUser(fabriquerUtilisateur(donnee,0));  
        char *numUtilStr = (char *) calloc(10,sizeof(char));
	    sprintf(numUtilStr,"%d",numUtil);


        //Creation du dossier du nouveau user
        creerFichiersUtilisateur(numUtilStr);
        envoyerReponse("31","200",NULL,"Utilisateur correctement ajouter");

    }else{
        
     
    }
}




int traiterEtat32(Ligne requete[],unsigned int taille){

    //Si la methode est GODATA
    if(strcmp(getMethode(requete),"GODATA") == 0){


        char *donnee = chercherDonnee(requete,taille,"Data");

        //On supprime le user dans le fichier utilisateur et aussi ses différents dossier
        supprimerLigneFichierUser(atoi(donnee));
        supprimerDossierUtilisateur(donnee);


        envoyerReponse("31","200",NULL,"Utilisateur correctement supprimer");

    }else{
        
     
    }
}




int traiterEtat33(Ligne requete[],unsigned int taille){


    //Si la methode est GODATA   
    if(strcmp(getMethode(requete),"GODATA") == 0){

        //Modification de l'utilisateur dans le fichier
        char *donnee = chercherDonnee(requete,taille,"Data");   
        modifierUtilisateur(fabriquerUtilisateur(donnee,1));
        envoyerReponse("31","200",NULL,"Utilisateur correctement modifier");

    }else{
        
     
    }
}