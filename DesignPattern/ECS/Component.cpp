#include "Component.h"

using namespace Jay;

Component::Component(ComponentType type) 
	: _type(type)
{
}

void Component::OnUpdate(const std::chrono::milliseconds& deltaTime)
{
}

std::string Component::ToStr() const
{
	return std::string("type: " + std::to_string(static_cast<uint8_t>(_type)));
}

ComponentType Component::GetType() const
{
	return _type;
}

Entity* Component::GetOwner() const
{
	return _owner;
}

void Component::SetOwner(Entity* owner)
{
	_owner = owner;
}
