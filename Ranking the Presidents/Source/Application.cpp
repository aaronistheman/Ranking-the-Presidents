#include <Presidents/Application.hpp>
#include <Presidents/AboutState.hpp>
#include <Presidents/DescriptionsState.hpp>
#include <Presidents/MainMenuState.hpp>
#include <Presidents/ProfilesState.hpp>
#include <Presidents/RankingsState.hpp>
#include <Presidents/State.hpp>
#include <Presidents/StateIdentifiers.hpp>
#include <Presidents/Utility.hpp>

#include <SFML/Window/Event.hpp>


const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application()
  : mWindow(sf::VideoMode(800, 550), "Ranking the Presidents")
  , mTextures()
  , mFonts()
  , mStateStack(State::Context(mWindow, mTextures, mFonts))
  , mStatisticsText()
  , mStatisticsUpdateTime()
  , mStatisticsNumFrames(0)
{
  mWindow.setKeyRepeatEnabled(false);

  mTextures.load(Textures::JohnTyler, "Media/Textures/JohnTyler.png");
  mFonts.load(Fonts::Main, "Media/Sansation.ttf");

  mStatisticsText.setFont(mFonts.get(Fonts::Main));
  mStatisticsText.setPosition(5.f, 5.f);
  mStatisticsText.setCharacterSize(10);

  registerStates();
  mStateStack.pushState(States::MainMenu);
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

      // Check inside this loop, because stack might be empty before update() call
      if (mStateStack.isEmpty())
        mWindow.close();
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
    mStateStack.handleEvent(event);

    if (event.type == sf::Event::Closed)
      mWindow.close();
  }
}

void Application::update(sf::Time dt)
{
  mStateStack.update(dt);
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

  mStateStack.draw();

  mWindow.setView(mWindow.getDefaultView());
  mWindow.draw(mStatisticsText);

  mWindow.display();
}

void Application::registerStates()
{
  mStateStack.registerState<MainMenuState>(States::MainMenu);
  mStateStack.registerState<ProfilesState>(States::Profiles);
  mStateStack.registerState<DescriptionsState>(States::Descriptions);
  mStateStack.registerState<RankingsState>(States::Rankings);
  mStateStack.registerState<AboutState>(States::About);
}