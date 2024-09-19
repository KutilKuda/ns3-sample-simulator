#include <iostream>
#include "ns3/simulator.h"
#include "ns3/nstime.h"
#include "ns3/command-line.h"
#include "ns3/double.h"
#include "ns3/random-variable-stream.h"

using namespace ns3;

int main (int argc, char *argv[])
{
    CommandLine cmd;
    cmd. Parse (argc, argv);
    
    MyModel model;
    Ptr<UniformRandomVariable> v = CreateObject<UniformRandomVariable> ();
    v ->  SetAttribute ("Min", DoubleValue (10));
    v ->  SetAttribute ("Max", DoubleValue (20));

    Simulator:: Schedule (Seconds (10.0), &ExampleFunction, &model);

    Simulator:: Schedule (Seconds (v->GetValue ()), &RandomFunction);

    EventId id = Simulator :: Schedule (Seconds (30.0), &CancelledEvent);
    Simulator::Cancel (id);

    Simulator::Run ();
    Simulator::Destroy ();
}

