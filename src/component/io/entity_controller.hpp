#ifndef ENTITY_CONTROLLER_HPP
#define ENTITY_CONTROLLER_HPP

namespace sl {
  class Entity;
  class EntityController final {
    private:
      Entity* entity;
      float speedConstant{200};
    public:
      explicit EntityController(Entity* entity);

      void control(float deltaTime);
  };
};

#endif