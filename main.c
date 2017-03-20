#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "file.h"
#include "leds.h"
#include "test.h"

/**
 * Bits de configuration:
 */
#pragma config FOSC = INTIO67  // Osc. interne, A6 et A7 comme IO.
#pragma config IESO = OFF      // Pas d'osc. au démarrage.
#pragma config FCMEN = OFF     // Pas de monitorage de l'oscillateur.

// Nécessaires pour ICSP / ICD:
#pragma config MCLRE = EXTMCLR // RE3 est actif comme master reset.
#pragma config WDTEN = OFF     // Watchdog inactif.
#pragma config LVP = OFF       // Single Supply Enable bits off.

#ifndef TEST

void interrupt low_priority interruptionsBassePriorite() {
    if (PIR1bits.TX1IF) {
        uartTransmission();
    }
    if (PIR1bits.RC1IF) {
        uartReception();
    }
}

/**
 * Initialise la sortie 1 de la EUSART.
 * Si le UP est à 1MHz, le Virtual Terminal dans Proteus
 * doit être configuré comme suit:
 * - 1200 bauds.
 * - Transmission 8 bits.
 * - Bit de stop activé.
 */
void initialiseHardware() {
    // Configure le port A comme sortie digitale, pour configurer les LED:
    TRISA = 0;
    ANSELA = 0;

    // Horloge principale Fosc = 8MHz
    OSCCONbits.IRCF = 0b110;
    
    // Pour une fréquence de 8MHz, ceci donne 9600 bauds:
    TXSTA1bits.BRGH = 1;    // Mode haute vitesse.
    BAUDCON1bits.BRG16 = 1; // Générateur de fréquence à 16 bits.
    SPBRG = 207;            // 9615 bauds
    SPBRGH = 0;

    // Active RC1 (Enable):
    TRISCbits.RC1 = 0;
    PORTCbits.RC1 = 1;
    
    // Configure RC6 et RC7 comme entrées digitales, pour que
    // la EUSART puisse en prendre le contrôle:
    ANSELCbits.ANSC6 = 0;
    ANSELCbits.ANSC7 = 0;
    TRISCbits.RC6 = 1;
    TRISCbits.RC7 = 1;
    
    // Configure la EUSART:
    // (BRGH et BRG16 sont à leur valeurs par défaut)
    // (TX9 est à sa valeur par défaut)
    TXSTAbits.SYNC = 0;  // Mode asynchrone.
    TXSTAbits.TXEN = 1;  // Active l'émetteur.
    RCSTAbits.CREN = 1;  // Active le récepteur.
    RCSTAbits.SPEN = 1;  // Active la EUSART.
    
    // Active les interruptions (basse priorité):
    PIE1bits.TX1IE = 1;
    IPR1bits.TX1IP = 0;
    PIE1bits.RC1IE = 1;
    IPR1bits.RC1IP = 0;
    
    // Active les interruptions générales:
    RCONbits.IPEN = 1;
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
}

/**
 * Point d'entrée du programme.
 */
void main(void) {
    char buffer[40];
    
    initialiseHardware();
    uartReinitialise();
    while(1) {
        printf("Commande:\r\n");    
        gets(buffer);
        PORTA = interprete(buffer);
        if (statusDerniereCommande() == SUCCES) {
            printf("OK\r\n");
        } else {
            printf("Erreur\r\n");
        }
    }
}

#endif

#ifdef TEST
void main() {
    initialiseTests();
    testFile();
    testLeds();
    finaliseTests();
    while(1);
}
#endif