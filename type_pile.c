#include <stdio.h>
#include "type_pile.h"

/* Constructeurs */

/* Cr�er une pile vide */
void creer_pile(PileEntiers * p) {
  p->n = 0;
}

/* Op�rations d'acc�s */

/* Retourne vrai ssi p est vide */
int est_vide(PileEntiers p) {
  return (p.n == 0);
}

/* Renvoie l'entier en haut de la pile */
/* p doit �tre non vide */
int sommet(PileEntiers p) {
  return p.tab[p.n-1];
}

/* Renvoie le nombre d'�l�ments dans la pile */
int taille(PileEntiers p) {
  return p.n;
}

/* Afficher les �l�ments de la pile */
void print(PileEntiers p) {
  int i;

  printf("[ ");
  for(i = p.n-1; i >= 0; i--) {
    printf("%d ", p.tab[i]);
  }
  printf("]");
}

/* Op�rations de modification */

/* Vider la pile p */
void vider(PileEntiers * p) {
  p->n = 0;
}

/* Empiler un entier x */
/* Pr�condition : taille(p) < TAILLE_MAX */
void empiler(PileEntiers * p, int x) {
  p->tab[p->n] = x;
  p->n = p->n + 1;
}

/* Supprimer l'entier en haut de la pile */
/* Pr�condition : p non vide */
void depiler(PileEntiers * p) {
  p->n = p->n - 1;
}

