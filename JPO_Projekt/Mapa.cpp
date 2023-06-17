#include "Mapa.h"

void Mapa::initTextur_andSprite()
{
	float scaleX;
	float scaleY;
	//path
	if (!pathtext.loadFromFile("Textures/path.png")) {
		cout << "ERROR-TMP blad wczytania tekstury siezki mapy" << endl;
	}
	path.setTexture(pathtext);
	scaleX = 50.f / pathtext.getSize().x;
	scaleY = 50.f / pathtext.getSize().y; 
	path.setScale(scaleX, scaleY);
	//doors
	if (!doortext.loadFromFile("Textures/drzwi.png")) {
		cout << "ERROR-TMP blad wczytania tekstury drzwi mapy" << endl;
	}
	door.setTexture(doortext);
	scaleX = 50.f / doortext.getSize().x;
	scaleY = 50.f / doortext.getSize().y;
	door.setScale(scaleX, scaleY);
	//wall
	if (!walltext.loadFromFile("Textures/wall.png")) {
		cout << "ERROR-TMW blad wczytania tekstury sciany mapy" << endl;
	}
	wall.setTexture(walltext);
	scaleX = 50.f / walltext.getSize().x;
	scaleY = 50.f / walltext.getSize().y;
	wall.setScale(scaleX, scaleY);
	///points
	if (!corntext.loadFromFile("Textures/corn.png")) {
		cout << "ERROR-TMW blad wczytania tekstury kukurydzy" << endl;
	}
	corn.setTexture(&corntext);
	corn.setRadius(10);
	//bonus
	if (!bonustext.loadFromFile("Textures/diamond.png")) {
		cout << "ERROR-TMW blad wczytania tekstury miecza" << endl;
	}
	bonus.setTexture(&bonustext);
	bonus.setRadius(30);
	//shield
	if (!shieldtext.loadFromFile("Textures/protection.png")) { 
		cout << "ERROR-TMW blad wczytania tekstury tarczy na mapie" << endl;
	}
	shield.setTexture(&shieldtext);
	shield.setRadius(25);
	// Boost
	if (!boosttext.loadFromFile("Textures/boost.png")) { 
		cout << "ERROR-TMW blad wczytania tekstury boosta" << endl;
	}
	boost.setTexture(&boosttext);
	boost.setRadius(25);
	// energizer
	if (!energizertext.loadFromFile("Textures/energizer.png")) {
		cout << "ERROR-TMW blad wczytania tekstury energizera" << endl;
	}
	energizer.setTexture(&energizertext);
	energizer.setRadius(25);
	///dodatkowe tekstuy do utrudnien
	if (!dziuratext.loadFromFile("Textures/dziura.png")) {
		cout << "ERROR-TMP blad wczytania tekstury dziury mapy" << endl;
	}
	dziura.setTexture(dziuratext);
	scaleX = 50.f / dziuratext.getSize().x;
	scaleY = 50.f / dziuratext.getSize().y;
	dziura.setScale(scaleX, scaleY);

	if (!lepkietext.loadFromFile("Textures/lepkie.png")) {
		cout << "ERROR-TMP blad wczytania tekstury lepkiego pola mapy" << endl;
	}
	lepkie.setTexture(lepkietext);
	scaleX = 50.f / lepkietext.getSize().x;
	scaleY = 50.f / lepkietext.getSize().y;
	lepkie.setScale(scaleX, scaleY);

	if (!lodtext.loadFromFile("Textures/lod.png")) {
		cout << "ERROR-TMP blad wczytania tekstury dziury mapy" << endl;
	}
	lod.setTexture(lodtext);
	scaleX = 50.f / lodtext.getSize().x;
	scaleY = 50.f / lodtext.getSize().y;
	lod.setScale(scaleX, scaleY);
}
void Mapa::initSpriteMap()
{
	for (int y = 0; y < Map_wysokosc; y++) {
		for (int x = 0; x < Map_szerokosc; x++) {
			if (SzkicMapy[y][x] == '#' or SzkicMapy[y][x] == 'D') {
				if (SzkicMapy[y][x] == 'D') {
					door.setPosition(x * door.getGlobalBounds().width, y * door.getGlobalBounds().height);
					MapaSprite[y][x] = door;
				}
				else {
					wall.setPosition(x * wall.getGlobalBounds().width, y * wall.getGlobalBounds().height);
					MapaSprite[y][x] = wall;
				}
			}
			else if (SzkicMapy[y][x] == ' ' or SzkicMapy[y][x] == 'X' or SzkicMapy[y][x] == 'P' or SzkicMapy[y][x] == '.'  or SzkicMapy[y][x] == '?' or SzkicMapy[y][x] == 'B' or SzkicMapy[y][x] == 'E' or SzkicMapy[y][x] == 'H' or SzkicMapy[y][x] == 'K') {
				path.setPosition(x * path.getGlobalBounds().width,y * path.getGlobalBounds().height);
				MapaSprite[y][x] = path;
				if (SzkicMapy[y][x] == 'X') {
					dziury.push_back(Vector2f(x*50.0,y*50.0));
				}
				else if (SzkicMapy[y][x] == 'P') {
					Pacmanposition = MapaSprite[y][x].getPosition();
				}
				else if (SzkicMapy[y][x] == '.' or SzkicMapy[y][x] == '?') {
					if ((x != 9 and y != 9) or (x != 10 and y != 9) or (x != 11 and y != 9)) {
						corn.setPosition((x * path.getGlobalBounds().width) + 15.f, (y * path.getGlobalBounds().height) + 15.f);
						MapaCorn[y][x] = corn;
						liczbapunktow++;
					}
				}
				else if (SzkicMapy[y][x] == 'B') {
					bonus.setPosition((x * path.getGlobalBounds().width), (y * path.getGlobalBounds().height)-3);
					MapaCorn[y][x] = bonus;
				}
				else if (SzkicMapy[y][x] == 'K') {
					boost.setPosition((x * path.getGlobalBounds().width), (y * path.getGlobalBounds().height) +2);
					MapaCorn[y][x] = boost;
				}
				else if (SzkicMapy[y][x] == 'H') {
					shield.setPosition((x * path.getGlobalBounds().width), (y * path.getGlobalBounds().height) - 3);
					MapaCorn[y][x] = shield;
				}
				else if (SzkicMapy[y][x] == 'E') {
					energizer.setPosition((x * path.getGlobalBounds().width), (y * path.getGlobalBounds().height)+2);
					MapaCorn[y][x] = energizer;
				}
			}
		}
	}
	GhostYposition = Vector2f(550.f,450.f);
	GhostGposition = Vector2f(450.f,450.f);
	GhostBposition = Vector2f(550.f,450.f);
	GhostPposition = Vector2f(450.f, 450.f);
}

bool Mapa::GetEnergizerBool()
{
	return BonusBool;
}
bool Mapa::GetProtectionBool()
{
	return ShieldBool;
}
bool Mapa::GetSpeedBool()
{
	return SpeedBool;
}
void Mapa::ResetBonus() {
	reset = true;
	BonusBool = false;
}
void Mapa::ResetShield() {
	Shieldreset = true;
	ShieldBool = false;
}
void Mapa::ResetBoost() {
	Speedreset = true;
	SpeedBool = false;
}
void Mapa::CreateHoles() {
	if (dziuraduration == chagnedziuratime) {
		dziuraduration = 0;
		wybranedziuryTYP.clear();
		wybranedziuryPOS.clear();
		while (wybranedziuryPOS.size() < iloscdziur) {
			int a = rand() % dziury.size();
			if (find(wybranedziuryPOS.begin(), wybranedziuryPOS.end(), dziury[a]) == wybranedziuryPOS.end()) {
				int losowa = rand() % 5;
				if (losowa == 0)wybranedziuryTYP.push_back(1); //dziura
				else if (losowa == 2 or losowa == 3)wybranedziuryTYP.push_back(2); //mrozne
				else wybranedziuryTYP.push_back(3); //lepkie
				wybranedziuryPOS.push_back(dziury[a]);
			}
		}
	}
	else dziuraduration++;
}
void Mapa::DrawMap(RenderTarget& window,bool pauza) {
	//update dziury
	if(!pauza)CreateHoles();
	//mapa rysowanie 
	for (int y = 0; y < Map_wysokosc; y++) {
		for (int x = 0; x < Map_szerokosc; x++) {
			window.draw(MapaSprite[y][x]);
			if (MapaCorn[y][x].getTexture() == corn.getTexture() or MapaCorn[y][x].getTexture() == energizer.getTexture()) {
				window.draw(MapaCorn[y][x]);
			}
			//bonus 
			else if (TimerBonus > BonusTimeMin and TimerBonus < BonusTimeMax and SzkicMapy[y][x]=='B') {
				window.draw(MapaCorn[y][x]);
				BonusBool = true;
			}
			else if (TimerBonus > BonusTimeMax and BonusBool == true) {
				ResetBonus();
			}
			if (ResetBonusTimer == RespawnTime and SzkicMapy[y][x] == 'B') {
				BonusBool = false;
				TimerBonus = 0;
				MapaCorn[y][x] = bonus;
				ResetBonusTimer = 0;
				reset = false;
			}
			//shield bonusowy
			if (ShieldBonus > ShieldTimeMin and ShieldBonus < ShieldTimeMax and SzkicMapy[y][x] == 'H') { //tarcza-H
				window.draw(MapaCorn[y][x]);
				ShieldBool = true;
			}
			else if (ShieldBonus > ShieldTimeMax and ShieldBool == true) {
				ResetShield();
			}
			if (ResetShieldTimer == RespawnTime and SzkicMapy[y][x] == 'H') {
				ShieldBool = false;
				ShieldBonus = 0;
				MapaCorn[y][x] = shield;
				ResetShieldTimer = 0;
				reset = false;
			}
			//speed bonusowy
			if (SpeedBonus > SpeedTimeMin and SpeedBonus < SpeedTimeMax and SzkicMapy[y][x] == 'K') {
				window.draw(MapaCorn[y][x]);
				SpeedBool = true;
			}
			else if (SpeedBonus > SpeedTimeMax and SpeedBool == true) {
				ResetBoost();
			}
			if (ResetSpeedTimer == RespawnTime and SzkicMapy[y][x] == 'K') {
				SpeedBool = false;
				SpeedBonus = 0;
				MapaCorn[y][x] = boost;
				ResetSpeedTimer = 0;
				Speedreset = false;
			}
			//dziury
			if (SzkicMapy[y][x] == 'X') {
				int type= 0;
				int i = 0;
				for (auto it : wybranedziuryPOS) {
					if ((it.x/50) == x and (it.y/50) == y) {
						 type = wybranedziuryTYP[i];
						 break;
					}
					i++;
				}
				if (type==1) { //dziura
						dziura.setPosition(x * dziura.getGlobalBounds().width, y * dziura.getGlobalBounds().height);
						window.draw(dziura);
				}
				else if (type == 2) { //lodowe
					lod.setPosition(x * lod.getGlobalBounds().width, y * lod.getGlobalBounds().height);
					window.draw(lod);
				}
				else if (type == 3) { //lepkie
					lepkie.setPosition(x * lepkie.getGlobalBounds().width, y * lepkie.getGlobalBounds().height);
					window.draw(lepkie);
				}
			}
		}
	}
	if (!pauza) {
		TimerBonus++;
		ShieldBonus++;
		SpeedBonus++;
		if (reset)ResetBonusTimer++;
		if (Shieldreset)ResetShieldTimer++;
		if (Speedreset)ResetSpeedTimer++;
	}
}
Sprite Mapa::Getwall()
{
	return wall;
}
Sprite Mapa::Getdoor()
{
	return door;
}
Vector2f Mapa::GetPacmanPosition()
{
	return Pacmanposition;
}
Vector2f Mapa::GetGhostPosition(char kolor)
{
	Vector2f Ghostposition;
	switch (kolor)
	{
		case 'Y':
		Ghostposition = GhostYposition;
		break;
		case 'G':
		Ghostposition = GhostGposition;
		break;
		case 'B':
		Ghostposition = GhostBposition;
		break;
		case 'P':
		Ghostposition = GhostPposition;
		break;
	default:
		break;
	}
	return Ghostposition;
}
Texture Mapa::Getcorn()
{
	return corntext;
}
Mapa::Mapa( unsigned short int poziomtrudnosi)//1-3
{
	liczbapunktow = 0;
	initTextur_andSprite();
	initSpriteMap();
	//Bonus
	TimerBonus = 0;
	ResetBonusTimer = 0;
	reset = false;
	BonusBool = false;
	//Shield
	ShieldBonus = 0;
	ShieldBool = false;
	Shieldreset = false;
	ResetShieldTimer = 0;
	//boost
	SpeedBonus = 0;
	SpeedBool = false;
	Speedreset = false;
	ResetSpeedTimer = 0;
	//dziura
	dziuraduration = 0;
	switch (poziomtrudnosi)
	{
	case 1: {
		iloscdziur = 2;
		chagnedziuratime = 1300;
		SpeedTimeMin = 300;
		SpeedTimeMax = SpeedTimeMin + 600;
		BonusTimeMin =400 ;
		BonusTimeMax = BonusTimeMin + 600;
		ShieldTimeMin = 400;
		ShieldTimeMax = ShieldTimeMin+600;
		RespawnTime = 250;
		break;
	}
	case 2: {
		iloscdziur = 5;
		chagnedziuratime = 900;
		SpeedTimeMin = 420;
		SpeedTimeMax = SpeedTimeMin + 500;
		BonusTimeMin = 500;
		BonusTimeMax = BonusTimeMin + 380;
		ShieldTimeMin = 400;
		ShieldTimeMax = ShieldTimeMin + 480;
		RespawnTime = 700;
		break;
	}
	case 3: {
		iloscdziur = 8;
		chagnedziuratime = 600;
		SpeedTimeMin = 500;
		SpeedTimeMax= SpeedTimeMin+400;
		BonusTimeMin = 900;
		BonusTimeMax = BonusTimeMin + 320;
		ShieldTimeMin = 520;
		ShieldTimeMax = ShieldTimeMin + 400;
		RespawnTime = 1000;
		break;
	}
	default:
		break;
	}

}

Mapa::~Mapa()
{
}

void Mapa::ResetMap() {
	//bonus
	TimerBonus = 0;
	ResetBonusTimer = 0;
	reset = false;
	BonusBool = false;
	//shield
	ShieldBonus=0;
	ShieldBool=false;
	Shieldreset=false;
	ResetShieldTimer=0;
	//boost
	SpeedBonus = 0;
	SpeedBool = false;
	Speedreset = false;
	ResetSpeedTimer = 0;

	BonusTimeMin = BonusTimeMin + 10;
	BonusTimeMax = BonusTimeMax + 10;
	SpeedTimeMin = SpeedTimeMin + 10;
	SpeedTimeMax = SpeedTimeMax + 10;
	ShieldTimeMin = ShieldTimeMin+10;
	ShieldTimeMax = ShieldTimeMax+10;
	RespawnTime= RespawnTime+10;
	liczbapunktow = 0;
	dziuraduration = 0;
	for (int y = 0; y < Map_wysokosc; y++) {
		for (int x = 0; x < Map_szerokosc; x++) {
			 if ( SzkicMapy[y][x] == '.'  or SzkicMapy[y][x] == '?'  or SzkicMapy[y][x] == 'E') {
				if (SzkicMapy[y][x] == '.' or SzkicMapy[y][x] == '?') {
					if ((x != 9 and y != 9) or (x != 10 and y != 9) or (x != 11 and y != 9)) {
						corn.setPosition((x * path.getGlobalBounds().width) + 15.f, (y * path.getGlobalBounds().height) + 15.f);
						MapaCorn[y][x] = corn;
						liczbapunktow++;
					}
				}
				if (SzkicMapy[y][x] == 'E') {
					energizer.setPosition((x * path.getGlobalBounds().width), (y * path.getGlobalBounds().height)+2);
					MapaCorn[y][x] = energizer;
				}
			}
		}
	}

	//reset dziur
	wybranedziuryTYP.clear();
	wybranedziuryPOS.clear();
}
void  Mapa::ResetMapNextRound() {
	//bonus
	TimerBonus = 0;
	ResetBonusTimer = 0;
	reset = false;
	BonusBool = false;
	dziuraduration = 0;
	//shield
	ShieldBonus = 0;
	ShieldBool = false;
	Shieldreset = false;
	ResetShieldTimer = 0;
	//boost
	SpeedBonus = 0;
	SpeedBool = false;
	Speedreset = false;
	ResetSpeedTimer = 0;

	BonusTimeMin = BonusTimeMin + 10;
	BonusTimeMax = BonusTimeMax + 10;
	SpeedTimeMin = SpeedTimeMin + 10;
	SpeedTimeMax = SpeedTimeMax + 10;
	ShieldTimeMin = ShieldTimeMin + 10;
	ShieldTimeMax = ShieldTimeMax + 10;
	RespawnTime = RespawnTime + 10;
	//reset dziur
	wybranedziuryTYP.clear();
	wybranedziuryPOS.clear();
}

bool Mapa::CheckWall(char dir,Vector2f pos) {
	pos=pos/50.f;
	switch (dir){
	case 'W': {
		if (SzkicMapy[((int)pos.y)-1][(int)pos.x] == 'W') {
			return true;
		}
		break;
	}
	case 'S': {
		if (SzkicMapy[((int)pos.y) + 1][(int)pos.x] == 'W') {
			return true;
		}
		break;
	}
	case 'D': {
		if (SzkicMapy[(int)pos.y][((int)pos.x)+1] == 'W') {
			return true;
		}
		break;
	}
	case 'A': {
		if (SzkicMapy[(int)pos.y][((int)pos.x) - 1] == 'W') {
			return true;
		}
		break;
	}
	default:
		return false;
	}
}
char Mapa::WhereCanGo(Vector2f pos) {
	pos = pos / 50.f;
	if (SzkicMapy[((int)pos.y) - 1][(int)pos.x] != 'W') {
		return 'W';
	}
	if (SzkicMapy[((int)pos.y) + 1][(int)pos.x] != 'W') {
		return 'S';
	}
	if (SzkicMapy[(int)pos.y][((int)pos.x) + 1] != 'W') {
		return 'D';
	}
	if (SzkicMapy[(int)pos.y][((int)pos.x) - 1] != 'W') {
		return 'A';
	}
}