#ifndef PRESIDENTS_APPLICATION_HPP
#define PRESIDENTS_APPLICATION_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>


class Application
{
  public:
                Application();
    void        run();

  private:
    void        processInput();
    void        update(sf::Time dt);
    void        render();

  private:		
    static const sf::Time	  TimePerFrame;

    sf::RenderWindow      mWindow;
    sf::Texture           mTexture;
    sf::Sprite            mSprite;
};

#endif