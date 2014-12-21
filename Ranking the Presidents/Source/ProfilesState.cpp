#include <Presidents/ProfilesState.hpp>
#include <Presidents/Foreach.hpp>
#include <Presidents/ResourceHolder.hpp>
#include <Presidents/Utility.hpp>

#include <SFML/Graphics/RenderWindow.hpp>


ProfilesState::ProfilesState(StateStack& stack, Context context)
  : State(stack, context)
  , mOptions()
  , mOptionIndex(0)
{
  sf::Font& font = context.fonts->get(Fonts::Main);

  // Add descriptions option to menu
  sf::Text descriptionsOption;
  descriptionsOption.setFont(font);
  descriptionsOption.setString("View Presidential Descriptions");
  centerOrigin(descriptionsOption);
  descriptionsOption.setPosition(context.window->getView().getSize() / 2.f);
  mOptions.push_back(descriptionsOption);

  // Add rankings option to menu
  sf::Text rankingsOption;
  rankingsOption.setFont(font);
  rankingsOption.setString("View Rankings");
  centerOrigin(rankingsOption);
  rankingsOption.setPosition(descriptionsOption.getPosition() + sf::Vector2f(0.f, 30.f));
  mOptions.push_back(rankingsOption);

  // Add back option to menu
  sf::Text backOption;
  backOption.setFont(font);
  backOption.setString("Back");
  centerOrigin(backOption);
  backOption.setPosition(descriptionsOption.getPosition() + sf::Vector2f(0.f, 60.f));
  mOptions.push_back(backOption);

  updateOptionText();
}

void ProfilesState::draw()
{
  sf::RenderWindow& window = *getContext().window;

  window.setView(window.getDefaultView());

  FOREACH(const sf::Text& text, mOptions)
    window.draw(text);
}

bool ProfilesState::update(sf::Time dt)
{
  return true;
}

bool ProfilesState::handleEvent(const sf::Event& event)
{
  if (event.type != sf::Event::KeyPressed)
    return false;

  if (event.key.code == sf::Keyboard::Return)
  {
    if (mOptionIndex == Descriptions)
    {
      requestStackPop();
      requestStackPush(States::Descriptions);
    }
    else if (mOptionIndex == Rankings)
    {
      requestStackPop();
      requestStackPush(States::Rankings);
    }
    else if (mOptionIndex == Back)
    {
			requestStackPop();
      requestStackPush(States::MainMenu);
    }
  }

  else if (event.key.code == sf::Keyboard::Up)
  {
    // Decrement and wrap-around
    if (mOptionIndex > 0)
      mOptionIndex--;
    else
      mOptionIndex = mOptions.size() - 1;

    updateOptionText();
  }

  else if (event.key.code == sf::Keyboard::Down)
  {
    // Increment and wrap-around
    if (mOptionIndex < mOptions.size() - 1)
      mOptionIndex++;
    else
      mOptionIndex = 0;

    updateOptionText();
  }

  return true;
}

void ProfilesState::updateOptionText()
{
  if (mOptions.empty())
    return;

  // White all texts
  FOREACH(sf::Text& text, mOptions)
    text.setColor(sf::Color::White);

  // Red the selected text
  mOptions[mOptionIndex].setColor(sf::Color::Red);
}