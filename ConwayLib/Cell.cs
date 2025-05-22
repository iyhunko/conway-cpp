namespace ConwayLib;

public enum Cell
{
    Dead,
    Alive
}

public static class Extensions
{
    public static string ToEnumString(this Cell cell) => cell switch
    {
        Cell.Alive => " x |",
        _ => "   |"
    };
}
