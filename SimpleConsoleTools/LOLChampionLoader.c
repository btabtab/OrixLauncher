#define _CRT_SECURE_NO_WARNINGS

#include "LOL_Champion_tools.h"
#include "../EngineCode/Saving.h"
#include "../Jlib/Text_input_Handling_System.h"
#include <stdlib.h>
#include <string.h>
#include <windows.h>
float getFloat()
{
	float a = *((float*)grabTextFromConsole());
	return a;
}

int main()
{
	Champion champ;
	system("cls");
	printf("enter the 'champions name' and then press enter (use the wiki for this pls<3)!\n");
	strcat(champ.name, grabTextFromConsole());
	system("cls");
	printf("enter the 'champions health' and then press enter (use the wiki for this pls<3)!\n");
	champ.health = getFloat();
	system("cls");
	printf("enter the 'champions mana' and then press enter (use the wiki for this pls<3)!\n");
	champ.mana = getFloat();
	system("cls");
	printf("enter the 'champions health_reger_per_second' and then press enter (use the wiki for this pls<3)!\n");
	champ.health_reger_per_second = getFloat();
	system("cls");
	printf("enter the 'champions mana_regen_per_second' and then press enter (use the wiki for this pls<3)!\n");
	champ.mana_regen_per_second = getFloat();
	system("cls");
	printf("enter the 'champions armor' and then press enter (use the wiki for this pls<3)!\n");
	champ.armor = getFloat();
	system("cls");
	printf("enter the 'champions attack_damage' and then press enter (use the wiki for this pls<3)!\n");
	champ.attack_damage = getFloat();
	system("cls");
	printf("enter the 'champions magic_resistance' and then press enter (use the wiki for this pls<3)!\n");
	champ.magic_resistance = getFloat();
	system("cls");
	printf("enter the 'champions crit_damege' and then press enter (use the wiki for this pls<3)!\n");
	champ.crit_damege = getFloat();
	system("cls");
	printf("enter the 'champions move_speed' and then press enter (use the wiki for this pls<3)!\n");
	champ.move_speed = getFloat();
	system("cls");
	printf("enter the 'champions attack_range' and then press enter (use the wiki for this pls<3)!\n");
	champ.attack_range = getFloat();
	system("cls");
	printf("enter the 'champions base_AS' and then press enter (use the wiki for this pls<3)!\n");
	champ.base_AS = getFloat();
	system("cls");
	printf("enter the 'champions attack_windup' and then press enter (use the wiki for this pls<3)!\n");
	champ.attack_windup = getFloat();
	system("cls");
	printf("enter the 'champions AS_ratio' and then press enter (use the wiki for this pls<3)!\n");
	champ.AS_ratio = getFloat();
	system("cls");
	printf("enter the 'champions bonus_AS' and then press enter (use the wiki for this pls<3)!\n");
	champ.bonus_AS = getFloat();
	system("cls");
	printf("enter the 'champions missile_speed' and then press enter (use the wiki for this pls<3)!\n");
	champ.missile_speed = getFloat();
	system("cls");
	printf("enter the 'champions unit_radius' and then press enter (use the wiki for this pls<3)!\n");
	champ.unit_radius = getFloat();
	system("cls");
	printf("enter the 'champions selection_radius' and then press enter (use the wiki for this pls<3)!\n");
	champ.selection_radius = getFloat();
	system("cls");
	printf("enter the 'champions pathing_radius' and then press enter (use the wiki for this pls<3)!\n");
	champ.pathing_radius = getFloat();
	system("cls");
	printf("enter the 'champions acq_radius' and then press enter (use the wiki for this pls<3)!\n");
	champ.acq_radius = getFloat();
	
	Beep(650, 100);
	printf("enter the file name!\n");
	saveData(&champ, sizeof(champ), (char*)grabTextFromConsole());
	Beep(700, 100);

}