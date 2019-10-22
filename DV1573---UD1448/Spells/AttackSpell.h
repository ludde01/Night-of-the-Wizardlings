#pragma once
#include <Pch/Pch.h>
#include <GameObject/GameObject.h>
#include <Spells/Spell.h>

class AttackSpell : public Spell
{
public:
	AttackSpell(glm::vec3 pos, glm::vec3 direction, const AttackSpellBase* spellBase);
	~AttackSpell();

	const int& getNrofBounce() const;
	const int& getLocalBounce() const;
	void setBounceNormal(glm::vec3& normal);	

	virtual void update(float deltaTime);
	void updateRigidbody(float deltaTime, btRigidBody* body);
	const AttackSpellBase* getSpellBase();

private:
	const AttackSpellBase* m_spellBase;
	int m_localBounce = 0;
	int m_nrOfBounce = 0;
	int m_bounceCounter = 0;
	float m_bounceTime = 0;
	glm::vec3 m_bounceNormal;
	bool m_setNewDir = true;	


};