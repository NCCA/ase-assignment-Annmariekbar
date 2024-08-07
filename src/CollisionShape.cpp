#include "CollisionShape.h"
#include <ngl/Obj.h>

CollisionShape *CollisionShape::instance()
{
  // in C++ 11 we use this to avoid having to do a double check lock pattern
  static CollisionShape s_instance;

  return &s_instance;
}

void CollisionShape::addMesh(const std::string & _name, const std::string &_objFilePath)
{
  ngl::Obj mesh(_objFilePath);
  //create a dynamic rigidbody

	btConvexHullShape*  shape =  new btConvexHullShape();
	auto points=mesh.getVertexList();
	for(auto p : points)
	{
		shape->addPoint(btVector3(p.m_x,p.m_y,p.m_z));
	}
	m_shapes[_name].reset(shape);
}

void CollisionShape::addTank(const std::string& _name)
{

}



void CollisionShape::addSphere(const std::string & _name, ngl::Real _rad)
{
	btCollisionShape* shape = new btSphereShape(btScalar(_rad/2.0));
	m_shapes[_name].reset(shape);

}

void CollisionShape::addBox(const std::string & _name, ngl::Real _w, ngl::Real _h, ngl::Real _d)
{
	btCollisionShape* shape = new btBoxShape(btVector3(_w/2.0,_h/2.0,_d/2.0));
	m_shapes[_name].reset(shape);

}

void CollisionShape::addCapsule(const std::string & _name, ngl::Real _rad, ngl::Real _height)
{
	btCollisionShape* shape = new  btCapsuleShape(_rad,_height);
	m_shapes[_name].reset(shape);

}

void CollisionShape::addCylinder(const std::string & _name, ngl::Real _rad, ngl::Real _height)
{
	btCollisionShape* shape = new  btCylinderShapeZ(btVector3(_rad,_height/2.0,_rad));
	m_shapes[_name].reset(shape);

}

void CollisionShape::addCone(const std::string & _name, ngl::Real _rad, ngl::Real _height)
{
	btCollisionShape* shape = new  btConeShapeZ(_rad,_height);
	m_shapes[_name].reset(shape);

}

btCollisionShape* CollisionShape::getShape(const std::string &_name)
{
	btCollisionShape *shape=nullptr;
	auto shapeIt=m_shapes.find(_name);
	// make sure we have a valid shader
	if(shapeIt!=m_shapes.end())
	{
		shape=shapeIt->second.get();
	}
	return shape;
}



