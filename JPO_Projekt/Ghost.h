#pragma once
#include "Pacman.h"
#include "Mapa.h"
class Ghost
{
private:
	unsigned char direction;
	float movementspeed; float slowmovmentspeed; float frethmovmentspeed; float runmovmentspeed;
	Texture texture;
	Sprite sprite;

	//funkcje private
	void initTexture(string text);
	void initSprite();

public:
	Vector2f lastposition;
	///boole od AI i sterowania
		//scater
	short unsigned int ScatterTime;
	bool ScatterBool;
		//movment
	short unsigned int duration;
	bool movmentrun1, movmentrun2, energBool;
	bool GhostKilledBool, again, reversbo;
		//respawn i change 
	short unsigned int changeduration,RespawnTime,SwitchTime, energizerDur;
	bool RespawnBool; bool timeBool; bool odliczaj; // ucieczka mode
	void ResetGhost(char direct);
	void ReseTGhostAfterKilled(char dir,Vector2f pos);
	void ReseTGhostNoKilled();
	void SetOpossiteDirection();
	//konstruktor
	Ghost(string text, float speed,char direct,short unsigned int SwitchModeTime);
	//funkcje public
	void Drawghost(RenderTarget& window);
	void Move(string type);
	void Update(string type);

	//get 
	float Getmovmentspeed()const;
	unsigned char Getdirection()const;
	Sprite Getsprite()const;
	void setPos(Vector2f pos);
	//set
	void SetPosition(float x, float y);
	void Setdirection(char d);
};

