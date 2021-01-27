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
// Fonction qui a pour but de supprimer l'utilisateur dont on a mis en paramètre le numéro d'utilisateur
// Concrètement, on stocke dans un tampon toutes les lignes sauf la ligne à supprimer et on recolle ces infos dans un autre fichier utilisateur
int supprimerLigneFichierUser(int numeroUtilisateur){
    int numeroCourant =0;
    FILE *utilisateur = fopen("utilisateur","r+"); // ouverture du fichier
    char *contenuFichier = (char *) calloc(sizeof(char), 100); //
    char ligne[150] = ""; // on déclare un tableau de caractère "ligne" qui aura la valeur d'une ligne a chaque fois
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
                if(strlen(contenuFichier)+strlen(ligne) > strlen(contenuFichier)){// si jamais la taille du tampon n'est plus assez grande on l'agrandit
                    contenuFichier = realloc(contenuFichier,strlen(contenuFichier) + 200); 
                }
                strcat(contenuFichier,ligne); // on copie le contenu de "ligne" dans le gros tampon "contenuFichier"
            }
            
        //fseek(utilisateur, 0, SEEK_END); // on se met à la fin du fichier
        }
        fclose(utilisateur); // on ferme le fichier car tout ce qu'on avait à faire dans le premier fichier est fini
    }
    // recopiage du nouveau tenumeroUtilisateurte sans la ligne supprimée
    utilisateur = fopen("utilisateur","w+"); // ouverture du nouveau fichier Utilisateur
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
        fputs(contenuFichier,utilisateur); // on colle le contenu de notre tampon 
        fclose(utilisateur); // on ferme notre fichier
    }
}


//ALEXANDRE SALIOU
// Fonction permettant de créer un fichier utilisateur 
// en paramètre on rentrera le numéro utilisateur d'un utilisateur, et on créera un fichier qui aura pour nom le numéro, et dans ce fichier il 
// y aura deux fichiers, "mesContact" et "perm"
// Son fonctionnement est simple, on concatène les nom des dossier ainsi que la syntaxe de creation d'un fichier
// pour creer des commande avec les noms de fichier qu'il nous faut
int creerFichiersUtilisateur(char *numeroUtilisateur){
   
    char path[100] =""; // on créer trois chaine de caractère tampon qui auront les chemins d'accès des fichiers
    char path2[100] = "";
    char path3[100] ="";
    strcat(path,"./"); // on concatène dans "path" ces informations :"./numeroUtilisateur"
    strcat(path,numeroUtilisateur);
    mkdir(path,0777); //  ensuite on créer le fichier avec le chemin "./numeroUtilisateur" et comme mask on met 777 pour le départ et si jamais cela pose un problème
    // de sécurité on pourra changer

    strcat(path2,path); // on concatène dans le path2 les informations du path déja présente pour ne pas avoir à recopier
    strcat(path2,"/mesContact.an"); // ensuite on rajoute dans le path2 "/mesContact.an" pour continuer le chemin dans le dossier

    FILE *mesContact = fopen(path2,"w"); // on ouvre le fichier en ecriture pour "l'initialiser"

    strcat(path3,path);// on concatène dans le path3 les informations du path pour ne pas avoir à recopier
    strcat(path3,"/perm");// ensuite on rajoute dans le path2 "/perm.an" pour continuer le chemin dans le dossier

    FILE *perm = fopen(path3,"w"); // on ouvre le fichier en ecriture pour "l'initialiser"
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
// Fonction qui a pour but d'ajouter un nouvel utilisateur dans le fichier utilisateur
// Ainsi le fonctionnement sera le suivant : en paramètre de la fonction, on rentre la structure nouveau ce qui signifie toutes les informations d'un nouvel utilisateur
// et ces information seront liées a un numero utilisateur qui sera le numero utilisateur le plus grand du fichier
int ajouterLigneFichierUser(Utilisateur nouveau){
 
    FILE *utilisateur = fopen("utilisateur","r+"); // ouverture du fichier
    int numeroUser =0; 
    int numeroMaxUser =0; 
    char ligne[100] = ""; // On déclare un tableau de caractère qui servira de tampon
    //boucle qui annonce si l'ouverture s'est mal faite
    if(utilisateur == NULL){ 
       printf("le fichier ne  s'est pas ouvert\n");
        exit(1);
    }
    // Sinon qui permet de travailler sur le programme
    else if (utilisateur != NULL)
    {
        // On peut lire et écrire dans le fichier
        // boucle qui parcours tout le fichier permettant de recuperer les numeros d'utilisateurs
        while(fgets(ligne,100,utilisateur) != NULL){
            sscanf(ligne,"%d",&numeroUser); // on scan dans la variable ligne le numéro d'utilisateur
            if(numeroMaxUser < numeroUser){ // on regarde quel est le numero le plus grand peut importe son endroit dans le fichier
                numeroMaxUser = numeroUser; // le numero utilisateur devient donc le numéro maximal du fichier
            }
        }
        fseek(utilisateur, 0, SEEK_END); // on se met à la fin du fichier
        // ensuite on rajoute le nouvel utilisateur rentré en paramètre dans le fichier
        fprintf(utilisateur,"\n%d %s %s %s %s %s %s",numeroMaxUser+1,nouveau.prenom, 
                                                                nouveau.nom, 
                                                                nouveau.email, 
                                                                nouveau.tel,
                                                                nouveau.identifiant,
                                                                nouveau.mdp); 
        
        fclose(utilisateur); // on ferme le fichier
        return numeroMaxUser+1; //On retourne le numéro d'utlisateur en l'implémentant de 1
    }
    

}


//ALEXANDRE SALIOU
// Fonction permettant de modifier un utilisateur
// Elle fonctionnera de la manière suivante : elle scannera l'entièretée des lignes sauf celle à modifier
// ensuite, toutes les informations scannées seront remisent dans un autre fichier utilisateur et ensuite la nouvelle ligne à modifier sera 
// rajouter à la suite des informations des utilisateurs
int modifierUtilisateur(Utilisateur modifier){

    int numeroCourant =0; // on déclare un entier qui nous servira par la suite 
    FILE *utilisateur = fopen("utilisateur","r+"); // ouverture du fichier
    char *contenuFichier = (char *) calloc(sizeof(char), 100); 
    char ligne[150] = "";



    char ligne[150] = ""; // déclaration d'un tableau de caractère "ligne" qui par la suite récuperera les informations d'une ligne 
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
// Fonction créant une chaine de caractère composé des informations de tous les utilisateur (sauf les identifiants et mots de passe)
// Chaque bloc d'information de chaque utilisateur seront séparé par un "|"
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
            // avec le sscanf on scan chaque ligne et on met chaque information dans la structure "courant" 
            sscanf(ligne,"%d %s %s %s %s %s %s",&courant.numeroUtilisateur,
                                                courant.prenom,
                                                courant.nom, 
                                                courant.email, 
                                                courant.tel,
                                                courant.identifiant,
                                                courant.mdp);
            char numUserSTR[5] = ""; //tableau de caractères pour le numero utilisateur
            sprintf(numUserSTR,"%d",courant.numeroUtilisateur); // on note dans le tableau le numéro d'utilisateur de la structure courant
            strcat(data,numUserSTR);// on concatène toutes les informations  dans "data"
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
        data[strlen(data)-1] = '\0'; // ligne permettant de supprimer le dernier caractère donc dans notre cas le "\n" de la ligne pour eviter d'avoir un saut de ligne
        // printf("%s",data);
    fclose(utilisateur); // on ferme le fichier
    return data; // on retourne data a la fin de la fonction
    }
}




// ALEXANDRE SALIOU 
// 