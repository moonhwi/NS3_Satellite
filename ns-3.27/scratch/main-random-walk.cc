/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2006,2007 INRIA
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
 */

#include "ns3/core-module.h"
#include "ns3/mobility-module.h"
#include <fstream>
#include <iostream>
#include "ns3/position-allocator.h"
using namespace std;
using namespace ns3;
double number=0;
static void
CourseChange (std::string foo, Ptr<const MobilityModel> mobility)
{
  Vector pos = mobility->GetPosition ();
  Vector vel = mobility->GetVelocity ();
if (number == 10000) {
  std::cout << Simulator::Now () << ", model=" << fixed<<mobility << ", POS: x=" << pos.x << ", y=" << pos.y
            << ", z=" << pos.z << "; VEL:" << vel.x << ", y=" << vel.y
            << ", z=" << vel.z << std::endl;
}


            if (number==10000) {
              ofstream outfile;
              outfile.open("/mnt/hgfs/share/erw.txt");
              outfile <<std::fixed<< pos.x<<" "<<pos.y<<" "<<pos.z<<" "<< vel.x<<" "<<vel.y<<" "<<vel.z<< endl;
              number=1;

            }
            else{
              ofstream outfile;
              outfile.open("/mnt/hgfs/share/erw.txt",ios::app);
            //cout << "Writing to the file" << endl;
            //cout << "Enter your name: ";outfile.close();
            outfile <<std::fixed <<pos.x<<" "<<pos.y<<" "<<pos.z<<" "<< vel.x<<" "<<vel.y<<" "<<vel.z<< endl;
            number+=1;
          }
/*ofstream outfile;
outfile.open("/mnt/hgfs/share/erw.txt",ios::app);
        //cout << "Writing to the file" << endl;
        //cout << "Enter your name: ";outfile.close();
        outfile <<std::fixed<<pos.x<<" "<<pos.y<<" "<<pos.z<<" "<< vel.x<<" "<<vel.y<<" "<<vel.z<< endl;
        number+=1;
        std::cout<<"number"<<number<<'\n';
        outfile.close();
        */

}

int main (int argc, char *argv[])
{



  CommandLine cmd;
  cmd.Parse (argc, argv);
//  GlobalValue::Bind ("SimulatorImplementationType", StringValue ("ns3::RealtimeSimulatorImpl"));
  NodeContainer c;
  c.Create (1);

  MobilityHelper mobility;
  /*mobility.SetPositionAllocator ("ns3::RandomBoxPositionAllocator",
    "X", DoubleValue (-3748836.954),
    "Y", DoubleValue(4856904.662),
    "Z", DoubleValue(2637084.068));
*/
    Ptr<ListPositionAllocator> positionAlloc =
    CreateObject<ListPositionAllocator>();
  positionAlloc->Add (Vector( 1322713.551148 ,-3055603.419702, -5903973.108231 ));
  //positionAlloc->Add (Vector(1170481.522283 ,-1934584.659257 ,-6389877.703193));
  mobility.SetPositionAllocator (positionAlloc);

  mobility.SetMobilityModel ("ns3::GaussMarkovMobilityModel",
    "Bounds", BoxValue (Box (-150000000, 150000000, -150000000, 150000000,-150000000, 150000000)),
    "TimeStep", TimeValue (Seconds (0.0001))
    );


  mobility.InstallAll ();
 for (uint n=0 ; n < c.GetN() ; n++) {
      Ptr<GaussMarkovMobilityModel> mob =c.Get(n)->GetObject<GaussMarkovMobilityModel>();
        mob->DoSetVelocity(Vector( 815.190247 ,-6695.813821, 3648.054352));
      }

  Config::Connect ("/NodeList/*/$ns3::MobilityModel/$ns3::GaussMarkovMobilityModel/CourseChange",
  // /NodeList/*/$ns3::MobilityModel/CourseChange
                   MakeCallback (&CourseChange));

  Simulator::Stop (Seconds (10000.0));

  Simulator::Run ();

  Simulator::Destroy ();
  return 0;

}
