#include <Presidents/RankingsState.hpp>
#include <Presidents/DataTables.hpp>
#include <Presidents/Foreach.hpp>
#include <Presidents/ResourceHolder.hpp>
#include <Presidents/Utility.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <string>
#include <iostream>


namespace
{
  const std::vector<RankingData> Table = initializeRankingData();
}

RankingsState::RankingsState(StateStack& stack, Context context)
  : State(stack, context)
  , mDescriptionText()
  , mView(context.window->getDefaultView())
  , mIsScrollingUp(false)
  , mIsScrollingDown(false)
{
  sf::Font& font = context.fonts->get(Fonts::Main);

  mDescriptionText.setFont(font);
  mDescriptionText.setString("RankingsState: Press Backspace to return");
  centerOrigin(mDescriptionText);
  mDescriptionText.setPosition(context.window->getView().getSize() / 2.f);

  createTexts(mTexts, Table);

  for (auto itr = Table.begin(); itr != Table.end(); ++itr)
    std::cout << itr->number << ' '
              << itr->name << ' ' 
              << itr->rank << '\n';
}

void RankingsState::draw()
{
  sf::RenderWindow& window = *getContext().window;

  window.setView(mView);
  window.draw(mDescriptionText);
  FOREACH(const sf::Text& text, mTexts)
    window.draw(text);
}

bool RankingsState::update(sf::Time dt)
{
  if (mIsScrollingUp)
    mView.move(0.f, -10.f);
  if (mIsScrollingDown)
    mView.move(0.f, 10.f);

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
                                const std::vector<RankingData>& data)
{
  texts.clear();

  float xPos = 30.f;
  float yPos = 30.f;

  sf::Font& font = getContext().fonts->get(Fonts::Main);
  sf::Text text;
  text.setFont(font);
  centerOrigin(text);

  // for (auto itr = data.begin(); itr != data.end(); ++itr)
  for (size_t i = 0; i < 5; ++i)
  {
    // Make a text for the president's name
    text.setString(data[i].name);
    text.setPosition(xPos, yPos);
    texts.push_back(text);

    // Make a text for the president's rank
    text.setString(std::to_string(data[i].rank));
    text.setPosition((xPos + 400.f), yPos);
    texts.push_back(text);

    // Prevent the texts from being displayed over each other
    yPos += 30.f;
  }
}