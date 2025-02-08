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

using namespace std;
using namespace sf;

int frameResolution = 192;
int ISMENUOPEN = 1;
int FrameLimit = 60;
int animationLatencyLimit = FrameLimit/14.4;
int moveLatency = 144 / FrameLimit;
int ALLYBASEHP = 500;
int ENEMYBASEHP = 500;
int MONEY = 30;
int moneyLatency = 0;
int moneyLatencyLimit = 5*animationLatencyLimit;
int hpBarOffset = 74;
int endScore = 0;



//CLASS
class Unit {
public:
    int animationLatency = 0;
    int Xindex = 0;
    int unitHp = NULL;
    int unitDierction;
    int animationFrames = 6;
    int unitType;
    int attackDamage = NULL;
    int range = NULL;
    int currentState = 0;
    int unitMaxHp = NULL;

    Unit(int Direction, int Type) {
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

};

//FUNC

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
    RectangleShape hpBar({44,10});
    if (Direction == 1) {
        hpBar.setPosition(Vector2f(100 + hpBarOffset, 104));
    } else {
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

void attackBase(Sprite& objectS, Unit& objectU, int& Basehp,vector<Sprite> listB, Texture ArrowTexture) {
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

int main() {

    // ZASOBY
    string MAINFOLDER = "C:/Users/Bartek/Desktop/Giera-master/";

    Font font(MAINFOLDER + "Giera/Assets/Canterbury.ttf"); //Zmieniona czcionka
    Music MainThemeS(MAINFOLDER + "Giera/Assets/MainTheme.ogg"); //Muzyka
    string AnimationAllyLink1 = MAINFOLDER + "Giera/Assets/Warrior_Blue.png";
    string AnimationAllyLink2 = MAINFOLDER + "Giera/Assets/Torch_Blue.png";
    string AnimationAllyLink3 = MAINFOLDER + "Giera/Assets/Archer_Blue.png";
    string AnimationEnemyLink1 = MAINFOLDER + "Giera/Assets/Warrior_Red.png";
    string AnimationEnemyLink2 = MAINFOLDER + "Giera/Assets/Torch_Red.png";
    string AnimationEnemyLink3 = MAINFOLDER + "Giera/Assets/Archer_Red.png";
    string ArrowLinkEnemy = MAINFOLDER + "Giera/Assets/ArrowR.png";
    string ArrowLinkAlly = MAINFOLDER + "Giera/Assets/Arrow.png";
    string backgroundLink = MAINFOLDER + "Giera/Assets/background.png";
    string playButtonLink = MAINFOLDER + "Giera/Assets/PlayButton.png";
    string heartBaseHP = MAINFOLDER + "Giera/Assets/heart.png";
    string coinLink = MAINFOLDER + "Giera/Assets/MonetaBezTla.png";
    string menuBackgroundLink = MAINFOLDER + "Giera/Assets/menuBackground.png";


    // CZAS
    time_t now;
    time_t before;
    time_t nowEnemy1;
    time_t beforeEnemy1;
    time_t nowEnemy2;
    time_t beforeEnemy2;
    time_t nowEnemy3;
    time_t beforeEnemy3;

    time(&before);
    time(&beforeEnemy1);
    time(&beforeEnemy2);
    time(&beforeEnemy3);

    //Teksty
    Text pressEnter(font);
    Text startButton(font);
    Text endScreen(font);
    Text endScoreText(font);
    Text moneyInfo(font);
    Text allyBaseInfo(font);
    Text enemyBaseInfo(font);
    Text title(font);

    pressEnter.setString("Press Enter to Play");
    pressEnter.setCharacterSize(40);
    pressEnter.setFillColor(Color::Black);
    pressEnter.setPosition({ 800, 680 });

    endScreen.setString("Game Over!");
    endScreen.setFillColor(Color::Black);
    endScreen.setCharacterSize(100);
    endScreen.setPosition({ 640, 300 });

    endScoreText.setFillColor(Color::Black);
    endScoreText.setCharacterSize(70);
    endScoreText.setPosition({ 660, 420 });

    title.setFillColor(Color::Black);
    title.setCharacterSize(150);
    title.setString("Age of Before");
    title.setPosition({ 590, 150 });

    moneyInfo.setCharacterSize(50);
    moneyInfo.setPosition(Vector2f(0, 10));

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
    playButtonS.setPosition({ 800, 300 });

    //Moneta
    Texture Coin(coinLink, false, IntRect({ 0,0 }, { 136, 214 }));
    Sprite CoinS(Coin);
    CoinS.setPosition({ 300,0 });
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

    //pressEscape
    Text pressEscape(font);
    pressEscape.setFillColor(Color::Black);
    pressEscape.setString("Press Escape to Exit");
    pressEscape.setCharacterSize(40);
    pressEscape.setPosition({ 715, 520 });

    //Ceny 
    Texture WarriorBlueMoneyT(AnimationAllyLink1, false, IntRect({ 0,0 }, { 192, 192 }));
    Texture TorchBlueMoneyT(AnimationAllyLink2, false, IntRect({ 0,0 }, { 192, 192 }));
    Texture ArcherBlueMoneyT(AnimationAllyLink3, false, IntRect({ 0,0 }, { 192, 192 }));

    Sprite WarriorBlueMoneyS(WarriorBlueMoneyT);
    Sprite ArcherBlueMoneyS(ArcherBlueMoneyT);
    Sprite TorchBlueMoneyS(TorchBlueMoneyT);

    WarriorBlueMoneyS.setPosition({ 400, 5 });
    TorchBlueMoneyS.setPosition({ 592, 5 });
    ArcherBlueMoneyS.setPosition({ 784, 5 });

    Text WarriorMoney(font);
    WarriorMoney.setFillColor(Color::Red);
    WarriorMoney.setString("10     Q");
    WarriorMoney.setCharacterSize(40);
    WarriorMoney.setPosition(WarriorBlueMoneyS.getPosition() + Vector2f(20, 10));

    Text ArcherMoney(font);
    ArcherMoney.setFillColor(Color::Red);
    ArcherMoney.setString("25     W");
    ArcherMoney.setCharacterSize(40);
    ArcherMoney.setPosition(TorchBlueMoneyS.getPosition() + Vector2f(20, 10));

    Text TorchMoney(font);
    TorchMoney.setFillColor(Color::Red);
    TorchMoney.setString("20     E");
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

    //-------------------------------------------------------- LOAD ----------------------------------------------------
    // Tlo
    Texture backgroundTexture(backgroundLink, false, IntRect({ 0, 0 }, { 1920, 1080 }));
    Sprite background(backgroundTexture);

    //Tekstury
    Texture allyArrowTexture;
    Texture enemyArrowTexture;
    Texture allyTexture1;
    Texture allyTexture2;
    Texture allyTexture3;
    Texture enemyTexture1;
    Texture enemyTexture2;
    Texture enemyTexture3;

    if (allyTexture1.loadFromFile(AnimationAllyLink1));
    if (allyTexture2.loadFromFile(AnimationAllyLink2));
    if (allyTexture3.loadFromFile(AnimationAllyLink3));
    if (enemyTexture1.loadFromFile(AnimationEnemyLink1));
    if (enemyTexture2.loadFromFile(AnimationEnemyLink2));
    if (enemyTexture3.loadFromFile(AnimationEnemyLink3));
    if (enemyArrowTexture.loadFromFile(ArrowLinkEnemy));
    if (allyArrowTexture.loadFromFile(ArrowLinkAlly));

    //Music
    MainThemeS.play();
    MainThemeS.setLooping(true);
    
    Clock clock;

    //--------------------------------------------------------- LOAD ----------------------------------------------
    while (window.isOpen()) // GLOWNA PETLA GRY
    {
        //------------------------------------------------------- UPDATE ----------------------------------------------

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
                    ISMENUOPEN = 0;
                    time(&beforeEnemy1);
                    time(&beforeEnemy2);
                    time(&beforeEnemy3);
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


                // RESPIENIE PRZECIWNIKOW ---------------------------------------------------------------------------------------
                time(&nowEnemy1);
                if (difftime(nowEnemy1, beforeEnemy1) > 10) {
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

                // -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

                if (enemiesS.size() != 0 && alliesS.size() != 0) { // GDY SA JEDNOCZESNIE SOJUSZNIK I PRZECIWNIK


                    for (size_t i = 0; i < alliesS.size(); i++) { // PETLA SOJUSZNIKOW
                        alliesHp[i].setPosition(alliesS[i].getPosition() + Vector2f(hpBarOffset,10));
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
                                    enemiesS.erase(enemiesS.begin());
                                    enemiesU.erase(enemiesU.begin());
                                    enemiesHp.erase(enemiesHp.begin());


                                }
                                else {
                                    enemiesHp[0].setSize(Vector2f(((enemiesU[0].unitHp * 100 / enemiesU[0].unitMaxHp)) * 44.0f / 100, 10 ));
                                }

                            }
                        }
                    }


                    for (size_t i = 0; i < enemiesS.size(); i++) { // PETLA PRZECIWNIKOW
                        enemiesHp[i].setPosition(enemiesS[i].getPosition() + Vector2f(hpBarOffset, 10));
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
                                    alliesHp[0].setSize(Vector2f(((alliesU[0].unitHp * 100 / alliesU[0].unitMaxHp)) * 44.0f / 100, 10 ));
                                }

                            }
                        }
                    }
                }
                else {
                    if (enemiesS.size() == 0) { // GDY TYLKO SOJUSZNIK
                        for (size_t i = 0; i < alliesS.size(); i++) {
                            alliesHp[i].setPosition(alliesS[i].getPosition() + Vector2f(hpBarOffset, 10));
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
                            enemiesHp[i].setPosition(enemiesS[i].getPosition() + Vector2f(hpBarOffset, 10));
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
                for (size_t i = 0; i < alliesB.size(); i++) {
                    if (!empty(alliesB)) {
                        for (int j = 0; j < 3*moveLatency; j++) {
                            alliesB[i].setPosition(alliesB[i].getPosition() + Vector2f(1, 0));
                            if (!empty(enemiesS)) {
                                if (alliesB[i].getPosition().x - enemiesS[0].getPosition().x > -3 && (alliesB[i].getPosition().x - enemiesS[0].getPosition().x < 3)) {
                                    enemiesU[0].unitHp -= 25;
                                    if (enemiesU[0].unitHp <= 0) { // USUWANIE OPONENTA GDY MA 0 HP
                                        enemiesS.erase(enemiesS.begin());
                                        enemiesU.erase(enemiesU.begin());
                                        enemiesHp.erase(enemiesHp.begin());

                                    }else {
                                        enemiesHp[0].setSize(Vector2f(((enemiesU[0].unitHp * 100 / enemiesU[0].unitMaxHp)) * 44.0f / 100, 10 ));

                                    }
                                    alliesB.erase(alliesB.begin() + i);
                                    i -= 1;
                                    break;
                                }
                            }
                            else {
                                if (alliesB[i].getPosition().x - 1600 > -3 && (alliesB[i].getPosition().x - 1600 < 3)) {
                                    ENEMYBASEHP -= 25;
                                    alliesB.erase(alliesB.begin() + i);
                                    i -= 1;
                                    break;
                                }
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
                                    alliesU[0].unitHp -= 25;
                                    if (alliesU[0].unitHp <= 0) { // USUWANIE OPONENTA GDY MA 0 HP
                                        alliesS.erase(alliesS.begin());
                                        alliesU.erase(alliesU.begin()); 
                                        alliesHp.erase(alliesHp.begin());

                                    }
                                    else {
                                        alliesHp[0].setSize(Vector2f(((alliesU[0].unitHp * 100 / alliesU[0].unitMaxHp)) * 44.0f / 100, 10 ));
                                    }
                                    enemiesB.erase(enemiesB.begin() + i);
                                    i -= 1;
                                    break;
                                }
                            }
                            else {
                                if (enemiesB[i].getPosition().x - 100 > 125 && (enemiesB[i].getPosition().x - 100 < 131)) {
                                    ALLYBASEHP -= 25;
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

                //-------------------------------------------------------- UPDATE ----------------------------------------------
                // 
                //--------------------------------------------------------- DRAW -----------------------------------------------

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

                window.draw(WarriorBlueMoneyS); //Rysowanie postaci
                window.draw(TorchBlueMoneyS);
                window.draw(ArcherBlueMoneyS);

                window.draw(WarriorMoney); //Rysowanie Pieniedzy do postaci
                window.draw(ArcherMoney);
                window.draw(TorchMoney);


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

                window.display();

                //--------------------------------------------------------- DRAW -----------------------------------------------

            }
            //----------------------------------------------------- Warunek dla EndScreen -------------------------------------------------------

            else {   // ALLYBASEHP <= 0 \\ ENEMYBASEHP <= 0

                //Czas
                Time elapsedTime = clock.getElapsedTime();
                clock.stop();
                int timeInSeconds = static_cast<int>(elapsedTime.asSeconds()); //Zmiana na int

                //Wynik Koncowy
                int endScore = timeInSeconds * 513; 
                endScoreText.setString("End Score: " + to_string(endScore));

                endMenu(window, endScreen, endScoreText, pressEscape); //Rysowanie endMenu
            } //Koniec glownego warunku
        } // Koniec is menu open

    } //Koniec Petli Okna Gry

}//Koniec main()
            
    
