#ifndef PRESIDENTS_RANKINGSSTATE_HPP
#define PRESIDENTS_RANKINGSSTATE_HPP

#include <Presidents/RankingData.hpp>
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
    // Fills argument texts with the sf::Text objects needed to display
    // the data in argument data
    void              createTexts(std::vector<sf::Text>& texts, 
                                  const std::vector<RankingData>& data);

  private:
    sf::Text                mDescriptionText;
    std::vector<sf::Text>   mTexts;
};

#endif // PRESIDENTS_RANKINGSSTATE_HPP