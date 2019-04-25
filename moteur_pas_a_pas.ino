
/*
Commande des moteurs pas à pas à 4 phases / 5 fils type 28BYJ-48
disponibles par example sur Banggood (banggood.com)
Cette commande utilise la bibliothèque Pas_A_Pas_4_Phases

*/

#include <Pas_A_Pas_4_Phases.hpp>

#define DEBUG_28BYJ_48
//#undef DEBUG_28BYJ_48
#define LED_ALLUMEE LOW
#define LED_ETEINTE HIGH
/* Il y a 4096 pas pour un tour complet (360° / (5.625° / 64)). Un pas élémentaire (une impulsion sur les 4 fils)
correspond à 0,087890625°, donc une séquence de 8 pas élémentaires (un pas complet) correspond à 0,703125°.
Avec 4096 / 8 = 512 pas complets on a 360°, donc un tour ! */
const uint32_t nombrePasParTour = 512;
// pattes de control des phases
const uint8_t in1 = 2;	// D2
const uint8_t in2 = 3;  // D3
const uint8_t in3 = 4;  // D4
const uint8_t in4 = 5;  // D5
// La led bleu interne
const int led = LED_BUILTIN;

uint8_t nombrePas = 1;	// Nombre de pas réalisés
uint8_t sensRotation = direct;	// Sens de la rotation
uint16_t delais = 1;	// Vitesse

// initialisation du controleur 
Pas_A_Pas_4_Phases moteur28BYJ48(in1, in2, in3, in4, delais);

void setup() {
	// initialisation du port série :
#ifdef DEBUG_28BYJ_48
	Serial.begin(115200);
	Serial.println("Initialisation du moteur pas a pas.");
#endif
	// La led
	pinMode(led, OUTPUT);
}

void loop() {
#ifdef DEBUG_28BYJ_48
	Serial.println();
	Serial.println("Sens direct/antihoraire.");
#endif
	digitalWrite(led, LED_ALLUMEE);
	sensRotation = direct;
	for (uint16_t i = 0; i < 10; i++) {
		moteur28BYJ48.pas(512, sensRotation);
#ifdef DEBUG_28BYJ_48
		Serial.print(".");
#endif
		delay(1000);
	}
#ifdef DEBUG_28BYJ_48
 	Serial.println();
	Serial.println("Sens retrograde/horaire.");
#endif
	digitalWrite(led, LED_ETEINTE);
	sensRotation = retrograde;
	for (uint16_t i = 0; i < 10; i++) {
		moteur28BYJ48.pas(512, sensRotation);
#ifdef DEBUG_28BYJ_48
		Serial.print(".");
#endif
		delay(1000);
	}
	delay(10000);
}
