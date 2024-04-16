#include "klasy.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "ProjektPK4");
    tgui::Gui gui(window);
    GUI Interface;
    Password Pswd;
    Test Test;
    Test.Load();
    try
    {
        Interface.Initiate(gui);
        Pswd.AddElements(gui);
        Test.AddElements(gui);
        Test.OpenWindow(gui);
    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            gui.handleEvent(event);
        }

        window.clear();
        gui.draw();
        window.display();
    }

    return EXIT_SUCCESS;
}
