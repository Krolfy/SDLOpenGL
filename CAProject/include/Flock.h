#ifndef FLOCK_H__
#define FLOCK_H__
#include "Boid.h"
#include <memory>
#include <iostream>
#include <vector>
#include <ngl/Vec3.h>
#include <ngl/Colour.h>

class Boid;

class Flock
{

  public :
    Flock();
    ~Flock() = default;
    float PossitiveDif(float NeighbourDis);
    void Neighbourhood(int i, float m_radius);
    void AddBoid();
    void RemoveBoid();
    void Cohesion(int i, float CohStrength, ngl::Vec3 *OutCohesion);
    void Seperation(ngl::Vec3 m_pos, ngl::Vec3 m_dir, float m_radius, int i, float SepStrength, ngl::Vec3 *OutSeperation);
    void Allignment(ngl::Vec3 m_dir, float AllStrength, ngl::Vec3 *OutAllignment);
    void newDirection(ngl::Vec3 *OutCohesion,ngl::Vec3 *OutSeperation, ngl::Vec3 *OutAllignment, ngl::Vec3 *new_dir);
    void newPosition(ngl::Vec3 *new_dir,ngl::Vec3 m_pos, ngl::Vec3 *new_pos);
    void moveBoids(float, float, float CohStrength, float SepStrength, float AllStrength);
    int GetBoidCount(){return m_BoidCount;}
    void BoidsPositions(float *);




  private :
    int m_BoidCount;
    int m_NeighbourCount;
    std::vector<ngl::Vec3>m_BoidPositions;
    std::vector<Boid *>m_BoidList;
    std::vector<int>m_NeighbourList;

};

#endif

