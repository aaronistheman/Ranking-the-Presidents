#include <Presidents/AboutState.hpp>
#include <Presidents/ResourceHolder.hpp>
#include <Presidents/Utility.hpp>

#include <SFML/Graphics/RenderWindow.hpp>


AboutState::AboutState(StateStack& stack, Context context)
  : State(stack, context)
  , mDescriptionText()
{
  sf::Font& font = context.fonts->get(Fonts::Main);

  mDescriptionText.setFont(font);
  mDescriptionText.setString("AboutState");
  centerOrigin(mDescriptionText);
  mDescriptionText.setPosition(context.window->getView().getSize() / 2.f);
}

void AboutState::draw()
{
  sf::RenderWindow& window = *getContext().window;

  window.setView(window.getDefaultView());
  window.draw(mDescriptionText);
}

bool AboutState::update(sf::Time dt)
{
  return true;
}

bool AboutState::handleEvent(const sf::Event& event)
{
  return true;
}