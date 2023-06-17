#pragma once
#include "Pacman.h"
#include <chrono>
const short Map_wysokosc = 21;
const short Map_szerokosc = 22;

class Mapa
{
private:
	//mapa i tekstuy
	Texture pathtext;
	Texture walltext;
	Texture corntext;
	Texture energizertext;
	Texture bonustext;
	Texture doortext;
	Texture shieldtext;
	Texture boosttext;

	Texture dziuratext;
	Sprite dziura;
	Texture lepkietext;
	Sprite lepkie;
	Texture lodtext;
	Sprite lod;


	Sprite door;
	Sprite wall;
	Sprite path;

	CircleShape energizer;
	CircleShape corn;
	CircleShape bonus;
	CircleShape shield;
	CircleShape boost;
	void initTextur_andSprite();
	void initSpriteMap();
	void CreateHoles();
	//Bonus
	unsigned int TimerBonus;
	bool BonusBool;
	bool reset;
	unsigned int ResetBonusTimer;
	unsigned short int BonusTimeMin, BonusTimeMax;
	unsigned short int RespawnTime;
		//shield
	unsigned int ShieldBonus;
	bool ShieldBool;
	bool Shieldreset;
	unsigned int ResetShieldTimer;
	unsigned short int ShieldTimeMin, ShieldTimeMax;
	//speed
	unsigned int SpeedBonus;
	bool SpeedBool;
	bool Speedreset;
	unsigned int ResetSpeedTimer;
	unsigned short int SpeedTimeMin, SpeedTimeMax;
	//dziury
	unsigned short int chagnedziuratime;
	unsigned short int iloscdziur;
	unsigned short int dziuraduration;
	vector<Vector2f> dziury;

public:
	///Timery Get
	bool GetEnergizerBool();
	bool GetProtectionBool();
	bool GetSpeedBool();
	//gracz i duchy pozycja
	Vector2f Pacmanposition;
	Vector2f GhostYposition;
	Vector2f GhostGposition;
	Vector2f GhostBposition;
	Vector2f GhostPposition;
	//Inne dane
	vector<Vector2f> wybranedziuryPOS;
	vector<int>wybranedziuryTYP;
	short unsigned int liczbapunktow;
	array<string, Map_wysokosc> SzkicMapy = {
	"!###################!",
	"!#?.E?...?X?..X?E.?#!",
	"!#.##.###.#.###.##.#!",
	"!#?X.?.?X?#?.?.?..?#!",
	"!#.##.#.#####.#.##.#!",
	"!#?..?#?.?#?.?#?.X?#!",
	"!####.###.#.###.####!",
	"!!!!#.#?H???X?#.#!!!!",
	"#####.#X##D## #.#####",
	"     ? ?#???#?K?     ",
	"#####X# ##D## #.#####",
	"!!!!#.#? P?B ?#X#!!!!",
	"!####.#.#####.#.####!",
	"!#?X.?.?.?#?.?X?..?#!",
	"!#.##.###.#.###.##.#!",
	"!#?..?X?.?.?.?.?#??#!",
	"!#.##.#.#####.#.#.##!",
	"!#?.??#?.?#?.?#?X??#!",
	"!#.#.####.#.###.##.#!",
	"!#?E?X...?.?..X?.E?#!",
	"!###################!"
	};
	array<array<int, Map_szerokosc>, Map_wysokosc> KolizcjaMapy;
	std::array<std::array<sf::Sprite, Map_szerokosc>, Map_wysokosc> MapaSprite;
	std::array<std::array<sf::CircleShape, Map_szerokosc>, Map_wysokosc> MapaCorn;
	Mapa( unsigned short int poziomtrudnosi);
	~Mapa();
	void DrawMap(RenderTarget& window, bool pauza);
	void ResetMap();
	void ResetMapNextRound();
	void ResetBonus();
	void ResetShield();
	void ResetBoost();
	bool CheckWall(char dir,Vector2f pos);
	char WhereCanGo(Vector2f pos);
	//geter
	Sprite Getwall();
	Sprite Getdoor();
	Texture Getcorn();
	Vector2f GetPacmanPosition();
	Vector2f GetGhostPosition(char kolor);
};
