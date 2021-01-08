#include "traitementFichier.h"
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <strings.h>
#include <string.h>




//aller a une ligne précise
int ajouterNbUserALaLigneX(FILE *test, char *ligne, int nbDeLaLigne){
}
/*
    int i = 0;
    char caractere;
    do
    {
        caractere = fgetc(utilisateur);
        if (caractere = '\n')
            i++;
     } while (i != NbLigne);
    fgets(ligne, 30, utilisateur);
}
*/



////CREATION
//création d'un nouvel utilisateur (une ligne en +) dans le fichier utilisateur 
int ajouterUtilisateur(Utilisateur nouveau){
    printf("%s\n",nouveau.nom);
}

//crée le dossier utilisateur 
int creerDossierUtilisateur(char *numeroUtilisateur){

}


//lors d'un ajout d'un nouvel utilisateur cette fonction servira 
//a sauter une ligne et d'ajouter le numéro de la ligne
int ajouterLigneFichierUser(Utilisateur nouveau){
 
    FILE *utilisateur = fopen("utilisateur","r+"); // ouverture du fichier
    int numeroUser =0;
    int numeroMaxUser =0;
    char ligne[100] = "";
    //boucle qui annonce si l'ouverture s'est mal faite
    if(utilisateur == NULL){ 
       printf("le fichier ne  s'est pas ouvert\n");
        exit(1);
    }
    // Sinon qui permet de travailler sur le programme
    else if (utilisateur != NULL)
    {
        // On peut lire et écrire dans le fichier
        // boucle permettant de recuperer les numeros d'utilisateurs
        while(fgets(ligne,100,utilisateur) != NULL){
            sscanf(ligne,"%d",&numeroUser);
            if(numeroMaxUser < numeroUser){ // on regarde quel est le numero le plus grand peut importe son en droit dans le fichier
                numeroMaxUser = numeroUser;
            }
        }
        fseek(utilisateur, 0, SEEK_END); // on se met à la fin du fichier
        fprintf(utilisateur,"\n%d %s %s %s %s %s %s",numeroMaxUser+1,nouveau.prenom,
                                                                nouveau.nom, 
                                                                nouveau.email, 
                                                                nouveau.tel,
                                                                nouveau.identifiant,
                                                                nouveau.mdp); 
        
        
    }
    fclose(utilisateur); // on ferme le fichier


}


//creer un fichier 'perm', 'mesContact.an'
int creerFichiersUtilisateur(char *numeroUtilisateur){
    char path[100] ="";
    char path2[100] = "";
    char path3[100] ="";
    strcat(path,"./");
    strcat(path,numeroUtilisateur);
    printf("path : %s\n",path);
    mkdir(path,0777);

    strcat(path2,path);
    strcat(path2,"/mesContact.an");
    printf("path2 : %s\n",path2);
    FILE *mesContact = fopen(path2,"w");

    strcat(path3,path);
    strcat(path3,"/perm.an");
    printf("path3 : %s\n",path3);
    FILE *perm = fopen(path3,"w");
}


int estIdentifiantExistant(char *identifiant){

}

int supprimerUtilisateur(char *identifiant){

}


int supprimerLigneFichierUser(int numeroUtilisateur){
    int numeroCourant =0;
    FILE *utilisateur = fopen("utilisateur","r+"); // ouverture du fichier
    char *contenuFichier = (char *) calloc(sizeof(char), 100);
    char ligne[150] = "";
    //boucle qui annonce si l'ouverture s'est mal faite
    if(utilisateur == NULL){ 
       printf("le fichier ne  s'est pas ouvert\n");
        exit(1);
    }
    // Sinon qui permet de travailler sur le programme
    else if (utilisateur != NULL)
    {
        // On peut lire et écrire dans le fichier
        // boucle permettant de recuperer les numeros d'utilisateurs
        while(fgets(ligne,100,utilisateur) != NULL){
            sscanf(ligne,"%d",&numeroCourant);
            //printf("%s",ligne);
            if (numeroCourant != numeroUtilisateur){
                //copiage des la ligne dans
                if(strlen(contenuFichier)+strlen(ligne) > strlen(contenuFichier)){
                    contenuFichier = realloc(contenuFichier,strlen(contenuFichier) + 200);
                }
                strcat(contenuFichier,ligne);
            }
            
        //fseek(utilisateur, 0, SEEK_END); // on se met à la fin du fichier
        }
        fclose(utilisateur);
    }
    // recopiage du nouveau tenumeroUtilisateurte sans la ligne supprimée
    utilisateur = fopen("utilisateur","w+"); // ouverture du fichier
    //boucle qui annonce si l'ouverture s'est mal faite
    if(utilisateur == NULL){ 
       printf("le fichier ne  s'est pas ouvert\n");
        exit(1);
    }
    // Sinon qui permet de travailler sur le programme
    else if (utilisateur != NULL)
    {
        // On peut lire et écrire dans le fichier
        // boucle permettant de recuperer les numeros d'utilisateurs
        fputs(contenuFichier,utilisateur);
        fclose(utilisateur);
    }
}


int chercherUtilisateur(char *numeroUtilisateur){

}
void initUser(Utilisateur *user){
    user->prenom = (char *) calloc(sizeof(char),50);
    user->nom = (char *) calloc(sizeof(char),50);
    user->tel = (char *) calloc(sizeof(char),50);
    user->email = (char *) calloc(sizeof(char),50);
    user->mdp = (char *) calloc(sizeof(char),50);
    user->identifiant = (char *) calloc(sizeof(char),50);
    user->numeroUtilisateur = 0;
}

int verifierConnexion(char *identifiant,char *mdp){

    FILE *utilisateur = fopen("utilisateur","r"); // ouverture du fichier
    char ligne[200];
    //boucle qui annonce si l'ouverture s'est mal faite
    if(utilisateur == NULL){ 
       printf("Le fichier utilsiateur ne s'est pas ouvert\n");
    }


    // Sinon qui permet de travailler sur le programme
    else if (utilisateur != NULL)
    {
        // On peut lire et écrire dans le fichier
        // boucle permettant de recuperer les numeros d'utilisateurs
        while(fgets(ligne,200,utilisateur) != NULL){
            Utilisateur courant;
            initUser(&courant);
            sscanf(ligne,"%d %s %s %s %s %s %s",&courant.numeroUtilisateur,
                                                courant.prenom,
                                                courant.nom, 
                                                courant.email, 
                                                courant.tel,
                                                courant.identifiant,
                                                courant.mdp);

            if(strcmp(courant.identifiant,identifiant) == 0 ){
                if(strcmp(courant.mdp,mdp) == 0){
                    return 0;
                }
            }


            return 1;
        }


        fclose(utilisateur); 
    }



}