#pragma once
#include "Ghost.h"
#include "Pacman.h"
#include "Mapa.h"

class Game
{
private:
								//statystyki gry
	int Gamepoints;
	int level;
	bool EndGame; 
	int Lifes;
	int PoziomTrudnosci;
									//okno
	VideoMode videoMode;
	RenderWindow* window;
	Event GameEvent;
								//pacman i duchy
	Pacman* pacman;
	Ghost* ghost1;
	Ghost* ghost2;
	Ghost* ghost3;
	Ghost* ghost4;
								//Timery
	//short unsigned int duration;
	short unsigned int EnergizerDuration; 
	bool energBool;
	bool RoundStart;
	bool Pauza;
	short unsigned int RoundStartTimer,RoundStartDuration;

	//duchy
	short unsigned int bluchange, redchange, yellowchange;

	//Text
	sf::Font MyFont;

	sf::Text PointsTXT;
	sf::Text EndTXT;
	sf::Text PauseTXT;
	sf::Text Title;
	sf::Text LevelTXT;
	sf::Text LifesTXT;
	sf::Text PoziomTrudnosciTXT;
	sf::Text PoziomTrudnosciTypeTXT;
	sf::Text StartRoundTXT;
	//Textury itp
		//logo
	sf::Texture LogoTexture;
	sf::Sprite LogoSprite;

	Texture LifeTexture;
	Sprite LifeSprite;

	Texture BorderTexture;
	Sprite BorderSprite;

	Texture LineTexture;
	Sprite LineSprite;

	//Mapa
	Mapa* GameMap;
	void initMap(int difficultiLevel);
							//funkcje ktore wywoluja sie w konstrktorze 
	void initVariables();
	void initWindow();
							//finckje od ustawienia postaci
	void initPacman();
	void initGhost();
							//funkcje od kolizji
	void PacmanColision(int x, int y);
	void GhostColision(Ghost* ghost1, int x, int y);
public:
	Game(int difficultiLevel);
	~Game();

	//funkcje ogólne
	void DrawWindow();
	void Update();
	bool running();
	void pollEvents();
	void DisplayEndScreen();
	void RestartLevel();
	void ManageMenu();
	void ChangePause();

	//funckje od kolizji i poruszania sie
	void RestarPositions();
	void Teleport();
	void AddonColision(int y,int x);
	void TrapColision(int y, int x);
	void UpdateColission();
	void GhostsMovmentUpdate(Ghost* duch);

	//funkcje od poruszania sie
	void GhostDirectionUpdate(char kolor, Ghost* duch, const Vector2f rog, const Vector2f Spawn, const Vector2f Respawn, const Vector2f TargetPosiion);
	void GhostUpdate(Ghost* ghost1, Vector2f& g1_pos, const Vector2f target_pos);
	void GhostUpdateNoDors(Ghost* ghost1, Vector2f& g1_pos, const Vector2f target_pos);
	void GhostUpdateNoColission(Ghost* ghost1, Vector2f& g1_pos, const Vector2f target_pos);
	void PacmanMovmentUpdate(Pacman* pacman,Vector2f& Pacman_pos);
	void GhostsEnergizerReverse();
	Vector2f CalculateOpositePacman();
	//AI duchów
	bool YellowGhostAI();
	bool GreenGhostAI();
	bool BlueGhostAI();
	bool PurpleGhostAI();
};
