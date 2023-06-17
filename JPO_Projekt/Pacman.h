#pragma once
#include <cmath>
#include <iostream>
#include <ctime> 
#include <vector>
#include <array>
//random number inicjalizacja

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;
/// zmienne globalne




class Pacman
{
private:
	unsigned char direction;
	float movementspeed; float slowmovmentspeed; float frethmovmentspeed; float runmovmentspeed;
	Texture texture;
	Texture protectionTexture;
	Sprite sprite;
	Sprite protection;

					//protection
	bool Protection;
	short unsigned int ProtectionTime;
	short unsigned int duration;
	short unsigned int druationSpeed;
	short unsigned intProtectionTime;
				//poruszanie sie
	string Movetype;

	short unsigned int timerRun;//run
	short unsigned int timerSlow;//slow
	short unsigned int timerLod;//lod
						//funkcje private
	void initTexture();
	void initSprite();
public:
	Pacman();
	~Pacman();
	/// public zmienne
	Vector2f lastposition;
	short unsigned int BonusPoints;
	bool SpeedEnergizer;
	//od poruszania
	short unsigned int durationRun; //run
	short unsigned int durationSlow; //slow
	short unsigned int durationlod; //lod

	bool odliczajrun;
	bool odliczajslow;
	bool odliczajlod;
	bool SpeedRun;
	bool SpeedSlow;
	bool SpeedLod;
	char lastdirection;
	//funkcje public
	char direction2;
	void Update2();
	void DrawPacman(RenderTarget& window);
	void Update();
	void Move();
	void UpdateProtection();
	char calculateOpoDirPacman();
	void Restart(Vector2f pos);
											//get set
	string GetMovetype()const;
	void SetMovetype(string movetyp);
	unsigned short int GettimerSlow()const;
	unsigned short int GettimerRun()const;
	unsigned short int GettimerLod()const;
	bool GetProtection()const;
	Sprite Getsprite()const;
	float  Getmovmentspeed()const;
	unsigned char Getdirection()const;
										//set
	void SetPosition(float x_, float y_);
	void SetPosition(Vector2f pos);
	void Setdirection(char pos);
	void SetProtection(bool prot);
	void SetProtectionTime(short unsigned int time);
};
