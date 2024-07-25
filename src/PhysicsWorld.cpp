#include "PhysicsWorld.h"
#include "CollisionShape.h"
#include <ngl/Obj.h>


PhysicsWorld::PhysicsWorld()
        : m_lastHitTime(std::chrono::steady_clock::now()), // Initialize timestamp
          m_collisionConfiguration(new btDefaultCollisionConfiguration()),
          m_dispatcher(new btCollisionDispatcher(m_collisionConfiguration.get())),
          m_overlappingPairCache(new btDbvtBroadphase()),
          m_solver(new btSequentialImpulseConstraintSolver),
          m_dynamicsWorld(new btDiscreteDynamicsWorld(
                  m_dispatcher.get(),
                  m_overlappingPairCache.get(),
                  m_solver.get(),
                  m_collisionConfiguration.get()))
{
    // No additional setup is needed here, as all initialization is handled in the initializer list.
}

//PhysicsWorld::PhysicsWorld()
//{
//	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
//	m_collisionConfiguration.reset(  new btDefaultCollisionConfiguration());
//
//	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
//	m_dispatcher.reset( new	btCollisionDispatcher(m_collisionConfiguration.get()));
//
//	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
//	m_overlappingPairCache.reset( new btDbvtBroadphase());
//
//	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
//	m_solver.reset(new btSequentialImpulseConstraintSolver);
//
//  m_dynamicsWorld.reset(new btDiscreteDynamicsWorld(m_dispatcher.get(),
//                               m_overlappingPairCache.get(),
//								m_solver.get(),
//								m_collisionConfiguration.get()));
//}

void PhysicsWorld::updateMeshPosition(const std::string& name, const ngl::Vec3& newPos)
{
    for (auto& body : m_bodies)
    {
        if (body.name == name)
        {
            btTransform trans;
            body.body->getMotionState()->getWorldTransform(trans);
            trans.setOrigin(btVector3(newPos.m_x, newPos.m_y, newPos.m_z));
            body.body->getMotionState()->setWorldTransform(trans);
            body.body->setCenterOfMassTransform(trans);
            body.body->activate(true); // Activate the body to apply changes
            body.body->clearForces();
            break;
        }
    }
}

void PhysicsWorld::addPE(std::string _shapeName,const ngl::Vec3 &_pos)
{
//	//create a dynamic rigidbody
//	btCollisionShape* colShape = CollisionShape::instance()->getShape(_shapeName);
//	/// Create Dynamic Objects
//	btTransform startTransform;
//	startTransform.setIdentity();
//	btScalar	mass(10.0);
//
//	btVector3 localInertia(10,10,10);
//	colShape->calculateLocalInertia(mass,localInertia);
//	startTransform.setOrigin(btVector3(_pos.m_x,_pos.m_y,_pos.m_z));
//
//	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
//	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
//	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,colShape,localInertia);
//	btRigidBody* body = new btRigidBody(rbInfo);
//	body->setFriction(1.0);
//	body->setRollingFriction(1.0);
    btCollisionShape* shape = new btSphereShape(btScalar(0.2)); // Adjust the radius here
    btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(_pos.m_x, _pos.m_y, _pos.m_z)));
    btScalar mass = 1.0f;
    btVector3 inertia(0,0,0);
    shape->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, motionState, shape, inertia);
    btRigidBody* body = new btRigidBody(rigidBodyCI);
    body->setUserPointer(new std::string("player"));
    std::cout << "Player added at position: " << _pos.m_x << ", " << _pos.m_y << ", " << _pos.m_z << std::endl;
	m_dynamicsWorld->addRigidBody(body);
	Body b;
	b.name=_shapeName;
	b.body=body;
	m_bodies.push_back(b);
}


void PhysicsWorld::addGroundPlane(const ngl::Vec3 &_pos, const ngl::Vec3 &_size)
{
  m_groundShape.reset( new btStaticPlaneShape(btVector3(0,1,0),_pos.m_y));

	btTransform groundTransform;
	groundTransform.setIdentity();
	{
			btScalar mass(0.);
			btVector3 localInertia(0,0,0);

			//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
			btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
      btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,m_groundShape.get(),localInertia);

			btRigidBody* body = new btRigidBody(rbInfo);
			body->setFriction(1.);
			body->setRollingFriction(2.);
			//add the body to the dynamics world
			m_dynamicsWorld->addRigidBody(body);
			Body b;
			b.name="groundPlane";
			b.body=body;
			m_bodies.push_back(b);

		}

}

PhysicsWorld::~PhysicsWorld()
{

}

void PhysicsWorld::addSphere(std::string _shapeName,const ngl::Vec3 &_pos,ngl::Real _mass,const ngl::Vec3 &_inertia)
{
////create a dynamic rigidbody
//
//btCollisionShape* colShape = CollisionShape::instance()->getShape(_shapeName);
//
///// Create Dynamic Objects
//btTransform startTransform;
//startTransform.setIdentity();
//
//btScalar	mass(_mass);
//
//
//btVector3 localInertia(_inertia.m_x,_inertia.m_y,_inertia.m_z);
//colShape->calculateLocalInertia(mass,localInertia);
//startTransform.setOrigin(btVector3(_pos.m_x,_pos.m_y,_pos.m_z));
//
////using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
//btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
//btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,colShape,localInertia);
//
//btRigidBody* body = new btRigidBody(rbInfo);
//body->setFriction(1.0);
//body->setRollingFriction(1.0);

//attempting to fix collision issue

btCollisionShape* shape = new btSphereShape(btScalar(0.47)); // Adjust the radius here
btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(_pos.m_x, _pos.m_y, _pos.m_z)));
btVector3 inertia(_inertia.m_x, _inertia.m_y, _inertia.m_z);
shape->calculateLocalInertia(_mass, inertia);
btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(_mass, motionState, shape, inertia);
btRigidBody* body = new btRigidBody(rigidBodyCI);


body->setUserPointer(new std::string("sphere"));
//std::cout << "Sphere added at position: " << _pos.m_x << ", " << _pos.m_y << ", " << _pos.m_z << std::endl;
m_dynamicsWorld->addRigidBody(body);
Body b;
b.name=_shapeName;
b.body=body;
m_bodies.push_back(b);


}

//-----------------------------------------------------------------------------------------
void PhysicsWorld::addMesh(std::string _shapeName,const ngl::Vec3 &_pos)
{
    //create a dynamic rigidbody
    btCollisionShape* colShape = CollisionShape::instance()->getShape(_shapeName);
    /// Create Dynamic Objects
    btTransform startTransform;
    startTransform.setIdentity();
    btScalar	mass(2.0);

    btVector3 localInertia(10,10,10);
    colShape->calculateLocalInertia(mass,localInertia);
    startTransform.setOrigin(btVector3(_pos.m_x,_pos.m_y,_pos.m_z));

    //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,colShape,localInertia);
    btRigidBody* body = new btRigidBody(rbInfo);
    body->setFriction(1.0);
    body->setRollingFriction(1.0);
    body->setUserPointer(new std::string(_shapeName));
    m_dynamicsWorld->addRigidBody(body);
    Body b;
    b.name=_shapeName;
    b.body=body;
    m_bodies.push_back(b);
}


void PhysicsWorld::addBox(std::string _shapeName,const ngl::Vec3 &_pos)
{

	btCollisionShape* colShape = CollisionShape::instance()->getShape(_shapeName);



	/// Create Dynamic Objects
	btTransform startTransform;
	startTransform.setIdentity();

	btScalar	mass(2.f);


	btVector3 localInertia(20,120,120);
	colShape->calculateLocalInertia(mass,localInertia);
	startTransform.setOrigin(btVector3(_pos.m_x,_pos.m_y,_pos.m_z));

	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,colShape,localInertia);
	rbInfo.m_restitution = 0.1f;
  rbInfo.m_friction = 100.5f;
	rbInfo.m_additionalAngularDampingFactor=4.0;
	rbInfo.m_additionalDamping=true;
	btRigidBody* body = new btRigidBody(rbInfo);
    body->setUserPointer(new std::string(_shapeName));
    m_dynamicsWorld->addRigidBody(body);
	Body b;
	b.name=_shapeName;
	b.body=body;
	m_bodies.push_back(b);

}

void PhysicsWorld::step(float _time, float _step)
{
  m_dynamicsWorld->stepSimulation(_time,_step);
}


int PhysicsWorld::getCollisionShape(unsigned int _index) const
{
  btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[_index];
  btCollisionShape *collisionShape = obj->getCollisionShape();

  return collisionShape->getShapeType();
}

void * PhysicsWorld::getUserData(unsigned int _index)
{
  btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[_index];
  btCollisionShape *collisionShape = obj->getCollisionShape();
  return collisionShape->getUserPointer();
}


ngl::Mat4 PhysicsWorld::getTransformMatrix(unsigned int _index)
{
	btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[_index];
	btRigidBody* body = btRigidBody::upcast(obj);
	if (body && body->getMotionState())
	{
		btTransform trans;

		body->getMotionState()->getWorldTransform(trans);
		float matrix[16];
		trans.getOpenGLMatrix(matrix);
		return ngl::Mat4( matrix[0],matrix[1],matrix[2],matrix[3],
											 matrix[4],matrix[5],matrix[6],matrix[7],
											 matrix[8],matrix[9],matrix[10],matrix[11],
											 matrix[12],matrix[13],matrix[14],matrix[15]
				);
	}
	else return ngl::Mat4();

}

ngl::Vec3 PhysicsWorld::getPosition(unsigned int _index)
{
	btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[_index];
	btRigidBody* body = btRigidBody::upcast(obj);
	if (body && body->getMotionState())
	{
		btTransform trans;
		body->getMotionState()->getWorldTransform(trans);
		return ngl::Vec3(trans.getOrigin().getX(),
										 trans.getOrigin().getY(),
										 trans.getOrigin().getZ()
										);
	}
	else return ngl::Vec3();
}


void PhysicsWorld::reset()
{
	// start at 1 to leave the ground plane
	for(unsigned int i=1; i<m_bodies.size(); ++i)
	{
		m_dynamicsWorld->removeRigidBody(m_bodies[i].body);
	}
	m_bodies.erase(m_bodies.begin()+1,m_bodies.end());

}

void PhysicsWorld::addImpulse(const ngl::Vec3 &_i, const std::string& name)
{
    bool found = false;
    for (int i= 1; i<m_bodies.size();i++)
    {
        if (m_bodies[i].name == name)
        {
            m_bodies[i].body->applyCentralImpulse(btVector3(_i.m_x,_i.m_y,_i.m_z));
            std::cout << "found" <<std::endl;;
            found = true;
            break;
        }
    }
    if (!found)
    {
        std::cout << "not found"<<std::endl;;
    }
}

std::string PhysicsWorld::getCollision()
{
    int numManifolds = m_dynamicsWorld->getDispatcher()->getNumManifolds();

    for (int i = 0; i < numManifolds; i++)
    {
        btPersistentManifold* contactManifold = m_dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
        const btCollisionObject* obA = contactManifold->getBody0();
        const btCollisionObject* obB = contactManifold->getBody1();

        // Get the user pointers to identify the objects
        void* userPointerA = obA->getUserPointer();
        void* userPointerB = obB->getUserPointer();

        std::string nameA = userPointerA ? *(static_cast<std::string*>(userPointerA)) : "Unknown";
        std::string nameB = userPointerB ? *(static_cast<std::string*>(userPointerB)) : "Unknown";

        // std::cout << "Collision detected between " << nameA << " and " << nameB << std::endl;

        if ((nameA == "player" && nameB == "enemy1") || (nameA == "enemy1" && nameB == "player"))
        {
            return "enemy1";
        }
        else if ((nameA == "player" && nameB == "teapot") || (nameA == "teapot" && nameB == "player"))
        {
            return "teapot";
        }
        else if ((nameA == "player" && nameB == "box") || (nameA == "teapot" && nameB == "box"))
        {
            return "box";
        }
    }

    return "none";

}
