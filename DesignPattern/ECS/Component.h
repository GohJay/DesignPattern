#pragma once
#include <memory>
#include <chrono>

enum class ComponentType : std::uint8_t
{
	LocationCmpt = 0,
	Invalid = 255
};
constexpr std::uint8_t ComponentTypeCount = 2;
constexpr std::uint8_t ComponentTypeCountWithoutInvalid = 1;

namespace Jay
{
	class Entity;

	class Component
	{
	public:
		Component(ComponentType type);
		virtual ~Component() = default;

	public:
		virtual void OnUpdate(const std::chrono::milliseconds& deltaTime);
		virtual std::string ToStr() const;

	public:
		ComponentType GetType() const;
		Entity* GetOwner() const;
		void SetOwner(Entity* owner);

	private:
		ComponentType _type;
		Entity* _owner;
	};
}

class LocationCmpt : public Jay::Component
{
public:
	LocationCmpt() : Jay::Component(ComponentType::LocationCmpt)
	{}
	~LocationCmpt() = default;

public:
	std::string ToStr() const { return "LocationCmpt"; }
};

template<typename CMPT>
ComponentType GetStaticType()
{
	ComponentType type = ComponentType::Invalid;

	if (std::is_same<CMPT, LocationCmpt>::value)
	{
		type = ComponentType::LocationCmpt;
	}

	return type;
}
