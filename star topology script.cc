#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h" // For visualization

using namespace ns3;

int main (int argc, char *argv[])
{
    // Number of leaf nodes
    uint32_t nLeaf = 5;

    // Create hub node and leaf nodes
    NodeContainer hub;
    hub.Create (1);
    
    NodeContainer leafNodes;
    leafNodes.Create (nLeaf);

    // Define point-to-point links
    PointToPointHelper pointToPoint;
    pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
    pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

    // Connect each leaf node to the hub
    NetDeviceContainer devices[nLeaf];
    for (uint32_t i = 0; i < nLeaf; ++i)
    {
        devices[i] = pointToPoint.Install (NodeContainer(hub.Get(0), leafNodes.Get(i)));
    }

    // Install internet stack
    InternetStackHelper internet;
    internet.Install (hub);
    internet.Install (leafNodes);

    // Assign IP addresses
    Ipv4AddressHelper ipv4;
    for (uint32_t i = 0; i < nLeaf; ++i)
    {
        std::ostringstream subnet;
        subnet << "10.1." << i+1 << ".0";
        ipv4.SetBase (subnet.str().c_str(), "255.255.255.0");
        ipv4.Assign (devices[i]);
    }

    // Enable animation
    AnimationInterface anim ("qkd_star_topology.xml");

    Simulator::Run ();
    Simulator::Destroy ();
    return 0;
}
