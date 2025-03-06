#include "functions.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#pragma once

extern int frameResolution;
extern int ISMENUOPEN;
extern int FrameLimit;
extern int animationLatencyLimit;
extern int moveLatency;
extern int ALLYBASEHP;
extern int ENEMYBASEHP;
extern int MONEY;
extern int moneyLatency;
extern int moneyLatencyLimit;
extern int hpBarOffsetX;
extern int hpBarOffsetY;
extern int endScore;
extern int experience;

extern Sound swordSound;
extern Texture ArrowRainTexture;

Unit::Unit(int Direction, int Type, Texture& textureNew) {
    unitDierction = Direction;
    unitType = Type;
	sprite.setTexture(textureNew);
    if (unitType == 1) {
        unitHp = 100;
        unitMaxHp = 100;
        attackDamage = 25;
        range = -100;
    }
    else if (unitType == 2) {
        unitHp = 80;
        unitMaxHp = 80;
        attackDamage = 40;
        range = -100;
    }
    else if (unitType == 3) {
        unitHp = 40;
        unitMaxHp = 40;
        range = 100;
    }
}

void endMenu(RenderWindow& window, Text& endScreen, Text& endScoreText, Text& pressEscape)
{
    window.draw(endScreen);
    window.draw(endScoreText);
    window.draw(pressEscape);
    window.display();
}

void move(Unit& objectU, int direc) {
    if (objectU.currentState != 1) {
        objectU.Xindex = 0;
    }
    objectU.currentState = 1;
    for (int i = 0; i < moveLatency; i++) {
        objectU.sprite.setPosition(objectU.sprite.getPosition() + Vector2f(direc * 1, 0));
    }
    objectU.sprite.setTextureRect(IntRect({ objectU.Xindex * frameResolution,frameResolution }, { frameResolution,frameResolution }));
    objectU.animationLatency += 1;
    if (objectU.animationLatency >= animationLatencyLimit) {
        objectU.Xindex += 1;
        if (objectU.Xindex == objectU.animationFrames) {
            objectU.Xindex = 0;
        }
        objectU.animationLatency = 0;
    }
    
}

void addUnit(vector<Unit>& listU, Texture& Texture, vector<RectangleShape>& listHp, int Direction, int unitType) {
    Unit unit(Direction, unitType, Texture);
    if (unitType == 1) {
        if (Direction == 1) {
            unit.sprite.setOrigin(Vector2f(frameResolution, 0 ));
            unit.sprite.setPosition(Vector2f(320, 865));
        }
        else {
            unit.sprite.setPosition(Vector2f(1600, 865));
        }
        unit.sprite.setTextureRect(IntRect({ 0 * frameResolution,0 }, { frameResolution,frameResolution }));
        listU.push_back(unit);
    }
    else if (unitType == 2) {
        if (Direction == 1) {
            unit.sprite.setOrigin(Vector2f(frameResolution, 0));
            unit.sprite.setPosition(Vector2f(320, 865));
        }
        else {
            unit.sprite.setPosition(Vector2f(1600, 865));
        }
        unit.sprite.setTextureRect(IntRect({ 0 * frameResolution,0 }, { frameResolution,frameResolution }));
        listU.push_back(unit);
    }
    else if (unitType == 3) {
        if (Direction == 1) {
            unit.sprite.setOrigin(Vector2f(frameResolution, 0));
            unit.sprite.setPosition(Vector2f(320, 865));
        }
        else {
            unit.sprite.setPosition(Vector2f(1600, 865));
        }
        unit.sprite.setTextureRect(IntRect({ 2 * frameResolution,0 }, { frameResolution,frameResolution }));
        listU.push_back(unit);
    }
    RectangleShape hpBar({ 44,5 });
    hpBar.setFillColor(Color::Red);
    listHp.push_back(move(hpBar));
}

void attack(Unit& objectU, Unit& attacked, vector<Sprite>& listB, Texture& ArrowTexture) {
    if (objectU.currentState != 2) {
        objectU.Xindex = 0;
    }
    objectU.currentState = 2;
    if (objectU.unitType == 3) { 
         objectU.sprite.setTextureRect(IntRect({ objectU.Xindex * frameResolution,frameResolution * 4 }, { frameResolution,frameResolution }));
    }
    else {
         objectU.sprite.setTextureRect(IntRect({ objectU.Xindex * frameResolution,frameResolution * 2 }, { frameResolution,frameResolution }));
         if (objectU.Xindex == 0) {
             if (objectU.unitType == 1) {
                swordSound.play();
             }
             else {

             }
         }
    }
    objectU.animationLatency += 1;
    int attackLatency = animationLatencyLimit * 1.5;
    if (objectU.animationLatency >= attackLatency) {
        objectU.Xindex += 1;
        if (objectU.unitType != 3) {
            if (objectU.Xindex == objectU.animationFrames) {
                objectU.Xindex = 0;
                attacked.unitHp -= objectU.attackDamage;
                
            }
        }
        else { // STYTUACJA GDY LUCZNIK ATAKUJE BO MA WIECEJ KLATEK ANIMACJI klasa 3 - lucznik
            if (objectU.Xindex >= objectU.animationFrames + 2) {
                objectU.Xindex = 0;
                Sprite sprite(ArrowTexture);
				if (objectU.unitDierction == 1) {
                    sprite.setPosition(objectU.sprite.getPosition() + Vector2f(-128, 64));
				}
                else {
                    sprite.setPosition(objectU.sprite.getPosition() + Vector2f(64, 64));

                }
                sprite.setTextureRect(IntRect({ 0,0 }, { 64,64 }));
                listB.push_back(move(sprite));

            }
        }
        objectU.animationLatency = 0;
    }

}

void attackBase(Unit& objectU, int& Basehp, vector<Sprite> listB, Texture ArrowTexture) {
    if (objectU.currentState != 2) {
        objectU.Xindex = 0;
    }
    objectU.currentState = 2;
    if (objectU.unitType == 3) { 
            objectU.sprite.setTextureRect(IntRect({ objectU.Xindex * frameResolution,frameResolution * 4 }, { frameResolution,frameResolution }));
    }
    else {
           objectU.sprite.setTextureRect(IntRect({ objectU.Xindex * frameResolution,frameResolution * 2 }, { frameResolution,frameResolution }));
           if (objectU.Xindex == 0) {
               if (objectU.unitType == 1) {
                   swordSound.play();
               }
               else {

               }
           }
    }
    objectU.animationLatency += 1;
    int attackLatency = animationLatencyLimit * 1.5;
    if (objectU.animationLatency >= attackLatency) {
        objectU.Xindex += 1;
        if (objectU.unitType != 3) {
            if (objectU.Xindex == objectU.animationFrames) {
                objectU.Xindex = 0;
                Basehp -= objectU.attackDamage;
            }
        }
        else { // STYTUACJA GDY LUCZNIK ATAKUJE BO MA WIECEJ KLATEK ANIMACJI klasa 3 - lucznik
            if (objectU.Xindex >= objectU.animationFrames + 2) {
                objectU.Xindex = 0;
                Sprite sprite(ArrowTexture);
                sprite.setPosition(objectU.sprite.getPosition() + Vector2f(64, 64));
                sprite.setTextureRect(IntRect({ 0 * 64,0 }, { 64,64 }));
                listB.push_back(move(sprite));

            }
        }
        objectU.animationLatency = 0;
    }
}

void idle(Unit& objectU) {
    if (objectU.currentState != 0) {
         objectU.Xindex = 0;
    }
    objectU.currentState = 0;
    objectU.sprite.setTextureRect(IntRect({ objectU.Xindex * frameResolution,0 }, { frameResolution,frameResolution }));
    objectU.animationLatency += 1;
    if (objectU.animationLatency == animationLatencyLimit) {
        objectU.Xindex += 1;
        if (objectU.Xindex == objectU.animationFrames) {
            objectU.Xindex = 0;
        }
        objectU.animationLatency = 0;
    }
}

void arrowRain(vector<Sprite>& listB, int i) {
    Sprite sprite(ArrowRainTexture);
    sprite.setPosition(Vector2f(200 + i*100, 0));
    sprite.setTextureRect(IntRect({ 0 , 0 }, { 64,64 }));
    listB.push_back(move(sprite));
}

bool isColliding(Unit& object1, Unit& object2, int direction) {
    FloatRect border1 = object1.sprite.getGlobalBounds();
    FloatRect border2 = object2.sprite.getGlobalBounds();
    if (direction == 1) {
        if (border1.position.x + border1.size.x - border2.position.x >= 142) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        if (border1.position.x - border2.size.x - border2.position.x <= -142) {
            return 1;
        }
        else {
            return 0;
        }
    }

}

bool isAttacking(Unit& object1, Unit& object2) {
    if (object1.unitDierction == 1) {
        if (object1.sprite.getPosition().x - object2.sprite.getPosition().x >= -1 * object1.range) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        if (object1.sprite.getPosition().x - object2.sprite.getPosition().x <= object1.range) {
            return 1;
        }
        else {
            return 0;
        }
    }

}
