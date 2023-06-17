#include "Game.h"

//destruktor i konstruktor i funkcje od inicjalizacji
Game::Game(int difficultiLevel)
{
	PoziomTrudnosci = difficultiLevel;
	initVariables();
	initMap(difficultiLevel);
	initPacman();
	initGhost();
	initWindow();
}

Game::~Game()
{
	delete window;
	delete pacman;
	delete ghost1;
	delete ghost2;
	delete ghost3;
	delete ghost4;
	delete GameMap;
}

void Game::initMap(int difficultiLevel)
{
	GameMap = new Mapa(difficultiLevel); ///poziom trunodsi i timery dziur
}

void Game::initVariables()
{
	//GameTitle
	if (!LogoTexture.loadFromFile("Textures/MainMenu/logo.png"))
	{
		cout << "ERROR-TMP blad wczytania tekstury loga mapy w game.cpp" << endl;
	}
	LogoSprite.setTexture(LogoTexture);
	LogoSprite.setScale(5.5f, 5.5f);
	LogoSprite.setPosition(1210, 0);
	//Text
	MyFont.loadFromFile("fonts/Minecraft.ttf");

	PointsTXT.setFont(MyFont);
	PointsTXT.setCharacterSize(33);
	PointsTXT.setFillColor(sf::Color::White);
	PointsTXT.setPosition(1350, 420);
	PointsTXT.setOutlineColor(sf::Color::Black);
	PointsTXT.setOutlineThickness(5);

	LevelTXT.setFont(MyFont);
	LevelTXT.setCharacterSize(33);
	LevelTXT.setFillColor(sf::Color::White);
	LevelTXT.setPosition(1350, 530);
	LevelTXT.setOutlineColor(sf::Color::Black);
	LevelTXT.setOutlineThickness(5);

	LifesTXT.setFont(MyFont);
	LifesTXT.setCharacterSize(33);
	LifesTXT.setFillColor(sf::Color::White);
	LifesTXT.setPosition(1350, 640);
	LifesTXT.setOutlineColor(sf::Color::Black);
	LifesTXT.setOutlineThickness(5);

	PoziomTrudnosciTXT.setFont(MyFont);
	PoziomTrudnosciTXT.setCharacterSize(33);
	PoziomTrudnosciTXT.setFillColor(sf::Color::White);
	PoziomTrudnosciTXT.setPosition(1350, 750);
	PoziomTrudnosciTXT.setOutlineColor(sf::Color::Black);
	PoziomTrudnosciTXT.setOutlineThickness(5);
	PoziomTrudnosciTXT.setString("Poziom Trudnosci: ");

	
	PoziomTrudnosciTypeTXT.setFont(MyFont);
	PoziomTrudnosciTypeTXT.setCharacterSize(33);
	PoziomTrudnosciTypeTXT.setPosition(1670, 750);
	PoziomTrudnosciTypeTXT.setOutlineColor(sf::Color::Black);
	PoziomTrudnosciTypeTXT.setOutlineThickness(5);

	StartRoundTXT.setFont(MyFont);
    StartRoundTXT.setCharacterSize(90);
	StartRoundTXT.setFillColor(sf::Color::Red);
	StartRoundTXT.setPosition(160, 400);
	StartRoundTXT.setOutlineColor(sf::Color::Black);
	StartRoundTXT.setOutlineThickness(8);
	switch (PoziomTrudnosci)
	{
	case 1: {
		PoziomTrudnosciTypeTXT.setString("Easy");
		PoziomTrudnosciTypeTXT.setFillColor(sf::Color::Green);
		break;
	}
	case 2: {
		PoziomTrudnosciTypeTXT.setString("Normal");
		PoziomTrudnosciTypeTXT.setFillColor(sf::Color::Yellow);
		break;
	}
	case 3: {
		PoziomTrudnosciTypeTXT.setString("Hard");
		PoziomTrudnosciTypeTXT.setFillColor(sf::Color::Red);
		break;
	}
	default:
		break;
	}


	EndTXT.setFont(MyFont);
	EndTXT.setCharacterSize(90);
	EndTXT.setFillColor(sf::Color::Red);
	EndTXT.setPosition(400, 400);
	EndTXT.setOutlineColor(sf::Color::Black);
	EndTXT.setOutlineThickness(8);

	PauseTXT.setFont(MyFont);
	PauseTXT.setCharacterSize(90);
	PauseTXT.setFillColor(sf::Color::Red);
	PauseTXT.setPosition(100, 300);
	PauseTXT.setString("           PAUZA\n Nacisnij ponownie 'P'\n   aby wznowic gre ");
	PauseTXT.setOutlineColor(sf::Color::Black);
	PauseTXT.setOutlineThickness(8);

	Title.setFont(MyFont);
	Title.setCharacterSize(35);
	Title.setFillColor(sf::Color::White);
	Title.setPosition(1350, 300);
	Title.setString("Statystyki Rozgrywki");
	Title.setOutlineColor(sf::Color::Black);
	Title.setOutlineThickness(6);

	//tekstury etc
	if (!LifeTexture.loadFromFile("Textures/life.png")) {
		cout << "ERROR-TMP blad wczytania tekstury zycia game.cpp" << endl;
	}
	LifeSprite.setTexture(LifeTexture);
	LifeSprite.setScale(0.5f, 0.5f);

	if (!BorderTexture.loadFromFile("Textures/border2.png")) {
		cout << "ERROR-TMP blad wczytania tekstury border game.cpp" << endl;
	}
	BorderSprite.setTexture(BorderTexture);
	BorderSprite.setScale(1.5f, 1.5f);
	BorderSprite.setPosition(1220, 925);
	BorderSprite.setRotation(-90);

	if (!LineTexture.loadFromFile("Textures/line.png")) {
		cout << "ERROR-TMP blad wczytania tekstury line game.cpp" << endl;
	}
	LineSprite.setTexture(LineTexture);
	LineSprite.setScale(1.3f, 1.6f);
	LineSprite.setPosition(1050, 0);
	//zmienne
	EndGame = 0;
	Gamepoints = 0;
	Lifes = 4;
	level = 1;
	Pauza = false;
	//ustawienie wartosci timerow
	EnergizerDuration = 200; energBool = false;
	RoundStartDuration = 0; RoundStartTimer = 230; RoundStart = false;
}
void Game::ChangePause() {
	if (Pauza)Pauza = 0;
	else Pauza = 1;
}
void Game::initWindow()
{
	videoMode=  VideoMode::getDesktopMode();
	sf::Vector2u windowSize(videoMode.width, videoMode.height);
	window = new RenderWindow(sf::VideoMode(windowSize.x, windowSize.y), "Okno SFML", sf::Style::Fullscreen);
	window->setFramerateLimit(60);
}

void Game::initPacman()
{
	pacman = new Pacman();
	pacman->SetPosition(GameMap->GetPacmanPosition().x, GameMap->GetPacmanPosition().y);
	pacman->lastposition = GameMap->GetPacmanPosition();
}

void Game::initGhost()
{
	ghost1 = new Ghost("Textures/zoombie.png",2.f, 'A',280);
	ghost2 = new Ghost("Textures/skeleton.jpg",2.f, 'D',180); 
	ghost3 = new Ghost("Textures/creeper.jpg",2.f, 'A',250);
	ghost4 = new Ghost("Textures/blaze.png",1.f, 'D', 400);

	//ustawienia pacmana na odpowiednim polu
	ghost1->lastposition = GameMap->GetGhostPosition('Y');
	ghost2->lastposition = GameMap->GetGhostPosition('G');
	ghost3->lastposition = GameMap->GetGhostPosition('B');
	ghost4->lastposition = GameMap->GetGhostPosition('P');

	ghost1->SetPosition(ghost1->lastposition.x, ghost1->lastposition.y);
	ghost2->SetPosition(ghost2->lastposition.x, ghost2->lastposition.y);
	ghost3->SetPosition(ghost3->lastposition.x, ghost3->lastposition.y);
	ghost4->SetPosition(ghost4->lastposition.x, ghost4->lastposition.y);
}

//Draw window, event, Checkend running DisplayEndScreen
void Game::DisplayEndScreen() {
	pacman->SetPosition(pacman->Getsprite().getPosition().x, pacman->Getsprite().getPosition().y);
	pacman->DrawPacman(*window);
	pollEvents();
	EndTXT.setString("      KONIEC GRY\nZdobyles: " + std::to_string(Gamepoints) + " Punktow\n         Poziom: " + std::to_string(level));
	window->draw(EndTXT);
}
void Game::DrawWindow()
{
	// wyczysc
	window->clear();
	if(!EndGame){
		//rysuj mape i pacmana
		GameMap->DrawMap(*window,Pauza);
		pacman->DrawPacman(*window);
		//duchy
		ghost1->Drawghost(*window);
		ghost2->Drawghost(*window);
		ghost3->Drawghost(*window);
		ghost4->Drawghost(*window);
		//wyswietl tekst
		ManageMenu();
		if(Pauza) window->draw(PauseTXT);
		if (!RoundStart) {
				StartRoundTXT.setString("Rozpoczecie za: " + std::to_string((RoundStartTimer-RoundStartDuration) / 60));
				window->draw(StartRoundTXT);
		}
	}
	else {
		DisplayEndScreen();
	}
	//wyswietl okno
	window->display();
}
void Game::ManageMenu() {
	//linia
	window->draw(LineSprite);
	//ramka
	window->draw(BorderSprite);
	//ramka teksty
	window->draw(Title);
	window->draw(LogoSprite);
	//ustawienia tekstu od punktow
	PointsTXT.setString("Punkty:  " + std::to_string(Gamepoints));
	LevelTXT.setString("Poziom:  " + std::to_string(level));
	window->draw(PointsTXT); // Wyœwietl tekst na ekranie
	window->draw(LevelTXT);
	window->draw(PoziomTrudnosciTXT);
	window->draw(PoziomTrudnosciTypeTXT);
	// wypisz zycia
	LifesTXT.setString("Zycia: ");
	window->draw(LifesTXT);
	for (int i = 0; i < Lifes; i++) {
		LifeSprite.setPosition(1470 + i * 65, 630);
		window->draw(LifeSprite);
	}
}
bool Game::running()
{

	if (Lifes <= 0)EndGame=1;
	else if(GameMap->liczbapunktow == 0)RestartLevel();
	if (window->isOpen())return true;
	else return false;
}

void Game::RestartLevel() {
	//restart puntków na mapie
	GameMap->ResetMap();
	//ustawienia pacmana na odpowiednim polu
	ghost1->ResetGhost('A');
	ghost2->ResetGhost('D');
	ghost3->ResetGhost('A');
	ghost4->ResetGhost('D');

	ghost1->lastposition = GameMap->GetGhostPosition('Y');
	ghost2->lastposition = GameMap->GetGhostPosition('G');
	ghost3->lastposition = GameMap->GetGhostPosition('B');
	ghost4->lastposition = GameMap->GetGhostPosition('P');

	pacman->SetPosition(GameMap->GetPacmanPosition().x, GameMap->GetPacmanPosition().y);
	pacman->lastposition = GameMap->GetPacmanPosition();

	ghost1->SetPosition(ghost1->lastposition.x, ghost1->lastposition.y);
	ghost2->SetPosition(ghost2->lastposition.x, ghost2->lastposition.y);
	ghost3->SetPosition(ghost3->lastposition.x, ghost3->lastposition.y);
	ghost4->SetPosition(ghost4->lastposition.x, ghost4->lastposition.y);
	//inne
	Lifes = 4;
	level++;
	Pauza = false;
	//ustawienie wartosci timerow
	EnergizerDuration = 200; energBool = false; 
	RoundStartDuration = 0; RoundStart = false;
}
void Game::pollEvents()
{
	while (window->pollEvent(GameEvent)) {
		//jak event to zrob cos ( event loop )
		switch (GameEvent.type)
		{
		case Event::Closed: {
			window->close();
			break;
		}
		case Event::KeyPressed: {
			if (GameEvent.key.code == Keyboard::Escape) {
				window->close();
			}
			if (GameEvent.key.code == Keyboard::P) {
				ChangePause();
			}
		}

		}
	}


}

/// update

void Game::Update()
{
	pollEvents();
	if (RoundStart) {
		if (!EndGame and !Pauza) {
			//ruchy postaci i kolizja pacmana z map¹
			PacmanMovmentUpdate(pacman, pacman->lastposition);//pacman->Update();
			UpdateColission();
			//ruchy duchow
			if (YellowGhostAI())return;
			if (GreenGhostAI())return;
			if (BlueGhostAI())return;
			if (PurpleGhostAI())return;
		}
	}
	else {
		if (RoundStartDuration == RoundStartTimer) { RoundStartDuration = 0; RoundStart = true; }
		else RoundStartDuration++;
	}
}

void Game::UpdateColission()
{
	for (int y = 0; y < Map_wysokosc; y++) {
		for (int x = 0; x < Map_szerokosc; x++) {
			//kolizje postaci ducha i pacmana
			PacmanColision(x, y);
			AddonColision(y, x);
			TrapColision(y, x);
		}
	}
	Teleport();
}

/// kolizje

void Game::Teleport()
{
	//teleport dla pacmana 
	if (pacman->Getsprite().getPosition().x > 1060 && pacman->Getsprite().getPosition().y == 450) {
		pacman->SetPosition(-50, 450);
		pacman->lastposition.x = pacman->Getsprite().getPosition().x;
		pacman->lastposition.y = pacman->Getsprite().getPosition().y;
	}
	else if (pacman->Getsprite().getPosition().x < -50 && pacman->Getsprite().getPosition().y == 450) {
		pacman->SetPosition(1050, 450);
		pacman->lastposition.x = pacman->Getsprite().getPosition().x;
		pacman->lastposition.y = pacman->Getsprite().getPosition().y;
	}
	//teleport dla ducha1
	if (ghost1->Getsprite().getPosition().x > 1050 && ghost1->Getsprite().getPosition().y == 450) {
		ghost1->SetPosition(-50, 450);
		ghost1->lastposition.x = ghost1->Getsprite().getPosition().x;
		ghost1->lastposition.y = ghost1->Getsprite().getPosition().y;
	}
	else if (ghost1->Getsprite().getPosition().x < -50 && ghost1->Getsprite().getPosition().y == 450) {
		ghost1->SetPosition(1050, 450);
		ghost1->lastposition.x = ghost1->Getsprite().getPosition().x;
		ghost1->lastposition.y = ghost1->Getsprite().getPosition().y;
	}
	//teleport dla ducha2
	if (ghost2->Getsprite().getPosition().x > 1050 && ghost2->Getsprite().getPosition().y == 450) {
		ghost2->SetPosition(-50, 450);
		ghost2->lastposition.x = ghost2->Getsprite().getPosition().x;
		ghost2->lastposition.y = ghost2->Getsprite().getPosition().y;
	}
	else if (ghost2->Getsprite().getPosition().x < -50) {
		ghost2->SetPosition(1050, 450);
		ghost2->lastposition.x = ghost2->Getsprite().getPosition().x;
		ghost2->lastposition.y = ghost2->Getsprite().getPosition().y;
	}
	//teleport dla ducha3
	if (ghost3->Getsprite().getPosition().x > 1050 && ghost3->Getsprite().getPosition().y == 450) {
		ghost3->SetPosition(-50, 450);
		ghost3->lastposition.x = ghost3->Getsprite().getPosition().x;
		ghost3->lastposition.y = ghost3->Getsprite().getPosition().y;
	}
	else if (ghost3->Getsprite().getPosition().x < -50) {
		ghost3->SetPosition(1050, 450);
		ghost3->lastposition.x = ghost3->Getsprite().getPosition().x;
		ghost3->lastposition.y = ghost3->Getsprite().getPosition().y;
	}
	//teleport dla ducha4
	if (ghost4->Getsprite().getPosition().x > 1050 && ghost4->Getsprite().getPosition().y == 450) {
		ghost4->SetPosition(-50, 450);
		ghost4->lastposition.x = ghost4->Getsprite().getPosition().x;
		ghost4->lastposition.y = ghost4->Getsprite().getPosition().y;
	}
	else if (ghost4->Getsprite().getPosition().x < -50) {
		ghost4->SetPosition(1050, 450);
		ghost4->lastposition.x = ghost4->Getsprite().getPosition().x;
		ghost4->lastposition.y = ghost4->Getsprite().getPosition().y;
	}
}

void Game::AddonColision(int y, int x)
{
	//colision with corn
	if (!GameMap->MapaCorn.empty() && GameMap->MapaCorn[y][x].getGlobalBounds().intersects(pacman->Getsprite().getGlobalBounds())) {
		if (GameMap->SzkicMapy[y][x] == 'E') {
			Gamepoints += 50;
			pacman->SetProtection(1);
			GhostsEnergizerReverse();	
		}
		else if (GameMap->SzkicMapy[y][x] == 'B' and GameMap->GetEnergizerBool()) {
			Gamepoints += 1500;
			GameMap->ResetBonus();
			
		}
		else if (GameMap->SzkicMapy[y][x] == 'H' and GameMap->GetProtectionBool()) {
			Gamepoints += 100;
			pacman->SetProtection(1);
			GameMap->ResetShield();
		}
		else if (GameMap->SzkicMapy[y][x] == 'K' and GameMap->GetSpeedBool()) {
			pacman->SpeedRun = true;
			GameMap->ResetBoost();
		}
		else if (GameMap->SzkicMapy[y][x] == '.' or GameMap->SzkicMapy[y][x] == '?') {
			Gamepoints += 10;
			GameMap->liczbapunktow--;

		}
		//usuniecie 
		CircleShape c1;
		c1.setRadius(1);
		GameMap->MapaCorn[y][x] = c1;
	}
}

void Game::TrapColision(int y, int x) {
	if (GameMap->MapaSprite[y][x].getGlobalBounds().intersects(pacman->Getsprite().getGlobalBounds()) and GameMap->SzkicMapy[y][x] == 'X') {
			int type = 0;
			int i = 0;
			for (auto it : GameMap->wybranedziuryPOS) { //sprawdzanie typu dziury
				if ((it.x/50) == x and (it.y/50) == y) {
					type = GameMap->wybranedziuryTYP[i];
				}
				i++;
			}
			// konsekwencje spotkania z typem dziury
			if (type == 1) {
				RestarPositions();
			}
			else if (type == 2) {//lod
				pacman->SpeedLod = true;
			}
			else
			if (type == 3) {//lepkie
				pacman->SpeedSlow = true;
			}
	}
}

// ruchy postaci wszystkich
	//wszystkie postacie
void Game::RestarPositions() {
	RoundStartDuration = 0; RoundStart = false;
	if (--Lifes) {
		//pacman
		Pauza = false;
		pacman->Restart(GameMap->GetPacmanPosition());
		//etc
		pacman->Setdirection('g');
		pacman->SetMovetype("normal");
		///ghost1
		ghost1->ResetGhost('A');
		ghost1->Setdirection('g');
		ghost1->lastposition = GameMap->GetGhostPosition('Y');
		ghost1->SetPosition(ghost1->lastposition.x - 50.f, ghost1->lastposition.y);
		///ghost2
		ghost2->ResetGhost('D');
		ghost2->Setdirection('g');
		ghost2->lastposition = GameMap->GetGhostPosition('G');
		ghost2->SetPosition(ghost2->lastposition.x + 50.f, ghost2->lastposition.y);
		///ghost3
		ghost3->ResetGhost('A');
		ghost3->Setdirection('g');
		ghost3->lastposition = GameMap->GetGhostPosition('B');
		ghost3->SetPosition(ghost3->lastposition.x - 50.f, ghost3->lastposition.y);
		///ghost4
		ghost4->ResetGhost('D');
		ghost4->Setdirection('g');
		ghost4->lastposition = GameMap->GetGhostPosition('P');
		ghost4->SetPosition(ghost4->lastposition.x + 50.f, ghost4->lastposition.y);
		GameMap->ResetMapNextRound();
	}
}

	//duchy
void Game::GhostsMovmentUpdate(Ghost* duch) {
	if (duch->energBool and !duch->GhostKilledBool and !duch->again) {
		if ((fmod(duch->Getsprite().getPosition().x, 50) == 0 && fmod(duch->Getsprite().getPosition().y, 50) == 0) || duch->movmentrun1) {
			duch->Update("slow");
			duch->movmentrun1 = true;
		}
		else {

			duch->Update("normal");
			duch->movmentrun1 = false;
		}
	}
	else if (duch->GhostKilledBool) {
		if ((fmod(duch->Getsprite().getPosition().x, 50) < 1 && fmod(duch->Getsprite().getPosition().y, 50) < 1) || duch->movmentrun1) {
			duch->Update("run");
			duch->movmentrun1 = true;
		}
		else {

			duch->Update("normal");
			duch->movmentrun1 = false;
		}
	}
	else {
		duch->Update("normal");
		duch->movmentrun1 = false;
		duch->movmentrun2 = false;
	}
}
void Game::GhostDirectionUpdate(char kolor,Ghost* duch, const Vector2f rog,const Vector2f Spawn, const Vector2f Respawn, const Vector2f TargetPosiion)
{
	//start rundy i poczatkowy stater mode
	if (duch->again) {
		if (!duch->RespawnBool) {
			duch->duration++;
			if (duch->duration == duch->RespawnTime) {
				duch->duration = 0;
				duch->RespawnBool = true;
			}
			return;
		}
		if (duch->lastposition == Respawn) {
			duch->again = false;
			duch->duration = 0;
			duch->RespawnBool = false;
			duch->energBool = false;
			return;
		}
		if (duch->reversbo) {
			duch->setPos(Spawn);
			duch->lastposition.x = duch->lastposition.x - 50;
			duch->reversbo = false;
		}
		GhostUpdateNoDors(duch, duch->lastposition, Respawn);
		return;
	}
	if (duch->energBool) {
		if (duch->energizerDur == EnergizerDuration) {
			duch->ReseTGhostNoKilled();
			return;

		}

		if (duch->odliczaj) {
			duch->energizerDur++;
		}
		if (kolor != 'P')GhostUpdate(duch, duch->lastposition, CalculateOpositePacman());
		else GhostUpdateNoColission(duch, duch->lastposition, CalculateOpositePacman());
		return;
	}
	if (duch->duration == duch->ScatterTime) {
		duch->duration = 0;
		duch->ScatterBool = false;
	}
	if (duch->ScatterBool) {
		if (kolor == 'P')GhostUpdateNoColission(duch, duch->lastposition, rog);
		else GhostUpdate(duch, duch->lastposition, rog);
		duch->duration++;
		return;
	}
	if (duch->GhostKilledBool) {
		if (duch->lastposition == Spawn) {
			duch->setPos(Spawn);
			duch->duration = 0;
			duch->again = true;			
			duch->GhostKilledBool = false;
			duch->reversbo = true;
			duch->RespawnBool = false;
			duch->energBool = false;
			return; 
		}

		if (duch->lastposition != Spawn) { 
			 GhostUpdateNoDors(duch, duch->lastposition, Spawn);
		}
		 return;
	}
	if(kolor!='P')GhostUpdate(duch, duch->lastposition, TargetPosiion);
	else GhostUpdateNoColission(duch, duch->lastposition, TargetPosiion);
}

void Game::GhostUpdateNoDors(Ghost* ghost1, Vector2f& g1_pos, const Vector2f target_pos) {
	char NewDirection = 'g';
	char sNewDirection = 'g';
	double shortestDistance = 0;
	int x = 1; int y = 1; bool ruch = false;
	//sprawdz czy ghost poruszyl sie o jedno pole (50px)
	if (abs(g1_pos.x - static_cast<int>(ghost1->Getsprite().getPosition().x)) == 50 or abs(g1_pos.y - static_cast<int>(ghost1->Getsprite().getPosition().y)) == 50) {
		x = static_cast<int>(ghost1->Getsprite().getPosition().x / 50);
		y = static_cast<int>(ghost1->Getsprite().getPosition().y / 50);
		ruch = true;
		g1_pos.x = x * 50;
		g1_pos.y = y * 50;
	}
	if (ruch && g1_pos.x > 0 && g1_pos.x < 1000) { // jest ghost moze zmienic ruch i nie jest na krawedzi teleportu
		if (GameMap->MapaSprite[y][x + 1].getTexture() != GameMap->Getwall().getTexture() && ghost1->Getdirection() != 'A') {
			double vect = sqrt(pow(2, abs(x + 1 - target_pos.x / 50)) + pow(2, abs(y - target_pos.y / 50)));
			if (shortestDistance == 0 || vect < shortestDistance) {
				shortestDistance = vect;
				sNewDirection = NewDirection;
				NewDirection = 'D';
			}
		}
		if (GameMap->MapaSprite[y][x - 1].getTexture() != GameMap->Getwall().getTexture() && ghost1->Getdirection() != 'D') {
			double vect = sqrt(pow(2, abs(x - 1 - target_pos.x / 50)) + pow(2, abs(y - target_pos.y / 50)));
			if (shortestDistance == 0 || vect < shortestDistance) {
				shortestDistance = vect;
				sNewDirection = NewDirection;
				NewDirection = 'A';
			}
		}
		if (GameMap->MapaSprite[y + 1][x].getTexture() != GameMap->Getwall().getTexture() && ghost1->Getdirection() != 'W') {
			double vect = sqrt(pow(2, abs(x - target_pos.x / 50)) + pow(2, abs(y + 1 - target_pos.y / 50)));

			if (shortestDistance == 0 || vect < shortestDistance) {
				shortestDistance = vect;
				sNewDirection = NewDirection;
				NewDirection = 'S';
			}
		}
		if (GameMap->MapaSprite[y - 1][x].getTexture() != GameMap->Getwall().getTexture() && ghost1->Getdirection() != 'S') {
			double vect = sqrt(pow(2, abs(x - target_pos.x / 50)) + pow(2, abs(y - 1 - target_pos.y / 50)));

			if (shortestDistance == 0 || vect < shortestDistance) {
				shortestDistance = vect;
				NewDirection = 'W';
			}
		}
		if (GameMap->SzkicMapy[y][x] == '?') { ghost1->Setdirection(NewDirection); ruch = false; }
	}
}

void Game::GhostUpdateNoColission(Ghost* ghost1, Vector2f& g1_pos, const Vector2f target_pos) {
	char NewDirection = 'g';
	char sNewDirection = 'g';
	double shortestDistance = 0;
	int x = 1; int y = 1; bool ruch = false;
	//sprawdz czy ghost poruszyl sie o jedno pole (50px)
	if (abs(g1_pos.x - static_cast<int>(ghost1->Getsprite().getPosition().x)) == 50 or abs(g1_pos.y - static_cast<int>(ghost1->Getsprite().getPosition().y)) == 50) {
		x = static_cast<int>(ghost1->Getsprite().getPosition().x / 50);
		y = static_cast<int>(ghost1->Getsprite().getPosition().y / 50);
		ruch = true;
		g1_pos.x = x * 50;
		g1_pos.y = y * 50;
	}
	else {
		x = g1_pos.x / 50;
		y = g1_pos.y / 50;
	}
	if (ruch && g1_pos.x > 0 && g1_pos.x < 1000) { // jest ghost moze zmienic ruch i nie jest na krawedzi teleportu
		double vect = sqrt(pow(2, abs(x + 1 - target_pos.x / 50)) + pow(2, abs(y - target_pos.y / 50)));
		if (shortestDistance == 0 || vect < shortestDistance) {
			shortestDistance = vect;
			sNewDirection = NewDirection;
			NewDirection = 'D';
		}
		{			double vect = sqrt(pow(2, abs(x - 1 - target_pos.x / 50)) + pow(2, abs(y - target_pos.y / 50)));
		if (shortestDistance == 0 || vect < shortestDistance) {
			shortestDistance = vect;
			sNewDirection = NewDirection;
			NewDirection = 'A';
		}
		 vect = sqrt(pow(2, abs(x - target_pos.x / 50)) + pow(2, abs(y + 1 - target_pos.y / 50)));

		if (shortestDistance == 0 || vect < shortestDistance) {
			shortestDistance = vect;
			sNewDirection = NewDirection;
			NewDirection = 'S';
		}
		 vect = sqrt(pow(2, abs(x - target_pos.x / 50)) + pow(2, abs(y - 1 - target_pos.y / 50)));

		if (shortestDistance == 0 || vect < shortestDistance) {
			shortestDistance = vect;
			NewDirection = 'W';
		}
		 ghost1->Setdirection(NewDirection);
		 ruch = false; 
		}
	}
}
void Game::GhostUpdate(Ghost* ghost, Vector2f& g1_pos, const Vector2f target_pos) {
	char NewDirection = 'g';
	char sNewDirection = 'g';
	double shortestDistance = 0;
	int x = 1; int y = 1; bool ruch = false;
	//sprawdz czy ghost poruszyl sie o jedno pole (50px)
	if (abs(g1_pos.x - static_cast<int>(ghost->Getsprite().getPosition().x)) == 50 or abs(g1_pos.y - static_cast<int>(ghost->Getsprite().getPosition().y)) == 50) {
		x = static_cast<int>(ghost->Getsprite().getPosition().x / 50);
		y = static_cast<int>(ghost->Getsprite().getPosition().y / 50);
		ruch = true;
		g1_pos.x = x * 50;
		g1_pos.y = y * 50;
		if (ghost->timeBool) {
			ghost->odliczaj = true;
		}
	}
	else {
		x = g1_pos.x / 50;
		y = g1_pos.y / 50;
	}
	if (ruch && g1_pos.x > 0 && g1_pos.x < 1000) { // jest ghost moze zmienic ruch i nie jest na krawedzi teleportu
		if (GameMap->MapaSprite[y][x + 1].getTexture() != GameMap->Getwall().getTexture() && GameMap->MapaSprite[y][x + 1].getTexture() != GameMap->Getdoor().getTexture()) {
			if (ghost->Getdirection() != 'A' or ghost->timeBool) {
				double vect = sqrt(pow(2, abs(x + 1 - target_pos.x / 50)) + pow(2, abs(y - target_pos.y / 50)));
				if (shortestDistance == 0 || vect < shortestDistance) {
					shortestDistance = vect;
					sNewDirection = NewDirection;
					NewDirection = 'D';
				}
			}
		}
		if (GameMap->MapaSprite[y][x - 1].getTexture() != GameMap->Getwall().getTexture() && GameMap->MapaSprite[y][x - 1].getTexture() != GameMap->Getdoor().getTexture()){
			if (ghost->Getdirection() != 'D' or ghost->timeBool) {
				double vect = sqrt(pow(2, abs(x - 1 - target_pos.x / 50)) + pow(2, abs(y - target_pos.y / 50)));
				if (shortestDistance == 0 || vect < shortestDistance) {
					shortestDistance = vect;
					sNewDirection = NewDirection;
					NewDirection = 'A';
				}
			}
		}
		if (GameMap->MapaSprite[y + 1][x].getTexture() != GameMap->Getwall().getTexture() && GameMap->MapaSprite[y+1][x].getTexture() != GameMap->Getdoor().getTexture()) {
			if (ghost->Getdirection() != 'W' or ghost->timeBool) {
				double vect = sqrt(pow(2, abs(x - target_pos.x / 50)) + pow(2, abs(y + 1 - target_pos.y / 50)));
				if (shortestDistance == 0 || vect < shortestDistance) {
					shortestDistance = vect;
					sNewDirection = NewDirection;
					NewDirection = 'S';
				}
			}
		}
		if (GameMap->MapaSprite[y - 1][x].getTexture() != GameMap->Getwall().getTexture() && GameMap->MapaSprite[y-1][x].getTexture() != GameMap->Getdoor().getTexture()) {
			if (ghost->Getdirection() != 'S' or ghost->timeBool) {
				double vect = sqrt(pow(2, abs(x - target_pos.x / 50)) + pow(2, abs(y - 1 - target_pos.y / 50)));
				if (shortestDistance == 0 || vect < shortestDistance) {
					shortestDistance = vect;
					NewDirection = 'W';
				}
			}
		}
		if (GameMap->SzkicMapy[y][x] == '?' and !ghost->timeBool) { ghost->Setdirection(NewDirection); ruch = false; }
		if (ghost->timeBool) { ghost->timeBool = false; ghost->Setdirection(NewDirection); ruch = false; }
	}
}

void Game::GhostColision(Ghost* ghost1, int x, int y)
{
	if (GameMap->MapaSprite[y][x].getGlobalBounds().intersects(ghost1->Getsprite().getGlobalBounds()) && GameMap->MapaSprite[y][x].getTexture() == GameMap->Getwall().getTexture()) {
		switch (ghost1->Getdirection()) {
		case 'A': {
			if (GameMap->MapaSprite[y][x].getPosition().x < ghost1->Getsprite().getPosition().x) {
				ghost1->Setdirection('D');
				ghost1->Move("normal");
				ghost1->Setdirection('g');
			}
		}
		case 'D': {
			if (GameMap->MapaSprite[y][x].getPosition().x > ghost1->Getsprite().getPosition().x) {
				ghost1->Setdirection('A');
				ghost1->Move("normal");
				ghost1->Setdirection('g');
			}
		}
		case 'W': {
			if (GameMap->MapaSprite[y][x].getPosition().y < ghost1->Getsprite().getPosition().y) {
				ghost1->Setdirection('S');
				ghost1->Move("normal");
				ghost1->Setdirection('g');
			}
		}
		case 'S': {
			if (GameMap->MapaSprite[y][x].getPosition().y > ghost1->Getsprite().getPosition().y) {
				ghost1->Setdirection('W');
				ghost1->Move("normal");
				ghost1->Setdirection('g');
			}
		}
		}
	}
}

	//pacman
void Game::PacmanColision(int x, int y)
{
	if (GameMap->MapaSprite[y][x].getGlobalBounds().intersects(pacman->Getsprite().getGlobalBounds()) && GameMap->MapaSprite[y][x].getTexture() == GameMap->Getwall().getTexture()) {
		switch (pacman->Getdirection()) {
		case 'A': {
			if (GameMap->MapaSprite[y][x].getPosition().x < pacman->Getsprite().getPosition().x) {
				pacman->Setdirection('D');
				pacman->Move();
				pacman->Setdirection('g');
			}
			return;
		}
		case 'D': {
			if (GameMap->MapaSprite[y][x].getPosition().x > pacman->Getsprite().getPosition().x) {
				pacman->Setdirection('A');
				pacman->Move();
				pacman->Setdirection('g');
			}
			return;
		}
		case 'W': {
			if (GameMap->MapaSprite[y][x].getPosition().y < pacman->Getsprite().getPosition().y) {
				pacman->Setdirection('S');
				pacman->Move();
				pacman->Setdirection('g');
			}
			return;
		}
		case 'S': {
			if (GameMap->MapaSprite[y][x].getPosition().y > pacman->Getsprite().getPosition().y) {
				pacman->Setdirection('W');
				pacman->Move();
				pacman->Setdirection('g');
			}
			return;
		}
		}
	}
}

void Game::PacmanMovmentUpdate(Pacman* pacman1,Vector2f& Pacman_pos)
{
	pacman->UpdateProtection();
	///setup
	char NewDirection= pacman1->Getdirection();
	int x = 1; int y = 1; bool ruch = false; bool czyruszam = true;
	//czy polozenie zmienilo sie o pelny blok ?
	if (abs(Pacman_pos.x - static_cast<int>(pacman1->Getsprite().getPosition().x ))==50 or abs(Pacman_pos.y - static_cast<int>(pacman1->Getsprite().getPosition().y )) == 50) {
		 x = static_cast<int>(pacman1->Getsprite().getPosition().x / 50.0);
		 y = static_cast<int>(pacman1->Getsprite().getPosition().y / 50.0);
		 ruch = true;
		 czyruszam = false;
		 Pacman_pos.x = x*50.0;
		 Pacman_pos.y = y*50.0;
		 //run
		 if (pacman1->SpeedRun and !pacman1->odliczajrun) {
			 pacman1->odliczajrun = true;
		 }
		 if (pacman1->durationRun == pacman1->GettimerRun()) {
			 pacman1->SetPosition(pacman1->lastposition);
			 pacman1->odliczajrun = false;
			 pacman1->SpeedRun = false;
			 pacman1->durationRun = 0;
			 pacman1->SetMovetype("normal");

		 }
		 //slow
		 if (pacman1->SpeedSlow and !pacman1->odliczajslow) {
			 pacman1->odliczajslow = true;
		 }
		 if (pacman1->durationSlow == pacman1->GettimerSlow()) {
			 pacman1->SetPosition(pacman1->lastposition);
			 pacman1->odliczajslow = false;
			 pacman1->SpeedSlow = false;
			 pacman1->durationSlow = 0;
			 pacman1->SetMovetype("normal");

		 }
		 //lod
		 if (pacman1->SpeedLod and !pacman1->odliczajlod) {
			 pacman1->odliczajlod = true;
		 }
		 if (pacman1->durationlod == pacman1->GettimerLod()+1) {
			 pacman1->SetPosition(pacman1->lastposition); 
			 pacman1->odliczajlod = false;
			 pacman1->SpeedLod = false;
			 pacman1->durationlod = 0;
			 pacman1->SetMovetype("normal");
		 }
	}
	//jesli sie zablokowal to ponownie mozemy wybrac kierunek poruszania
	if (pacman1->Getdirection() == 'g') {
		pacman1->SetPosition(pacman1->lastposition);
		x = static_cast<int>(pacman1->Getsprite().getPosition().x / 50.0);
		y = static_cast<int>(pacman1->Getsprite().getPosition().y / 50.0);
		czyruszam = false;
		pacman1->Update();
	}
	//jestli nie to ruszaj tak ciagle ta sama strone
	if (czyruszam) {
		pacman1->Update2();
	}
	else if (ruch && Pacman_pos.x > 0 && Pacman_pos.x < 1000) { // inaczej zmienin kierunek na mozliwy na skrzyzowaniu 
		if (GameMap->MapaSprite[y][x + 1].getTexture() != GameMap->Getwall().getTexture() && GameMap->MapaSprite[y][x + 1].getTexture() != GameMap->Getdoor().getTexture() && pacman1->direction2=='D') {
			NewDirection = 'D';
		}
		else if (GameMap->MapaSprite[y][x - 1].getTexture() != GameMap->Getwall().getTexture() && GameMap->MapaSprite[y][x - 1].getTexture() != GameMap->Getdoor().getTexture() && pacman1->direction2 == 'A') {
			NewDirection = 'A';
		}
		else if (GameMap->MapaSprite[y + 1][x].getTexture() != GameMap->Getwall().getTexture() && GameMap->MapaSprite[y+1][x].getTexture() != GameMap->Getdoor().getTexture() && pacman1->direction2 == 'S') {
			NewDirection = 'S';
		}
		else if (GameMap->MapaSprite[y - 1][x].getTexture() != GameMap->Getwall().getTexture() && GameMap->MapaSprite[y-1][x].getTexture() != GameMap->Getdoor().getTexture() && pacman1->direction2 == 'W') {
			NewDirection = 'W';
		}
			pacman1->lastdirection = pacman1->Getdirection();
			pacman1->Setdirection(NewDirection); 
	}
	pacman1->Move();

}

///Artifical Inteligence duchów 

bool Game::YellowGhostAI() {
	//ghost1-YELLOW
	//zmiana trybu
	if (ghost1->Getsprite().getGlobalBounds().intersects(pacman->Getsprite().getGlobalBounds())) {
		if (pacman->GetProtection() and ghost1->GhostKilledBool == false) {
			if (!GameMap->CheckWall(pacman->lastdirection, pacman->lastposition)) {
				ghost1->ReseTGhostAfterKilled(pacman->lastdirection, pacman->lastposition);
			}
			else {
				if (pacman->lastdirection == 'g')  ghost1->ReseTGhostAfterKilled(GameMap->WhereCanGo(pacman->lastposition), pacman->lastposition);
				else ghost1->ReseTGhostAfterKilled(pacman->calculateOpoDirPacman(), pacman->lastposition);
			}
			pacman->BonusPoints += 100;
			Gamepoints += pacman->BonusPoints;
		}
		else if (!pacman->GetProtection() and !ghost1->GhostKilledBool) {
			RestarPositions();
			return true;
		}
	}
	if (ghost1->changeduration == ghost1->SwitchTime) {
		ghost1->changeduration = 0;
		ghost1->ScatterBool = true;
	}
	if (!ghost1->ScatterBool and !ghost1->GhostKilledBool)ghost1->changeduration++;
	//poruszanie sie
	GhostsMovmentUpdate(ghost1);
	GhostDirectionUpdate('Y',ghost1, Vector2f(0.f, 0.f), Vector2f(450.f, 450.f), Vector2f(450.f, 350.f),pacman->Getsprite().getPosition());
	return false;
}
bool Game::GreenGhostAI() {
	//ghost2-GREEN
	Vector2f target;
	switch (pacman->Getdirection())
	{
	case 'W': {
		 target= Vector2f( pacman->Getsprite().getPosition().x - 100,pacman->Getsprite().getPosition().y - 100 );
		break;
	}
	case 'A': {
		 target = Vector2f(pacman->Getsprite().getPosition().x - 100, pacman->Getsprite().getPosition().y);
		break;
	}
	case 'D': {
		 target = Vector2f(pacman->Getsprite().getPosition().x + 100, pacman->Getsprite().getPosition().y);
		break;
	}
	case 'S': {
		 target = Vector2f(pacman->Getsprite().getPosition().x, pacman->Getsprite().getPosition().y - 100);
		break;
	}
	default:
		break;
	}
	//zmiana trybu
	if (ghost2->Getsprite().getGlobalBounds().intersects(pacman->Getsprite().getGlobalBounds())) {
		if (pacman->GetProtection() and ghost2->GhostKilledBool == false) {
			if (!GameMap->CheckWall(pacman->lastdirection, pacman->lastposition)) {
				ghost2->ReseTGhostAfterKilled(pacman->lastdirection, pacman->lastposition);
			}
			else {
				if (!pacman->lastdirection == 'g')ghost2->ReseTGhostAfterKilled(GameMap->WhereCanGo(pacman->lastposition), pacman->lastposition);
				else ghost2->ReseTGhostAfterKilled(pacman->calculateOpoDirPacman(), pacman->lastposition);
			}
			pacman->BonusPoints += 100;
			Gamepoints += pacman->BonusPoints;
		}
		else if (!pacman->GetProtection() and !ghost2->GhostKilledBool) {
			RestarPositions();
			return true;
		}
	}
	if (ghost2->changeduration == ghost2->SwitchTime) {
		ghost2->changeduration = 0;
		ghost2->ScatterBool = true;
	}
	if (!ghost2->ScatterBool and !ghost2->GhostKilledBool)ghost2->changeduration++;
	//poruszanie sie
	GhostsMovmentUpdate(ghost2);
	GhostDirectionUpdate('G',ghost2, Vector2f(1000.f, 0.f), Vector2f(550.f, 450.f), Vector2f(450.f, 550.f),target);
	return false;
}

bool Game::BlueGhostAI() {
	//ghost3-BLUE
	Vector2f target;
	Vector2f temp(pacman->lastposition.x - ghost1->lastposition.x, pacman->lastposition.y - ghost1->lastposition.y);
	if (abs(temp.x) >8  and abs(temp.y) >  8)target = Vector2f(pacman->Getsprite().getPosition().x , pacman->Getsprite().getPosition().y);
	else if (temp.x <= 0.f and temp.y <= 0.f)target = Vector2f(pacman->Getsprite().getPosition().x - temp.x, pacman->Getsprite().getPosition().y + temp.y);
	else if (temp.x <= 0.f and temp.y >= 0.f)target = Vector2f(pacman->Getsprite().getPosition().x - temp.x, pacman->Getsprite().getPosition().y + temp.y);
	else if (temp.x >= 0.f and temp.y <= 0.f)target = Vector2f(pacman->Getsprite().getPosition().x + temp.x, pacman->Getsprite().getPosition().y + temp.y);
	else if (temp.x >= 0.f and temp.y >= 0.f)target = Vector2f(pacman->Getsprite().getPosition().x + temp.x, pacman->Getsprite().getPosition().y + temp.y);
	//zmiana trybu
	if (ghost3->Getsprite().getGlobalBounds().intersects(pacman->Getsprite().getGlobalBounds())) {
		if (pacman->GetProtection() and ghost3->GhostKilledBool == false) { 
			if (!GameMap->CheckWall(pacman->lastdirection, pacman->lastposition)) {
				ghost3->ReseTGhostAfterKilled(pacman->lastdirection, pacman->lastposition);
			}
			else {
				if (!pacman->lastdirection == 'g')  ghost3->ReseTGhostAfterKilled(GameMap->WhereCanGo(pacman->lastposition), pacman->lastposition);
				else  ghost3->ReseTGhostAfterKilled(pacman->calculateOpoDirPacman(), pacman->lastposition);
			}
			pacman->BonusPoints += 100;
			Gamepoints += pacman->BonusPoints;

		}
		else if(!pacman->GetProtection() and !ghost3->GhostKilledBool){
			RestarPositions();
			return true;
		}
	}
	if (ghost3->changeduration == ghost3->SwitchTime and !ghost3->GhostKilledBool) {
		ghost3->changeduration = 0;
		ghost3->ScatterBool = true;
	}
	if (!ghost3->ScatterBool and !ghost3->GhostKilledBool) { ghost3->changeduration++; }
	//poruszanie sie
	GhostsMovmentUpdate(ghost3);
	GhostDirectionUpdate('B', ghost3, Vector2f(1000.f, 1000.f), Vector2f(450.f, 450.f), Vector2f(550, 350.f), target);
	return false;
}

bool Game::PurpleGhostAI() {
	//ghost4-PURPLE
	Vector2f target(pacman->Getsprite().getPosition().x - 150, pacman->Getsprite().getPosition().y + 100);
	double vect = sqrt(pow(2, abs(ghost4->lastposition.x - pacman->Getsprite().getPosition().x)) + pow(2, abs(ghost4->lastposition.y - pacman->Getsprite().getPosition().y)));
	//zmiana trybu
	if (vect <= 150 and !ghost4->GhostKilledBool) {
		ghost4->ScatterBool = true;

	}
	if (ghost4->Getsprite().getPosition().x <= 0 or ghost4->Getsprite().getPosition().x >= 1000 or ghost4->Getsprite().getPosition().y <= 0 or ghost4->Getsprite().getPosition().y >= 1000) {
		target = Vector2f(550.f, 450.f);
	}
	if (ghost4->Getsprite().getGlobalBounds().intersects(pacman->Getsprite().getGlobalBounds())) {
		if (pacman->GetProtection() and ghost4->GhostKilledBool == false) {
			if (!GameMap->CheckWall(pacman->lastdirection, pacman->lastposition)) {
				ghost4->ReseTGhostAfterKilled(pacman->lastdirection, pacman->lastposition);
			}
			else {
				if(!pacman->lastdirection=='g')ghost4->ReseTGhostAfterKilled(GameMap->WhereCanGo(pacman->lastposition), pacman->lastposition);
				else ghost4->ReseTGhostAfterKilled(pacman->calculateOpoDirPacman(), pacman->lastposition);
			}
			pacman->BonusPoints += 100;
			Gamepoints += pacman->BonusPoints;
		}
		else if (!pacman->GetProtection() and !ghost4->GhostKilledBool) {
			RestarPositions();
			return true;
		}
	}
	if (ghost4->changeduration == ghost4->SwitchTime and !ghost4->GhostKilledBool) {
		ghost4->changeduration = 0;
		ghost4->ScatterBool = true;
	}
	if (!ghost4->ScatterBool and !ghost4->GhostKilledBool) { ghost4->changeduration++; }
	//poruszanie sie
	GhostsMovmentUpdate(ghost4);
	GhostDirectionUpdate('P', ghost4, Vector2f(100.f, 950.f), Vector2f(550.f, 450.f), Vector2f(450.f, 550.f), target);
	return false;
}
void Game::GhostsEnergizerReverse() {
	//duch->setPos(duch->lastposition);
	ghost1->timeBool = true;
	ghost2->timeBool = true;
	ghost3->timeBool = true;
	ghost4->timeBool = true;

	ghost1->energBool = true;
	ghost2->energBool = true;
	ghost3->energBool = true;
	ghost4->energBool = true;
}
Vector2f Game::CalculateOpositePacman() {
	Vector2f wynik;
	float x = pacman->Getsprite().getPosition().x / 50.f;
	float y = pacman->Getsprite().getPosition().y / 50.f;
	if (x <= 10 and y <= 9)wynik = Vector2f(950, 950.f);
	if (x > 10 and y < 9)wynik = Vector2f(0.f, 950.f);
	if (x < 10 and y > 9)wynik = Vector2f(950.f, 0.f);
	if (x > 10 and y > 9)wynik = Vector2f(0.f, 0.f);
	return wynik;
}