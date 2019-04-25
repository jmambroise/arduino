/***************************************************************************************************************
Classe Pas_A_Pas_4_Phases
Commande d'un moteur pas à pas à 4 phases comme le 28BYJ-48 (Banggood.com).
Inspiré de :
* http://www.geeetech.com/wiki/index.php/Stepper_Motor_5V_4-Phase_5-Wire_%26_ULN2003_Driver_Board_for_Arduino
* des exemples dérivés de Nuno Sarmento sur Mbed
* de https://os.mbed.com/teams/Coreonetech/code/CORE-1000_StepperMotor/file/481ac50cc86b/main.cpp/
* et de la classe sMotor de Mbed.

Référence du moteur 28BYJ-48 : https://www.geeetech.com/5v-4phase-5wire-stepper-motor-p-368.html
Propriétés angulaire, pas élémentaires, pas "complets", tour :
Il y a 4096 pas pour un tour complet (360° / (5.625° / 64)). Un pas élémentaire (une impulsion sur les 4 fils)
correspond à 0,087890625°, donc une séquence de 8 pas élémentaires (un pas complet) correspond à 0,703125°.
Avec 4096 / 8 = 512 pas complets on a 360°, donc un tour !
La tension d'alimentation va de 5V à 12V.

Séquences de commande :
fils		1	2	3	4	5	6	7	8
4 orange	x	x						x
3 jaune		x	x	x
2 rose					x	x	x
1 bleu							x	x	x

L'interface de commande est un ULN2003A monté sur un module chinois (banggood.com).

Copyleft Jean-Michel Ambroise

***************************************************************************************************************/

#include "Pas_A_Pas_4_Phases.hpp"
//										Phase 1		Phase 2		Phase 3		Phase 4		Délais entre pas élémentaires
Pas_A_Pas_4_Phases::Pas_A_Pas_4_Phases(uint8_t A0, uint8_t A1, uint8_t A2, uint8_t A3, uint16_t delais = 1) : _A0(A0), _A1(A1), _A2(A2), _A3(A3), _delais(delais) { // Constructeur : définition des broches du moteur
	pinMode(_A0, OUTPUT);
	pinMode(_A1, OUTPUT);
	pinMode(_A2, OUTPUT);
	pinMode(_A3, OUTPUT);
}

void Pas_A_Pas_4_Phases::unPasSensDirect() {
	for (int i = 0; i < 8; i++) {
		switch(i) {
			case 0:
				digitalWrite(_A0, HIGH); digitalWrite(_A1, LOW); digitalWrite(_A2, LOW); digitalWrite(_A3, LOW);
				break;
			case 1:
				digitalWrite(_A0, HIGH); digitalWrite(_A1, HIGH); digitalWrite(_A2, LOW); digitalWrite(_A3, LOW);
				break;
			case 2:
				digitalWrite(_A0, LOW); digitalWrite(_A1, HIGH); digitalWrite(_A2, LOW); digitalWrite(_A3, LOW);
				break;
			case 3:
				digitalWrite(_A0, LOW); digitalWrite(_A1, HIGH); digitalWrite(_A2, HIGH); digitalWrite(_A3, LOW);
				break;
			case 4:
				digitalWrite(_A0, LOW); digitalWrite(_A1, LOW); digitalWrite(_A2, HIGH); digitalWrite(_A3, LOW);
				break;
			case 5:
				digitalWrite(_A0, LOW); digitalWrite(_A1, LOW); digitalWrite(_A2, LOW); digitalWrite(_A3, HIGH);
				break;
			case 6:
				digitalWrite(_A0, LOW); digitalWrite(_A1, LOW); digitalWrite(_A2, LOW); digitalWrite(_A3, HIGH);
				break;
			case 7:
				digitalWrite(_A0, HIGH); digitalWrite(_A1, LOW); digitalWrite(_A2, LOW); digitalWrite(_A3, HIGH);
				break;
			default:
				digitalWrite(_A0, LOW); digitalWrite(_A1, LOW); digitalWrite(_A2, LOW); digitalWrite(_A3, LOW);
				break;
		}
		delay(_delais);
	}
}

void Pas_A_Pas_4_Phases::unPasSensRetrograde() {
	for (int i = 7; i > -1; i--) {
		switch(i) {
			case 0:
				digitalWrite(_A0, HIGH); digitalWrite(_A1, LOW); digitalWrite(_A2, LOW); digitalWrite(_A3, LOW);
				break;
			case 1:
				digitalWrite(_A0, HIGH); digitalWrite(_A1, HIGH); digitalWrite(_A2, LOW); digitalWrite(_A3, LOW);
				break;
			case 2:
				digitalWrite(_A0, LOW); digitalWrite(_A1, HIGH); digitalWrite(_A2, LOW); digitalWrite(_A3, LOW);
				break;
			case 3:
				digitalWrite(_A0, LOW); digitalWrite(_A1, HIGH); digitalWrite(_A2, HIGH); digitalWrite(_A3, LOW);
				break;
			case 4:
				digitalWrite(_A0, LOW); digitalWrite(_A1, LOW); digitalWrite(_A2, HIGH); digitalWrite(_A3, LOW);
				break;
			case 5:
				digitalWrite(_A0, LOW); digitalWrite(_A1, LOW); digitalWrite(_A2, LOW); digitalWrite(_A3, HIGH);
				break;
			case 6:
				digitalWrite(_A0, LOW); digitalWrite(_A1, LOW); digitalWrite(_A2, LOW); digitalWrite(_A3, HIGH);
				break;
			case 7:
				digitalWrite(_A0, HIGH); digitalWrite(_A1, LOW); digitalWrite(_A2, LOW); digitalWrite(_A3, HIGH);
				break;
			default:
				digitalWrite(_A0, LOW); digitalWrite(_A1, LOW); digitalWrite(_A2, LOW); digitalWrite(_A3, LOW);
				break;
		}
		delay(_delais);
	}

}

void Pas_A_Pas_4_Phases::pas(uint16_t nombrePas, uint8_t sensRotation) {
    for (uint16_t i = 0; i < nombrePas; i++) {
        if (sensRotation == retrograde)
            unPasSensRetrograde();
        else if (sensRotation == direct)
            unPasSensDirect();
    }
    stop();
}

void Pas_A_Pas_4_Phases::stop() {
	digitalWrite(_A0, LOW); digitalWrite(_A1, LOW); digitalWrite(_A2, LOW); digitalWrite(_A3, LOW);
}

void Pas_A_Pas_4_Phases::ecrisDelais(uint16_t delais) {
	_delais = delais;
}

uint16_t Pas_A_Pas_4_Phases::lisDelais() {
	return(_delais);
}
