#ifndef _ENVIRONNEMENT_H_
#define _ENVIRONNEMENT_H_

#include "robot.h"
#include "terrain.h"

/* Environnement : terrain + robot */

typedef struct {
  Robot r;
  Terrain t;
} Environnement;

/* Initialise l'environnement envt :
   - lit le terrain dans le fichier fichier_terrain
   - initialise le robot : coordonn�es initiales lues dans le fichier
   terrain, orientation initiale vers l'est
*/
erreur_terrain initialise_environnement(Environnement * envt, char * fichier_terrain);

/* R�sultat d'un d�placement de robot */
typedef enum {
  OK_DEPL,     /* D�placement sur case libre */
  PLOUF,  /* D�placement dans l'eau */
  CRASH,  /* D�placement dans un rocher */
  SORTIE, /* Sortie du terrain */
} resultat_deplacement;

/* Avancer le robot sur le terrain : */
resultat_deplacement avancer_envt(Environnement * envt);

/* Tourner le robot � gauche */
void gauche_envt(Environnement * envt);

/* Tourner le robot � droite */
void droite_envt(Environnement * envt);

/* Effectuer une mesure
   Param�tre d : la direction de la mesure
     0 sur place      
     1 devant         
     2 devant droite  
     3 droite         
     4 derri�re droite
     5 derri�re       
     6 derri�re gauche
     7 gauche         
     8 devant gauche
   Renvoie le r�sultat de la mesure :
     0 rien (case libre ou en-dehors du terrain)
     1 eau
     2 rocher
 */
int mesure_envt(Environnement * envt, int d);

/* Afficher le terrain avec la position et l'orientation du robot */
void afficher_envt(Environnement * envt);

#endif
