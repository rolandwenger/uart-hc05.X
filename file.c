#include "test.h"
#include "file.h"

/**
 * Si il y a de la place dans la file, enfile un caractère.
 * @param c Le caractère.
 */
void fileEnfile(File *file, char c) {
    // À faire
}

/**
 * Si la file n'est pas vide, défile un caractère.
 * @return Le caractère défilé, ou 0 si la file est vide.
 */
char fileDefile(File *file) {
    // À faire
    return 0;
}

/**
 * Indique si la file est vide.
 */
char fileEstVide(File *file) {
    // À faire
    return 0;
}

/**
 * Indique si la file est pleine.
 */
char fileEstPleine(File *file) {
    // À faire
    return 0;
}

/**
 * Vide et réinitialise la file.
 */
void fileReinitialise(File *file) {
    // À faire
}

#ifdef TEST
void testEnfileEtDefile() {
    File file;
    fileReinitialise(&file);
    
    testeEgaliteEntiers("FIL01", fileEstVide(&file), 255);    
    testeEgaliteEntiers("FIL02", fileDefile(&file), 0);
    testeEgaliteEntiers("FIL03", fileDefile(&file), 0);

    fileEnfile(&file, 10);
    fileEnfile(&file, 20);

    testeEgaliteEntiers("FIL04", fileEstVide(&file), 0);
    testeEgaliteEntiers("FIL05", fileDefile(&file), 10);
    testeEgaliteEntiers("FIL06", fileDefile(&file), 20);
    testeEgaliteEntiers("FIL07", fileEstVide(&file), 255);
    testeEgaliteEntiers("FIL08", fileDefile(&file), 0);
}

void testEnfileEtDefileBeaucoupDeCaracteres() {
    File file;
    int n = 0;
    char c = 0;
    
    fileReinitialise(&file);

    for (n = 0; n < FILE_TAILLE * 4; n++) {
        fileEnfile(&file, c);
        if (testeEgaliteEntiers("FBC001", fileDefile(&file), c)) {
            return;
        }
        c++;
    }
}

void testDebordePuisRecupereLesCaracteres() {
    File file;
    char c = 1;
    
    fileReinitialise(&file);
    while(!fileEstPleine(&file)) {
        fileEnfile(&file, c++);
    }

    testeEgaliteEntiers("FDB001", fileDefile(&file), 1);
    testeEgaliteEntiers("FDB002", fileDefile(&file), 2);
    
    while(!fileEstVide(&file)) {
        c = fileDefile(&file);
    }
    fileEnfile(&file, 1);      // Ces caractères sont ignorés...
    fileEnfile(&file, 1);      // ... car la file est pleine.

    testeEgaliteEntiers("FDB003", c, FILE_TAILLE);
}

int testFile() {
    testEnfileEtDefile();
    testEnfileEtDefileBeaucoupDeCaracteres();
    testDebordePuisRecupereLesCaracteres();
}
#endif
