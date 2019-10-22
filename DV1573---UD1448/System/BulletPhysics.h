#ifndef BULLETPHYSICS_H
#define BULLETPHYSICS_H
#include <Pch/Pch.h>
#include <Bullet/BulletDynamics/Character/btKinematicCharacterController.h>
#include <Bullet/BulletCollision/CollisionDispatch/btGhostObject.h>

// box, sphere, capsule
enum CollisionObject
{
	box,
	sphere,
	capsule
};

class BulletPhysics
{
public:
	BulletPhysics(float gravity);
	~BulletPhysics();

	//objects box, sphere, capsule. (Extend.x is radius, Extend.y is height) 
	btRigidBody* createObject(CollisionObject object, float inMass,
		glm::vec3 position, glm::vec3 extend, glm::vec3 rotation = glm::vec3(), float friction = 0.2f);

	btDiscreteDynamicsWorld* getDynamicsWorld() const;
	btKinematicCharacterController* createCharacter();

	void update(float dt);

private:

	btDefaultCollisionConfiguration* m_collisionConfiguration;
	btCollisionDispatcher* m_dispatcher;
	btBroadphaseInterface* m_overlappingPairCache;
	btSequentialImpulseConstraintSolver* m_solver;
	btDiscreteDynamicsWorld* m_dynamicsWorld;

	btAlignedObjectArray<btCollisionShape*> m_collisionShapes;

	//character controller
	btConvexShape* m_playerShape;
	btPairCachingGhostObject* m_ghostObject;
	btKinematicCharacterController* m_character;
	btGhostPairCallback* m_ghostCallback;
};

#endif
