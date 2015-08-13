#ifndef PRESIDENTS_ABOUTSTATE_HPP
#define PRESIDENTS_ABOUTSTATE_HPP

#include <Presidents/State.hpp>

#include <SFML/Graphics/Text.hpp>


class AboutState : public State
{
  public:
                      AboutState(StateStack& stack, Context context);

    virtual void      draw();
    virtual bool      update(sf::Time dt);
    virtual bool      handleEvent(const sf::Event& event);


  private:
    sf::Text          mDescriptionText;
};

#endif // PRESIDENTS_ABOUTSTATE_HPP