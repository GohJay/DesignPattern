#include "Entity.h"

using namespace Jay;

Entity::Entity(EntityType type, EntityId id)
	: _type(type), _id(id)
{
}

void Entity::OnUpdate(const std::chrono::milliseconds& deltaTime)
{
	for (const auto& cmpt : _cmpts)
	{
		if (!cmpt)
			continue;

		cmpt->OnUpdate(deltaTime);
	}
}

std::string Entity::ToStr() const
{
	return std::string("type: " + std::to_string(static_cast<uint8_t>(_type)) +
		", id: " + std::to_string(static_cast<uint64_t>(_id)));
}

EntityType Entity::GetType() const
{
	return _type;
}

EntityId Entity::GetId() const
{
	return _id;
}
