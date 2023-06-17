#include "Ghost.h"

Ghost::Ghost(string text, float speed,char direct, short unsigned int SwitchModeTime) {
	movementspeed = speed;						
	slowmovmentspeed = 0.5f;						
	frethmovmentspeed = 0.5f;
	runmovmentspeed = 5.f;
	initTexture(text);
	initSprite();
	direction = direct;
	lastposition = { 0.f,0.f };
	//Ai
	//movment
	movmentrun1 = false; 
	movmentrun2 = false;
	GhostKilledBool = true; 
	again = false; 
	reversbo = false; 
	energBool = false; /// idk
	duration = 0;
	changeduration = 0;
	energizerDur = 0;
	//scater mode
	ScatterTime = 200; 
	ScatterBool = false;
	//respawn
	 RespawnBool = false;
	 RespawnTime = 150;
	 SwitchTime=SwitchModeTime;
	 timeBool = false;
	 odliczaj = false;
}
void Ghost::initTexture(string text)
{
	if (!texture.loadFromFile(text)) {
		cout << "ERROR-TP blad wczytania tekstury ducha" << endl;
	}
}

void Ghost::initSprite()
{
	sprite.setTexture(texture);
	sprite.setPosition(0.f, 0.f);
	float scaleX = 50.f / texture.getSize().x; // Skalowanie wzd³u¿ osi X
	float scaleY = 50.f / texture.getSize().y; // Skalowanie wzd³u¿ osi Y
	//sala-powieksz
	sprite.scale(scaleX, scaleY);
}

void Ghost::Drawghost(RenderTarget& window)
{
	window.draw(sprite);
}

void Ghost::SetPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

void Ghost::Setdirection(char d)
{
	direction = d;
}

void Ghost::Move(string type)
{
	if (type == "normal") {
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
	else if (type == "slow") {
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
	else if (type == "run") {
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
	//zmian.second = sprite.getPosition();
}

void Ghost::Update(string type)
{
	bool ab = false;
	if (type == "slow") {
		Move("slow");
	}
	else if(type=="normal") {
		Move("normal");
	}
	else if (type == "run") {
		Move("run");
	}
}

float Ghost::Getmovmentspeed() const
{
	return movementspeed;
}

unsigned char Ghost::Getdirection() const
{
	return direction;
}

Sprite Ghost::Getsprite() const
{
	return sprite;
}

void Ghost::setPos(Vector2f pos)
{
	sprite.setPosition(pos);
}

void Ghost::ResetGhost(char direct=0) {
	//Ai
	//movment
	movmentrun1 = false;
	movmentrun2 = false;
	GhostKilledBool = true;
	again = false;
	reversbo = false;
	energBool = false; /// idk
	duration = 0;
	changeduration = 0;
	//scater mode
	ScatterBool = false;
	//respawn
	RespawnBool = false;
	direction = direct;
	SwitchTime += 10;       //////utrudnienie poziomu z danym levelem, duchy bed¹ coraz czêsciej goniæ zamiast scater modu co w przypadku przenikaj¹cego jest dosyæ utrudniaj¹ce 
	timeBool = false;
	odliczaj = false;
}
void Ghost::ReseTGhostAfterKilled(char dir, Vector2f pos) {
	//Ai
	//movment
	movmentrun1 = false;
	movmentrun2 = false;
	GhostKilledBool = true;
	again = false;
	reversbo = false;
	energBool = false; 
	duration = 0;
	changeduration = 0;
	energizerDur = 0;
	//scater mode
	ScatterBool = false;
	//respawn
	RespawnBool = false;;
	timeBool = false;
	odliczaj = false;
	//zmieninie pozycji 
	setPos(pos);
	Setdirection(dir);
	lastposition = pos;
}
void Ghost::ReseTGhostNoKilled() {
	//Ai
//movment
	movmentrun1 = false;
	movmentrun2 = false;
	GhostKilledBool = false;
	again = false;
	reversbo = false;
	energBool = false;
	duration = 0;
	changeduration = 0;
	energizerDur = 0;
	//scater mode
	ScatterBool = false;
	//respawn
	RespawnBool = false;;
	timeBool = false;
	odliczaj = false;
	//zmieninie pozycji 
	setPos(lastposition);
}
void Ghost::SetOpossiteDirection() {
	switch (direction)
	{
	case 'W': {
		direction = 'S';
		break;
	}
	case 'S':
		direction = 'W';
		break; {
	}
	case 'D':
		direction = 'A';
		break; {
	}
	case 'A':
		direction = 'D';
		break; {
	}
	default:
		break;
	}
}