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

fils      1	2	3	4	5	6	7	8

4 orange  x	x           x

3 jaune   x	x	x

2 rose          x	x	x

1 bleu							x	x	x


L'interface de commande est un ULN2003A monté sur un module chinois (banggood.com).

L'exemple (moteur_pas_a_pas.ino) montre l'utilisation de cette classe.

Copyleft Jean-Michel Ambroise
