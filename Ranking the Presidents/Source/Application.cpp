#include <Presidents/Application.hpp>

#include <SFML/Window/Event.hpp>


const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application()
  : mWindow(sf::VideoMode(400, 400), "Ranking the Presidents")
  , mTexture()
  , mSprite()
{
  if (!mTexture.loadFromFile("Media/Textures/JohnTyler.png"))
  {
    // handle loading error
  }
  mSprite.setTexture(mTexture);
  mSprite.setPosition(100.f, 100.f);
}

void Application::run()
{
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  while (mWindow.isOpen())
  {
    timeSinceLastUpdate += clock.restart();
    while (timeSinceLastUpdate > TimePerFrame)
    {
      timeSinceLastUpdate -= TimePerFrame;
      processInput();
      update(TimePerFrame);
    }
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

void Application::update(sf::Time dt)
{
}

void Application::render()
{
  mWindow.clear();
  mWindow.draw(mSprite);
  mWindow.display();
}