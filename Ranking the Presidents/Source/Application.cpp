#include <Presidents/Application.hpp>

#include <SFML/Window/Event.hpp>


Application::Application()
  : mWindow(sf::VideoMode(200, 200), "Ranking the Presidents")
{
}

void Application::run()
{
  while (mWindow.isOpen())
  {
    processInput();
    update();
    render();
  }
}

void Application::processInput()
{
  sf::Event event;
  while (mWindow.pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
      mWindow.close();
  }
}

void Application::update()
{
}

void Application::render()
{
  mWindow.clear();
  mWindow.display();
}