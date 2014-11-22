#ifndef PRESIDENTS_MAINMENUSTATE_HPP
#define PRESIDENTS_MAINMENUSTATE_HPP

#include <Presidents/State.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class MainMenuState : public State
{
  public:
                  MainMenuState(StateStack& stack, Context context);

    virtual void      draw();
    virtual bool      update(sf::Time dt);
    virtual bool      handleEvent(const sf::Event& event);

  private:
    sf::Sprite        mBackgroundSprite;
    sf::Text          mText;              // for testing purposes
};

#endif // PRESIDENTS_MAINMENUSTATE_HPP