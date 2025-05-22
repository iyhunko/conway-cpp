using Xunit;
using ConwayLib;

namespace Tests;

public class ConwayTests
{
    [Fact]
    public void Blinker()
    {
        var alive = World.Blinker(new Coord { X = 0, Y = 1 });
        var original = new World(3, alive);
        var gen1 = original.Evolve();
        var expectedAlive = new List<Coord>
        {
            new() {X = 1, Y = 0},
            new() {X = 1, Y = 1},
            new() {X = 1, Y = 2}
        };
        var expected = new World(3, expectedAlive);
        Assert.Equal(expected, gen1);
        var gen2 = gen1.Evolve();
        Assert.Equal(original, gen2);
    }

    [Fact]
    public void Block()
    {
        var alive = World.Block(new Coord { X = 0, Y = 0 });
        var original = new World(5, alive);
        var next = original.Evolve();
        Assert.Equal(next, original);
    }

    [Fact]
    public void Tub()
    {
        var alive = World.Tub(new Coord { X = 0, Y = 0 });
        var original = new World(5, alive);
        var next = original.Evolve();
        Assert.Equal(next, original);
    }
}
