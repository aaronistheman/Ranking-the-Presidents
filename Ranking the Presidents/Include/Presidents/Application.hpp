#ifndef PRESIDENTS_APPLICATION_HPP
#define PRESIDENTS_APPLICATION_HPP

#include <SFML/Graphics/RenderWindow.hpp>


class Application
{
  public:
                Application();
    void        run();

  private:
    void        processInput();
    void        update();
    void        render();

  private:
    sf::RenderWindow      mWindow;
};

#endif