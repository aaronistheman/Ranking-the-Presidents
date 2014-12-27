#ifndef PRESIDENTS_RANKINGSSTATE_HPP
#define PRESIDENTS_RANKINGSSTATE_HPP

#include <Presidents/DescriptionData.hpp>
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
    void              updateLabelTexts(std::vector<sf::Text>& texts) const;
    
    // Fills argument texts with the sf::Text objects to display the rankings
    void              updateRankingsTexts(std::vector<sf::Text>& texts, 
                                  const std::vector<DescriptionData>& data) const;
    
    std::string       getDisplayOrderAsString() const;

    void              switchDisplayOrder();
    
    // Returns the boundaries in which to display the rankings
    sf::FloatRect     getRankingsDisplayBounds() const;

  private:
    enum DisplayOrder
    {
      Chronological,
      AscendingRank,
      DescendingRank,
    };

  private:
    std::vector<sf::Text>   mLabelTexts;
    std::vector<sf::Text>   mChronologicalRankingsTexts;
    std::vector<sf::Text>   mAscendingRankingsTexts;
    std::vector<sf::Text>   mDescendingRankingsTexts;
    sf::View                mView;
    sf::FloatRect           mDisplayBounds;

    bool                    mIsScrollingUp;
    bool                    mIsScrollingDown;
    float                   mScrollSpeed;
    DisplayOrder            mDisplayOrder;

    // Details regarding table dimensions
    float                   mCharacterSize;   // also used as row height
    float                   mLeftRankingsDisplayBound;
    float                   mUpperRankingsDisplayBound;
    float                   mDistanceBetweenNameAndRank;
};

#endif // PRESIDENTS_RANKINGSSTATE_HPP