#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <SFML/Window/ContextSettings.hpp>
#include <iostream>
#include <vector>
#include <cstdint>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "main.cpp";


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
    if (objectU.unitDierction == -1 && objectU.unitType == 3) {
        if (objectU.Xindex < 2) {
            objectU.Xindex = 2;
        }
    }
    for (int i = 0; i < moveLatency; i++) {
        objectS.setPosition(objectS.getPosition() + Vector2f(direc * 1, 0));
    }
    objectS.setTextureRect(IntRect({ objectU.Xindex * frameResolution,frameResolution }, { frameResolution,frameResolution }));
    objectU.animationLatency += 1;
    if (objectU.unitType == 3 && objectU.unitDierction == -1) { // STYTUACJA GDY lucznik i WAZNE TYLKO RPZECIWNIK BO MA W DRUGA STRONE KLATKI USTAWIONE
        if (objectU.animationLatency >= animationLatencyLimit) {
            objectU.Xindex += 1;
            if (objectU.Xindex == objectU.animationFrames + 2) {
                objectU.Xindex = 2;
            }
            objectU.animationLatency = 0;
        }
    }
    else {
        if (objectU.animationLatency >= animationLatencyLimit) {
            objectU.Xindex += 1;
            if (objectU.Xindex == objectU.animationFrames) {
                objectU.Xindex = 0;
            }
            objectU.animationLatency = 0;
        }
    }
}

void addUnit(vector<Sprite>& listS, vector<Unit>& listU, Texture& Texture, int Direction, int unitType) {
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

}

void attack(Sprite& objectS, Unit& objectU, Unit& attacked, vector<Sprite>& listB, Texture& ArrowTexture) {
    if (objectU.currentState != 2) {
        objectU.Xindex = 0;
    }
    objectU.currentState = 2;
    if (objectU.unitType == 3) {
        if (objectU.unitDierction == 1) {
            objectS.setTextureRect(IntRect({ objectU.Xindex * frameResolution,frameResolution * 4 }, { frameResolution,frameResolution }));
        }
        else {
            objectS.setTextureRect(IntRect({ frameResolution * (objectU.animationFrames + 1) - objectU.Xindex * frameResolution ,frameResolution * 4 }, { frameResolution,frameResolution }));
        }
    }
    else {
        if (objectU.unitDierction == 1) {
            objectS.setTextureRect(IntRect({ objectU.Xindex * frameResolution,frameResolution * 2 }, { frameResolution,frameResolution }));
        }
        else {
            objectS.setTextureRect(IntRect({ frameResolution * (objectU.animationFrames - 1) - objectU.Xindex * frameResolution ,frameResolution * 2 }, { frameResolution,frameResolution }));
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
                sprite.setTextureRect(IntRect({ 0 * 64,0 }, { 64,64 }));
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
        if (objectU.unitDierction >= 1) {
            objectS.setTextureRect(IntRect({ objectU.Xindex * frameResolution,frameResolution * 4 }, { frameResolution,frameResolution }));
        }
        else {
            objectS.setTextureRect(IntRect({ frameResolution * (objectU.animationFrames + 1) - objectU.Xindex * frameResolution ,frameResolution * 4 }, { frameResolution,frameResolution }));
        }
    }
    else {
        if (objectU.unitDierction >= 1) {
            objectS.setTextureRect(IntRect({ objectU.Xindex * frameResolution,frameResolution * 2 }, { frameResolution,frameResolution }));
        }
        else {
            objectS.setTextureRect(IntRect({ frameResolution * (objectU.animationFrames - 1) - objectU.Xindex * frameResolution ,frameResolution * 2 }, { frameResolution,frameResolution }));
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
        if (objectU.unitType == 3 && objectU.unitDierction == -1) {
            objectU.Xindex = 2;
        }
        else {
            objectU.Xindex = 0;
        }
    }
    objectU.currentState = 0;
    objectS.setTextureRect(IntRect({ objectU.Xindex * frameResolution,0 }, { frameResolution,frameResolution }));
    objectU.animationLatency += 1;

    if (objectU.unitType == 3 && objectU.unitDierction == -1) {
        if (objectU.animationLatency == animationLatencyLimit) {
            objectU.Xindex += 1;
            if (objectU.Xindex == objectU.animationFrames + 2) {
                objectU.Xindex = 2;
            }
            objectU.animationLatency = 0;
        }
    }
    else {
        if (objectU.animationLatency == animationLatencyLimit) {
            objectU.Xindex += 1;
            if (objectU.Xindex == objectU.animationFrames) {
                objectU.Xindex = 0;
            }
            objectU.animationLatency = 0;
        }
    }
}
