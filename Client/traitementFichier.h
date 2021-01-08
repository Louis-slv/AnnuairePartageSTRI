#ifndef __TRAITEMENTF_H__
#define __TRAITEMENTF_H__


typedef struct Utilisateur Utilisateur;
struct Utilisateur
{
    char *nom;
    char *prenom;
    char *email;
    char *tel;
    char *identifiant;
    char *mdp;
    int numeroUtilisateur;
};

////CREATION
int ajouterUtilisateur(Utilisateur nouveau);

int creerDossierUtilisateur(char *numeroUtilisateur);

int ajouterLigneFichierUser(Utilisateur nouveau);



//creer un fichier 'perm', 'mesContact.an'
int creerFichiersUtilisateur(char *numeroUtilisateur);

int estIdentifiantExistant(char *identifiant);

int supprimerUtilisateur(char *identifiant);

int supprimerLigneFichierUser(char *numeroUtilisateur);

int chercherUtilisateur(char *numeroUtilisateur);


#endif
