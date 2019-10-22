#include "Pch/Pch.h"
#include "BulletPhysics.h"

BulletPhysics::BulletPhysics(float gravity)
{
	m_collisionConfiguration = new btDefaultCollisionConfiguration();

	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

	m_overlappingPairCache = new btDbvtBroadphase();

	m_solver = new btSequentialImpulseConstraintSolver;

	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_overlappingPairCache,
		m_solver, m_collisionConfiguration);

	m_dynamicsWorld->setGravity(btVector3(0, gravity, 0));

	m_ghostCallback = new btGhostPairCallback();
}

BulletPhysics::~BulletPhysics()
{
	m_dynamicsWorld->removeAction(m_character);
	//Remove the rigidbodies from the dynamics world and delete them
	for (int i = m_dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		m_dynamicsWorld->removeCollisionObject(obj);

		delete obj;
	}
	
	//Delete collsion shapes
	for (int i = 0; i < m_collisionShapes.size(); i++)
	{
		btCollisionShape* shape = m_collisionShapes[i];
		m_collisionShapes[i] = 0;
		delete shape;
	}
	
	delete m_character;

	delete m_ghostCallback;
	delete m_dynamicsWorld;
	delete m_solver;
	delete m_overlappingPairCache;
	delete m_dispatcher;
	delete m_collisionConfiguration;


	m_collisionShapes.clear();
}

btRigidBody* BulletPhysics::createObject(CollisionObject object, float inMass, glm::vec3 position, glm::vec3 extend, glm::quat rotation, float friction)
{
	btCollisionShape* objectShape;
	switch (object)
	{
	case box:
		objectShape = new btBoxShape(btVector3(
			btScalar(extend.x),
			btScalar(extend.y),
			btScalar(extend.z)));
		break;

	case sphere:
		objectShape = new btSphereShape(btScalar(extend.x));
		break;

	case capsule:
		objectShape = new btCapsuleShape(extend.x, extend.y);
		break;

	default:
		break;
	}
	m_collisionShapes.push_back(objectShape);

	/// Create Dynamic Objects
	btTransform startTransform;
	startTransform.setIdentity();

	// if you want to rotate something 
	btQuaternion rot;
	rot.setX(rotation.x);
	rot.setY(rotation.y);
	rot.setZ(rotation.z);
	rot.setW(rotation.w);
	startTransform.setRotation(rot);
	
	startTransform.setOrigin(btVector3(position.x, position.y, position.z));

	btScalar mass(inMass);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0.0f, 0.0f, 0.0f);
	//btVector3 localInertia(inLocalInertia.x, inLocalInertia.y, inLocalInertia.z);
	if (isDynamic)
		objectShape->calculateLocalInertia(mass, localInertia);


	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, objectShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);

	body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

	//how much bounce and friction a object should have
	body->setRestitution(0.0f);
	body->setFriction(friction);
	body->setSpinningFriction(1.0f);

	m_dynamicsWorld->addRigidBody(body);

	return body;
}

btDiscreteDynamicsWorld* BulletPhysics::getDynamicsWorld() const
{
	return m_dynamicsWorld;
}

btKinematicCharacterController* BulletPhysics::createCharacter()
{
	//create the character and add him to the dynamicsWorld
	m_playerShape = new btCapsuleShape(0.8, 1);
	m_ghostObject = new btPairCachingGhostObject();
	
	m_ghostObject->setWorldTransform(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 120, 0)));

	m_dynamicsWorld->getPairCache()->setInternalGhostPairCallback(m_ghostCallback);
	m_ghostObject->setCollisionShape(m_playerShape);
	m_ghostObject->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	m_character = new btKinematicCharacterController(m_ghostObject, m_playerShape, 0.5f, btVector3(0.0f, 1.0f, 0.0f));
	m_dynamicsWorld->addCollisionObject(m_ghostObject, btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter | btBroadphaseProxy::DefaultFilter);

	m_collisionShapes.push_back(m_playerShape);
	m_dynamicsWorld->addAction(m_character);
	m_character->setGravity(btVector3(0.0f, -5.0f, 0.0f));
	m_character->setMaxPenetrationDepth(0.1f);
	m_character->setUp(btVector3(0.0f, 1.0f, 0.0f));

	return m_character;
}

void BulletPhysics::update(float dt)
{
	m_dynamicsWorld->stepSimulation(dt, 10);
}
