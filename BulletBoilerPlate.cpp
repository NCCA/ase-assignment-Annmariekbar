#include <iostream>
#include <memory>
#include <fmt/format.h>
#include <cstdlib>
#include <btBulletDynamicsCommon.h>

int main()
{
    // Build the broadphaselsl
    auto broadphase = std::make_unique<btDbvtBroadphase>();
    // Set up the collision configuration and dispatcher
    auto collisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
    auto dispatcher = std::make_unique<btCollisionDispatcher>(collisionConfiguration.get());
    // The actual physics solver
    auto solver = std::make_unique<btSequentialImpulseConstraintSolver>();
    // The world. Note we use .get() to get a raw pointer from the unique pointer
    auto dynamicsWorld = std::make_unique<btDiscreteDynamicsWorld>(dispatcher.get(), broadphase.get(), solver.get(), collisionConfiguration.get());
    // Set gravity
    dynamicsWorld->setGravity(btVector3(0, -9.82, 0));
    // create static ground plane
    auto groundShape = std::make_unique<btStaticPlaneShape>(btVector3(0, 1, 0), 1);
    auto groundMotionState = std::make_unique<btDefaultMotionState>(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
    auto groundRigidBodyCI = btRigidBody::btRigidBodyConstructionInfo(0, groundMotionState.get(), groundShape.get(), btVector3(0, 0, 0));
    auto groundRigidBody = std::make_unique<btRigidBody>(groundRigidBodyCI);
    // add static ground plane to world
    dynamicsWorld->addRigidBody(groundRigidBody.get());

    // create dynamic sphere
    auto fallShape = std::make_unique<btSphereShape>(1);
    auto fallMotionState = std::make_unique<btDefaultMotionState>(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
    btScalar mass = 1;
    btVector3 fallInertia(2, 1, 2);
    fallShape->calculateLocalInertia(mass, fallInertia);
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState.get(), fallShape.get(), fallInertia);
    auto fallRigidBody = std::make_unique<btRigidBody>(fallRigidBodyCI);
    // add dynamic sphere to world
    dynamicsWorld->addRigidBody(fallRigidBody.get());
    // simple simulation loop
    for (int i = 0; i < 300; i++)
    {
        // step simulation
        dynamicsWorld->stepSimulation(1 / 60.f, 10);
        // print sphere position
        btTransform trans;
        fallRigidBody->getMotionState()->getWorldTransform(trans);
        fmt::print("{} {} {} \n", trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
    }

    return EXIT_SUCCESS;
}

/*struct sphere{
    vec3 pos;
    vec3 vel;
    float scale = ;
    vec4 col;
}

sphere.pos = anywhere in tank;
sphere.vel = dependent on mouse;
sphere.col = randomofthreecolouroptions;



constraints{
    if (hits == TankSide || hits == otherBall){
        currentVelocity ==-(currentVelocity);
    }


};*/