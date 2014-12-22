#include <Presidents/MainMenuState.hpp>
#include <Presidents/Foreach.hpp>
#include <Presidents/ResourceHolder.hpp>
#include <Presidents/Utility.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>


MainMenuState::MainMenuState(StateStack& stack, Context context)
  : State(stack, context)
  , mBackgroundSprite()
  , mOptions()
  , mOptionIndex(0)
{
  sf::Texture& texture = context.textures->get(Textures::JohnTyler);
	sf::Font& font = context.fonts->get(Fonts::Main);

  mBackgroundSprite.setTexture(texture);

  // Add profiles option to menu
  sf::Text profilesOption;
  profilesOption.setFont(font);
  profilesOption.setString("Profiles");
  centerOrigin(profilesOption);
  profilesOption.setPosition(context.window->getView().getSize() / 2.f);
  mOptions.push_back(profilesOption);

  // Add about option to menu
  sf::Text aboutOption;
  aboutOption.setFont(font);
  aboutOption.setString("About");
  centerOrigin(aboutOption);
  aboutOption.setPosition(
    profilesOption.getPosition() + sf::Vector2f(0.f, 30.f));
  mOptions.push_back(aboutOption);

  // Add exit option to menu
  sf::Text exitOption;
  exitOption.setFont(font);
  exitOption.setString("Exit");
  centerOrigin(exitOption);
  exitOption.setPosition(
    profilesOption.getPosition() + sf::Vector2f(0.f, 60.f));
  mOptions.push_back(exitOption);

  updateOptionText();
}

void MainMenuState::draw()
{
  sf::RenderWindow& window = *getContext().window;

  window.setView(window.getDefaultView());
  window.draw(mBackgroundSprite);

  FOREACH(const sf::Text& text, mOptions)
    window.draw(text);
}

bool MainMenuState::update(sf::Time dt)
{
  return true;
}

bool MainMenuState::handleEvent(const sf::Event& event)
{
  if (event.type != sf::Event::KeyPressed)
    return false;

  if (event.key.code == sf::Keyboard::Return)
  {
    if (mOptionIndex == Profiles)
    {
      requestStackPop();
      requestStackPush(States::Profiles);
    }
    else if (mOptionIndex == About)
    {
      requestStackPop();
      requestStackPush(States::About);
    }
    else if (mOptionIndex == Exit)
    {
      // The exit option was chosen; by removing itself, 
      // the stack will be empty, and the game will know it is time to close.
			requestStackPop();
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

void MainMenuState::updateOptionText()
{
  if (mOptions.empty())
    return;

  // White all texts
  FOREACH(sf::Text& text, mOptions)
    text.setColor(sf::Color::White);

  // Blue the selected text
  mOptions[mOptionIndex].setColor(sf::Color::Blue);
}