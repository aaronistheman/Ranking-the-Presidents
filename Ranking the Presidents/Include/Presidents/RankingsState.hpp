#ifndef PRESIDENTS_RANKINGSSTATE_HPP
#define PRESIDENTS_RANKINGSSTATE_HPP

#include <Presidents/RankingData.hpp>
#include <Presidents/State.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>


class RankingsState : public State
{
  public:
                      RankingsState(StateStack& stack, Context context);

    virtual void      draw();
    virtual bool      update(sf::Time dt);
    virtual bool      handleEvent(const sf::Event& event);


  private:
    // Fills argument texts with the labels for the rankings table
    void              createLabelTexts(std::vector<sf::Text>& texts) const;
    
    // Fills argument texts with the sf::Text objects to display the rankings
    void              createRankingsTexts(std::vector<sf::Text>& texts, 
                                  const std::vector<RankingData>& data) const;
    
    // Returns the boundaries in which to display the rankings
    sf::FloatRect     getRankingsDisplayBounds() const;

  private:
    std::vector<sf::Text>   mLabelTexts;
    std::vector<sf::Text>   mRankingsTexts;
    sf::View                mView;
    sf::FloatRect           mDisplayBounds;

    bool                    mIsScrollingUp;
    bool                    mIsScrollingDown;

    float                   mCharacterSize;
    float                   mScrollSpeed;
    float                   mUpperRankingsDisplayBound;
};

#endif // PRESIDENTS_RANKINGSSTATE_HPP