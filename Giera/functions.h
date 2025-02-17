#pragma once
#include <SFML/Graphics.hpp>
#include <vector>


using namespace sf;
using namespace std;

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

    Unit(int Direction, int Type);
};

// Funkcje do obs³ugi gry
void endMenu(RenderWindow& window, Text& endScreen, Text& endScoreText, Text& pressEscape);
void move(Sprite& objectS, Unit& objectU, int direc);
void addUnit(vector<Sprite>& listS, vector<Unit>& listU, Texture& Texture, vector<RectangleShape>& listHp, int Direction, int unitType);
void attack(Sprite& objectS, Unit& objectU, Unit& attacked, vector<Sprite>& listB, Texture& ArrowTexture);
void attackBase(Sprite& objectS, Unit& objectU, int& Basehp, vector<Sprite> listB, Texture ArrowTexture);
void idle(Sprite& objectS, Unit& objectU);
void arrowRain(vector<Sprite>& listb, int i);
bool isColliding(Sprite& object1S, Sprite& object2S, int direction);
bool isAttacking(Sprite& object1S, Sprite& object2S, Unit& object1U, Unit& object2U);
