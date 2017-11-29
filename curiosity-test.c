#include "environnement.h"
#include "programme.h"
#include "interprete.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gestion_erreur_terrain(erreur_terrain e) {
  switch(e) {
  case OK: break;
  case ERREUR_FICHIER:
    printf("Erreur lecture du terrain : erreur d'ouverture du fichier\n");
    exit(1);
  case ERREUR_LECTURE_LARGEUR:
    printf("Erreur lecture du terrain : erreur de lecture de la largeur\n");
    exit(1);
  case ERREUR_LECTURE_HAUTEUR:
    printf("Erreur lecture du terrain : erreur de lecture de la hauteur\n");
    exit(1);
  case ERREUR_LARGEUR_INCORRECTE:
    printf("Erreur lecture du terrain : largeur incorrecte\n");
    exit(1);
  case ERREUR_HAUTEUR_INCORRECTE:
    printf("Erreur lecture du terrain : hauteur incorrecte\n");
    exit(1);
  case ERREUR_CARACTERE_INCORRECT:
    printf("Erreur lecture du terrain : caractère incorrect\n");
    exit(1);
  case ERREUR_LIGNE_TROP_LONGUE:
    printf("Erreur lecture du terrain : ligne trop longue\n");
    exit(1);
  case ERREUR_LIGNE_TROP_COURTE:
    printf("Erreur lecture du terrain : ligne trop courte\n");
    exit(1);
  case ERREUR_LIGNES_MANQUANTES:
    printf("Erreur lecture du terrain : lignes manquantes\n");
    exit(1);
  case ERREUR_POSITION_ROBOT_MANQUANTE:
    printf("Erreur lecture du terrain : position initiale du robot manquante\n");
    exit(1);
  }
}

void affichage_position_programme(erreur_programme e) {
  int i;
  printf("Ligne %d, colonne %d :\n", e.num_ligne, e.num_colonne);
  printf("%s\n", e.ligne);
  /* Impression de e.num_colonne-1 espaces */
  for(i = 1; i < e.num_colonne; i++) {
    printf(" ");
  }
  /* Impression d'un curseur de position */
  printf("^\n");
}

static void search(char *chaine)
{
	char *p = strchr(chaine, '\n');
	if (p){
		*p = 0;
	}
}

void gestion_erreur_programme(erreur_programme e) {
  switch(e.type_err) {
  case OK_PROGRAMME: break;
  case ERREUR_FICHIER_PROGRAMME:
    printf("Erreur lecture du programme : erreur d'ouverture du fichier\n");
    exit(2);
  case ERREUR_BLOC_NON_FERME:
    printf("Erreur lecture du programme : bloc non fermé\n");
    exit(2);
  case ERREUR_FERMETURE_BLOC_EXCEDENTAIRE:
    printf("Erreur lecture du programme : fermeture de bloc excédentaire\n");
    affichage_position_programme(e);
    exit(2);
  case ERREUR_COMMANDE_INCORRECTE:
    printf("Erreur lecture du programme : commande incorrecte\n");
    affichage_position_programme(e);
    exit(2);
  }
}

int main(int argc, char ** argv) {
  Environnement envt;
  Programme prog;
  erreur_terrain errt;
  erreur_programme errp;
  etat_inter etat;
  resultat_inter res;
  
  char *fichier = NULL;
	int x,y,nbPas,cpt;
	char orient;
	char ligne [ 128 ];

  if (argc < 2) {
  	printf("Usage:  %s <fichier>\n\n", argv[0]);
    exit(1);
  } else {
    int arg=1;
		while (arg < argc) {
    	if (fichier == NULL) {
      	fichier = argv[arg];
        arg++;
        continue;
      } else {
      	printf ("Trop de fichiers sur la ligne de commande!\n");
        exit(1);
     	}
		}
  }

  printf ("Ouverture de %s\n", fichier);
  FILE* f = fopen (fichier, "r");
  if (!f) {
   printf ("Erreur à l'ouverture du fichier `%s'\n", fichier);
   perror (fichier);
   exit(1);
  }
	
  /* Initialisation de l'environnement : lecture du terrain,
     initialisation de la position du robot */
	fgets ( ligne, sizeof ligne, f );
	printf("Terrain : %s", ligne);
  errt = initialise_environnement(&envt, ligne);
  gestion_erreur_terrain(errt);

  /* Lecture du programme */
	fgets ( ligne, sizeof ligne, f );
	printf("Programme : %s\n", ligne);
  errp = lire_programme(&prog, ligne);
  gestion_erreur_programme(errp);

	/* Initialisation de l'état */
	fgets ( ligne, sizeof ligne, f );
  search( ligne);
  printf("Nombre de pas : %s\n", ligne);
  nbPas = atoi(ligne);
  cpt = 0;
  init_etat(&etat);
  do {
    res = exec_pas(&prog, &envt, &etat);
    /* Affichage du terrain et du robot */
    afficher_envt(&envt);
		cpt++;
  } while(res == OK_ROBOT || cpt == nbPas);

	fgets ( ligne, sizeof ligne, f );
	search( ligne);
  printf("Resultat attentu :");
	if(strcmp(ligne,"N") == 0 || strcmp(ligne,"F") == 0){
		fgets ( ligne, sizeof ligne, f );search( ligne); x= atoi(ligne);
		fgets ( ligne, sizeof ligne, f );search( ligne); y= atoi(ligne);
		fgets ( ligne, sizeof ligne, f );search( ligne); orient = ligne[0];
		printf("Le robot est située %d %d dans le sens %c.\n",x,y,orient);
  }
  if(strcmp(ligne,"N") == 0 ){
		printf("Le robot est sur une position normal à l'interieur du terrain\n");
		if(res == OK_ROBOT && x==envt.r.x && y==envt.r.y) printf("\n OK \n");
	}else if(strcmp(ligne,"F") == 0){ 
		printf("Le programme est terminé\n");
		if(res == ARRET_ROBOT && x==envt.r.x && y==envt.r.y) printf("\n OK \n");
  }else if(strcmp(ligne,"S") == 0){ 
		printf("Le robot est sorti du terrain\n");
		if(res == SORTIE_ROBOT) printf("\n OK \n");
  }else if(strcmp(ligne,"O") == 0){ 
		printf("Le robot a rencontré un obstacle\n");
		if(res == CRASH_ROBOT) printf("\n OK \n");
  }else if(strcmp(ligne,"P") == 0){ 
		printf("Le robot est tombé dans l'eau\n");
		if(res == PLOUF_ROBOT) printf("\n OK \n");
  }
	return 1;
}
