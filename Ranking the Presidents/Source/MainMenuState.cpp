#include <Presidents/MainMenuState.hpp>
#include <Presidents/ResourceHolder.hpp>
#include <Presidents/Utility.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>


MainMenuState::MainMenuState(StateStack& stack, Context context)
  : State(stack, context)
  , mBackgroundSprite()
  , mText()
{
  mBackgroundSprite.setTexture(context.textures->get(Textures::JohnTyler));

  mText.setFont(context.fonts->get(Fonts::Main));
  mText.setString("MainMenuState");
  centerOrigin(mText);
}

void MainMenuState::draw()
{
  sf::RenderWindow& window = *getContext().window;
  window.draw(mBackgroundSprite);
  window.draw(mText);
}

bool MainMenuState::update(sf::Time dt)
{
  return true;
}

bool MainMenuState::handleEvent(const sf::Event& event)
{
  if (event.type == sf::Event::KeyReleased)
  {
    requestStackPop();
    requestStackPush(States::Profiles);
  }

  return true;
}