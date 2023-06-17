#include "Pacman.h"

void Pacman::initTexture()
{
	if (!texture.loadFromFile("Textures/steve.jpg")) {
		cout << "ERROR-TP blad wczytania tekstury pacmana" << endl;
	}
	if (!protectionTexture.loadFromFile("Textures/ochrona.png")) { //shield
		cout << "ERROR-TMW blad wczytania tekstury tarczy" << endl;
	}
}

void Pacman::initSprite()
{
	sprite.setTexture(texture);
	float scaleX = 50.f / texture.getSize().x;
	float scaleY = 50.f / texture.getSize().y; 
	sprite.setPosition(0.f, 0.f);
	sprite.scale(scaleX, scaleY);
	//
	protection.setTexture(protectionTexture);
	scaleX = 50.f / protectionTexture.getSize().x;
	scaleY = 50.f / protectionTexture.getSize().y;
	protection.setScale(scaleX, scaleY);
}

void Pacman::DrawPacman(RenderTarget& window)
{
	window.draw(sprite);
	if (Protection) {
		protection.setPosition(sprite.getPosition().x, sprite.getPosition().y );
		window.draw(protection);
	}
}
void Pacman::UpdateProtection() {
	if (Protection) {
		if (duration == ProtectionTime) {
			Protection = false;
			duration = 0;
			BonusPoints = 0;
		}
		else {
			duration++;
		}
	}
}
void Pacman::Update()
{

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		direction = 'A';
	}
	else if (Keyboard::isKeyPressed(Keyboard::D)) {
		direction = 'D';
	}
	else if (Keyboard::isKeyPressed(Keyboard::W)) {
		direction = 'W';
	}
	else if (Keyboard::isKeyPressed(Keyboard::S)) {
		direction = 'S';
	}
	if (direction != direction2)direction2 = direction;
}
void Pacman::Update2()
{

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		direction2 = 'A';
	}
	else if (Keyboard::isKeyPressed(Keyboard::D)) {
		direction2 = 'D';
	}
	else if (Keyboard::isKeyPressed(Keyboard::W)) {
		direction2 = 'W';
	}
	else if (Keyboard::isKeyPressed(Keyboard::S)) {
		direction2 = 'S';
	}
}

string Pacman::GetMovetype() const
{
	return Movetype;
}

void Pacman::SetMovetype(string typ) 
{
	Movetype=typ;
}

unsigned short int Pacman::GettimerSlow() const
{
	return timerSlow;
}

unsigned short int Pacman::GettimerRun() const
{
	return timerRun;
}

unsigned short int Pacman::GettimerLod() const
{
	return timerLod;
}

bool Pacman::GetProtection() const
{
	return Protection;
}

Sprite Pacman::Getsprite()const
{
	return sprite;
}

void Pacman::SetPosition(float x_, float y_)
{
	sprite.setPosition(x_, y_);
}

void Pacman::SetPosition(Vector2f pos)
{
	sprite.setPosition(pos);
}

float Pacman::Getmovmentspeed()const
{
	return movementspeed;
}

unsigned char Pacman::Getdirection()const
{
	return direction;
}

void Pacman::Setdirection(char pos)
{
	direction = pos;
}

void Pacman::SetProtection(bool prot)
{
	Protection = prot;
}

void Pacman::SetProtectionTime(short unsigned int time)
{
	ProtectionTime = time;
}

void Pacman::Move()
{
	if (odliczajlod) {
		if (durationlod <= timerLod) {
			durationlod++;
			return;
		}
	}
	else if (odliczajslow) {
		if (durationSlow < timerSlow) {
			durationSlow++;
			Movetype = "slow";
		}
	}
	else if (odliczajrun) {
		if (durationRun < timerRun) {
			durationRun++;
			Movetype = "run";
		}
	}
	//poruszaj sie 
	if (Movetype == "normal") {
		switch (Getdirection()) {
		case 'A': {
			sprite.move(-Getmovmentspeed(), 0.f);
			break;
		}
		case 'D': {
			sprite.move(Getmovmentspeed(), 0.f);
			break;
		}
		case 'W': {
			sprite.move(0.f, -Getmovmentspeed());
			break;
		}
		case 'S': {
			sprite.move(0.f, Getmovmentspeed());
			break;
		}
		}
	}
	else if (Movetype == "slow") {
		switch (Getdirection()) {
		case 'A': {
			sprite.move(-slowmovmentspeed, 0.f);
			break;
		}
		case 'D': {
			sprite.move(slowmovmentspeed, 0.f);
			break;
		}
		case 'W': {
			sprite.move(0.f, -slowmovmentspeed);
			break;
		}
		case 'S': {
			sprite.move(0.f, slowmovmentspeed);
			break;
		}
		}
	}
	else if (Movetype == "run") {
		switch (Getdirection()) {
		case 'A': {
			sprite.move(-runmovmentspeed, 0.f);
			break;
		}
		case 'D': {
			sprite.move(runmovmentspeed, 0.f);
			break;
		}
		case 'W': {
			sprite.move(0.f, -runmovmentspeed);
			break;
		}
		case 'S': {
			sprite.move(0.f, runmovmentspeed);
			break;
		}
		}
	}

}
char Pacman::calculateOpoDirPacman() {
	switch (lastdirection) {
	case 'A': {
		return 'D';
	}
	case 'D': {
		return 'A';
	}
	case 'W': {
		return 'S';
	}
	case 'S': {
		return 'W';
	}
	}
}
Pacman::Pacman()
{
	movementspeed = 2.5f;
	slowmovmentspeed = 0.5f;						// dotyczy to funkcji GhostUpdate w Game.cpp
	frethmovmentspeed = 0.5f;
	runmovmentspeed = 5.f;
	initTexture();
	initSprite();
	lastposition = {0.f,0.f};
	direction = 'g';
	direction2='D';
	//protection
	Protection = false;
	ProtectionTime= 200;
	duration=0;
	BonusPoints = 0;
	//poruszanie
	odliczajrun =false;
	odliczajslow = false;
	odliczajlod = false;
	SpeedRun = false;
	SpeedSlow = false;
	SpeedLod = false;
	durationRun = 0;
	durationSlow = 0;
	durationlod = 0;
	timerRun=95;
	timerSlow = 95;
	timerLod = 50;

	//etc
	lastdirection = 'g';
	Movetype = "normal";
}

Pacman::~Pacman()
{
}
void Pacman::Restart(Vector2f pos) {
	lastposition =pos;
	SetPosition(lastposition.x, lastposition.y);
	//protection
	Protection = false;
	duration = 0;
	BonusPoints = 0;
	//poruszanie
	odliczajrun = false;
	odliczajslow = false;
	odliczajlod = false;
	SpeedRun = false;
	SpeedSlow = false;
	SpeedLod = false;
	durationRun = 0;
	durationSlow = 0;
	durationlod = 0;
	//etc
	lastdirection = 'g';
	Movetype = "normal";
}