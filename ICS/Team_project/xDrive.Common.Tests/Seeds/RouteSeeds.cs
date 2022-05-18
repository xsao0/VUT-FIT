using Microsoft.EntityFrameworkCore;
using xDrive.DAL.Entities;

namespace xDrive.Common.Tests.Seeds;

public static class RouteSeeds
{
    public static readonly RouteEntity EmptyEntityRouteEntity = new(
        default,
        default,
        default,
        default,
        default,
        default,
        default
    ) {Driver = default, Car = default};

    public static readonly RouteEntity Route1 = new(
        Guid.Parse("fabde0cd-eefe-443f-baf6-3d96cc2cbf2e"),
        "Brno",
        "Praha",
        new DateTime(2022, 4, 1, 14, 0, 0),
        new DateTime(2022, 4, 1, 16, 0, 0),
        5,
        UserSeeds.User1.Id) {Driver = UserSeeds.User1, Car = CarSeeds.Car1};

    public static readonly RouteEntity Route2 = new(
        Guid.Parse("fabde0cd-eefe-443f-baf6-3d96cc2cbf2f"),
        "Jihlava",
        "Praha",
        new DateTime(2022, 4, 1, 14, 0, 0),
        new DateTime(2022, 4, 1, 16, 0, 0),
        5,
        UserSeeds.User2.Id) {Driver = UserSeeds.User2, Car = CarSeeds.Car2};

    public static readonly RouteEntity RouteEntityDelete = Route1 with
    {
        Id = Guid.Parse("450a2fcc-61ca-441c-b11a-c51b36d350b8"),
        Passengers = Array.Empty<SeatReservationEntity>(),
        Driver = null,
        Car = null
    };

    public static readonly RouteEntity RouteEntityUpdate = Route1 with
    {
        Id = Guid.Parse("96ab3671-1300-4f61-a2b6-4f4ba61fdd96"),
        Passengers = Array.Empty<SeatReservationEntity>(),
        Driver = null,
        Car = null
    };

    static RouteSeeds()
    {
        Route1.Passengers.Add(SeatReservationSeeds.PassengerSeat);
        Route2.Passengers.Add(SeatReservationSeeds.PassengerSeat2);
    }

    public static void Seed(this ModelBuilder modelBuilder) =>
        modelBuilder.Entity<RouteEntity>().HasData(
            Route1 with { Passengers = Array.Empty<SeatReservationEntity>(), Driver = null, Car = null },
            Route2 with { Passengers = Array.Empty<SeatReservationEntity>(), Driver = null, Car = null },
            RouteEntityDelete, RouteEntityUpdate);
}
