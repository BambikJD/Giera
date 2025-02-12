//Biblioteki
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <SFML/Window/ContextSettings.hpp>
#include <iostream>
#include <vector>
#include <cstdint>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "functions.h"

using namespace std;
using namespace sf;

int frameResolution = 192;
int FrameLimit = 60;
int animationLatencyLimit = FrameLimit/14.4;
int ALLYBASEHP = 500;
int ENEMYBASEHP = 500;
int EXPERIENCE = 0;
int MONEY = 30;

bool isRain = false;
int moveLatency = 144 / FrameLimit;
int moneyLatency = 0;
int moneyLatencyLimit = 5 * animationLatencyLimit;
int arrowNumber = 0;
int ISMENUOPEN = 1;
int hpBarOffset = 74;


// ZASOBY
string MAINFOLDER = "C:/Users/Bartek/Desktop/Giera-master/";

Font font(MAINFOLDER + "Giera/Assets/Canterbury.ttf"); //Zmieniona czcionka
Music MainThemeS(MAINFOLDER + "Giera/Assets/MainTheme.ogg"); //Muzyka
string AnimationAllyLink1 = MAINFOLDER + "Giera/Assets/Warrior_Blue.png";
string AnimationAllyLink2 = MAINFOLDER + "Giera/Assets/Torch_Blue.png";
string AnimationAllyLink3 = MAINFOLDER + "Giera/Assets/Archer_Blue.png";
string AnimationEnemyLink1 = MAINFOLDER + "Giera/Assets/Warrior_Red_reversed.png";
string AnimationEnemyLink2 = MAINFOLDER + "Giera/Assets/Torch_Red.png";
string AnimationEnemyLink3 = MAINFOLDER + "Giera/Assets/Archer_Red_reversed.png";
string ArrowLinkEnemy = MAINFOLDER + "Giera/Assets/ArrowR.png";
string ArrowLinkAlly = MAINFOLDER + "Giera/Assets/Arrow.png";
string backgroundLink = MAINFOLDER + "Giera/Assets/background.png";
string playButtonLink = MAINFOLDER + "Giera/Assets/PlayButton.png";
string heartBaseHP = MAINFOLDER + "Giera/Assets/heart.png";
string coinLink = MAINFOLDER + "Giera/Assets/MonetaBezTla.png";
string menuBackgroundLink = MAINFOLDER + "Giera/Assets/menuBackgroundL.png";
string swordSoundLink = MAINFOLDER + "Giera/Assets/swordAttackSound.wav";
string ArrowRainLink = MAINFOLDER + "Giera/Assets/ArrowD.png";

Texture ArrowRainTexture(ArrowRainLink);


SoundBuffer swordSoundBuffer(swordSoundLink);
Sound swordSound(swordSoundBuffer);

int main() {
    // CZAS
    time_t now;
    time_t before;
    time_t nowEnemy1;
    time_t beforeEnemy1;
    time_t nowEnemy2;
    time_t beforeEnemy2;
    time_t nowEnemy3;
    time_t beforeEnemy3;
    time_t nowRain;
    time_t beforeRain;

    //Teksty
    Text pressEnter(font);
    Text startButton(font);
    Text endScreen(font);
    Text endScoreText(font);
    Text moneyInfo(font);
    Text allyBaseInfo(font);
    Text enemyBaseInfo(font);
    Text title(font);
    Text expInfo(font);
    Text pressEscape(font);

    pressEnter.setString("Press Enter to Play");
    pressEnter.setCharacterSize(40);
    pressEnter.setFillColor(Color::Black);
    pressEnter.setPosition({ 790, 680 });

    endScreen.setString("Game Over!");
    endScreen.setFillColor(Color::Black);
    endScreen.setCharacterSize(100);
    endScreen.setPosition({ 690, 300 });

    pressEscape.setFillColor(Color::Black);
    pressEscape.setString("Press Escape to Exit or Enter to return to Menu");
    pressEscape.setCharacterSize(40);
    pressEscape.setPosition({ 580, 520 });

    endScoreText.setFillColor(Color::Black);
    endScoreText.setCharacterSize(70);
    endScoreText.setPosition({ 725, 420 });

    title.setFillColor(Color::Black);
    title.setCharacterSize(150);
    title.setString("Age of Before");
    title.setPosition({ 590, 150 });

    moneyInfo.setCharacterSize(50);
    moneyInfo.setPosition(Vector2f(20, 10));

    expInfo.setCharacterSize(50);
    expInfo.setFillColor(Color::Red);
    expInfo.setPosition(Vector2f(20, 90));

    allyBaseInfo.setCharacterSize(40);
    allyBaseInfo.setPosition(Vector2f(70, 665));

    enemyBaseInfo.setCharacterSize(40);
    enemyBaseInfo.setPosition(Vector2f(1770, 665));
    
    // Menu 
    Texture menuBackground(menuBackgroundLink, false, IntRect({ 0,0 }, { 1920, 192 }));
    Sprite topInterface(menuBackground);

    //Przycisk Play
    Texture playButton(playButtonLink, false, IntRect({ 0,0 }, { 1024, 1024 }));
    Sprite playButtonS(playButton);
    playButtonS.setPosition({ 775, 300 });

    //Moneta
    Texture Coin(coinLink, false, IntRect({ 0,0 }, { 136, 214 }));
    Sprite CoinS(Coin);
    CoinS.setPosition({ 300,10 });
    Coin.setSmooth(true);

    //Serce HP bazy Ally
    Texture Heart(heartBaseHP, false, IntRect({ 0,0 }, { 363, 309 }));
    Sprite HeartS(Heart);
    HeartS.setPosition({ 132,668 });
    HeartS.setScale({ 0.12f, 0.12f });

    //Serce HP bazy Enemy
    Sprite HeartSEnemy(Heart);
    HeartSEnemy.setPosition({ 1832,668 });
    HeartSEnemy.setScale({ 0.12f, 0.12f });

    //Ceny 
    Texture WarriorBlueMoneyT(AnimationAllyLink1);
    Texture TorchBlueMoneyT(AnimationAllyLink2);
    Texture ArcherBlueMoneyT(AnimationAllyLink3);

    Sprite WarriorBlueMoneyS(WarriorBlueMoneyT); Unit WarriorBlueMoneyU(1,1);
    Sprite ArcherBlueMoneyS(ArcherBlueMoneyT); Unit ArcherBlueMoneyU(1, 3);
    Sprite TorchBlueMoneyS(TorchBlueMoneyT); Unit TorchBlueMoneyU(1, 2);
    Sprite ArrowAbility(ArrowRainTexture);

    WarriorBlueMoneyS.setPosition({ 400, 5 });
    TorchBlueMoneyS.setPosition({ 592, 5 });
    ArcherBlueMoneyS.setPosition({ 784, 5 });
    ArrowAbility.setPosition({ 1400, 45 }); ArrowAbility.setScale({ 1.5,1.5 });

    Text WarriorMoney(font);
    WarriorMoney.setFillColor(Color::Red);
    WarriorMoney.setString("10     Q");
    WarriorMoney.setCharacterSize(40);
    WarriorMoney.setPosition(WarriorBlueMoneyS.getPosition() + Vector2f(20, 10));

    Text ArcherMoney(font);
    ArcherMoney.setFillColor(Color::Red);
    ArcherMoney.setString("20     W");
    ArcherMoney.setCharacterSize(40);
    ArcherMoney.setPosition(TorchBlueMoneyS.getPosition() + Vector2f(20, 10));

    Text TorchMoney(font);
    TorchMoney.setFillColor(Color::Red);
    TorchMoney.setString("25     E");
    TorchMoney.setCharacterSize(40); 
    TorchMoney.setPosition(ArcherBlueMoneyS.getPosition() + Vector2f(20, 10));

    //------------------------------------------------------- INITIALIZE ----------------------------------------------
    //Glowne okno gry
    ContextSettings settings;
    settings.antiAliasingLevel = 16;
    RenderWindow window(VideoMode({ 1920, 1080 }), "Age of War", Style::Default, State::Fullscreen, settings);
    window.setFramerateLimit(FrameLimit);

    vector<Sprite> enemiesS;
    vector<Unit> enemiesU;
    vector<Sprite> alliesS;
    vector<Unit> alliesU;
    vector<Sprite> enemiesB;
    vector<Sprite> alliesB;
    vector<RectangleShape> alliesHp;
    vector<RectangleShape> enemiesHp;
    vector<Sprite> rain;

    //-------------------------------------------------------- LOAD ----------------------------------------------------
    // Tlo
    Texture backgroundTexture(backgroundLink, false, IntRect({ 0, 0 }, { 1920, 1080 }));
    Sprite background(backgroundTexture);

    //Tekstury
    Texture allyArrowTexture(ArrowLinkAlly);
    Texture enemyArrowTexture(ArrowLinkEnemy);
    Texture allyTexture1(AnimationAllyLink1);
    Texture allyTexture2(AnimationAllyLink2);
    Texture allyTexture3(AnimationAllyLink3);
    Texture enemyTexture1(AnimationEnemyLink1);
    Texture enemyTexture2(AnimationEnemyLink2);
    Texture enemyTexture3(AnimationEnemyLink3);

    //Music
    MainThemeS.play();
    MainThemeS.setLooping(true);

    //--------------------------------------------------------- LOAD ----------------------------------------------
    while (window.isOpen()) // GLOWNA PETLA GRY
    {
        //------------------------------------------------------- UPDATE ----------------------------------------------

        if (Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            if (Mouse::getPosition().x - 600 > 0 && Mouse::getPosition().x - 600 < 720 &&
                Mouse::getPosition().y - 300 > 0 && Mouse::getPosition().y - 300 < 480) {
                if (ISMENUOPEN == 1) {
                    ISMENUOPEN = 0;
                    time(&before);
                    time(&beforeEnemy1);
                    time(&beforeEnemy2);
                    time(&beforeEnemy3);
                    time(&beforeRain);
                }
                else {
                    ISMENUOPEN = 1;
                    time(&before);
                    time(&beforeEnemy1);
                    time(&beforeEnemy2);
                    time(&beforeEnemy3);
                    ALLYBASEHP = 500;
                    ENEMYBASEHP = 500;
                    EXPERIENCE = 0;
                    MONEY = 30;
                    moneyLatency = 0;
                    enemiesS = {};
                    enemiesU = {};
                    alliesS = {};
                    alliesU = {};
                    enemiesB = {};
                    alliesB = {};
                    alliesHp = {};
                    enemiesHp = {};
                    rain = {};
                }
            }
        }
        while (const optional event = window.pollEvent()) // EVENT ZAMKNIECIA OKNA
        {
            if (event->is<Event::Closed>())
                window.close();
          

            if (const auto* keyPressed = event->getIf<Event::KeyPressed>()) //Escape = Exit
            {
                if (keyPressed->scancode == Keyboard::Scancode::Escape)
                {
                    window.close();
                }

                if (keyPressed->scancode == Keyboard::Scancode::Enter)
                {
                    if (ISMENUOPEN == 1) {
                        ISMENUOPEN = 0;
                        time(&before);
                        time(&beforeEnemy1);
                        time(&beforeEnemy2);
                        time(&beforeEnemy3);
                        time(&beforeRain);
                    }
                    else {
                        ISMENUOPEN = 1;
                        time(&before);
                        time(&beforeEnemy1);
                        time(&beforeEnemy2);
                        time(&beforeEnemy3);
                        ALLYBASEHP = 500;
                        ENEMYBASEHP = 500;
                        EXPERIENCE = 0;
                        MONEY = 30;
                        moneyLatency = 0;
                        enemiesS = {};
                        enemiesU = {};
                        alliesS = {};
                        alliesU = {};
                        enemiesB = {};
                        alliesB = {};
                        alliesHp = {};
                        enemiesHp = {};
                        rain = {};
                    }
                }
            }


        }

        if (ISMENUOPEN == 1) {
            window.clear(Color::White);
            //Rysowanie Menu
            window.draw(background);
            window.draw(title);
            window.draw(pressEnter);
            window.draw(playButtonS);
            window.display();

        }
        else {
       
            if (!(ENEMYBASEHP <= 0 || ALLYBASEHP <= 0)) { // WARUNEK ZAKONCZENIA GRY

                if (moneyLatency == moneyLatencyLimit) { // Mamona
                    MONEY += 1;
                    moneyLatency = 0;
                }
                else {
                    moneyLatency += 1;
                }

                moneyInfo.setString("Money: " + to_string(MONEY)); //Wyswietlanie mamony

                idle(WarriorBlueMoneyS, WarriorBlueMoneyU);
                idle(TorchBlueMoneyS, TorchBlueMoneyU);
                idle(ArcherBlueMoneyS, ArcherBlueMoneyU);

                // RESPIENIE PRZECIWNIKOW ---------------------------------------------------------------------------------------
                time(&nowEnemy1);
                if (difftime(nowEnemy1, beforeEnemy1) > 1) {
                    addUnit(enemiesS, enemiesU, enemyTexture1,enemiesHp, -1, 1);
                    time(&beforeEnemy1);
                }
                time(&nowEnemy2);
                if (difftime(nowEnemy2, beforeEnemy2) > 17) {
                    addUnit(enemiesS, enemiesU, enemyTexture2,enemiesHp, -1, 2);
                    time(&beforeEnemy2);
                }
                time(&nowEnemy3);
                if (difftime(nowEnemy3, beforeEnemy3) > 20) {
                    addUnit(enemiesS, enemiesU, enemyTexture3,enemiesHp, -1, 3);
                    time(&beforeEnemy3);
                }

                // EVENTY KLAWIATURY -----------------------------------------------------------------------------------------------------------------------------------------------------------

                if (Keyboard::isKeyPressed(Keyboard::Key::Q)) { // DODAWANIE SOJUSZNIKOW
                    time(&now);
                    if (difftime(now, before) > 0.1 && MONEY >= 10) {
                        addUnit(alliesS, alliesU, allyTexture1,alliesHp, 1, 1);
                        time(&before);
                        MONEY -= 10;
                    }
                }

                if (Keyboard::isKeyPressed(Keyboard::Key::W)) { // DODAWANIE SOJUSZNIKOW
                    time(&now);
                    if (difftime(now, before) > 0.1 && MONEY >= 20) {
                        addUnit(alliesS, alliesU, allyTexture2,alliesHp, 1, 2);
                        time(&before);
                        MONEY -= 20;
                    }
                }

                if (Keyboard::isKeyPressed(Keyboard::Key::E)) { // DODAWANIE SOJUSZNIKOW
                    time(&now);
                    if (difftime(now, before) > 0.1 && MONEY >= 25) {
                        addUnit(alliesS, alliesU, allyTexture3,alliesHp, 1, 3);
                        time(&before);
                        MONEY -= 25;
                    }
                }

                if (Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    if (Mouse::getPosition().x - WarriorBlueMoneyS.getPosition().x > 0 && Mouse::getPosition().x - WarriorBlueMoneyS.getPosition().x < 192 &&
                        Mouse::getPosition().y - WarriorBlueMoneyS.getPosition().y > 0 && Mouse::getPosition().y - WarriorBlueMoneyS.getPosition().y < 192) {
                        time(&now);
                        if (difftime(now, before) > 0.1 && MONEY >= 10) {
                            addUnit(alliesS, alliesU, allyTexture1, alliesHp, 1, 1);
                            time(&before);
                            MONEY -= 10;
                        }
                    
                    } else 
                    if (Mouse::getPosition().x - TorchBlueMoneyS.getPosition().x > 0 && Mouse::getPosition().x - TorchBlueMoneyS.getPosition().x < 192 &&
                        Mouse::getPosition().y - TorchBlueMoneyS.getPosition().y > 0 && Mouse::getPosition().y - TorchBlueMoneyS.getPosition().y < 192) {
                        time(&now);
                        if (difftime(now, before) > 0.1 && MONEY >= 20) {
                            addUnit(alliesS, alliesU, allyTexture2, alliesHp, 1, 2);
                            time(&before);
                            MONEY -= 20;
                        }

                    } else 
                    if (Mouse::getPosition().x - ArcherBlueMoneyS.getPosition().x > 0 && Mouse::getPosition().x - ArcherBlueMoneyS.getPosition().x < 192 &&
                        Mouse::getPosition().y - ArcherBlueMoneyS.getPosition().y > 0 && Mouse::getPosition().y - ArcherBlueMoneyS.getPosition().y < 192) {
                        time(&now);
                        if (difftime(now, before) > 0.1 && MONEY >= 25) {
                            addUnit(alliesS, alliesU, allyTexture3, alliesHp, 1, 3);
                            time(&before);
                            MONEY -= 25;
                        }
                    } else
                    if (Mouse::getPosition().x - 1344 > 0 && Mouse::getPosition().x - 1344 < 192 &&
                        Mouse::getPosition().y - 5 > 0 && Mouse::getPosition().y - 5 < 192) {
                        time(&now);
                        if (difftime(now, before) > 1) {
                            time(&before);
                            isRain = true;
                        }
                    }
                }

                if (Keyboard::isKeyPressed(Keyboard::Key::R)) { // DESZCZ STRZAl
                        time(&now);
                        if (difftime(now, before) > 1) {
                             time(&before);
                             isRain = true;
                        }
                }

                // -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

                if (enemiesS.size() != 0 && alliesS.size() != 0) { // GDY SA JEDNOCZESNIE SOJUSZNIK I PRZECIWNIK


                    for (size_t i = 0; i < alliesS.size(); i++) { // PETLA SOJUSZNIKOW
                        alliesHp[i].setPosition(alliesS[i].getPosition() + Vector2f(hpBarOffset,25));
                        if (!empty(enemiesS)) { // GDY SA PRZECIWNICY - Zabezpieczenie przed brakiem przeciwnikow i niesamowicie trudnym do zlokalizowania bledem (error konczacy gre) - po zabiciu przeciwnika, petla iterujaca wychodzila poza rozmiar listy typu wektor
                            if (!((alliesS[i].getPosition().x - enemiesS[0].getPosition().x >= -1 * alliesU[i].range) && (alliesS[i].getPosition().x - enemiesS[0].getPosition().x <= 0))) { // GDY NIE JEST W ZASIEGU ATAKU
                                if (alliesS.size() > 1 && i > 0) { // GDY JEST WIECEJ NIZ 1 SOJUSZNIK
                                    if (!((alliesS[i].getPosition().x - alliesS[i - 1].getPosition().x >= -50) && (alliesS[i].getPosition().x - alliesS[i - 1].getPosition().x <= 0))) { // GDY NIE JEST W KOLIZJI Z INNYM SOJUSZNIKIEM
                                        move(alliesS[i], alliesU[i], 1); // RUCH
                                    }
                                    else { // GDY JEST W KOLIZJI Z INNYM SOJUSZNIKIEM
                                        idle(alliesS[i], alliesU[i]); //USTAWIENIE STOJACEJ TEKSTURY
                                    }
                                }
                                else { // GDY JEST TYLKO 1 SOJUSZNIK
                                    move(alliesS[i], alliesU[i], 1); // RUCH
                                }
                            }
                            else { // GDY JEST W ZASIEGU ATAKU
                                attack(alliesS[i], alliesU[i], enemiesU[0], alliesB, allyArrowTexture); // ATAK NA OPONENTA    
                                if (enemiesU[0].unitHp <= 0) { // USUWANIE OPONENTA GDY MA 0 HP
                                    EXPERIENCE += enemiesU[0].unitType * 10;
                                    MONEY += enemiesU[0].unitType * 5;
                                    enemiesS.erase(enemiesS.begin());
                                    enemiesU.erase(enemiesU.begin());
                                    enemiesHp.erase(enemiesHp.begin());
                                }
                                else {
                                    enemiesHp[0].setSize(Vector2f(((enemiesU[0].unitHp * 100 / enemiesU[0].unitMaxHp)) * 44.0f / 100, 5 ));
                                }

                            }
                        }
                    }


                    for (size_t i = 0; i < enemiesS.size(); i++) { // PETLA PRZECIWNIKOW
                        enemiesHp[i].setPosition(enemiesS[i].getPosition() + Vector2f(hpBarOffset, 25));
                        if (!empty(alliesS)) {
                            if (!((enemiesS[i].getPosition().x - alliesS[0].getPosition().x <= enemiesU[i].range) && (enemiesS[i].getPosition().x - alliesS[0].getPosition().x >= 0))) {
                                if (enemiesS.size() > 1 && i > 0) {
                                    if (!((enemiesS[i].getPosition().x - enemiesS[i - 1].getPosition().x >= 0) && (enemiesS[i].getPosition().x - enemiesS[i - 1].getPosition().x <= 50))) {
                                        move(enemiesS[i], enemiesU[i], -1);
                                    }
                                    else {
                                        idle(enemiesS[i], enemiesU[i]);
                                    }
                                }
                                else {
                                    move(enemiesS[i], enemiesU[i], -1);
                                }
                            }
                            else {
                                attack(enemiesS[i], enemiesU[i], alliesU[0], enemiesB, enemyArrowTexture);
                                if (alliesU[0].unitHp <= 0) {
                                    alliesS.erase(alliesS.begin());
                                    alliesU.erase(alliesU.begin());
                                    alliesHp.erase(alliesHp.begin());

                                }
                                else {
                                    alliesHp[0].setSize(Vector2f(((alliesU[0].unitHp * 100 / alliesU[0].unitMaxHp)) * 44.0f / 100, 5 ));
                                }

                            }
                        }
                    }
                }
                else {
                    if (enemiesS.size() == 0) { // GDY TYLKO SOJUSZNIK
                        for (size_t i = 0; i < alliesS.size(); i++) {
                            alliesHp[i].setPosition(alliesS[i].getPosition() + Vector2f(hpBarOffset, 25));
                            if (!(alliesS[i].getPosition() == Vector2f(1600 - alliesU[i].range, 865))) {
                                if (i > 0) {
                                    if (!((alliesS[i].getPosition().x - alliesS[i - 1].getPosition().x >= -50) && (alliesS[i].getPosition().x - alliesS[i - 1].getPosition().x <= 0))) {
                                        move(alliesS[i], alliesU[i], 1);
                                    }
                                    else {
                                        idle(alliesS[i], alliesU[i]);
                                    }
                                }
                                else {
                                    move(alliesS[i], alliesU[i], 1);
                                }
                            }
                            else {
                                if (alliesU[i].unitType != 3) {
                                    attackBase(alliesS[i], alliesU[i], ENEMYBASEHP, alliesB, allyArrowTexture);
                                }
                                else {
                                    attack(alliesS[i], alliesU[i], alliesU[i], alliesB, allyArrowTexture);
                                }
                            }
                        }
                    }

                    if (alliesS.size() == 0) { // GDY TYLKO PRZECIWNIK
                        for (size_t i = 0; i < enemiesS.size(); i++) {
                            enemiesHp[i].setPosition(enemiesS[i].getPosition() + Vector2f(hpBarOffset, 25));
                            if (!(enemiesS[i].getPosition() == Vector2f(100 + enemiesU[i].range, 865))) {
                                if (i > 0) {
                                    if (!((enemiesS[i].getPosition().x - enemiesS[i - 1].getPosition().x >= 0) && (enemiesS[i].getPosition().x - enemiesS[i - 1].getPosition().x <= 50))) {
                                        move(enemiesS[i], enemiesU[i], -1);
                                    }
                                    else {
                                        idle(enemiesS[i], enemiesU[i]);
                                    }
                                }
                                else {
                                    move(enemiesS[i], enemiesU[i], -1);
                                }
                            }
                            else {
                                if (enemiesU[i].unitType != 3) {
                                    attackBase(enemiesS[i], enemiesU[i], ALLYBASEHP, enemiesB, enemyArrowTexture);
                                }
                                else {
                                    attack(enemiesS[i], enemiesU[i], enemiesU[i], enemiesB, enemyArrowTexture);
                                }
                            }
                        }
                    }
                }

                // Strza³y 
                if (isRain == true) {
                    time(&nowRain);
                    if (arrowNumber < 15) {
                        if (difftime(nowRain*2, beforeRain*2) > 1) {
                            time(&beforeRain);
                            arrowRain(rain, arrowNumber);
                            arrowNumber += 1;
                        }
                    }
                    else {
                        isRain = false;
                        arrowNumber = 0;
                    }
                }

                for (size_t i = 0; i < alliesB.size(); i++) {
                    if (!empty(alliesB)) {
                        for (int j = 0; j < 3*moveLatency; j++) {
                            alliesB[i].setPosition(alliesB[i].getPosition() + Vector2f(1, 0));
                            if (!empty(enemiesS)) {
                                if (alliesB[i].getPosition().x - enemiesS[0].getPosition().x > -3 && (alliesB[i].getPosition().x - enemiesS[0].getPosition().x < 3)) {
                                    enemiesU[0].unitHp -= 20;
                                    if (enemiesU[0].unitHp <= 0) { // USUWANIE OPONENTA GDY MA 0 HP
                                        EXPERIENCE += enemiesU[0].unitType * 10;
                                        MONEY += enemiesU[0].unitType * 5;
                                        enemiesS.erase(enemiesS.begin());
                                        enemiesU.erase(enemiesU.begin());
                                        enemiesHp.erase(enemiesHp.begin());
                                    }else {
                                        enemiesHp[0].setSize(Vector2f(((enemiesU[0].unitHp * 100 / enemiesU[0].unitMaxHp)) * 44.0f / 100, 5 ));

                                    }
                                    alliesB.erase(alliesB.begin() + i);
                                    i -= 1;
                                    break;
                                }
                            }
                            else {
                                if (alliesB[i].getPosition().x - 1600 > -3 && (alliesB[i].getPosition().x - 1600 < 3)) {
                                    ENEMYBASEHP -= 20;
                                    alliesB.erase(alliesB.begin() + i);
                                    i -= 1;
                                    break;
                                }
                            }
                        }
                    }
                }

                for (size_t i = 0; i < rain.size(); i++) {
                    if (!empty(rain)) {
                        for (int j = 0; j < 3 * moveLatency; j++) {
                            if (i != -1 && !empty(rain)) {
                                rain[i].setPosition(rain[i].getPosition() + Vector2f(0, 1));
                                for (int k = 0; k < enemiesS.size(); k++) {
                                    if (!empty(enemiesS)) {
                                        if (rain[i].getPosition().x - enemiesS[k].getPosition().x > 0 && rain[i].getPosition().x - enemiesS[k].getPosition().x < 100 &&
                                            rain[i].getPosition().y - enemiesS[k].getPosition().y > 0 && rain[i].getPosition().y - enemiesS[k].getPosition().y < 50) {
                                            enemiesU[k].unitHp -= 100;
                                            if (enemiesU[k].unitHp <= 0) { // USUWANIE OPONENTA GDY MA 0 HP
                                                EXPERIENCE += enemiesU[k].unitType * 10;
                                                MONEY += enemiesU[k].unitType * 5;
                                                enemiesS.erase(enemiesS.begin() + k);
                                                enemiesU.erase(enemiesU.begin() + k);
                                                enemiesHp.erase(enemiesHp.begin() + k);
                                                rain.erase(rain.begin() + i);                                                
                                                k -= 1;
                                                i -= 1;
                                                break;
                                            }
                                            else {
                                                enemiesHp[k].setSize(Vector2f(((enemiesU[k].unitHp * 100 / enemiesU[k].unitMaxHp)) * 44.0f / 100, 5));
                                                rain.erase(rain.begin() + i);
                                                i -= 1;
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                            else {
                                if (i == -1) {
                                    i = 0;
                                }
                                break;
                            }
                        }
                        if (!empty(rain)) {
                            if (rain[i].getPosition().y > 1080) {
                                rain.erase(rain.begin() + i);
                                i -= 1;
                                break;
                            }
                        }
                    } 
                }

                for (size_t i = 0; i < enemiesB.size(); i++) {
                    if (!empty(enemiesB)) {
                        for (int j = 0; j < 3*moveLatency; j++) {
                            enemiesB[i].setPosition(enemiesB[i].getPosition() + Vector2f(-1, 0));
                            if (!empty(alliesS)) {
                                if (enemiesB[i].getPosition().x - alliesS[0].getPosition().x > 125 && (enemiesB[i].getPosition().x - alliesS[0].getPosition().x < 131)) {
                                    alliesU[0].unitHp -= 20;
                                    if (alliesU[0].unitHp <= 0) { // USUWANIE OPONENTA GDY MA 0 HP
                                        alliesS.erase(alliesS.begin());
                                        alliesU.erase(alliesU.begin()); 
                                        alliesHp.erase(alliesHp.begin());

                                    }
                                    else {
                                        alliesHp[0].setSize(Vector2f(((alliesU[0].unitHp * 100 / alliesU[0].unitMaxHp)) * 44.0f / 100, 5 ));
                                    }
                                    enemiesB.erase(enemiesB.begin() + i);
                                    i -= 1;
                                    break;
                                }
                            }
                            else {
                                if (enemiesB[i].getPosition().x - 100 > 125 && (enemiesB[i].getPosition().x - 100 < 131)) {
                                    ALLYBASEHP -= 20;
                                    enemiesB.erase(enemiesB.begin() + i);
                                    i -= 1;
                                    break;
                                }
                            }
                        }
                    }
                }

                allyBaseInfo.setString(to_string(ALLYBASEHP));
                enemyBaseInfo.setString(to_string(ENEMYBASEHP));
                expInfo.setString("Exp: " + to_string(EXPERIENCE));

                //-------------------------------------------------------- UPDATE ----------------------------------------------
                // 
                //--------------------------------------------------------- DRAW -----------------------------------------------
                if (true) {
                    window.clear(Color::White);

                    //Rysowanie skladnikow okna

                    window.draw(background);

                    window.draw(topInterface);

                    window.draw(moneyInfo);
                    window.draw(HeartS);
                    window.draw(HeartSEnemy);
                    window.draw(CoinS);
                    window.draw(allyBaseInfo);
                    window.draw(enemyBaseInfo);
                    window.draw(expInfo);

                    window.draw(WarriorBlueMoneyS); //Rysowanie postaci
                    window.draw(TorchBlueMoneyS);
                    window.draw(ArcherBlueMoneyS);

                    window.draw(WarriorMoney); //Rysowanie Pieniedzy do postaci
                    window.draw(ArcherMoney);
                    window.draw(TorchMoney);

                    window.draw(ArrowAbility);


                    for (const auto& sprite : alliesS) {
                        window.draw(sprite); // Rysuj kazdy sojusznik
                    }

                    for (const auto& sprite : enemiesS) {
                        window.draw(sprite); // Rysuj kazdy oponent
                    }

                    for (const auto& sprite : alliesB) {
                        window.draw(sprite); // Rysuj kazdy sojusznik strzal
                    }

                    for (const auto& sprite : enemiesB) {
                        window.draw(sprite); // Rysuj kazdy oponent strzal
                    }

                    for (const auto& sprite : enemiesHp) {
                        window.draw(sprite); // Rysuj kazdy pasek zdrowia 
                    }

                    for (const auto& sprite : alliesHp) {
                        window.draw(sprite); // Rysuj kazdy pasek zdrowia
                    }

                    for (const auto& sprite : rain) {
                        window.draw(sprite); // Rysuj kazdy pasek zdrowia
                    }

                    window.display();
                }
                //--------------------------------------------------------- DRAW -----------------------------------------------

            }
            //----------------------------------------------------- Warunek dla EndScreen -------------------------------------------------------

            else {   // ALLYBASEHP <= 0 \\ ENEMYBASEHP <= 0

                int endScore = EXPERIENCE * 100; 
                endScoreText.setString("End Score: " + to_string(endScore));

                endMenu(window, endScreen, endScoreText, pressEscape); //Rysowanie endMenu
            } //Koniec glownego warunku
        } // Koniec is menu open

    } //Koniec Petli Okna Gry

}//Koniec main()
            
    
