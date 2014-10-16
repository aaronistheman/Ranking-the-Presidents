#include <Presidents/Application.hpp>
#include <Presidents/Utility.hpp>

#include <SFML/Window/Event.hpp>


const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application()
  : mWindow(sf::VideoMode(400, 400), "Ranking the Presidents")
  , mTexture()
  , mSprite()
  , mStatisticsFont()
  , mStatisticsText()
  , mStatisticsUpdateTime()
  , mStatisticsNumFrames(0)
{
  if (!mTexture.loadFromFile("Media/Textures/JohnTyler.png"))
  {
    // handle loading error
  }
  mSprite.setTexture(mTexture);
  mSprite.setPosition(100.f, 100.f);

  mStatisticsFont.loadFromFile("Media/Sansation.ttf");
  mStatisticsText.setFont(mStatisticsFont);
  mStatisticsText.setPosition(5.f, 5.f);
  mStatisticsText.setCharacterSize(10);
}

void Application::run()
{
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  while (mWindow.isOpen())
  {
    // elapsedTime is passed as an argument to updateStatistics()
    sf::Time elapsedTime = clock.restart();
    timeSinceLastUpdate += elapsedTime;

    while (timeSinceLastUpdate > TimePerFrame)
    {
      timeSinceLastUpdate -= TimePerFrame;
      processInput();
      update(TimePerFrame);
    }

    updateStatistics(elapsedTime);
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

void Application::updateStatistics(sf::Time dt)
{
  mStatisticsUpdateTime += dt;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");
							 
		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Application::render()
{
  mWindow.clear();
  mWindow.draw(mSprite);
  mWindow.draw(mStatisticsText);
  mWindow.display();
}