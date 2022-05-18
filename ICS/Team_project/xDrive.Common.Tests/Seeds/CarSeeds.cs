using Microsoft.EntityFrameworkCore;
using xDrive.DAL.Entities;

namespace xDrive.Common.Tests.Seeds;

public static class CarSeeds
{
    public static readonly CarEntity EmptyCarEntity = new(
        default,
        default,
        default,
        default,
        default,
        default,
        default,
        default) {Owner = default};

    public static readonly CarEntity Car1 = new(
        Id: Guid.Parse(input: "55939f75-d897-4a4d-9fd5-28ddd78d9e96"),
        "1HU 1981",
        "Volkswagen",
        "Passat",
        FirstDateRegistration:new DateTime(2015, 12, 1),
        @"https://upload.wikimedia.org/wikipedia/commons/c/c7/06-VW-Passat.jpg",
        5,
        UserSeeds.User1.Id) { Owner = UserSeeds.User1 };

    public static readonly CarEntity Car2 = new(
        Id: Guid.Parse("c4c5432d-f6c1-4c3c-8858-93f1e8a1763c"),
        "CZ5 HOMER",
        "Škoda",
        "Kodiaq",
        new DateTime(2020, 10, 10),
        @"https://upload.wikimedia.org/wikipedia/commons/2/2c/Skoda_Kodiaq_2.0_TDI_4x4_Sportline_%E2%80%93_f_28042021.jpg",
        5,
        UserSeeds.User2.Id) { Owner = UserSeeds.User2 };

    public static readonly CarEntity CarEntityUpdate = Car1 with
    {
        Id = Guid.Parse(input:"cb9157db-d0a0-4847-9686-89e78165ab61"),
        Owner = null,
        PlannedRoutes = Array.Empty<RouteEntity>()
    };

    public static readonly CarEntity CarEntityDelete = Car1 with
    {
        Id = Guid.Parse(input: "b89bf52a-fce5-4247-91bd-e82a79260d99"),
        Owner = null,
        PlannedRoutes = Array.Empty<RouteEntity>()
    };

    static CarSeeds()
    {
        //Car1.PlannedRoutes.Add(RouteSeeds.Route1);
    }

    public static void Seed(this ModelBuilder modelBuilder) =>
        modelBuilder.Entity<CarEntity>().HasData(
            Car1 with { Owner = null, PlannedRoutes = Array.Empty<RouteEntity>() },
            Car2 with { Owner = null, PlannedRoutes = Array.Empty<RouteEntity>() },
            CarEntityUpdate,
            CarEntityDelete);
}
