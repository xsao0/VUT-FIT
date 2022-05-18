using Microsoft.EntityFrameworkCore;
using xDrive.DAL.Entities;

namespace xDrive.DAL.Seeds;

public static class SeatReservationSeeds
{
    public static readonly SeatReservationEntity PassengerSeat1 = new(
        Id: Guid.Parse("f6f92945-e893-4c63-ad5f-64123ff7b96b"),
        RouteId: RouteSeeds.Route1.Id,
        UserId: UserSeeds.User1.Id,
        Count: 1)
    {
        Passenger = UserSeeds.User1,
        PlannedRoute = RouteSeeds.Route1
    };

    public static readonly SeatReservationEntity PassengerSeat = new(
        Id: Guid.Parse("5369538b-2f91-4057-8bb9-348aada2db0e"),
        RouteId: RouteSeeds.Route1.Id,
        UserId: UserSeeds.User2.Id,
        Count: 1)
    {
        Passenger = UserSeeds.User2,
        PlannedRoute = RouteSeeds.Route1
    };

    public static void Seed(this ModelBuilder modelBuilder) =>
        modelBuilder.Entity<SeatReservationEntity>().HasData(
            PassengerSeat with { Passenger = null, PlannedRoute = null },
            PassengerSeat1 with { Passenger = null, PlannedRoute = null }
        );
}
