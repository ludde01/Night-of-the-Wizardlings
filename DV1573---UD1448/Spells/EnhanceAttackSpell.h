#pragma once
#include <Pch/Pch.h>
#include <GameObject/GameObject.h>
#include <Spells/Spell.h>

class EnhanceAttackSpell : public Spell
{
public:
	EnhanceAttackSpell(glm::vec3 pos);
	EnhanceAttackSpell(std::string name, glm::vec3 pos, glm::vec3 direction, float speed, float travelTime, std::string meshName, float cooldown, float nrOfEnhancedAttacks, float attackCooldown, float spellActiveTime);
	~EnhanceAttackSpell();


	float getNrOfAttacks() const;
	float getAttackCooldown() const;

	void setNrOfAttacks(float nrOfEnhancedAttacks);
	void reduceNrOfAttacks(float nrOfEnhancedAttacks);
	void setAttackCooldown(float attackCooldown);
	

	
	void updateActiveSpell(float deltaTime);
	void spellCooldownUpdate(float deltaTime);
	void attackCooldownUpdate(float deltaTime);
	void createSpell(float deltaTime, glm::vec3 spellPos, glm::vec3 directionVector);



	void update(float dt);

private:

	float m_nrOfAttacks = 3;
	float m_attackCooldown = 0;
	float m_spellActiveTime = 0;
};