using Microsoft.EntityFrameworkCore;
using xDrive.DAL.Entities;

namespace xDrive.Common.Tests.Seeds;

public static class SeatReservationSeeds
{
    public static readonly SeatReservationEntity EmptySeatReservationEntity = new(
        Id: default,
        RouteId: default,
        UserId: default,
        Count: default)
    {
        Passenger = default,
        PlannedRoute = default
    };

    public static readonly SeatReservationEntity PassengerSeat = new(
        Id: Guid.Parse(input: "f6f92945-e893-4c63-ad5f-64123ff7b96b"),
        RouteId: RouteSeeds.Route1.Id,
        UserId: UserSeeds.User1.Id,
        Count: 1)
    {
        Passenger = UserSeeds.User1,
        PlannedRoute = RouteSeeds.Route1
    };

    public static readonly SeatReservationEntity PassengerSeat2 = new(
        Id: Guid.Parse(input: "aaa92945-e893-4c63-ad5f-64123ff7b96b"),
        RouteId: RouteSeeds.Route2.Id,
        UserId: UserSeeds.User2.Id,
        Count: 1)
    {
        Passenger = UserSeeds.User2,
        PlannedRoute = RouteSeeds.Route2
    };

    public static readonly SeatReservationEntity SeatReservationEntityUpdate = PassengerSeat with
    {
        Id = Guid.Parse("4d0d20ec-4839-4dd4-b40f-a330103134c3"), Passenger = null, PlannedRoute = null
    };

    public static readonly SeatReservationEntity SeatReservationEntityDelete = PassengerSeat with
    {
        Id = Guid.Parse("cb102dab-f16e-47c9-a58e-d12d122db7f8"), Passenger = null, PlannedRoute = null
    };

    public static void Seed(this ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<SeatReservationEntity>().HasData(
            PassengerSeat with {Passenger = null, PlannedRoute = null},
            PassengerSeat2 with {Passenger = null, PlannedRoute = null},
            SeatReservationEntityUpdate,
            SeatReservationEntityDelete
        );
    }
}
