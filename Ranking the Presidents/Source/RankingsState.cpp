#include <Presidents/RankingsState.hpp>
#include <Presidents/DataTables.hpp>
#include <Presidents/Foreach.hpp>
#include <Presidents/ResourceHolder.hpp>
#include <Presidents/Utility.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <string>


namespace
{
  const std::vector<RankingData> Table = initializeRankingData();
}

RankingsState::RankingsState(StateStack& stack, Context context)
  : State(stack, context)
  , mLabelTexts()
  , mChronologicalRankingsTexts()
  , mAscendingRankingsTexts()
  , mDescendingRankingsTexts()
  , mView(context.window->getDefaultView())
  , mDisplayBounds(getRankingsDisplayBounds())
  , mIsScrollingUp(false)
  , mIsScrollingDown(false)
  , mScrollSpeed(5.f)
  , mDisplayOrder(Chronological)
  , mCharacterSize(30.f)
  , mLeftRankingsDisplayBound(30.f)
  , mUpperRankingsDisplayBound(130.f)
  , mDistanceBetweenNameAndRank(600.f)
{
  sf::Font& font = context.fonts->get(Fonts::Main);

  updateLabelTexts(mLabelTexts);

  std::vector<RankingData> table = Table;

  updateRankingsTexts(mChronologicalRankingsTexts, table);

  // Sort data in ascending order by rank
  std::sort(table.begin(), table.end(), 
    [] (RankingData a, RankingData b)
	{
		return a.rank < b.rank;
	});
  updateRankingsTexts(mAscendingRankingsTexts, table);

  // Sort data in descending order by rank
  std::sort(table.begin(), table.end(), 
    [] (RankingData a, RankingData b)
	{
		return a.rank > b.rank;
	});
  updateRankingsTexts(mDescendingRankingsTexts, table);
}

void RankingsState::draw()
{
  sf::RenderWindow& window = *getContext().window;

  // Use default view when drawing the labels
  window.setView(window.getDefaultView());
  FOREACH(const sf::Text& text, mLabelTexts)
    window.draw(text);

  // Update the view and display bounds
  window.setView(mView);
  mDisplayBounds = getRankingsDisplayBounds();

  // Determine which vector to draw with
  std::vector<sf::Text>* textsToDraw;
  switch (mDisplayOrder)
  {
    case Chronological:
      textsToDraw = &mChronologicalRankingsTexts;
      break;
    case AscendingRank:
      textsToDraw = &mAscendingRankingsTexts;
      break;
    case DescendingRank:
      textsToDraw = &mDescendingRankingsTexts;
      break;
  }

  // Draw the rankings
  FOREACH(const sf::Text& text, *textsToDraw)
  {
    if (mDisplayBounds.intersects(text.getGlobalBounds()))
      window.draw(text);
  }
}

bool RankingsState::update(sf::Time dt)
{
  float lowerRankingsDisplayBound = 
    mUpperRankingsDisplayBound + (Table.size() * mCharacterSize);
  
  if (mIsScrollingUp && (mDisplayBounds.top > mUpperRankingsDisplayBound))
    mView.move(0.f, -mScrollSpeed);
  if (mIsScrollingDown && ((mDisplayBounds.top + mDisplayBounds.height) < 
    lowerRankingsDisplayBound))
    mView.move(0.f, mScrollSpeed);

  return true;
}

bool RankingsState::handleEvent(const sf::Event& event)
{
  if (event.type == sf::Event::KeyPressed)
  {
    if (event.key.code == sf::Keyboard::BackSpace)
    {
      requestStackPop();
      requestStackPush(States::Profiles);
    }
    if (event.key.code == sf::Keyboard::Return)
    {
      switchDisplayOrder();
    }
  }
  
  // Scroll up if desired
  mIsScrollingUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);

  // Scroll down if desired
  mIsScrollingDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

  return true;
}

void RankingsState::updateLabelTexts(std::vector<sf::Text>& texts) const
{
  texts.clear();

  float xPosition = mLeftRankingsDisplayBound;
  float yPosition = mUpperRankingsDisplayBound - (mCharacterSize * 2);

  sf::Font& font = getContext().fonts->get(Fonts::Main);
  sf::Text text;
  text.setFont(font);
  text.setCharacterSize(mCharacterSize);
  text.setColor(sf::Color::Red);
  text.setStyle(sf::Text::Bold);
  
  // Name label
  text.setString("Name");
  text.setPosition(xPosition, yPosition);
  texts.push_back(text);

  // Rank label
  text.setString("Rank");
  text.setPosition((xPosition + mDistanceBetweenNameAndRank), yPosition);
  texts.push_back(text);

  // Display order label
  text.setString(getDisplayOrderAsString());
  centerOrigin(text);
  text.setPosition((getContext().window->getSize().x / 2.f), 30.f);
  texts.push_back(text);
}

void RankingsState::updateRankingsTexts(std::vector<sf::Text>& texts, 
                                const std::vector<RankingData>& data) const
{
  texts.clear();

  float xPosition = mLeftRankingsDisplayBound;
  float yPosition = mUpperRankingsDisplayBound;

  sf::Font& font = getContext().fonts->get(Fonts::Main);
  sf::Text text;
  text.setFont(font);
  text.setCharacterSize(mCharacterSize);

  for (auto itr = data.begin(); itr != data.end(); ++itr)
  {
    // Make a text for the president's name
    text.setString(itr->name);
    text.setPosition(xPosition, yPosition);
    texts.push_back(text);

    // Make a text for the president's rank
    text.setString(std::to_string(itr->rank));
    text.setPosition((xPosition + mDistanceBetweenNameAndRank), yPosition);
    texts.push_back(text);

    // Prevent the texts from being displayed over each other
    yPosition += mCharacterSize;
  }
}

std::string RankingsState::getDisplayOrderAsString() const
{
  switch (mDisplayOrder)
  {
    case Chronological:
      return "Chronological";
      break;
    case AscendingRank:
      return "Ascending by Rank";
      break;
    case DescendingRank:
      return "Descending by Rank";
      break;
  }

  return "";
}

void RankingsState::switchDisplayOrder()
{
  switch (mDisplayOrder)
  {
    case Chronological:
      mDisplayOrder = AscendingRank;
      break;
    case AscendingRank:
      mDisplayOrder = DescendingRank;
      break;
    case DescendingRank:
      mDisplayOrder = Chronological;
      break;
  }
  
  // Update the label for the display order
  updateLabelTexts(mLabelTexts);
}

sf::FloatRect RankingsState::getRankingsDisplayBounds() const
{
  sf::FloatRect bounds = sf::FloatRect(
    mView.getCenter() - mView.getSize() / 2.f, mView.getSize());

  bounds.top += mUpperRankingsDisplayBound;
  bounds.height -= (mUpperRankingsDisplayBound + 10.f);

  return bounds;
}