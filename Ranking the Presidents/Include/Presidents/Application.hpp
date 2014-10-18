#ifndef PRESIDENTS_APPLICATION_HPP
#define PRESIDENTS_APPLICATION_HPP

#include <Presidents/StateStack.hpp>

#include <SFML/Graphics.hpp>


class Application
{
  public:
                Application();
    void        run();

  private:
    void        processInput();
    void        update(sf::Time dt);
    void        updateStatistics(sf::Time dt);
    void        render();

    void        registerStates();

  private:		
    static const sf::Time	  TimePerFrame;

    sf::RenderWindow      mWindow;
    sf::Texture           mTexture;
    sf::Sprite            mSprite;

    StateStack            mStateStack;

    sf::Font              mStatisticsFont;
    sf::Text              mStatisticsText;
    sf::Time              mStatisticsUpdateTime;
    std::size_t           mStatisticsNumFrames;
};

#endif