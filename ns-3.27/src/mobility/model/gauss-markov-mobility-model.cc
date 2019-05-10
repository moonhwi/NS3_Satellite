/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 Dan Broyles
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Dan Broyles <dbroyl01@ku.edu>
 */
#include <cmath>
#include "ns3/simulator.h"
#include "ns3/double.h"
#include "ns3/pointer.h"
#include "ns3/string.h"
#include "gauss-markov-mobility-model.h"
#include "position-allocator.h"
#include <cstdlib>
#include <iostream>

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (GaussMarkovMobilityModel);

TypeId
GaussMarkovMobilityModel::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::GaussMarkovMobilityModel")
    .SetParent<MobilityModel> ()
    .SetGroupName ("Mobility")
    .AddConstructor<GaussMarkovMobilityModel> ()
    .AddAttribute ("Bounds",
                   "Bounds of the area to cruise.",
                   BoxValue (Box (-100.0, 100.0, -100.0, 100.0, 0.0, 100.0)),
                   MakeBoxAccessor (&GaussMarkovMobilityModel::m_bounds),
                   MakeBoxChecker ())
    .AddAttribute ("TimeStep",
                   "Change current direction and speed after moving for this time.",
                   TimeValue (Seconds (1.0)),
                   MakeTimeAccessor (&GaussMarkovMobilityModel::m_timeStep),
                   MakeTimeChecker ());
  /*  .AddAttribute ("Alpha",
                   "A constant representing the tunable parameter in the Gauss-Markov model.",
                   DoubleValue (1.0),
                   MakeDoubleAccessor (&GaussMarkovMobilityModel::m_alpha),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("MeanVelocity",
                   "A random variable used to assign the average velocity.",
                   StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=1.0]"),
                   MakePointerAccessor (&GaussMarkovMobilityModel::m_rndMeanVelocity),
                   MakePointerChecker<RandomVariableStream> ())
    .AddAttribute ("MeanDirection",
                   "A random variable used to assign the average direction.",
                   StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=6.283185307]"),
                   MakePointerAccessor (&GaussMarkovMobilityModel::m_rndMeanDirection),
                   MakePointerChecker<RandomVariableStream> ())
    .AddAttribute ("MeanPitch",
                   "A random variable used to assign the average pitch.",
                   StringValue ("ns3::ConstantRandomVariable[Constant=0.0]"),
                   MakePointerAccessor (&GaussMarkovMobilityModel::m_rndMeanPitch),
                   MakePointerChecker<RandomVariableStream> ())
    .AddAttribute ("NormalVelocity",
                   "A gaussian random variable used to calculate the next velocity value.",
                   StringValue ("ns3::NormalRandomVariable[Mean=0.0|Variance=1.0|Bound=10.0]"), // Defaults to zero mean, and std dev = 1, and bound to +-10 of the mean
                   MakePointerAccessor (&GaussMarkovMobilityModel::m_normalVelocity),
                   MakePointerChecker<NormalRandomVariable> ())
    .AddAttribute ("NormalDirection",
                   "A gaussian random variable used to calculate the next direction value.",
                   StringValue ("ns3::NormalRandomVariable[Mean=0.0|Variance=1.0|Bound=10.0]"),
                   MakePointerAccessor (&GaussMarkovMobilityModel::m_normalDirection),
                   MakePointerChecker<NormalRandomVariable> ())
    .AddAttribute ("NormalPitch",
                   "A gaussian random variable used to calculate the next pitch value.",
                   StringValue ("ns3::NormalRandomVariable[Mean=0.0|Variance=1.0|Bound=10.0]"),
                   MakePointerAccessor (&GaussMarkovMobilityModel::m_normalPitch),
                   MakePointerChecker<NormalRandomVariable> ());
*/
  return tid;
}

GaussMarkovMobilityModel::GaussMarkovMobilityModel ()
{
/*  m_meanVelocity = 0.0;
  m_meanDirection = 0.0;
  m_meanPitch = 0.0;*/
  m_event = Simulator::ScheduleNow (&GaussMarkovMobilityModel::Start, this);
  m_helper.Unpause ();
}

void
GaussMarkovMobilityModel::Start (void)
{
  /*if (m_meanVelocity == 0.0)
    {
      //Initialize the mean velocity, direction, and pitch variables
      m_meanVelocity = m_rndMeanVelocity->GetValue ();
      m_meanDirection = m_rndMeanDirection->GetValue ();
      m_meanPitch = m_rndMeanPitch->GetValue ();
      double cosD = std::cos (m_meanDirection);
      double cosP = std::cos (m_meanPitch);
      double sinD = std::sin (m_meanDirection);
      double sinP = std::sin (m_meanPitch);
      //Initialize the starting velocity, direction, and pitch to be identical to the mean ones
      m_Velocity = m_meanVelocity;
      m_Direction = m_meanDirection;
      m_Pitch = m_meanPitch;
      //Set the velocity vector to give to the constant velocity helper
      //m_helper.SetVelocity (Vector (m_Velocity*cosD*cosP, m_Velocity*sinD*cosP, m_Velocity*sinP));
    }*/



//  m_helper.SetPosition (Vector(-3748836.954130,4856904.662021,2637084.068845));
//  m_helper.SetVelocity (Vector (-6076.564494, 1672.881634, 3686.270584));
  //m_helper.Update ();



  //Get the next values from the gaussian distributions for velocity, direction, and pitch
  /*double rv = m_normalVelocity->GetValue ();
  double rd = m_normalDirection->GetValue ();
  double rp = m_normalPitch->GetValue ();
*/
  //Calculate the NEW velocity, direction, and pitch values using the Gauss-Markov formula:
  //newVal = alpha*oldVal + (1-alpha)*meanVal + sqrt(1-alpha^2)*rv
  //where rv is a random number from a normal (gaussian) distribution
//  double one_minus_alpha = 1 - m_alpha;
//  double sqrt_alpha = std::sqrt (1 - m_alpha*m_alpha);
/*  m_Velocity.x  = m_alpha * m_Velocity  + one_minus_alpha * m_meanVelocity  + sqrt_alpha * rv;
  m_Direction = m_alpha * m_Direction + one_minus_alpha * m_meanDirection + sqrt_alpha * rd;
  m_Pitch     = m_alpha * m_Pitch     + one_minus_alpha * m_meanPitch     + sqrt_alpha * rp;

  //Calculate the linear velocity vector to give to the constant velocity helper
  double cosDir = std::cos (m_Direction);
  double cosPit = std::cos (m_Pitch);
  double sinDir = std::sin (m_Direction);
  double sinPit = std::sin (m_Pitch);
  double vx = m_Velocity * cosDir * cosPit;
  double vy = m_Velocity * sinDir * cosPit;
  double vz = m_Velocity * sinPit;
  m_helper.SetVelocity (Vector (vx, vy, vz));
*/
  m_helper.Unpause ();
  DoWalk (m_timeStep);
}

void
GaussMarkovMobilityModel::DoWalk (Time delayLeft)
{
  //m_helper.UpdateWithBounds (m_bounds);
  Vector position = m_helper.GetCurrentPosition ();
  Vector speed = m_helper.GetVelocity ();
  double r=sqrt(pow(position.x,2)+ pow(position.y,2)+pow(position.z,2));
//this is a and @t
  double j2=(-1.08263/1000);//j2 argument
  double j3=2.540*pow(10,-6);//j3 argument
  double re=6.371*pow(10,6);//re is mean radius of earth
  double miu=39860044*pow(10,7);//miu is the gravity argument
  //std::cout<<"position .x"<<position.x<<"position y "<<position.y<<"position z "<<position.z<<"r:"<<r<<"\n";
  double rou=2.28*pow(10,-112);//rou is air density
  double s_m=0.0054;//s_m is the area toward wind rate weight
  double cd =2.2;//cd is the stoping argument
  double vr=sqrt(speed.x*speed.x+speed.y*speed.y+speed.z*speed.z);//vr is the velocity of one time


  double ax = -miu/pow(10,10)*position.x/pow(r,3)*pow(10,10)*(1+3/2*j2*pow((re/r),2)*(1-5*pow(position.z/r,2))+5/2*j3*pow((re/r),3)*(3*position.z/r-7*pow(position.z/r,3)))-1/2*cd*s_m*rou*vr*speed.x;
  double ay = ax*position.y/position.x-1/2*cd*s_m*rou*vr*speed.y;
  double az = -miu*position.z/pow(r,3)*(1+3/2*j2*pow((re/r),2)*(3-5*pow((position.z/r),2)+5/2*j3*pow((re/r),3)*(6*position.z/r-7*pow(position.z/r,3)-3/5*r/position.z)))-1/2*cd*s_m*rou*vr*speed.z;
  //std::cout<<"ax"<<ax<<"ay "<<ay<<"az "<<az<<"\n";
  Vector nextPosition = position;
  nextPosition.x += (speed.x+1/2*ax*delayLeft.GetSeconds ()) * delayLeft.GetSeconds ();
  //std::cout<<delayLeft.GetSeconds ();
  nextPosition.y += (speed.y+1/2*ay*delayLeft.GetSeconds ())* delayLeft.GetSeconds ();
  nextPosition.z += (speed.z+1/2*az*delayLeft.GetSeconds ()) * delayLeft.GetSeconds ();
  //std::cout<<"speedx"<<speed.x<<" speedy"<<speed.y<< " speedz"<<speed.z<<"\n";
  if (delayLeft.GetSeconds () < 0.0) delayLeft = Seconds (0.0001);

  // Make sure that the position by the next time step is still within the boundary.
  // If out of bounds, then alter the velocity vector and average direction to keep the position in bounds
  if (m_bounds.IsInside (nextPosition))
    {
      m_helper.SetPosition (Vector(nextPosition.x, nextPosition.y, nextPosition.z));
      m_helper.SetVelocity (Vector (speed.x+ax*delayLeft.GetSeconds (),speed.y+ay*delayLeft.GetSeconds (), speed.z+az*delayLeft.GetSeconds ()));
      m_event = Simulator::Schedule (delayLeft, &GaussMarkovMobilityModel::Start, this);
    }
  else
    {
      if (nextPosition.x > m_bounds.xMax || nextPosition.x < m_bounds.xMin)
        {
          speed.x = -speed.x;
          m_meanDirection = M_PI - m_meanDirection;
        }

      if (nextPosition.y > m_bounds.yMax || nextPosition.y < m_bounds.yMin)
        {
          speed.y = -speed.y;
          m_meanDirection = -m_meanDirection;
        }

      if (nextPosition.z > m_bounds.zMax || nextPosition.z < m_bounds.zMin)
        {
          speed.z = -speed.z;
          m_meanPitch = -m_meanPitch;
        }

      m_Direction = m_meanDirection;
      m_Pitch = m_meanPitch;
      m_helper.SetVelocity (Vector (speed.x+ax*delayLeft.GetSeconds (),speed.y+ay*delayLeft.GetSeconds (), speed.z+az*delayLeft.GetSeconds ()));
      m_helper.Unpause ();
      m_event = Simulator::Schedule (delayLeft, &GaussMarkovMobilityModel::Start, this);
    }
  NotifyCourseChange ();
}

void
GaussMarkovMobilityModel::DoDispose (void)
{
  // chain up
  MobilityModel::DoDispose ();
}

Vector
GaussMarkovMobilityModel::DoGetPosition (void) const
{
  //m_helper.Update ();
  return m_helper.GetCurrentPosition ();
}
void
GaussMarkovMobilityModel::DoSetPosition (const Vector &position)
{
  m_helper.SetPosition (position);
  Simulator::Remove (m_event);
  m_event = Simulator::ScheduleNow (&GaussMarkovMobilityModel::Start, this);
}
void
GaussMarkovMobilityModel::DoSetPositionForLMH (const Vector &position)
{
  m_helper.SetPosition (position);
}
void
GaussMarkovMobilityModel::DoSetVelocity(const Vector &vel)
{
  m_helper.SetVelocity (vel);
}
Vector
GaussMarkovMobilityModel::DoGetVelocity (void) const
{
  return m_helper.GetVelocity ();
}

int64_t
GaussMarkovMobilityModel::DoAssignStreams (int64_t stream)
{

  /*
  m_rndMeanVelocity->SetStream (stream);
  m_normalVelocity->SetStream (stream + 1);
  m_rndMeanDirection->SetStream (stream + 2);
  m_normalDirection->SetStream (stream + 3);
  m_rndMeanPitch->SetStream (stream + 4);
  m_normalPitch->SetStream (stream + 5);
  */
  return 6;
}

} // namespace ns3
