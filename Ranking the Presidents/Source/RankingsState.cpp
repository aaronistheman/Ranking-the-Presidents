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
  , mRankingsTexts()
  , mView(context.window->getDefaultView())
  , mDisplayBounds(getRankingsDisplayBounds())
  , mIsScrollingUp(false)
  , mIsScrollingDown(false)
  , mCharacterSize(30.f)
  , mScrollSpeed(5.f)
  , mUpperRankingsDisplayBound(100.f)
{
  sf::Font& font = context.fonts->get(Fonts::Main);

  createLabelTexts(mLabelTexts);
  createRankingsTexts(mRankingsTexts, Table);
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

  // Draw the rankings
  FOREACH(const sf::Text& text, mRankingsTexts)
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
  if (event.type == sf::Event::KeyReleased &&
      event.key.code == sf::Keyboard::BackSpace)
  {
    requestStackPop();
    requestStackPush(States::Profiles);
  }
  
  // Scroll up if desired
  mIsScrollingUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);

  // Scroll down if desired
  mIsScrollingDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

  return true;
}

void RankingsState::createLabelTexts(std::vector<sf::Text>& texts) const
{
  texts.clear();

  float xPosition = 30.f;
  float yPosition = mUpperRankingsDisplayBound - (mCharacterSize * 2);

  sf::Font& font = getContext().fonts->get(Fonts::Main);
  sf::Text text;
  text.setFont(font);
  text.setCharacterSize(mCharacterSize);
  text.setColor(sf::Color::Red);
  text.setStyle(sf::Text::Bold);
  centerOrigin(text);
  
  // Name label
  text.setString("Name");
  text.setPosition(xPosition, yPosition);
  texts.push_back(text);

  // Rank label
  text.setString("Rank");
  text.setPosition((xPosition + 400.f), yPosition);
  texts.push_back(text);
}

void RankingsState::createRankingsTexts(std::vector<sf::Text>& texts, 
                                const std::vector<RankingData>& data) const
{
  texts.clear();

  float xPosition = 30.f;
  float yPosition = mUpperRankingsDisplayBound;

  sf::Font& font = getContext().fonts->get(Fonts::Main);
  sf::Text text;
  text.setFont(font);
  text.setCharacterSize(mCharacterSize);
  centerOrigin(text);

  for (auto itr = data.begin(); itr != data.end(); ++itr)
  {
    // Make a text for the president's name
    text.setString(itr->name);
    text.setPosition(xPosition, yPosition);
    texts.push_back(text);

    // Make a text for the president's rank
    text.setString(std::to_string(itr->rank));
    text.setPosition((xPosition + 400.f), yPosition);
    texts.push_back(text);

    // Prevent the texts from being displayed over each other
    yPosition += mCharacterSize;
  }
}

sf::FloatRect RankingsState::getRankingsDisplayBounds() const
{
  sf::FloatRect bounds = sf::FloatRect(
    mView.getCenter() - mView.getSize() / 2.f, mView.getSize());

  bounds.top += mUpperRankingsDisplayBound;
  bounds.height -= (mUpperRankingsDisplayBound + 10.f);

  return bounds;
}