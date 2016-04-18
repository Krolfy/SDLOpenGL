#include "Boid.h"
#include "Flock.h"
#include <ngl/NGLStream.h>
#include <ngl/Vec3.h>
#include <ngl/Transformation.h>
#include <ngl/VAOPrimitives.h>
#include <vector>
#include <algorithm>
#include <math.h>


float Flock::PossitiveDif(float NeighbourDis)
{
    //converts any given coordinate distance to a possitive float number
    //to do, square and take the root (to work for both possitive and negative numbers)
    NeighbourDis=sqrt(NeighbourDis*NeighbourDis);

    //std::cout<<"NeighbourDis"<<std::endl;

    return NeighbourDis;
}

Flock::Flock()
{

  m_BoidCount = 0;
  m_NeighbourCount = 0;
  m_BoidList.clear();
  m_NeighbourList.clear();

}

//iterates through all boids and compares distance to current boid (see 'possitive difference') to determie if they are within the neighbourhood.
void Flock::Neighbourhood(int i,float m_radius)
{

  float NeighbourDis = 0;
  m_NeighbourCount=0;
  int j=0;

       //iterate through all boids, where this is the boid to be compared
       for(j=0;j<m_BoidCount;j++)
       {
         //std::cout<<"j="<<j<<std::endl;

         //only compare if not comparing to itself
         if (j!=i)
         {
            //compares distance to current boid, where EuclidDistance = sqrt((x1-x2)^2 + (y1-y2)^2 + (z1-z2)^2)
            NeighbourDis = m_BoidList[i]->getPos().length();
                             //m_BoidList[i]->m_pos.m_x)-(m_BoidList[j]->m_pos.m_x))+((m_BoidList[i]->m_pos.m_y)-(m_BoidList[j]->m_pos.m_y)) + ((m_BoidList[i]->m_pos.m_z)-(m_BoidList[j]->m_pos.m_z));
            //std::cout<<"NeighbourDis1="<<NeighbourDis<<std::endl;

            //Convert to possitive
            PossitiveDif(NeighbourDis);
            //std::cout<<"NeighbourDis2="<<NeighbourDis<<std::endl;

              //If other boid is within Neighbourhood radius
              if (NeighbourDis<m_radius)
              {
                //adds neighbour boid to neighbour list array
                m_NeighbourList.push_back(j);
                //increments neighbour counter
                m_NeighbourCount++;
              }
         }
       }
  //for (int k=0; k<m_NeighbourCount;k++)
  //{
  //  std::cout<<"Neighbourlist %k:"<<m_NeighbourList[k]<<std::endl;
  //}
  //std::cout<<"NeighbourCount: "<<m_NeighbourCount<<std::endl;
  //std::cout<<"Neighbourhood working"<<std::endl;
}

/*void Flock::Normalise()
{
    //normalises boid vector, to convert to unit vector (direction, not length)
    //float NormVec = sqrt(exp2(m_BoidList[?]->m_dir[0]) + exp2(m_BoidList[?]->m_dir[1]) + exp2(m_BoidList[?]->m_dir[2])); //FIND OUT WHEN THIS IS USED AND EDIT!

    //std::cout<<"Normalise working"<<std::endl;

}*/


void Flock::AddBoid()
{
  //push onto array
  m_BoidList.push_back(new Boid(this));
  //increment boid counter
  m_BoidCount++;

  //std::cout<<"AddBoid working"<<std::endl;
}

void Flock::RemoveBoid()
{
  //call destructer
  m_BoidList[m_BoidCount-1]->~Boid();
  //delete position

  //pop off array
  //m_BoidList.pop_back(Boid);
  //decrement boid counter
  m_BoidCount--;

  //std::cout<<"RemoveBoid working"<<std::endl;
}

void Flock::Cohesion(int i, float CohStrength, ngl::Vec3 *OutCohesion)
{
  //initialise a position sum;
  ngl::Vec3 positionSum;
  ngl::Vec3 average_pos;
  ngl::Vec3 aim_pos;
  positionSum.set(0,0,0);
  average_pos.set(0,0,0);
  aim_pos.set(0,0,0);

  //iterate through boids in neighbourhood
  for (int j=0; j<m_NeighbourCount; j++)  //COME BACK TO THIS
  {
    //add their position to position sum
    positionSum+=m_BoidList[m_NeighbourList[j]]->getPos();
    //positionSum.m_x+=(m_BoidList[m_NeighbourList[j]]->m_pos.m_x);
    //positionSum.m_y+=(m_BoidList[m_NeighbourList[j]]->m_pos.m_y);
    //positionSum.m_z+=(m_BoidList[m_NeighbourList[j]]->m_pos.m_z);
  }

  //std::cout<<positionSum<<std::endl;
  //calculate average position by taking sum and dividing it by the local boid counter
  if (m_NeighbourCount!=0)
  {
    average_pos=positionSum/m_NeighbourCount;
    //average_pos.m_x = positionSum.m_x/m_NeighbourCount;
    //average_pos.m_y = positionSum.m_y/m_NeighbourCount;
    //average_pos.m_z = positionSum.m_z/m_NeighbourCount;

    //work out position vector (current average position - position)
    aim_pos=average_pos-(m_BoidList[i]->getPos());
    //aim_pos.m_x = average_pos.m_x-m_pos.m_x;
    //aim_pos.m_y = average_pos.m_y-m_pos.m_y;
    //aim_pos.m_z = average_pos.m_z-m_pos.m_z;

    //work out direction vector
    OutCohesion = average_pos-(m_BoidList[i]->getPos());
   // OutCohesion->m_x = average_pos.m_x-m_pos.m_x;
   // OutCohesion->m_y = average_pos.m_y-m_pos.m_y;
   // OutCohesion->m_z = average_pos.m_z-m_pos.m_z;

    float cohesion = OutCohesion->length();
    //float cohesion = sqrt(((OutCohesion->m_x)*(OutCohesion->m_x))+((OutCohesion->m_y)*(OutCohesion->m_y))+((OutCohesion->m_z)*(OutCohesion->m_z)));
    OutCohesion/=cohesion*CohStrength;
    //OutCohesion->m_x = (OutCohesion->m_x/cohesion)*(CohStrength);
    //OutCohesion->m_y = (OutCohesion->m_y/cohesion)*(CohStrength);
    //OutCohesion->m_z = (OutCohesion->m_z/cohesion)*(CohStrength);
  }
  //OutCohesion->m_x =(OutCohesion->m_x)*CohStrength;
  //OutCohesion->m_y =(OutCohesion->m_z)*CohStrength;
  //OutCohesion->m_z =(OutCohesion->m_y)*CohStrength;

  //Cohension - average position of local boids
  //std::cout<<"Cohesion working"<<std::endl;
}


void Flock::Seperation(ngl::Vec3 m_pos, ngl::Vec3 m_dir,float m_boundary, int i, float SepStrength, ngl::Vec3 *OutSeperation)
{

  //interate through boids in neighbourhood
  for (int j=0;j<m_NeighbourCount;j++)
  {
    ngl::Vec3 distanceVec;
    ngl::Vec3 NormDistance;
    distanceVec.set(1,0,0);
    NormDistance.set(0,0,0);

    //calculate vector between two boid centres (boundingsphere2-boundingsphere1) -> vector d(istance)
    distanceVec = (m_BoidList[i]->getPos())-(m_BoidList[m_NeighbourList[j]]->getPos());
    //distanceVec.m_x = (m_BoidList[i]->m_pos.m_x)-(m_BoidList[m_NeighbourList[j]]->m_pos.m_x);
    //distanceVec.m_y = (m_BoidList[i]->m_pos.m_y)-(m_BoidList[m_NeighbourList[j]]->m_pos.m_y);
    //distanceVec.m_z = (m_BoidList[i]->m_pos.m_z)-(m_BoidList[m_NeighbourList[j]]->m_pos.m_z);

    //std::cout<<"Seperation distanceVec:["<<distanceVec.m_y<<" "<<distanceVec.m_y<<" "<<distanceVec.m_z<<"]"<<std::endl;

    //Calculate distance - vector magnitude
    float distance = sqrt((distanceVec.m_x*distanceVec.m_x)+(distanceVec.m_y*distanceVec.m_y)+(distanceVec.m_z*distanceVec.m_z));
    //std::cout<<"seperation distance:"<<distance<<std::endl;

    //calculate the intersection (distance-boundingsphere radius)
    //float intersection = distance-m_boundary;
   //std::cout<<"seperation intersection:"<<intersection<<std::endl;

    //if s>0 then there is no collision -> no action
    //but if s<=0 then the spheres are colliding -> action
    if (distance <= m_boundary)
    {
        //std::cout << m_BoidCount << std::endl;
     //calculate collision normal (normalize distance -> NormDistance)
     NormDistance = distanceVec/distance;
     //NormDistance.m_x = distanceVec.m_x/distance;
     //NormDistance.m_y = distanceVec.m_y/distance;
     //NormDistance.m_z = distanceVec.m_z/distance;

     //test if moving towards or away from eachother (v1-v2=v3 v3.Nd=direction)
     //ngl::Vec3 velocityVec;
     //velocityVec.m_x = (m_BoidList[m_NeighbourList[j]]->m_dir.m_x)-(m_BoidList[i]->m_dir.m_x);
     //velocityVec.m_y = (m_BoidList[m_NeighbourList[j]]->m_dir.m_y)-(m_BoidList[i]->m_dir.m_y);
     //velocityVec.m_z = (m_BoidList[m_NeighbourList[j]]->m_dir.m_z)-(m_BoidList[i]->m_dir.m_z);

     //float direction = (NormDistance.m_x*velocityVec.m_x)+(NormDistance.m_y*velocityVec.m_y)+(NormDistance.m_z*velocityVec.m_z);

        //if direction is positive, then they are moving away from eachother -> no action
        //but if direction is negative, then they are moving towards eachother -> action
        //if (direction<0)
        //{
          //reverse vector s to repel boids
          //OutSeperation = (getDir())*(-1);
          OutSeperation->m_x = (m_dir.m_x)*(-1);
          OutSeperation->m_y = (m_dir.m_y)*(-1);
          OutSeperation->m_z = (m_dir.m_z)*(-1);

          float seperation = OutSeperation->length();
          //float seperation = sqrt((OutSeperation->m_x)*(OutSeperation->m_x))+((OutSeperation->m_y)*(OutSeperation->m_y))+((OutSeperation->m_z)*(OutSeperation->m_z));
          //OutSeperation->m_x = (OutSeperation->m_x/seperation)*(SepStrength);
          //OutSeperation->m_y = (OutSeperation->m_y/seperation)*(SepStrength);
          //OutSeperation->m_z = (OutSeperation->m_z/seperation)*(SepStrength);

          //OutSeperation->m_x = (OutSeperation->m_x)*(SepStrength);
          //OutSeperation->m_y = (OutSeperation->m_y)*(SepStrength);
          //OutSeperation->m_z = (OutSeperation->m_z)*(SepStrength);
        //}
     }
   }
  //std::cout<<"Seperation working"<<std::endl;
}

void Flock::Allignment(ngl::Vec3 m_dir, float AllStrength, ngl::Vec3 *OutAllignment)
{
  //initialise a position sum;
  ngl::Vec3 directionSum;
  ngl::Vec3 average_dir;
  directionSum.set(0,0,0);
  average_dir.set(0,0,0);

  //iterate through boids in neighbourhood
  for (int j=0; j<m_NeighbourCount; j++)
  {
    //add their position to position sum
//    directionSum.m_x = directionSum.m_x+(m_BoidList[m_NeighbourList[j]]->m_dir.m_x);
//    directionSum.m_y = directionSum.m_y+(m_BoidList[m_NeighbourList[j]]->m_dir.m_y);
//    directionSum.m_z = directionSum.m_z+(m_BoidList[m_NeighbourList[j]]->m_dir.m_z);
    directionSum+=m_BoidList[m_NeighbourList[j]]->getDir();

  }

  if(m_NeighbourCount !=0)
  {
    //calculate average position by taking sum and dividing it by the local boid counter
    average_dir=directionSum/m_NeighbourCount;
    //average_dir.m_x = directionSum.m_x/m_NeighbourCount;
    //average_dir.m_y = directionSum.m_y/m_NeighbourCount;
    //average_dir.m_z = directionSum.m_z/m_NeighbourCount;

  //std::cout<<average_dir<<std::endl;

  //work out vector (current average position - position)
  //OutAllignment = average_dir-getDir();
  OutAllignment->m_x = average_dir.m_x-m_dir.m_x;
  OutAllignment->m_y = average_dir.m_y-m_dir.m_y;
  OutAllignment->m_z = average_dir.m_z-m_dir.m_z;
  //std::cout<<average_dir<<std::endl;
  }

  float allignment = OutAllignment->length();

  if (allignment !=0)
  {

    //float allignment = sqrt(((OutAllignment->m_x)*(OutAllignment->m_x))+((OutAllignment->m_y)*(OutAllignment->m_y))+((OutAllignment->m_z)*(OutAllignment->m_x)));
    //OutAllignment/=allignment*Allstrength;
    OutAllignment->m_x = (OutAllignment->m_x/allignment)*(AllStrength);
    OutAllignment->m_y = (OutAllignment->m_y/allignment)*(AllStrength);
    OutAllignment->m_z = (OutAllignment->m_z/allignment)*(AllStrength);
  }

  //OutAllignment->m_x = (OutAllignment->m_x)*AllStrength;
  //OutAllignment->m_y = (OutAllignment->m_y)*AllStrength;
  //OutAllignment->m_z = (OutAllignment->m_z)*AllStrength;

  //Out
  //std::cout<<"OutAllignment: ["<<OutAllignment->m_y<<" "<<OutAllignment->m_y<<" "<<OutAllignment->m_z<<"]"<<std::endl;
  //std::cout<<"allignment working"<<std::endl;
}

void Flock::newDirection(ngl::Vec3 *OutCohesion,ngl::Vec3 *OutSeperation, ngl::Vec3 *OutAllignment, ngl::Vec3 *new_dir)
{
  new_dir->m_x = ((OutCohesion->m_x)+(OutSeperation->m_x)+(OutAllignment->m_x))/3;
  new_dir->m_y = ((OutCohesion->m_y)+(OutSeperation->m_y)+(OutAllignment->m_y))/3;
  new_dir->m_z = ((OutCohesion->m_z)+(OutSeperation->m_z)+(OutAllignment->m_z))/3;
}

void Flock::newPosition(ngl::Vec3 *new_dir,ngl::Vec3 m_pos, ngl::Vec3 *new_pos)
{
  //new_pos->m_x = (new_dir->m_x)+getPos(m_pos.m_x);
  //new_pos->m_y = (new_dir->m_y)+getPos(m_pos.m_y);
  //new_pos->m_z = (new_dir->m_z)+getPos(m_pos.m_z);
  new_pos = new_dir + getPos();
}

void Flock::BoidsPositions(float *PosArr) //USE VEC3!
{
  int j = 0;
  ngl::Vec3 CurrentPos;

  for (int i = 0; i < m_BoidCount; i++)
  {

    CurrentPos = m_BoidList[i]->GetPos();

    PosArr[j] = CurrentPos.m_x;
    PosArr[j+1] = CurrentPos.m_y;
    PosArr[j+2] = CurrentPos.m_z;

    j+=3;
  }

}


void Flock::moveBoids(float m_radius,float m_boundary, float CohStrength, float SepStrength, float AllStrength)
{
  ngl::Vec3 OutCohesion;
  ngl::Vec3 OutSeperation;
  ngl::Vec3 OutAllignment;
  ngl::Vec3 new_dir;
  ngl::Vec3 new_pos;

  for (int i=0; i<m_BoidCount; i++)
    {
      ngl::Vec3 CurrentBoidPos = m_BoidList[i]->GetPos();
      ngl::Vec3 CurrentBoidDir = m_BoidList[i]->GetDir();

      Neighbourhood(i,m_radius);

      OutCohesion.set(0,0,0);
      Cohesion(CurrentBoidPos,CohStrength,&OutCohesion);

      OutSeperation.set(0,0,0);
      Seperation(CurrentBoidPos, CurrentBoidDir, m_boundary, i,SepStrength, &OutSeperation);

      OutAllignment.set(0,0,0);
      Allignment(CurrentBoidDir,AllStrength, &OutAllignment);

      newDirection( &OutCohesion, &OutSeperation, &OutAllignment, &new_dir);
      newPosition( &new_dir, CurrentBoidPos, &new_pos);
      m_BoidList[i]->SetDir(new_dir);
      m_BoidList[i]->SetPos(new_pos);
    }


}
