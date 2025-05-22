using System.Text;

namespace ConwayLib;

public class World
{
    public readonly Dictionary<Coord, Cell> Cells = new();
    public int Size { get; }

    public World(int size, ICollection<Coord> aliveCells)
    {
        Size = size;
        for (var a = 0; a < size; ++a)
            for (var b = 0; b < size; ++b)
            {
                var coord = new Coord { X = a, Y = b };
                Cells[coord] = (aliveCells.Contains(coord)) ? Cell.Alive : Cell.Dead;
            }
    }

    public World Evolve()
    {
        var aliveCells = new List<Coord>();
        var range = new[] { -1, 0, 1 };
        foreach (var item in Cells)
        {
            var count = (from a in range
                         from b in range
                         select new Coord { X = item.Key.X + a, Y = item.Key.Y + b })
                .Count(currentCoord => currentCoord != item.Key
                                        && Cells.ContainsKey(currentCoord)
                                        && Cells[currentCoord] == Cell.Alive);

            switch (item.Value)
            {
                case Cell.Alive:
                    if (count == 2 || count == 3) aliveCells.Add(item.Key);
                    break;

                case Cell.Dead:
                    if (count == 3) aliveCells.Add(item.Key);
                    break;
            }
        }

        return new World(Size, aliveCells);
    }

    public override string ToString()
    {
        var builder = new StringBuilder("\n");
        for (var a = 0; a < Size; ++a)
        {
            if (a == 0)
            {
                // First line with coordinates
                builder.Append("    ");
                for (var b = 0; b < Size; ++b) builder.AppendFormat("{0,3}|", b);
                builder.Append('\n');
            }

            builder.AppendFormat("{0,3}|", a);
            for (var b = 0; b < Size; ++b)
            {
                var coord = new Coord { X = b, Y = a };
                var cell = Cells[coord];
                builder.Append(cell.ToEnumString());
            }

            builder.Append('\n');
        }

        return builder.ToString();
    }

    public override bool Equals(object? obj) => obj != null && Equals((World)obj);

    private bool Equals(World other) => Size == other.Size && Cells.SequenceEqual(other.Cells);

    public override int GetHashCode() => HashCode.Combine(Size, Cells);

    public static List<Coord> Blinker(Coord coord) => new()
    {
        new() {X = coord.X,     Y = coord.Y},
        new() {X = coord.X + 1, Y = coord.Y},
        new() {X = coord.X + 2, Y = coord.Y}
    };

    public static List<Coord> Beacon(Coord coord) => new()
    {
        new() {X = coord.X,     Y = coord.Y},
        new() {X = coord.X + 1, Y = coord.Y},
        new() {X = coord.X,     Y = coord.Y + 1},
        new() {X = coord.X + 1, Y = coord.Y + 1},
        new() {X = coord.X + 2, Y = coord.Y + 2},
        new() {X = coord.X + 3, Y = coord.Y + 2},
        new() {X = coord.X + 2, Y = coord.Y + 3},
        new() {X = coord.X + 3, Y = coord.Y + 3}
    };

    public static List<Coord> Glider(Coord coord) => new()
    {
        new() {X = coord.X + 2, Y = coord.Y + 2},
        new() {X = coord.X + 1, Y = coord.Y + 2},
        new() {X = coord.X,     Y = coord.Y + 2},
        new() {X = coord.X + 2, Y = coord.Y + 1},
        new() {X = coord.X + 1, Y = coord.Y}
    };

    public static List<Coord> Block(Coord coord) => new()
    {
        new() {X = coord.X,     Y = coord.Y},
        new() {X = coord.X + 1, Y = coord.Y},
        new() {X = coord.X,     Y = coord.Y + 1},
        new() {X = coord.X + 1, Y = coord.Y + 1}
    };

    public static List<Coord> Tub(Coord coord) => new()
    {
        new() {X = coord.X + 1, Y = coord.Y},
        new() {X = coord.X,     Y = coord.Y + 1},
        new() {X = coord.X + 2, Y = coord.Y + 1},
        new() {X = coord.X + 1, Y = coord.Y + 2}
    };
}
