#include "traitementFichier.h"



//SALVAGNIAC LOUIS
void initUser(Utilisateur *user){
    user->prenom = (char *) calloc(sizeof(char),50);
    user->nom = (char *) calloc(sizeof(char),50);
    user->tel = (char *) calloc(sizeof(char),50);
    user->email = (char *) calloc(sizeof(char),50);
    user->mdp = (char *) calloc(sizeof(char),50);
    user->identifiant = (char *) calloc(sizeof(char),50);
    user->numeroUtilisateur = 0;
}

//SALVAGNIAC LOUIS
void freeUser(Utilisateur *user){
    free(user->prenom);
    free(user->nom);
    free(user->tel);
    free(user->email);
    free(user->mdp);
    free(user->identifiant);
    user->numeroUtilisateur = 0;
}

//SALVAGNIAC LOUIS
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
        Utilisateur courant;
        while(fgets(ligne,200,utilisateur) != NULL){
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
            freeUser(&courant);
        }


        return 1;
       

        fclose(utilisateur); 
    }
    


}


//ALEXANDRE SALIOU
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
        contenuFichier[strlen(contenuFichier)-1] = '\0';
        fputs(contenuFichier,utilisateur);
        fclose(utilisateur);
    }
}


//ALEXANDRE SALIOU
int creerFichiersUtilisateur(char *numeroUtilisateur){
   
    char path[100] ="";
    char path2[100] = "";
    char path3[100] ="";
    strcat(path,"./");
    strcat(path,numeroUtilisateur);
    mkdir(path,0777);

    strcat(path2,path);
    strcat(path2,"/mesContact.an");

    FILE *mesContact = fopen(path2,"w");

    strcat(path3,path);
    strcat(path3,"/perm.an");
    FILE *perm = fopen(path3,"w");
}

int supprimerDossierUtilisateur(char *numeroUtilisateur){
  //  char *numeroUtilisateur = identifiant;
    char commande[20]= "";
    strcat(commande, "rm -r ");
    strcat(commande, numeroUtilisateur);
    printf("%s",commande);
    system(commande);

}

//SALVAGNIAC LOUIS
//Fabrique un utilisateur a partir des données d'une requête
Utilisateur fabriquerUtilisateur(char *donnee,int withNumUser){

    Utilisateur user;
    initUser(&user);
    if(withNumUser == 1){
        user.numeroUtilisateur = atoi(strtok(donnee," "));
        user.prenom = strtok(NULL," ");
        user.nom = strtok(NULL," ");
        user.email = strtok(NULL," ");
        user.tel = strtok(NULL," ");
        user.identifiant = strtok(NULL," ");
        user.mdp = strtok(NULL," ");
    }else{
        user.prenom = strtok(donnee," ");
        user.nom = strtok(NULL," ");
        user.email = strtok(NULL," ");
        user.tel = strtok(NULL," ");
        user.identifiant = strtok(NULL," ");
        user.mdp = strtok(NULL," ");
    }

    return user;

}


//ALEXANDRE SALIOU
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
        
        fclose(utilisateur); // on ferme le fichier
        return numeroMaxUser+1; //On retourne le numéro d'utlisateur
    }
    

}


//ALEXANDRE SALIOU
int modifierUtilisateur(Utilisateur modifier){

    int numeroCourant =0; // on déclare un entier qui nous servira par la suite 
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
        while(fgets(ligne,100,utilisateur) != NULL){ //boucle qui s'execute tant qu'on est pas a la fin du programme
            sscanf(ligne,"%d",&numeroCourant); // on fait un scanf mais avec la chaine de caractère "ligne" qui se mettra dans l'adresse de numeroCourant

            // boucle ou on rentre dedans quand on est dans la ligne à modifier
            if (numeroCourant != modifier.numeroUtilisateur){
                
                if(strlen(contenuFichier)+strlen(ligne) > strlen(contenuFichier)){// petite boucle qui augmente la taille du tampon des information quand la taille est depassé par les informations

                    contenuFichier = realloc(contenuFichier,strlen(contenuFichier) + 200); // on augmente la taille du contenuFichier qui est la variable tampon
                }
                strcat(contenuFichier,ligne); // on concatène la ligne dans la variable tampon
            }
            
        //fseek(utilisateur, 0, SEEK_END); // on se met à la fin du fichier
        }
        fclose(utilisateur); // on ferme le fichier utilisateur
    }
    // recopiage du nouveau tenumero Utilisateurte sans la ligne supprimée
    utilisateur = fopen("utilisateur","w+"); // ouverture du fichier utilisateur
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
        contenuFichier[strlen(contenuFichier)-1] = '\0'; // ligne permettant de supprimer le dernier caractère donc dans notre cas le "\n" de la ligne pour eviter d'avoir un saut de ligne
        fputs(contenuFichier,utilisateur); // on recole l'entiereté de la variable tampon dans le fichier utilisateur 
        fprintf(utilisateur,"\n%d %s %s %s %s %s %s",modifier.numeroUtilisateur,
                                                    modifier.prenom,
                                                    modifier.nom, 
                                                    modifier.email, 
                                                    modifier.tel,
                                                    modifier.identifiant,
                                                    modifier.mdp); // on la ligne modifié qui est en paramètre de la fonction dans la suite du fichier
        fclose(utilisateur); //on ferme le fichier utilisateur
    }
}


//ALEXANDRE SALIOU
// Fonction qui a pour but de prendre toutes les informations de chauqe utilisateur (sauf identifiant et mdp) et de les mettre dans une
// chaine de caractère, chaque paquete d'info de chaque utilisateur sera séparé par un "|"
char* afficherUtilisateurs(){
  FILE *utilisateur = fopen("utilisateur","r"); // ouverture du fichier Utilisateur
     char data[10000] =""; // on déclare data qui récuperera toutes les informations
    char ligne[200];  // déclaration de "ligne" qui aura les information de d'une ligne à chaque fois
    
    //boucle qui annonce si l'ouverture s'est mal faite
    if(utilisateur == NULL){ 
       printf("Le fichier utilsiateur ne s'est pas ouvert\n");
    }


    // Sinon qui permet de travailler sur le programme
    else if (utilisateur != NULL)
    {
        // On peut lire et écrire dans le fichier
        // boucle permettant de recuperer les numeros d'utilisateurs
        Utilisateur courant; // on déclare courant avec la structure utilisateur 
        while(fgets(ligne,200,utilisateur) != NULL){ //boucle qui s'execute tant qu'on est pas a la fin du programme
            initUser(&courant);
            sscanf(ligne,"%d %s %s %s %s %s %s",&courant.numeroUtilisateur,
                                                courant.prenom,
                                                courant.nom, 
                                                courant.email, 
                                                courant.tel,
                                                courant.identifiant,
                                                courant.mdp);
            char numUserSTR[5] = "";
            sprintf(numUserSTR,"%d",courant.numeroUtilisateur);
            strcat(data,numUserSTR);
            strcat(data," ");
            strcat(data,courant.prenom);
            strcat(data," ");
            strcat(data,courant.nom);
            strcat(data," ");
            strcat(data,courant.email);
            strcat(data," ");
            strcat(data,courant.tel);
            strcat(data,"|");
            freeUser(&courant);
        }
        data[strlen(data)-1] = '\0';
        // printf("%s",data);
    fclose(utilisateur);
    return data;
    }
}