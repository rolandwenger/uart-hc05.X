
#ifndef LEDS_H
#define	LEDS_H

typedef enum {
    SUCCES,
    ERREUR
} EtatCommande;

/**
 * Rend l'état de la dernière commande
 * @return L'état.
 */
EtatCommande statusDerniereCommande();

/**
 * Interprète la commande contenue dans 
 * @param buffer Contient la commande, en toutes lettres.
 * @return L'état des LED, après avoir interprété la commande.
 */
unsigned char interprete(const char *commande);

#ifdef TEST
void testLeds();
#endif

#endif

