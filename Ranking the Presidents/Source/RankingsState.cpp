#include <Presidents/RankingsState.hpp>
#include <Presidents/ResourceHolder.hpp>
#include <Presidents/Utility.hpp>

#include <SFML/Graphics/RenderWindow.hpp>


RankingsState::RankingsState(StateStack& stack, Context context)
  : State(stack, context)
  , mDescriptionText()
{
  sf::Font& font = context.fonts->get(Fonts::Main);

  mDescriptionText.setFont(font);
  mDescriptionText.setString("RankingsState: Press Backspace to return");
  centerOrigin(mDescriptionText);
  mDescriptionText.setPosition(context.window->getView().getSize() / 2.f);
}

void RankingsState::draw()
{
  sf::RenderWindow& window = *getContext().window;

  window.setView(window.getDefaultView());
  window.draw(mDescriptionText);
}

bool RankingsState::update(sf::Time dt)
{
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

  return true;
}