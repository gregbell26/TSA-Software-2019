#ifndef ACRYLIC_ENTITIES_HPP
#define ACRYLIC_ENTITIES_HPP

#include <functional>

namespace A2D::EntityManager {

    template<typename T, typename R>
    class UpdatableEntity {
    public:
        UpdatableEntity() = default;
        T onUpdate() { m_onUpdate(); }

        virtual ~UpdatableEntity() = default;

    protected:
        std::function<R> m_onUpdate;

    };
}


#endif //ACRYLIC_ENTITIES_HPP