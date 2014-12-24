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
  , mView(context.window->getDefaultView())
  , mIsScrollingUp(false)
  , mIsScrollingDown(false)
  , mCharacterSize(30.f)
  , mScrollSpeed(5.f)
  , mUpperRankingsDisplayBound(100.f)
{
  sf::Font& font = context.fonts->get(Fonts::Main);

  createTexts(mTexts, Table);
}

void RankingsState::draw()
{
  sf::RenderWindow& window = *getContext().window;

  window.setView(mView);
  sf::FloatRect bounds = getRankingsDisplayBounds();
  FOREACH(const sf::Text& text, mTexts)
  {
    if (bounds.intersects(text.getGlobalBounds()))
      window.draw(text);
  }
}

bool RankingsState::update(sf::Time dt)
{
  if (mIsScrollingUp)
    mView.move(0.f, -mScrollSpeed);
  if (mIsScrollingDown)
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

void RankingsState::createTexts(std::vector<sf::Text>& texts, 
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
  bounds.height -= mUpperRankingsDisplayBound;

  return bounds;
}