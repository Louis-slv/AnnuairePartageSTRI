#include "traitementFichier.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/dir.h>
#include <dirent.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>

int main(){


     FILE *utilisateur = fopen("utilisateur","r"); // ouverture du fichier
     char data[10000] ="";
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


    // prochaine fonction : supprimer le dernier /n 
        


    /*
    // pour tester une fonction avec utilisateur en paramètre
    Utilisateur test;
    initUser(&test);
    test.numeroUtilisateur = 3;
    test.prenom = "joan";
    test.nom = "duclos";
    test.email = "jojo@gmail.com";
    test.tel = "0606060606";
    test.identifiant =  "cestjojo";
    test.mdp = "mdpjojo";
    modifierUtilisateur(test);
    freeuser(test);
       */
       
       
       
        /*
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
            if (numeroCourant != modifier.numeroUtilisateur){
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
        fprintf(utilisateur,"\n%d %s %s %s %s %s %s",numeroMaxUser+1,modifier.prenom,
                                                                modifier.nom, 
                                                                modifier.email, 
                                                                modifier.tel,
                                                                modifier.identifiant,
                                                                modifier.mdp);
        fclose(utilisateur);*/
    

    /*utilise la suite du programme à mettre dans la partie du haut
    fprintf(utilisateur,"\n%d %s %s %s %s %s %s",numeroMaxUser+1,nouveau.prenom,
                                                                nouveau.nom, 
                                                                nouveau.email, 
                                                                nouveau.tel,
                                                                nouveau.identifiant,
                                                                nouveau.mdp); */
    /*
    char  *numeroUtilisateur = "2";
    char path4[100] ="";
    char path5[100] ="";
    char path6[100] ="";

    strcat(path4,"./");
    strcat(path4,numeroUtilisateur);
    strcat(path4,"/mesContact.an");
    printf("path4 : %s\n",path4);

     strcat(path5,"./");
    strcat(path5,numeroUtilisateur);
    strcat(path5,"/perm.an");
    printf("path5 : %s\n",path5);

    remove(path4);
    remove(path5);
    remove(path6);




    rmdir(numeroUtilisateur);
    */
    
    // exemple pour dossier 6 
    /* 

    

    remove(./6/);

    rmdir("6");
    ./6/mesContact.an
    ./6/perm.an
    // rmdir("5");

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

    remove("/mesContact.an")

	rmdir("5");*/
}
    

