#ifndef					INPUTMOVEMENTSYSTEM_HPP_
# define				INPUTMOVEMENTSYSTEM_HPP_

# include				<cmath>

# include				"components/PositionComponent.hpp"
# include				"components/InputMovementComponent.hpp"
# include				"components/OrientationComponent.hpp"

# include				"systems/Base.hpp"
# include				"systems/InputSystem.hpp"

# include				"managers/EntityManager.hh"

# include				"EntityFactory.hpp"

class					InputMovementSystem : public System::Base
{
public:
  InputMovementSystem(void)
    : System::Base()
  {}

  virtual ~InputMovementSystem()
  {}

  virtual void				init(void)
  {}

  virtual void				update(double dt,const ALLEGRO_EVENT &)
  {
    EntityManager::VectorEntity		*entities = EntityManager::getInstance().getAllEntitiesPosessingComponentOfClass<InputMovement>();

    if (entities)
      {
	EntityManager::VectorEntityIT	actualEntity = entities->begin();
	EntityManager::VectorEntityIT	lastEntity = entities->end();

	for (; actualEntity != lastEntity; ++actualEntity)
	  {
	    Entity			&entity = *(*actualEntity);

	    // Get component
	    Position			*p = EntityManager::getInstance().getComponent<Position>(entity);
	    InputMovement		*m = EntityManager::getInstance().getComponent<InputMovement>(entity);
	    Orientation			*o = EntityManager::getInstance().getComponent<Orientation>(entity);
	    Speed			*s = EntityManager::getInstance().getComponent<Speed>(entity);
	    (void)(o);
	    // Get system handling input
	    InputSystem			*input = SystemManager::getInstance().getSystem<InputSystem>();

	    if (input)
	      {
		if (input->isKeyDown(m->keyUp))
		  {
		    p->y -= s->value * dt;
		  }
		if (input->isKeyDown(m->keyDown))
		  {
		    p->y += s->value * dt;
		  }
		if (input->isKeyDown(m->keyLeft))
		  {
		    p->x -= s->value * dt;
		  }
		if (input->isKeyDown(m->keyRight))
		  {
		    p->x += s->value * dt;
		  }
		if (input->isKeyDown(m->keyShoot))
		  {
		    EntityFactory::getInstance().createBullet(entity);
		    input->setOff(m->keyShoot);
		  }
		if (input->isKeyDown(m->keyMissile))
		  {
		    EntityFactory::getInstance().createMissile(entity);
		    input->setOff(m->keyMissile);
		  }
	      }
	    else
	      {
		std::cout << "OMG ERROR" << std::endl; // TODO - throw expcetion
	      }
	  }
	delete entities;
      }
  }

  virtual void				draw(void) const
  {}

protected:

private:
  InputMovementSystem			&operator=(const InputMovementSystem &other);
  InputMovementSystem(const InputMovementSystem &other);
};


#endif					/* !INPUTMOVEMENTSYSTEM_HPP_ */
