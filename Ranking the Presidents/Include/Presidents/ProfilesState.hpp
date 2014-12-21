#ifndef PRESIDENTS_PROFILESSTATE_HPP
#define PRESIDENTS_PROFILESSTATE_HPP

#include <Presidents/State.hpp>

#include <SFML/Graphics/Text.hpp>


class ProfilesState : public State
{
  public:
                      ProfilesState(StateStack& stack, Context context);

    virtual void      draw();
    virtual bool      update(sf::Time dt);
    virtual bool      handleEvent(const sf::Event& event);

    void              updateOptionText();


  private:
    enum OptionNames
    {
      Descriptions,
      Rankings,
      Back,
    };

  private:
    std::vector<sf::Text> mOptions;
    std::size_t       mOptionIndex;
};

#endif // PRESIDENTS_PROFILESSTATE_HPP