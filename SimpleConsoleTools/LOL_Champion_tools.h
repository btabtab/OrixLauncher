#ifndef GRAPHING
#define GRAPHING

typedef struct Ratings
{
	int damage;
	int toughness;
	int control;
	int mobility;
	int utility;
}
Ratings;

typedef struct Champion
{
	float health;
	float mana;
	float health_reger_per_second;
	float mana_regen_per_second;
	float armor;
	float attack_damage;
	float magic_resistance;
	float crit_damege;
	float move_speed;
	float attack_range;

	float base_AS;
	float attack_windup;
	float AS_ratio;
	float bonus_AS;
	float missile_speed;

	float unit_radius;
	float selection_radius;
	float pathing_radius;
	float acq_radius;

	Ratings ratings;
    char name[40];
}
Champion;

// Champion getTestChamp()
// {
// 	Champion champ;
// 	champ.health;
// 	champ.mana;
// 	champ.health_reger_per_second;
// 	champ.mana_regen_per_second;
// 	champ.armor;
// 	champ.attack_damage;
// 	champ.magic_resistance;
// 	champ.crit_damege;
// 	champ.move_speed;
// 	champ.attack_range;

// 	champ.base_AS;
// 	champ.attack_windup;
// 	champ.AS_ratio;
// 	champ.bonus_AS;
// 	champ.missile_speed;

// 	champ.unit_radius;
// 	champ.selection_radius;
// 	champ.pathing_radius;
// 	champ.acq_radius;
// }
// #include <raylib.h>
#ifdef RAYLIB_H
Color findInverseColour(Color colour)
{
	return (Color){~colour.r, ~colour.g, ~colour.b, colour.a};
}

void drawGrid(int x_res, int y_res, int spacing, Color col)
{
	for(int x = 0; x != x_res / spacing; x++)
	{
		for(int y = 0; y != y_res / spacing; y++)
		{
			DrawPixel((x * spacing) + (spacing / 2), (y * spacing) + (spacing / 2), findInverseColour(col));
		}
	}
}

void drawStatComprison(Champion attacking, Champion defending)
{
}
void LOLAnalasisTools()
{
	int x = 750, y = 600;
	Color background_col = BLACK;
	Camera cam = startup("LOL analysis", 750, 600);
	UIElement champion_stat_screen;

	while(!WindowShouldClose())
	{
		BeginDrawing();
		{
			ClearBackground(background_col);
			drawGrid(x, y, 25, background_col);
		}
		
		// renderCursor(getMainCursor());
		DrawFPS(10, 10);
		EndDrawing();
	}

}
#endif

#endif