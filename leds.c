#include "leds.h"
#include "test.h"

EtatCommande etatCommande = SUCCES;

unsigned char leds = 0;

void ledsInitialise() {
    // À faire
}

EtatCommande statusDerniereCommande() {
    // À faire;
    return SUCCES;
}

unsigned char interprete(const char *commande) {
    // À faire.
    return 0;
}

#ifdef TEST
void testAllumeEtEtteintDesLeds() {
    ledsInitialise();
    
    testeEgaliteEntiers("LDA01", interprete("A1"), 1);
    testeEgaliteEntiers("LDA02", interprete("A2"), 3);
    testeEgaliteEntiers("LDA03", interprete("A3"), 7);
    
    testeEgaliteEntiers("LDA08", interprete("A8"), 135);
    testeEgaliteEntiers("LDA07", interprete("A7"), 199);
    testeEgaliteEntiers("LDA06", interprete("A6"), 231);
    
    testeEgaliteEntiers("LDA05", interprete("A5"), 247);
    testeEgaliteEntiers("LDA04", interprete("A4"), 255);
    
    
    testeEgaliteEntiers("LDE01", interprete("E1"), 254);
    testeEgaliteEntiers("LDE02", interprete("E2"), 252);
    testeEgaliteEntiers("LDE03", interprete("E3"), 248);
    
    testeEgaliteEntiers("LDE08", interprete("E8"), 120);
    testeEgaliteEntiers("LDE07", interprete("E7"),  56);
    testeEgaliteEntiers("LDE06", interprete("E6"),  24);
    
    testeEgaliteEntiers("LDE05", interprete("E5"),   8);
    testeEgaliteEntiers("LDE04", interprete("E4"),   0);
}

void testDetecteDesErreurs() {
    ledsInitialise();
    
    interprete("R1");
    testeEgaliteEntiers("LDER1", statusDerniereCommande(), ERREUR);
    interprete("A9");
    testeEgaliteEntiers("LDER2", statusDerniereCommande(), ERREUR);
    interprete("E0");
    testeEgaliteEntiers("LDER3", statusDerniereCommande(), ERREUR);
    
    interprete("A1");
    testeEgaliteEntiers("LDOK1", statusDerniereCommande(), SUCCES);
    interprete("E1");
    testeEgaliteEntiers("LDOK2", statusDerniereCommande(), SUCCES);
}

void testLeds() {
    testAllumeEtEtteintDesLeds();
    testDetecteDesErreurs();
}

#endif
