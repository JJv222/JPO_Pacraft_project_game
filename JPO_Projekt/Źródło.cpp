#include "Game.h"

enum  GameState { Menu, Tutorial, Controls, Playing };

int main()
{
    // Utworzenie okna
    sf::RenderWindow window(sf::VideoMode(800, 600), "Gra");

    // Aktualny stan gry
    GameState currentState = GameState::Menu;

    // Wybrany poziom trudnoœci
    int selectedDifficulty = 0; // Domyœlnie wybrany pierwszy poziom trudnoœci
    int selectedLevel = 0; // Wybrany poziom trudnoœci w menu poziomów
    //Tekstury
    // przyciski do sterowania
    sf::Texture ControlTexture1;
    sf::Sprite ControlSprite1;
    if (!ControlTexture1.loadFromFile("Textures/MainMenu/klawisz1.png"))
    {
		return -1;
	}
    ControlSprite1.setTexture(ControlTexture1);
    ControlSprite1.setScale(3.5, 3.5f);
    ControlSprite1.setPosition(200.f, 380.f);

    sf::Texture ControlTexture2;
    sf::Sprite ControlSprite2;
    if (!ControlTexture2.loadFromFile("Textures/MainMenu/klawisz2.png"))
    {
        return -1;
    }
    ControlSprite2.setTexture(ControlTexture2);
    ControlSprite2.setScale(2.3f, 2.3f);
    ControlSprite2.setPosition(0.f, 465);

    sf::Texture ControlTexture3;
    sf::Sprite ControlSprite3;
    if (!ControlTexture3.loadFromFile("Textures/MainMenu/klawisz3.png"))
    {
		return -1;
	}
    ControlSprite3.setTexture(ControlTexture3);
    ControlSprite3.setScale(3.5f, 3.5f);
    ControlSprite3.setPosition(130.f, 150.f);
    //logo
    sf::Texture LogoTexture;
    sf::Sprite LogoSprite;
    if (!LogoTexture.loadFromFile("Textures/MainMenu/logo.png"))
    {
        return -1;
    }
    LogoSprite.setTexture(LogoTexture);
    LogoSprite.setScale(5.5f, 5.5f);
    LogoSprite.setPosition(65.5f, -90.f);
    //t³o
    sf::Texture BackgroundTexture;
    sf::Sprite BackgroundSprite;
    if (!BackgroundTexture.loadFromFile("Textures/MainMenu/background.jpg"))
    {
        return -1;
    }
    BackgroundSprite.setTexture(BackgroundTexture);
    float scaleX = 800.f / 1280.f; // Skalowanie wzd³u¿ osi X
    float scaleY = 600.f / 800.f; // Skalowanie wzd³u¿ osi Y
    BackgroundSprite.setScale(scaleX, scaleY);
    //przyciski
    sf::Texture ButtonTexture;
    sf::Sprite ButtonSprite;
    if (!ButtonTexture.loadFromFile("Textures/MainMenu/button.png"))
    {
        return -1;
    }
    ButtonSprite.setTexture(ButtonTexture);
    vector<sf::Sprite> Buttons;
    for (int i = 0; i < 6; i++) {
        Buttons.push_back(ButtonSprite);
        Buttons[i].setTexture(ButtonTexture);
        Buttons[i].setScale(3.2f, 3.2f);
        Buttons[i].setPosition(195.f, 100.f + i * 70.f);
    }
    // Tekst i czcionka dla opcji menu
    sf::Font font;
    if (!font.loadFromFile("fonts/minecraft.ttf"))
    {
        return -1;
    }
    Text menuTexts[6];
    string menuOptions[6] = { "Easy", "Normal", "Hard", "Poradnik","Sterowanie", "Wyjscie" };
    for (int i = 0; i < 6; ++i) //Generowanie napisów menu
    {
        menuTexts[i].setFont(font);
        menuTexts[i].setString(menuOptions[i]);
        menuTexts[i].setCharacterSize(24);
        menuTexts[i].setFillColor(sf::Color::White);
        menuTexts[i].setPosition(360, 200 + i * 70);
    }

    // Pe³ne wyjaœnienie gry
    Text tutorialText1;
    tutorialText1.setFont(font);
    tutorialText1.setString("Witaj w PACRAFT! Gra polega na zebraniu wszystkich monet w labiryncie, \nunikajac jednoczesnie schwytania przez potwory! Kazdy kontakt z potworem \noznacza utrate jednego cennego zycia. Nie pozwol sobie stracic wszystkich,\nponiewaz oznacza to koniec rozgrywki.\n ");
    tutorialText1.setCharacterSize(22);
    tutorialText1.setFillColor(sf::Color::White);
    tutorialText1.setPosition(0, 115);
    tutorialText1.setOutlineColor(sf::Color::Black);
    tutorialText1.setOutlineThickness(1.4);
    Text tutorialText2;
    tutorialText2.setFont(font);
    tutorialText2.setString("Omowmy teraz plansze, poniewaz na mapie moze spotkac wiele obiektow:\n- monety, dajace punkty\n- zlote jablko, ktore po zjedzeniu daje wieksza ilosc puntkow, potwory zaczy\nnaja od ciebie uciekac oraz daje mozliwosc elimiacji przeciwnikow zyskujac przy tym \ndodatkowe punkty, im wiecej pokonanych tym wiecej punktow zgarniasz !\n- diament, ktory pojawia sie sporadycznie i daje mozliwosc zdobycia bardzo\nduzej ilosc punktow\n-mikstura przyspieszenia ktora na chwile przyspiesza poruszanie bohatera\n-mikstura sily, ktora chwilowo daje bohaterowi mozliwosc pokonania potworow\n-pola lawy, ktore po zetknieciu z bohaterem sprawiaja ze umiera\n-piasekdusz, ktory sprawia bardzo wolne poruszanie bohatera\n-lod, ktory sprawia chwilowe zatrzymanie bohatera\n\nIlosc i czas pojawiania przeszkod zalezy od wybranego poziomu trudnosci\n Skoro juz wszystko wiesz o grze to zycze powodzenia !! : )");
    tutorialText2.setCharacterSize(22);
    tutorialText2.setFillColor(sf::Color::White);
    tutorialText2.setPosition(0, 220);
    tutorialText2.setOutlineColor(sf::Color::Black);
    tutorialText2.setOutlineThickness(1.4);
    //setrowanie
    Text controlText1;
    controlText1.setFont(font);
    controlText1.setString("Gora\n\nDol\n\nWybierz:");
    controlText1.setCharacterSize(22);
    controlText1.setFillColor(sf::Color::White);
    controlText1.setPosition(93, 469);
    controlText1.setOutlineColor(sf::Color::Black);
    controlText1.setOutlineThickness(1.4);

    Text controlText2;
    controlText2.setFont(font);
    controlText2.setString("          Gora\n\n\n\n\nLewo   Dol   Prawo");
    controlText2.setCharacterSize(30);
    controlText2.setFillColor(sf::Color::White);
    controlText2.setPosition(110, 135);
    controlText2.setOutlineColor(sf::Color::Black);
    controlText2.setOutlineThickness(1.4);

    Text controlText3;
    controlText3.setFont(font);
    controlText3.setString("Wstrzymaj/Wznow rozgrywke\n\nPrzerwij gre");
    controlText3.setCharacterSize(30);
    controlText3.setFillColor(sf::Color::White);
    controlText3.setPosition(350, 400);
    controlText3.setOutlineColor(sf::Color::Black);
    controlText3.setOutlineThickness(1.4);


    // Pêtla gry
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (currentState == GameState::Menu)
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        if (selectedLevel > 0)
                            selectedLevel--;
                    }
                    else if (event.key.code == sf::Keyboard::Down)
                    {
                        if (selectedLevel < 5)
                            selectedLevel++;
                    }
                    else if (event.key.code == sf::Keyboard::Enter)
                    {
                        if (selectedLevel == 5)
                        {
                            window.close();
                        }
                        else if (selectedLevel == 3)
                        {
                            currentState = GameState::Tutorial;
                        }
                        else if(selectedLevel == 4)
                        {
                            currentState = GameState::Controls;
                        }
                        else
                        {
                            currentState = GameState::Playing;
                        }
                    }
                }
            }
            else if (currentState == GameState::Tutorial or currentState == GameState::Controls)
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        currentState = GameState::Menu;
                    }
                }
            }
        }

        window.clear();
        window.draw(BackgroundSprite);
        if (currentState == GameState::Menu)
        {

            window.draw(LogoSprite);
            // Rysowanie menu
            for (int i = 0; i < 6; ++i)
            {
                if (selectedLevel == i)
                {
                    menuTexts[i].setFillColor(sf::Color::Green);
                }
                else
                {
                    menuTexts[i].setFillColor(sf::Color::White);
                }
                if (i == 1 || i==3 || i==5) menuTexts[i].setPosition(348, menuTexts[i].getPosition().y);
                if(i == 4) menuTexts[i].setPosition(335, menuTexts[i].getPosition().y);
                window.draw(Buttons[i]);
                window.draw(menuTexts[i]);
            }
            window.draw(ControlSprite2);
            window.draw(controlText1);
        }
        else if (currentState == GameState::Tutorial)
        {
            LogoSprite.setPosition(70.5f, -150.f);
            window.draw(LogoSprite);
            // Rysowanie tutorialu
            window.draw(tutorialText1);
            window.draw(tutorialText2);
        }
        else if (currentState == GameState::Controls)
        {
			LogoSprite.setPosition(70.5f, -150.f);
			window.draw(LogoSprite);
            window.draw(ControlSprite1);
            window.draw(ControlSprite3);
            window.draw(controlText2);
            window.draw(controlText3);
		}
        window.display();

        if (currentState == GameState::Playing)
        {
            window.draw(LogoSprite);
            // Inicjalizacja gry
            Game game(selectedLevel + 1);

            // Pêtla gry
            while (game.running())
            {
                game.Update();
                game.DrawWindow();
            }

            currentState = GameState::Menu; // Powrót do menu po zakoñczeniu gry
        }
    }

    // Koniec programu
    return 0;
}
