#pragma once
#include <SFML/Graphics.hpp>
#include <vector>


using namespace sf;
using namespace std;

extern string AnimationAllyLink1;

class Unit {
public:
    int animationLatency = 0;
    int Xindex = 0;
    int unitHp = 0;
    int unitDierction;
    int animationFrames = 6;
    int unitType;
    int attackDamage = 0;
    int range = 0;
    int currentState = 0;
    int unitMaxHp = 0;
	Texture texture = Texture(AnimationAllyLink1);
	Sprite sprite = Sprite(texture);
  
    Unit(int Direction, int Type, Texture& textureNew);
};

// Funkcje do obsługi gry
void endMenu(RenderWindow& window, Text& endScreen, Text& endScoreText, Text& pressEscape);
void move(Unit& objectU, int direc);
void addUnit(vector<Unit>& listU, Texture& Texture, vector<RectangleShape>& listHp, int Direction, int unitType);
void attack(Unit& objectU, Unit& attacked, vector<Sprite>& listB, Texture& ArrowTexture);
void attackBase(Unit& objectU, int& Basehp, vector<Sprite> listB, Texture ArrowTexture);
void idle(Unit& objectU);
void arrowRain(vector<Sprite>& listB, int i);
bool isColliding(Unit& object1, Unit& object2, int direction);
bool isAttacking(Unit& object1, Unit& object2);
