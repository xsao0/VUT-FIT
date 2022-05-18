using Microsoft.EntityFrameworkCore;
using xDrive.DAL.Entities;

namespace xDrive.DAL.Seeds;

public static class CarSeeds
{
    public static readonly CarEntity Car1 = new(
        Id: Guid.Parse(input: "55939f75-d897-4a4d-9fd5-28ddd78d9e96"),
        "FST DRIV3",
        "BMW",
        "M4",
        new DateTime(2018, 12, 1),
        @"https://cdn.bmwblog.com/wp-content/uploads/2020/03/bmw-m4.jpg",
        4,
        UserSeeds.User3.Id)
    {
        Owner = UserSeeds.User3
    };

    public static readonly CarEntity Car2 = new(
        Id: Guid.Parse("c4c5432d-f6c1-4c3c-8858-93f1e8a1763c"),
        "CZ5 HOMER",
        "Škoda",
        "Kodiaq",
        new DateTime(2020, 10, 10),
        @"https://upload.wikimedia.org/wikipedia/commons/2/2c/Skoda_Kodiaq_2.0_TDI_4x4_Sportline_%E2%80%93_f_28042021.jpg",
        5,
        UserSeeds.User1.Id)
    {
        Owner = UserSeeds.User1
    };

    static CarSeeds()
    {
        Car1.PlannedRoutes.Add(RouteSeeds.Route1);
        Car2.PlannedRoutes.Add(RouteSeeds.Route2);
    }

    public static void Seed(this ModelBuilder modelBuilder) =>
        modelBuilder.Entity<CarEntity>().HasData(
            Car1 with { PlannedRoutes = Array.Empty<RouteEntity>(), Owner = null },
            Car2 with { PlannedRoutes = Array.Empty<RouteEntity>(), Owner = null }
        );
}
