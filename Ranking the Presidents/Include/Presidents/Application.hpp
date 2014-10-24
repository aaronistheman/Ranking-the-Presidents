#ifndef PRESIDENTS_APPLICATION_HPP
#define PRESIDENTS_APPLICATION_HPP

#include <Presidents/ResourceHolder.hpp>
#include <Presidents/ResourceIdentifiers.hpp>
// #include <Presidents/StateStack.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>


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
    TextureHolder         mTextures;
    FontHolder            mFonts;
    // StateStack            mStateStack;

    sf::Text              mStatisticsText;
    sf::Time              mStatisticsUpdateTime;
    std::size_t           mStatisticsNumFrames;
};

#endif