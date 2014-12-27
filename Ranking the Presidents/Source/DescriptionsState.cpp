#include <Presidents/DescriptionsState.hpp>
#include <Presidents/DataTables.hpp>
#include <Presidents/ResourceHolder.hpp>
#include <Presidents/Utility.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>


namespace
{
  const std::vector<DescriptionData> Table = initializeDescriptionData();
}

DescriptionsState::DescriptionsState(StateStack& stack, Context context)
  : State(stack, context)
  , mDescriptionText()
{
  sf::Font& font = context.fonts->get(Fonts::Main);

  mDescriptionText.setFont(font);
  mDescriptionText.setString("DescriptionsState: Press Backspace to return");
  centerOrigin(mDescriptionText);
  mDescriptionText.setPosition(context.window->getView().getSize() / 2.f);

  for (auto itr = Table.begin(); itr != Table.end(); ++itr)
    std::cout << "Number: " << itr->number << '\n' 
              << "Name: " << itr->name << '\n' 
              << "Rank: " << itr->rank << '\n'
              << "Category: " << itr->category << '\n'
              << '\n';
}

void DescriptionsState::draw()
{
  sf::RenderWindow& window = *getContext().window;

  window.setView(window.getDefaultView());
  window.draw(mDescriptionText);
}

bool DescriptionsState::update(sf::Time dt)
{
  return true;
}

bool DescriptionsState::handleEvent(const sf::Event& event)
{
  if (event.type == sf::Event::KeyReleased &&
      event.key.code == sf::Keyboard::BackSpace)
  {
    requestStackPop();
    requestStackPush(States::Profiles);
  }

  return true;
}