#ifndef PRESIDENTS_DESCRIPTIONSSTATE_HPP
#define PRESIDENTS_DESCRIPTIONSSTATE_HPP

#include <Presidents/State.hpp>

#include <SFML/Graphics/Text.hpp>


class DescriptionsState : public State
{
  public:
                      DescriptionsState(StateStack& stack, Context context);

    virtual void      draw();
    virtual bool      update(sf::Time dt);
    virtual bool      handleEvent(const sf::Event& event);


  private:
    sf::Text          mDescriptionText;
};

#endif // PRESIDENTS_DESCRIPTIONS_HPP