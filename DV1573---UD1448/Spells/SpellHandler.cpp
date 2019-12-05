#include "Pch/Pch.h"
#include "SpellHandler.h"
#include <Networking/Client.h>
#include <Loader/BGLoader.h>


SpellHandler::SpellHandler(BulletPhysics * bp)
{
	m_bp = bp;

	attackBase = nullptr;
	enhanceAtkBase = nullptr;
	flamestrikeBase = nullptr;
	fireBase = nullptr;
	reflectBase = nullptr;

	initAttackSpell();
	initEnhanceSpell();
	initFlamestrikeSpell();
	initReflectSpell();
	initFireSpell();
	
	if(bp != nullptr && Client::getInstance()->isSpectating() == false)
		setCharacter(CHARACTER);
}

void SpellHandler::initAttackSpell()
{
	attackBase = new AttackSpellBase();
	attackBase->m_mesh = new Mesh();
	attackBase->m_material = new Material();

	BGLoader tempLoader;	// The file loader
	tempLoader.LoadMesh(MESHPATH + "attackSpell.mesh");
	attackBase->m_mesh->saveFilePath(tempLoader.GetFileName(), 0);
	attackBase->m_mesh->nameMesh(tempLoader.GetMeshName());
	attackBase->m_mesh->setUpMesh(tempLoader.GetVertices(), tempLoader.GetFaces());
	attackBase->m_mesh->setUpBuffers();

	const Material& newMaterial = tempLoader.GetMaterial();
	attackBase->m_material->ambient = newMaterial.ambient;
	attackBase->m_material->diffuse = newMaterial.diffuse;
	attackBase->m_material->name = newMaterial.name;
	attackBase->m_material->specular = newMaterial.specular;
	tempLoader.Unload();

	attackBase->m_material->diffuse = glm::vec3(0.65f, 1.0f, 1.0f); // Light blue
	//attackBase->m_material->diffuse = glm::vec3(0.5f, 0.0f, 0.9f);	// Purple
	attackBase->m_material->ambient = glm::vec3(0.65f, 1.0f, 1.0f);
	//attackBase->m_material->ambient = glm::vec3(0.5f, 0.0f, 0.9f);


    mySpellLoader.LoadProjectileSpell("bestSpell.spell");

    attackBase->m_lowDamage = mySpellLoader.m_projectile.m_lowDamage;
    attackBase->m_highDamage = mySpellLoader.m_projectile.m_highDamage;
    attackBase->m_speed = mySpellLoader.m_projectile.m_speed;
    attackBase->m_radius = mySpellLoader.m_projectile.m_radius;
    attackBase->m_coolDown = mySpellLoader.m_projectile.m_coolDown;
    attackBase->m_lifeTime = mySpellLoader.m_projectile.m_lifeTime;
    attackBase->m_maxBounces = mySpellLoader.m_projectile.m_maxBounces;

	attackBase->m_attenAndRadius = glm::vec4(1.0f, 0.14f, 0.07f, 22.0f);// OLD
	attackBase->m_attenAndRadius = glm::vec4(1.0f, 2.15f, 4.5f, 22.0f);
}

void SpellHandler::initEnhanceSpell()
{
	enhanceAtkBase = new AttackSpellBase();
	enhanceAtkBase->m_mesh = new Mesh();
	enhanceAtkBase->m_material = new Material();

	BGLoader tempLoader;	// The file loader
	tempLoader.LoadMesh(MESHPATH + "enhanceSpell.mesh");
	enhanceAtkBase->m_mesh->saveFilePath(tempLoader.GetFileName(), 0);
	enhanceAtkBase->m_mesh->nameMesh(tempLoader.GetMeshName());
	enhanceAtkBase->m_mesh->setUpMesh(tempLoader.GetVertices(), tempLoader.GetFaces());
	enhanceAtkBase->m_mesh->setUpBuffers();

	const Material& newMaterial = tempLoader.GetMaterial();
	enhanceAtkBase->m_material->ambient = newMaterial.ambient;
	enhanceAtkBase->m_material->diffuse = newMaterial.diffuse;
	enhanceAtkBase->m_material->name = newMaterial.name;
	enhanceAtkBase->m_material->specular = newMaterial.specular;
	tempLoader.Unload();

	//enhanceAtkBase->m_material->diffuse = glm::vec3(0.3f, 1.0f, 0.3f);
	//enhanceAtkBase->m_material->ambient = glm::vec3(0.3f, 1.0f, 0.3f);
	enhanceAtkBase->m_material->diffuse = glm::vec3(0.5f, 0.0f, 0.6f);
	enhanceAtkBase->m_material->ambient = glm::vec3(0.5f, 0.0f, 0.6f);

    enhanceAtkBase->m_lowDamage = 20;
    enhanceAtkBase->m_highDamage = 70;
	enhanceAtkBase->m_speed = 70.0f;
	enhanceAtkBase->m_radius = 0.5f;
	enhanceAtkBase->m_coolDown = 3.0f;
	enhanceAtkBase->m_lifeTime = 5.0f;
	enhanceAtkBase->m_maxBounces = 3;

	enhanceAtkBase->m_attenAndRadius = glm::vec4(1.0f, 0.14f, 0.07f, 22.0f); // OLD
	enhanceAtkBase->m_attenAndRadius = glm::vec4(1.0f, 1.55f, 3.7f, 22.0f);
}

void SpellHandler::initFlamestrikeSpell()
{
	flamestrikeBase = new FlamestrikeSpellBase();
	flamestrikeBase->m_mesh = new Mesh();
	flamestrikeBase->m_material = new Material();

	BGLoader tempLoader;	// The file loader
	tempLoader.LoadMesh(MESHPATH + "dragonfirepotion.mesh");
	flamestrikeBase->m_mesh->saveFilePath(tempLoader.GetFileName(), 0);
	flamestrikeBase->m_mesh->nameMesh(tempLoader.GetMeshName());
	flamestrikeBase->m_mesh->setUpMesh(tempLoader.GetVertices(), tempLoader.GetFaces());
	flamestrikeBase->m_mesh->setUpBuffers();

	const Material & newMaterial = tempLoader.GetMaterial();
	flamestrikeBase->m_material->ambient = newMaterial.ambient;
	flamestrikeBase->m_material->diffuse = newMaterial.diffuse;
	flamestrikeBase->m_material->diffuse = glm::vec3(1.0f, 0.5f, 0.0f);
	flamestrikeBase->m_material->ambient = glm::vec3(1.0f, 0.5f, 0.0f);

	flamestrikeBase->m_material->name = newMaterial.name;
	flamestrikeBase->m_material->specular = newMaterial.specular;

	MeshBox tempMeshBox;									// Meshbox holds the mesh identity and local transform to GameObject
	std::string meshName = tempLoader.GetMeshName();
	tempMeshBox.name = meshName;
	tempMeshBox.transform = tempLoader.GetTransform();

	if (!MaterialMap::getInstance()->existsWithName(flamestrikeBase->m_material->name)) 	// This creates the material if it does not exist (by name)
	{
		if (tempLoader.GetAlbedo() != "-1")
		{
			std::string albedoFile = TEXTUREPATH + tempLoader.GetAlbedo();
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			// set the texture wrapping/filtering options (on the currently bound texture object)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// load and generate the texture
			int width, height, nrChannels;
			unsigned char* data = stbi_load(albedoFile.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);

				flamestrikeBase->m_material->texture = true;
				flamestrikeBase->m_material->textureID.push_back(texture);
			}
			else
			{
				std::cout << "Failed to load texture" << std::endl;
			}
			stbi_image_free(data);
		}
		else
		{
			flamestrikeBase->m_material->texture = false;
		}
		//Get the material pointer so that we don't have to always search through the MatMap, when rendering
		tempMeshBox.material = MaterialMap::getInstance()->createMaterial(flamestrikeBase->m_material->name, *flamestrikeBase->m_material);
		logTrace("Material created: {0}", flamestrikeBase->m_material->name);
	}
	else {
		tempMeshBox.material = MaterialMap::getInstance()->getMaterial(flamestrikeBase->m_material->name);
	}
	flamestrikeBase->m_mesh->setMaterial(flamestrikeBase->m_material->name);
	tempLoader.Unload();

    mySpellLoader.loadAOESpell("newFireSpell.spell");

    flamestrikeBase->m_damage = mySpellLoader.m_AOESpell.m_damage; 
	flamestrikeBase->m_speed = 50;
	flamestrikeBase->m_coolDown = 5;
	flamestrikeBase->m_lifeTime = 5;
	flamestrikeBase->m_maxBounces = mySpellLoader.m_AOESpell.m_maxBounces;

	flamestrikeBase->m_attenAndRadius = glm::vec4(1.0f, 0.14f, 0.07f, 22.0f); // Old
	flamestrikeBase->m_attenAndRadius = glm::vec4(1.0f, 0.61f, 0.74f, 22.0f);
}

void SpellHandler::initFireSpell()
{
	fireBase = new FireSpellBase();
	fireBase->m_mesh = new Mesh();
	fireBase->m_material = new Material();

	BGLoader tempLoader;	// The file loader
	tempLoader.LoadMesh(MESHPATH + "TestSphere.mesh");
	fireBase->m_mesh->saveFilePath(tempLoader.GetFileName(), 0);
	fireBase->m_mesh->nameMesh(tempLoader.GetMeshName());
	fireBase->m_mesh->setUpMesh(tempLoader.GetVertices(), tempLoader.GetFaces());
	fireBase->m_mesh->setUpBuffers();

	const Material & newMaterial = tempLoader.GetMaterial();
	fireBase->m_material->ambient = newMaterial.ambient;
	fireBase->m_material->diffuse = newMaterial.diffuse;
	fireBase->m_material->name = newMaterial.name;
	fireBase->m_material->specular = newMaterial.specular;
	tempLoader.Unload();

	fireBase->m_material->diffuse = glm::vec3(1.0f, 0.5f, 0.0f);
	fireBase->m_material->ambient = glm::vec3(1.0f, 0.5f, 0.0f);

    mySpellLoader.loadAOESpell("newFireSpell.spell");

    fireBase->m_damage = mySpellLoader.m_AOESpell.m_damage;
    fireBase->m_speed = mySpellLoader.m_AOESpell.m_speed;
    fireBase->m_radius = mySpellLoader.m_AOESpell.m_radius;
    fireBase->m_coolDown = mySpellLoader.m_AOESpell.m_coolDown;
    fireBase->m_lifeTime = mySpellLoader.m_AOESpell.m_lifeTime;
    fireBase->m_maxBounces = mySpellLoader.m_AOESpell.m_maxBounces;

	fireBase->m_attenAndRadius = glm::vec4(1.0f, 0.14f, 0.07f, 22.0f); // Old
	fireBase->m_attenAndRadius = glm::vec4(1.0f, 0.61f, 0.74f, 22.0f);
}

void SpellHandler::initReflectSpell()
{
	reflectBase = new ReflectSpellBase();
	reflectBase->m_mesh = new Mesh();
	reflectBase->m_material = new Material();

	BGLoader tempLoader;	// The file loader
	tempLoader.LoadMesh(MESHPATH + "TestSphere.mesh");
	reflectBase->m_mesh->saveFilePath(tempLoader.GetFileName(), 0);
	reflectBase->m_mesh->nameMesh(tempLoader.GetMeshName());
	reflectBase->m_mesh->setUpMesh(tempLoader.GetVertices(), tempLoader.GetFaces());
	reflectBase->m_mesh->setUpBuffers();

	const Material& newMaterial = tempLoader.GetMaterial();
	reflectBase->m_material->ambient = newMaterial.ambient;
	reflectBase->m_material->diffuse = newMaterial.diffuse;
	reflectBase->m_material->name = newMaterial.name;
	reflectBase->m_material->specular = newMaterial.specular;
	tempLoader.Unload();

	reflectBase->m_material->diffuse = glm::vec3(1.0f, 0.0f, 0.5f);
	reflectBase->m_material->ambient = glm::vec3(1.0f, 0.0f, 0.5f);

	reflectBase->m_radius = 1.0f;
	reflectBase->m_coolDown = 10.0f;
	reflectBase->m_lifeTime = 2.5f;
}

SpellHandler::~SpellHandler()
{
	if (attackBase)
		delete attackBase;
	if (enhanceAtkBase)
		delete enhanceAtkBase;
	if (flamestrikeBase)
		delete flamestrikeBase;
	if (reflectBase)
		delete reflectBase;
	if (fireBase)
		delete fireBase;

	for (Spell* element : spells)
		delete element;
	spells.clear();

	for (Spell* element : flamestrikeSpells)
		delete element;
	flamestrikeSpells.clear();

	for (Spell* element : fireSpells)
		delete element;
	fireSpells.clear();
}

float SpellHandler::createSpell(glm::vec3 spellPos, glm::vec3 directionVector, OBJECT_TYPE type)
{
	SoundHandler* shPtr = SoundHandler::getInstance();
	auto* clientPtr = Client::getInstance();
	float cooldown = 0.0f;
	if (Client::getInstance()->getMyData().health <= 0)
		return cooldown;
	
	if (type == NORMALATTACK)
	{
		auto spell = new AttackSpell(spellPos, directionVector, attackBase);
		spell->setType(NORMALATTACK);
		cooldown = attackBase->m_coolDown;

		spell->setUniqueID(getUniqueID());
		Client::getInstance()->createSpellOnNetwork(*spell);
		spells.emplace_back(spell);
		Renderer::getInstance()->submit(spells.back(), SPELL);

		//bullet create
		btVector3 direction = btVector3(directionVector.x, directionVector.y, directionVector.z);
		m_BulletNormalSpell.emplace_back(
			m_bp->createObject(sphere, 10.0f, spellPos+directionVector*2, glm::vec3(spell->getTransform().scale.x, 0.0f, 0.0f)));
		spell->setBodyReference(m_BulletNormalSpell.back());
			
		int size = m_BulletNormalSpell.size();
		m_BulletNormalSpell.at(size - 1)->setGravity(btVector3(0.0f, 0.0f, 0.0f));
		m_BulletNormalSpell.at(size - 1)->setUserPointer(spell);
		m_BulletNormalSpell.at(size - 1)->setLinearVelocity(direction * attackBase->m_speed);
	}

	if (type == ENHANCEATTACK)
	{
		auto spell = new AttackSpell(spellPos, directionVector, enhanceAtkBase);
		spell->setType(ENHANCEATTACK);
		cooldown = enhanceAtkBase->m_coolDown;

		spell->setUniqueID(getUniqueID());
		Client::getInstance()->createSpellOnNetwork(*spell);
		spells.emplace_back(spell);
		Renderer::getInstance()->submit(spells.back(), SPELL);
		
		//bullet create
		btVector3 direction = btVector3(directionVector.x, directionVector.y, directionVector.z);
		m_BulletNormalSpell.emplace_back(
			m_bp->createObject(sphere, 30.0f, spellPos + directionVector * 2, glm::vec3(spell->getTransform().scale.x, 0.0f, 0.0f)));
		spell->setBodyReference(m_BulletNormalSpell.back());

		int size = m_BulletNormalSpell.size();
		m_BulletNormalSpell.at(size - 1)->setGravity(btVector3(0.0f, 0.0f, 0.0f));
		m_BulletNormalSpell.at(size - 1)->setUserPointer(spell);
		m_BulletNormalSpell.at(size - 1)->setLinearVelocity(direction * enhanceAtkBase->m_speed);
		int slot = shPtr->playSound(EnhanceAttackSound, clientPtr->getMyData().guid);		
	}

	if (type == REFLECT)
	{
		auto spell = new ReflectSpell(spellPos, directionVector, reflectBase);
		cooldown = reflectBase->m_coolDown;
		spell->setUniqueID(getUniqueID());
		Client::getInstance()->createSpellOnNetwork(*spell);
		spells.emplace_back(spell);
		Renderer::getInstance()->submit(spells.back(), SPELL);
		logTrace("Created reflect spell");

		//bullet create
		btVector3 direction = btVector3(directionVector.x, directionVector.y, directionVector.x);
		m_BulletNormalSpell.emplace_back(
			m_bp->createObject(sphere, 1.0f, spellPos + directionVector * 2, glm::vec3(spell->getTransform().scale.x, 0.0f, 0.0f)));
		spell->setBodyReference(m_BulletNormalSpell.back());

		int size = m_BulletNormalSpell.size();
		m_BulletNormalSpell.at(size - 1)->setGravity(btVector3(0.0f, 0.0f, 0.0f));
		m_BulletNormalSpell.at(size - 1)->setUserPointer(m_BulletNormalSpell.at(size - 1));
	}

	if (type == FLAMESTRIKE)
	{
		auto spell = new AOEAttack(spellPos, directionVector, flamestrikeBase);
		cooldown = flamestrikeBase->m_coolDown;

		spell->setUniqueID(getUniqueID());
		Client::getInstance()->createSpellOnNetwork(*spell);
		flamestrikeSpells.emplace_back(spell);
		Renderer::getInstance()->submit(flamestrikeSpells.back(), SPELL);

		//bullet create
		btVector3 direction = btVector3(directionVector.x, directionVector.y, directionVector.z);
		m_BulletFlamestrikeSpell.emplace_back(m_bp->createObject(
			sphere,
			1.0f,
			spellPos + directionVector * 2,
			glm::vec3(spell->getTransform().scale.x, 0.0f, 0.0f),
			glm::quat(),
			false,
			0.15f,
			1.0f
		));
		spell->setBodyReference(m_BulletFlamestrikeSpell.back());

		int size = m_BulletFlamestrikeSpell.size();
		m_BulletFlamestrikeSpell.back()->setGravity(btVector3(0.0f, -60.0f, 0.0f));
		float rndX = rand() % 1999 + 1 - 1000; rndX /= 100;
		float rndY = rand() % 1999 + 1 - 1000; rndY /= 100;
		float rndZ = rand() % 1999 + 1 - 1000; rndZ /= 100;
		m_BulletFlamestrikeSpell.back()->setAngularVelocity(btVector3(rndX, rndY, rndZ));
		m_BulletFlamestrikeSpell.back()->setLinearVelocity(btVector3(direction * flamestrikeBase->m_speed));
		m_BulletFlamestrikeSpell.back()->setUserPointer(spell);

		spell->setSoundSlot(shPtr->playSound(FireSound, clientPtr->getMyData().guid));

		if (spell->getSoundSlot() != -1) //out of slots
		{
			shPtr->setSourcePosition(spell->getPos(), FireSound, clientPtr->getMyData().guid, spell->getSoundSlot());
		}		
	}

	if (type == FIRE)
	{
		auto fireSpell = new fire(spellPos, directionVector, fireBase);
		cooldown = fireBase->m_coolDown;

		fireSpell->setUniqueID(getUniqueID());
		Client::getInstance()->createSpellOnNetwork(*fireSpell);
		fireSpells.emplace_back(fireSpell);
		Renderer::getInstance()->submit(fireSpells.back(), SPELL);	

		shPtr->setSourcePosition(spellPos, GlassBreakSound, clientPtr->getMyData().guid);
		shPtr->playSound(GlassBreakSound, clientPtr->getMyData().guid);		

	}

	
	return cooldown;
}

void SpellHandler::createSpellForTool(glm::vec3 spellPos, glm::vec3 directionVector, SpellCreatorTool_TYPE type)
{
    float cooldown = 0.0f;

    if (type == NORMALATTACKTOOL)
    {
        auto spell = new AttackSpell(spellPos, directionVector, attackBase);
        spell->setType(NORMALATTACK);
        cooldown = attackBase->m_coolDown;


        spell->setUniqueID(getUniqueID());
        spells.emplace_back(spell);
        Renderer::getInstance()->submit(spells.back(), SPELL);

        //bullet create
        btVector3 direction = btVector3(directionVector.x, directionVector.y, directionVector.z);
        m_BulletNormalSpell.emplace_back(
            m_bp->createObject(sphere, 20.0f, spellPos + directionVector * 2, glm::vec3(spell->getTransform().scale.x, 0.0f, 0.0f)));
        spell->setBodyReference(m_BulletNormalSpell.back());

        int size = m_BulletNormalSpell.size();
        m_BulletNormalSpell.at(size - 1)->setGravity(btVector3(0.0f, 0.0f, 0.0f));
        m_BulletNormalSpell.at(size - 1)->setUserPointer(spell);
        m_BulletNormalSpell.at(size - 1)->setLinearVelocity(direction * attackBase->m_speed);
    }

    if (type == FIRETOOL)
    {
        auto fireSpell = new fire(spellPos, directionVector, fireBase);
        cooldown = fireBase->m_coolDown;

        fireSpell->setUniqueID(getUniqueID());
        fireSpells.emplace_back(fireSpell);
        Renderer::getInstance()->submit(fireSpells.back(), SPELL);

    }

}

void SpellHandler::spellToolUpdate(float dt, float radius, float speed)
{

    for (size_t i = 0; i < spells.size(); i++)
    {

        spells[i]->updateTool(radius, speed, dt);
        if (activespell == 1)
        {
            spells[i]->setTravelTime(0);
        }


        if (spells[i]->getTravelTime() <= 0)
        {
            Renderer::getInstance()->removeRenderObject(spells[i], SPELL);

            delete spells[i];
            spells.erase(spells.begin() + i);

            m_bp->removeObject(m_BulletNormalSpell.at(i));
            m_BulletNormalSpell.erase(m_BulletNormalSpell.begin() + i);
        }
    }

    for (size_t i = 0; i < fireSpells.size(); i++)
    {
        
        if (activespell == 0)
        {
            fireSpells[i]->setTravelTime(0);
        }
        

        if (fireSpells[i]->getTravelTime() <= 0)
        {
            Renderer::getInstance()->removeRenderObject(fireSpells[i], SPELL);
            delete fireSpells[i];
            fireSpells.erase(fireSpells.begin() + i);
        }
    }
}

void SpellHandler::renderSpellTool()
{
    ShaderMap::getInstance()->useByName(BASIC_FORWARD);
    Renderer::getInstance()->renderSpell(this);
}

void SpellHandler::changeSpell(int state)
{
    activespell = state;
}

void SpellHandler::spellUpdate(float deltaTime)
{
	for (size_t i = 0; i < flamestrikeSpells.size(); i++)
	{		
		if (flamestrikeSpells[i]->getTravelTime() > 0)
		{			
			flamestrikeSpells[i]->update(deltaTime);
			flamestrikeSpells[i]->updateRigidbody(deltaTime, m_BulletFlamestrikeSpell.at(i));
			
			if (flamestrikeSpells[i]->getType() == FLAMESTRIKE)
			{				
				AOEAttack* flamestrike = static_cast<AOEAttack*>(flamestrikeSpells[i]);
				
				if (flamestrikeSpells[i]->getSoundSlot() != -1)
				{
					SoundHandler::getInstance()->setSourcePosition(flamestrike->getPos(),
						FireSound, Client::getInstance()->getMyData().guid,
						flamestrikeSpells[i]->getSoundSlot());	
				}

				if (flamestrike->spellOnGround())
				{
					createSpell(flamestrike->getTransform().position, glm::vec3(0, 0, 0), FIRE);
					flamestrike->setSpellBool(false);
				}
			}

			Client::getInstance()->updateSpellOnNetwork(*flamestrikeSpells[i]);
		}
		if (flamestrikeSpells[i]->getTravelTime() <= 0)
		{
			Renderer::getInstance()->removeRenderObject(flamestrikeSpells[i], SPELL);

			Client::getInstance()->destroySpellOnNetwork(*flamestrikeSpells[i]);
			delete flamestrikeSpells[i];
			flamestrikeSpells.erase(flamestrikeSpells.begin() + i);

			m_bp->removeObject(m_BulletFlamestrikeSpell.at(i));
			m_BulletFlamestrikeSpell.erase(m_BulletFlamestrikeSpell.begin() + i);
		}

	}

	for (size_t i = 0; i < fireSpells.size(); i++)
	{
		if (fireSpells[i]->getTravelTime() > 0)
		{
			fireSpells[i]->update(deltaTime);

			Client::getInstance()->updateSpellOnNetwork(*fireSpells[i]);			
		}

		if (fireSpells[i]->getTravelTime() <= 0)
		{
			Renderer::getInstance()->removeRenderObject(fireSpells[i], SPELL);

			Client::getInstance()->destroySpellOnNetwork(*fireSpells[i]);
			delete fireSpells[i];
			fireSpells.erase(fireSpells.begin() + i);
		}
	}


	for (size_t i = 0; i < spells.size(); i++)
	{
		if (spells[i]->getTravelTime() > 0)
		{
			spells[i]->update(deltaTime);
			spells[i]->updateRigidbody(deltaTime, m_BulletNormalSpell.at(i));
			Client::getInstance()->updateSpellOnNetwork(*spells[i]);
		}

		if (spells[i]->getTravelTime() <= 0)
		{
			Renderer::getInstance()->removeRenderObject(spells[i], SPELL);

			Client::getInstance()->destroySpellOnNetwork(*spells[i]);
			delete spells[i];
			spells.erase(spells.begin() + i);

			m_bp->removeObject(m_BulletNormalSpell.at(i));
			m_BulletNormalSpell.erase(m_BulletNormalSpell.begin() + i);
		}
	}
	spellCollisionCheck();
	
	// Scope
	{
		std::lock_guard<std::mutex> lockGuard(NetGlobals::UpdateDeflectSpellMutex);
		for (size_t i = 0; i < m_deflectedSpells.size(); i++)
		{
			deflectSpellData& data = m_deflectedSpells[i];
			createSpell(data.position, data.direction, data.type);
		}
	}
	m_deflectedSpells.clear();
}

void SpellHandler::setSpawnerPosition(glm::vec3 position)
{
	m_spawnerPos = position;
}

void SpellHandler::setSpawnerDirection(glm::vec3 direction)
{
	m_spawnerDir = direction;
}

void SpellHandler::setOnHitCallback(std::function<void()> func)
{
	m_onHitCallback = func;
}

void SpellHandler::renderSpell()
{
	ShaderMap::getInstance()->useByName(BASIC_FORWARD);
	Renderer::getInstance()->renderSpell(this);
}

const uint64_t SpellHandler::getUniqueID()
{
	// Starts at 1 because 0 is a "Undefined" id
	static uint64_t id = 1;
	
	if (id == UINT64_MAX)
		id = 1;
	
	return id++;
}

void SpellHandler::spellCollisionCheck()
{

	//get the list of att the players on the network

	auto list = Client::getInstance()->getNetworkPlayersREF().getPlayersREF();
	auto ownPlayer = Client::getInstance()->getMyData();
	
	fireDamageCounter = fireDamageCounter - DeltaTime * 1;
	ownfireDamageCounter = ownfireDamageCounter - DeltaTime * 1;

	if (ownPlayer.health > 0 && list.size() >= 0)
	{
		glm::vec3 ownPlayerPos = ownPlayer.position;

		glm::vec3 xAxis1 = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 yAxis1 = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 zAxis1 = glm::vec3(0.0f, 0.0f, 1.0f);
		std::vector<glm::vec3> axis1;

		glm::rotateX(xAxis1, ownPlayer.rotation.x);
		glm::rotateY(yAxis1, ownPlayer.rotation.y);
		glm::rotateZ(zAxis1, ownPlayer.rotation.z);

		axis1.emplace_back(xAxis1);
		axis1.emplace_back(yAxis1);
		axis1.emplace_back(zAxis1);

		
		//Me and fire spell
		for (size_t j = 0; j < fireSpells.size(); j++)
		{
			glm::vec3 spellPos = fireSpells.at(j)->getTransform().position;

			float scale = fireSpells.at(j)->getTransform().scale.x;
			
			if (specificSpellCollision(spellPos, ownPlayerPos, axis1, scale))
			{
				if (ownfireDamageCounter <= 0)
				{
					Client::getInstance()->sendHitRequest(*fireSpells[j], ownPlayer);
					ownfireDamageCounter = 0.5f;
				}
			}
		}	
	}
	//move camera and spell collision
	for (size_t i = 0; i < list.size() && (1 <= spells.size() || 1<= fireSpells.size()); i++)
	{
		if (list[i].data.health <= 0 || list[i].data.invulnerabilityTime > 0.0f)
			continue;

		glm::vec3 playerPos = list[i].data.position;
		
		//create the axis and rotate them
		glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);
		std::vector<glm::vec3> axis;

		glm::quat playerrot = glm::quat(list[i].data.rotation);
		xAxis =	glm::rotate(playerrot, xAxis);
		yAxis = glm::rotate(playerrot, yAxis);
		zAxis = glm::rotate(playerrot, zAxis);

		axis.emplace_back(xAxis);
		axis.emplace_back(yAxis);
		axis.emplace_back(zAxis);

		//create a box, obb or AABB? from the player position. Old hitdetection press L
		for (size_t j = 0; j < spells.size(); j++)
		{
			glm::vec3 lastSpellPos = spells.at(j)->getLastPosition();
			glm::vec3 spellPos = spells.at(j)->getTransform().position;

			//get the radius from the spelltype
			float radius = 0.0f;

			if (spells[j]->getType() == NORMALATTACK) {
				radius = attackBase->m_radius;
			}
			if (spells[j]->getType() == ENHANCEATTACK) {
				radius = enhanceAtkBase->m_radius;
			}

			//line is the walking we will do.
			glm::vec3 line = (spellPos - lastSpellPos) / m_nrSubSteps;
			glm::vec3 interpolationPos = lastSpellPos;

			//walk from last pos to new pos with substeps
			for (size_t k = 0; k < m_nrSubSteps; k++)
			{
				interpolationPos += line;
				if (specificSpellCollision(interpolationPos, playerPos, axis, radius))
				{
					spells[j]->setTravelTime(0.0f);
					Client::getInstance()->sendHitRequest(*spells[j], list[i]);

					if (m_onHitCallback != nullptr) {
						m_onHitCallback();
					}
					k = static_cast<size_t>(m_nrSubSteps);
				}
			}
		}

		for (size_t j = 0; j < fireSpells.size(); j++)
		{
			glm::vec3 spellPos = fireSpells.at(j)->getTransform().position;

			float scale = fireSpells.at(j)->getTransform().scale.x;

			if (specificSpellCollision(spellPos, playerPos, axis, scale))
			{
				if (fireDamageCounter <= 0)
				{
					Client::getInstance()->sendHitRequest(*fireSpells[j], list[i]);
					fireDamageCounter = 0.5f;
					
				}
			}
		}
	}
}

bool SpellHandler::specificSpellCollision(glm::vec3 spellPos, glm::vec3 playerPos, std::vector<glm::vec3>& axis, float radius)
{ 
	bool collision = false;
	float sphereRadius = 1.0f * radius;

	float distx2 = OBBsqDist(spellPos, axis, playerPos);

	if (distx2 <= sphereRadius * sphereRadius)
	{
		collision = true;
	}
	return collision;
}

float SpellHandler::OBBsqDist(glm::vec3& spherePos, std::vector<glm::vec3>& axis, glm::vec3& playerPos)
{	
	btVector3 box = m_bp->getCharacterSize();
	glm::vec3 halfSize = glm::vec3(box.getX(), box.getY(), box.getZ());
	
	float dist = 0.0f;
	//closest point on obb
	glm::vec3 boxPoint = playerPos;
	boxPoint.y += halfSize.y;

	glm::vec3 ray = glm::vec3(spherePos - boxPoint);

	for (int j = 0; j < 3; j++) {
		float distance = glm::dot(ray, axis.at(j));
		float distance2 = 0;

		if (distance > halfSize[j])
			distance2 = distance - halfSize[j];

		if (distance < -halfSize[j])
			distance2 = distance + halfSize[j];

		dist += distance2 * distance2;
	}
	return dist;
}

void SpellHandler::setCharacter(std::string meshName)
{
	std::string skeleton = MeshMap::getInstance()->getMesh(meshName)->getSkeleton();
	glm::vec3 min;
	glm::vec3 max;

	if (skeleton[0] == NULL)
	{
		const std::vector<Vertex> vertices = MeshMap::getInstance()->getMesh(meshName)->getVertices();
		min = vertices[0].position;
		max = vertices[0].position;

		for (size_t i = 1; i < vertices.size(); i++)
		{
			min.x = fminf(vertices[i].position.x, min.x);
			min.y = fminf(vertices[i].position.y, min.y);
			min.z = fminf(vertices[i].position.z, min.z);

			max.x = fmaxf(vertices[i].position.x, max.x);
			max.y = fmaxf(vertices[i].position.y, max.y);
			max.z = fmaxf(vertices[i].position.z, max.z);
		}
	}
	else
	{
		const std::vector<Vertex2> vertices = MeshMap::getInstance()->getMesh(meshName)->getVerticesSkele();
		min = vertices[0].position;
		max = vertices[0].position;

		for (size_t i = 1; i < vertices.size(); i++)
		{
			min.x = fminf(vertices[i].position.x, min.x);
			min.y = fminf(vertices[i].position.y, min.y);
			min.z = fminf(vertices[i].position.z, min.z);

			max.x = fmaxf(vertices[i].position.x, max.x);
			max.y = fmaxf(vertices[i].position.y, max.y);
			max.z = fmaxf(vertices[i].position.z, max.z);
		}
	}
	glm::vec3 halfSize = glm::vec3((max - min) * 0.5f);
	//glm::vec3 halfSize = glm::vec3((max - min) * 0.5f) * 0.7f;
	halfSize.x *= 0.6f;
	halfSize.z *= 0.6f;

	m_bp->setCharacterSize(halfSize);
	m_setcharacter = true;
}

void SpellHandler::REFLECTupdate(float deltaTime, int i)
{
	ReflectSpell* reflectSpell = static_cast<ReflectSpell*>(spells[i]);
	reflectSpell->updateReflection(deltaTime, m_BulletNormalSpell.at(i), m_spawnerPos, m_spawnerDir);

	auto spellList = Client::getInstance()->getNetworkSpells();
	for (size_t i = 0; i < spellList.size(); i++)
	{
		float hitboxRadius = 0.0f;
		OBJECT_TYPE type = spellList[i].SpellType;
		switch (type)
		{
		case NORMALATTACK:
			hitboxRadius = attackBase->m_radius;
			break;
		case ENHANCEATTACK:
			hitboxRadius = enhanceAtkBase->m_radius;
			break;
		case REFLECT:
			hitboxRadius = reflectBase->m_radius;
			break; 
		default:
			break;
		}

		if (reflectSpell->checkReflectCollision(spellList[i].Position, spellList[i].Direction, hitboxRadius))
		{
			createSpell(m_spawnerPos, m_spawnerDir, spellList[i].SpellType);
		}
	}
}
