#include <traitementFichier.h>
#include <stdio.h>



////CREATION
int ajouterUtilisateur(Utilisateur nouveau){
    printf("%s\n",nouveau.nom);
}

int creerDossierUtilisateur(char *numeroUtilisateur){

}

//creer un fichier 'perm', 'mesContact.an'
int creerFichiersUtilisateur(char *numeroUtilisateur){

}


int estIdentifiantExistant(char *identifiant){

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
            sscanf(ligne,"%d %s %s %s %s %s %s",&numeroUser);
        }
       


    }
    fclose(utilisateur); // on ferme le fichier


}
}

int estMDPExistant(char *identifiant){

}

int supprimerUtilisateur(char *identifiant){

}

int supprimerLigneFichierUser(char *numeroUtilisateur){

}

int chercherUtilisateur(char *numeroUtilisateur){

}



int ajouterLigneFichierUser(Utilisateur nouveau){
 
}