#ifndef BOID_H__
#define BOID_H__
#include <vector>
#include <memory>
#include <iostream>
#include <ngl/Vec3.h>
#include <ngl/Colour.h>

class Flock;
class Boid
{
  //friend class Flock;

  public :
    //Boid(ngl::Vec3 m_startPos);
    Boid(Flock *_flock);
    ~Boid() = default;
    ngl::Vec3 getPos(){return m_pos;}
    void setPos(ngl::Vec3);
    ngl::Vec3 getDir(){return m_dir;}
    void setDir(const ngl::Vec3 &_p);


  private :
    ngl::Vec3 m_pos;
    ngl::Vec3 m_dir;
    float m_radius;
    ngl::Vec3 m_startPos;
    ngl::Colour m_colour;
    int m_life;

    Flock *m_flock;

};

#endif
