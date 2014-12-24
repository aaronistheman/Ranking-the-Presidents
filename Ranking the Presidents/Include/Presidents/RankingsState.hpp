#ifndef PRESIDENTS_RANKINGSSTATE_HPP
#define PRESIDENTS_RANKINGSSTATE_HPP

#include <Presidents/State.hpp>

#include <SFML/Graphics/Text.hpp>


class RankingsState : public State
{
  public:
                      RankingsState(StateStack& stack, Context context);

    virtual void      draw();
    virtual bool      update(sf::Time dt);
    virtual bool      handleEvent(const sf::Event& event);


  private:
    sf::Text                mDescriptionText;
    std::vector<sf::Text>   mTexts;
};

#endif // PRESIDENTS_RANKINGSSTATE_HPP