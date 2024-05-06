#pragma once
#include "Component.h"
#include <array>
#include <optional>
#include <functional>

enum class EntityType : std::uint8_t
{
	Pc = 0,
	Mob,
	Prop,
	Invalid = 255
};
constexpr std::uint8_t EntityTypeCount = 4;
constexpr std::uint8_t EntityTypeCountWithoutInvalid = 3;

using EntityId = std::uint64_t;

namespace Jay
{
	class Entity final
	{
	public:
		Entity(EntityType type, EntityId id);
		~Entity() = default;
		
	public:
		void OnUpdate(const std::chrono::milliseconds& deltaTime);
		std::string ToStr() const;
		
	public:
		EntityType GetType() const;
		EntityId GetId() const;

	public:
		template<typename CMPT, typename... ARGS>
		bool Install(ARGS... args);

		template<typename... CMPTS>
		auto GetCmpts() const -> std::optional<std::tuple<std::shared_ptr<CMPTS>...>>;

	private:
		template<typename CMPT>
		auto GetCmpt() const -> std::shared_ptr<CMPT>;

	private:
		std::array<std::shared_ptr<Component>, ComponentTypeCountWithoutInvalid> _cmpts;
		EntityType _type;
		EntityId _id;
	};

	template<typename CMPT, typename ...ARGS>
	bool Entity::Install(ARGS... args)
	{
		ComponentType type = GetStaticType<CMPT>();
		if (ComponentType::Invalid == type)
			return false;

		_cmpts[static_cast<std::uint8_t>(type)] = std::make_shared<CMPT>(args...);
		return true;
	}

	template<typename ...CMPTS>
	auto Entity::GetCmpts() const -> std::optional<std::tuple<std::shared_ptr<CMPTS>...>>
	{
		std::tuple<std::shared_ptr<CMPTS>...> cmpts(GetCmpt<CMPTS>()...);

		bool hasCmpts = true;

		std::apply([&](const std::shared_ptr<CMPTS>&... cmpt)
			{
				hasCmpts = (hasCmpts && ... && cmpt);
			}, cmpts);

		if (!hasCmpts)
			return std::nullopt;

		return std::make_optional(cmpts);
	}

	template<typename CMPT>
	auto Entity::GetCmpt() const -> std::shared_ptr<CMPT>
	{
		ComponentType type = GetStaticType<CMPT>();
		if (ComponentType::Invalid == type)
			return nullptr;

		const std::shared_ptr<Component>& cmpt = _cmpts[static_cast<std::uint8_t>(type)];
		return std::static_pointer_cast<CMPT>(cmpt);
	}
}
