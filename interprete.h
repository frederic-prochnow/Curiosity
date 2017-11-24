#ifndef _INTERPRETE_H_
#define _INTERPRETE_H_

#include "environnement.h"
#include "programme.h"
#include "type_pile.h"

/* Interpr�tation d'un programme dans un environnement */

/* R�sultat de l'interpr�tation */
typedef enum {
  OK_ROBOT,     /* Le robot est sur une case libre */
  SORTIE_ROBOT, /* Le robot est sorti du terrain */
  ARRET_ROBOT,  /* Le programme est termin� */
  PLOUF_ROBOT,  /* Le robot est tomb� dans l'eau */
  CRASH_ROBOT,  /* Le robot est rentr� dans un rocher */
  ERREUR_PILE_VIDE, /* Erreur : pile vide */
  ERREUR_ADRESSAGE, /* Erreur d'adressage : indice de commande incorrect */
  ERREUR_DIVISION_PAR_ZERO, /* Erreur : tentative de division par 0 */
} resultat_inter;

/* Etat de l'interpr�te */
typedef struct {
   /* Program counter : adresse de la prochaine commande � ex�cuter */
  int pc;
  /* Pile de donn�es */
  PileEntiers stack;
  /* Pile d'adresses de retour */
  PileEntiers sp;
} etat_inter;

/* Initialisation de l'�tat */
void init_etat(etat_inter * etat);

/* Pas d'ex�cution de l'interpr�te : ex�cute une commande, modifie
   l'environnement et l'�tat, renvoie l'�tat du robot */
resultat_inter exec_pas(Programme * prog, Environnement * envt, etat_inter * etat);

#endif
