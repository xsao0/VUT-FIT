using Microsoft.EntityFrameworkCore;
using xDrive.DAL.Entities;

namespace xDrive.DAL.Seeds;

public static class RouteSeeds
{
    public static readonly RouteEntity Route1 = new(
        Guid.Parse("fabde0cd-eefe-443f-baf6-3d96cc2cbf2e"),
        "Brno",
        "Praha",
        new DateTime(2022, 4, 1, 14, 0, 0),
        new DateTime(2022, 4, 1, 16, 0, 0),
        3,
        UserSeeds.User3.Id);

    public static readonly RouteEntity Route2 = new(
        Guid.Parse("aabde0cd-eefe-443f-baf6-3d96cc2cbf2a"),
        "Brno",
        "Jihlava",
        new DateTime(2022, 4, 1, 14, 0, 0),
        new DateTime(2022, 4, 1, 16, 0, 0),
        4,
        UserSeeds.User1.Id);

    static RouteSeeds()
    {
        Route1.Passengers.Add(SeatReservationSeeds.PassengerSeat1);
        Route1.Passengers.Add(SeatReservationSeeds.PassengerSeat);
    }

    public static void Seed(this ModelBuilder modelBuilder) =>
        modelBuilder.Entity<RouteEntity>().HasData(
            Route1 with { Passengers = Array.Empty<SeatReservationEntity>(), Driver = null, Car = null },
            Route2 with { Passengers = Array.Empty<SeatReservationEntity>(), Driver = null, Car = null }
        );
}
