#include "Boid.h"
#include "Flock.h"
#include <ngl/NGLStream.h>
#include <ngl/Transformation.h>
#include <ngl/VAOPrimitives.h>
#include <vector>
#include <math.h>

//Boid::Boid(ngl::Vec3 m_startPos)
//{
//pass  m_pos=m_startPos;

//}

Boid::Boid(Flock *_flock)
{
  m_pos.m_x=rand()%5;
  m_pos.m_y=rand()%5;
  m_pos.m_z=rand()%5;
  m_dir.m_x=rand()%5;
  m_dir.m_y=rand()%5;
  m_dir.m_z=rand()%5;
  m_flock=_flock;

}

void Boid::setPos(ngl::Vec3 new_pos)
{
  m_pos=new_pos;
}

void Boid::setDir(const ngl::Vec3 &_p)
{
  m_dir=_p;
}

