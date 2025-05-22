using ConwayLib;

Console.CancelKeyPress += (sender, eventArgs) =>
{
    Console.Clear();
    Environment.Exit(0);
};

var alive = World.Blinker(new Coord { X = 0, Y = 1 });
alive.AddRange(World.Beacon(new Coord { X = 10, Y = 10 }));
alive.AddRange(World.Glider(new Coord { X = 4, Y = 5 }));
alive.AddRange(World.Block(new Coord { X = 1, Y = 10 }));
alive.AddRange(World.Block(new Coord { X = 18, Y = 3 }));
alive.AddRange(World.Tub(new Coord { X = 6, Y = 1 }));
var world = new World(30, alive);
var  generation = 0;

Console.Clear();
while (true)
{
    generation++;
    Console.WriteLine(world);
    Console.WriteLine("Generation " + generation);
    world = world.Evolve();
    Thread.Sleep(500);
    Console.Clear();
}
