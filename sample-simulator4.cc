import ns.core

def main(dummy_argv):

model = MyModel()
v = ns.core.UniformRandomVariable()
v.SetAttribute("Min", ns.core.DoubleValue (10))
v.SetAttribute("Max", ns.core.DoubleValue (20))

ns.core.Simulator.Schedule(ns.core.Seconds(10.0), ExampleFunction, model)

ns.core.Simulator.Schedule(ns.core.Seconds(v.GetValue()), RandomFunction, model)

id = ns.core.Simulator.Schedule(ns.core.Seconds(30.0), CancelledEvent)
ns.core.Simulator.Cancel(id)
ns.core.Simulator.Run()
ns.core.Simulator.Destroy()

if __name__ == '__main__':
import sys
main(sys.arv)

