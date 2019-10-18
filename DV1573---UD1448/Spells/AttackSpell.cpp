#pragma once
#include <Pch/Pch.h>
#include "AttackSpell.h"

AttackSpell::AttackSpell(glm::vec3 pos, glm::vec3 direction, const AttackSpellBase* spellBase)
	: Spell(pos, direction)
{
	m_type = 0;
	m_spellBase = spellBase;
	setTravelTime(spellBase->m_lifeTime);

	setWorldPosition(pos);
	setDirection(direction);
}

AttackSpell::~AttackSpell()
{
}

void AttackSpell::update(float deltaTime)
{
	setTravelTime(getTravelTime() - deltaTime);

	//DEBUG
}

void AttackSpell::updateRigidbody(float deltaTime, btRigidBody* body)
{
	btVector3 pos2 = btVector3(
		getDirection().x,
		getDirection().y,
		getDirection().z) * m_spellBase->m_speed;
	body->setLinearVelocity(pos2);

	btVector3 pos = body->getWorldTransform().getOrigin();
	setWorldPosition(glm::vec3(pos.getX(), pos.getY(), pos.getZ()));
}

const AttackSpellBase* AttackSpell::getSpellBase()
{
	return m_spellBase;
}