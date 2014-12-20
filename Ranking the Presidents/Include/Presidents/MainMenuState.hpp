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

    void              updateOptionText();


  private:
    enum OptionNames
    {
      Profiles,
      About,
      Exit,
    };

  private:
    sf::Sprite        mBackgroundSprite;

    std::vector<sf::Text> mOptions;
    std::size_t       mOptionIndex;
};

#endif // PRESIDENTS_MAINMENUSTATE_HPP