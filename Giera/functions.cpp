#include "functions.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
extern int hpBarOffset;
extern int endScore;
extern int experience;

extern Sound swordSound;
extern Texture ArrowRainTexture;

Unit::Unit(int Direction, int Type) {
    unitDierction = Direction;
    unitType = Type;
    if (unitType == 1) {
        unitHp = 100;
        unitMaxHp = 100;
        attackDamage = 25;
        range = 100;
    }
    else if (unitType == 2) {
        unitHp = 80;
        unitMaxHp = 80;
        attackDamage = 50;
        range = 100;
    }
    else if (unitType == 3) {
        unitHp = 40;
        unitMaxHp = 40;
        range = 300;
    }
}

void endMenu(RenderWindow& window, Text& endScreen, Text& endScoreText, Text& pressEscape)
{
    window.draw(endScreen);
    window.draw(endScoreText);
    window.draw(pressEscape);
    window.display();
}

void move(Sprite& objectS, Unit& objectU, int direc) {
    if (objectU.currentState != 1) {
        objectU.Xindex = 0;
    }
    objectU.currentState = 1;
    for (int i = 0; i < moveLatency; i++) {
        objectS.setPosition(objectS.getPosition() + Vector2f(direc * 1, 0));
    }
    objectS.setTextureRect(IntRect({ objectU.Xindex * frameResolution,frameResolution }, { frameResolution,frameResolution }));
    objectU.animationLatency += 1;
    if (objectU.animationLatency >= animationLatencyLimit) {
        objectU.Xindex += 1;
        if (objectU.Xindex == objectU.animationFrames) {
            objectU.Xindex = 0;
        }
        objectU.animationLatency = 0;
    }
    
}

void addUnit(vector<Sprite>& listS, vector<Unit>& listU, Texture& Texture, vector<RectangleShape>& listHp, int Direction, int unitType) {
    if (unitType == 1) {
        Sprite sprite(Texture);
        if (Direction == 1) {
            sprite.setPosition(Vector2f(100, 865));
        }
        else {
            sprite.setPosition(Vector2f(1600, 865));
        }
        sprite.setTextureRect(IntRect({ 0 * frameResolution,0 }, { frameResolution,frameResolution }));
        listS.push_back(move(sprite));
        listU.push_back(Unit(Direction, unitType));
    }
    else if (unitType == 2) {
        Sprite sprite(Texture);
        if (Direction == 1) {
            sprite.setPosition(Vector2f(100, 865));
        }
        else {
            sprite.setPosition(Vector2f(1600, 865));
        }
        sprite.setTextureRect(IntRect({ 0 * frameResolution,0 }, { frameResolution,frameResolution }));
        listS.push_back(move(sprite));
        listU.push_back(Unit(Direction, unitType));
    }
    else if (unitType == 3) {
        Sprite sprite(Texture);
        if (Direction == 1) {
            sprite.setPosition(Vector2f(100, 865));
        }
        else {
            sprite.setPosition(Vector2f(1600, 865));
        }
        sprite.setTextureRect(IntRect({ 2 * frameResolution,0 }, { frameResolution,frameResolution }));
        listS.push_back(move(sprite));
        listU.push_back(Unit(Direction, unitType));
    }
    RectangleShape hpBar({ 44,5 });
    if (Direction == 1) {
        hpBar.setPosition(Vector2f(100 + hpBarOffset, 104));
    }
    else {
        hpBar.setPosition(Vector2f(1600 + hpBarOffset, 104));
    }
    hpBar.setFillColor(Color::Red);
    listHp.push_back(move(hpBar));
}

void attack(Sprite& objectS, Unit& objectU, Unit& attacked, vector<Sprite>& listB, Texture& ArrowTexture) {
    if (objectU.currentState != 2) {
        objectU.Xindex = 0;
    }
    objectU.currentState = 2;
    if (objectU.unitType == 3) { 
         objectS.setTextureRect(IntRect({ objectU.Xindex * frameResolution,frameResolution * 4 }, { frameResolution,frameResolution }));
    }
    else {
         objectS.setTextureRect(IntRect({ objectU.Xindex * frameResolution,frameResolution * 2 }, { frameResolution,frameResolution }));
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
                sprite.setPosition(objectS.getPosition() + Vector2f(64, 64));
                sprite.setTextureRect(IntRect({ 0,0 }, { 64,64 }));
                listB.push_back(move(sprite));

            }
        }
        objectU.animationLatency = 0;
    }

}

void attackBase(Sprite& objectS, Unit& objectU, int& Basehp, vector<Sprite> listB, Texture ArrowTexture) {
    if (objectU.currentState != 2) {
        objectU.Xindex = 0;
    }
    objectU.currentState = 2;
    if (objectU.unitType == 3) { 
            objectS.setTextureRect(IntRect({ objectU.Xindex * frameResolution,frameResolution * 4 }, { frameResolution,frameResolution }));
    }
    else {
           objectS.setTextureRect(IntRect({ objectU.Xindex * frameResolution,frameResolution * 2 }, { frameResolution,frameResolution }));
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
                if (Basehp < 0) {
                    Basehp = 0;
                }
            }
        }
        else { // STYTUACJA GDY LUCZNIK ATAKUJE BO MA WIECEJ KLATEK ANIMACJI klasa 3 - lucznik
            if (objectU.Xindex >= objectU.animationFrames + 2) {
                objectU.Xindex = 0;
                Sprite sprite(ArrowTexture);
                sprite.setPosition(objectS.getPosition() + Vector2f(64, 64));
                sprite.setTextureRect(IntRect({ 0 * 64,0 }, { 64,64 }));
                listB.push_back(move(sprite));

            }
        }
        objectU.animationLatency = 0;
    }
}

void idle(Sprite& objectS, Unit& objectU) {
    if (objectU.currentState != 0) {
         objectU.Xindex = 0;
    }
    objectU.currentState = 0;
    objectS.setTextureRect(IntRect({ objectU.Xindex * frameResolution,0 }, { frameResolution,frameResolution }));
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