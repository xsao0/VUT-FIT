using Microsoft.EntityFrameworkCore;
using xDrive.DAL.Entities;

namespace xDrive.DAL.Seeds;

public static class UserSeeds
{
    public static readonly UserEntity User1 = new(
        Guid.Parse("08299a5a-b3ef-4502-8244-90cf4325e552"),
        "Josef",
        "Kuba",
        @"https://cdn.onlinewebfonts.com/svg/img_218090.png",
        "777888666");


    public static readonly UserEntity User2 = new(
        Guid.Parse("2ce98afd-036f-4117-a840-ade94b964902"),
        "User2",
        "Baláž",
        @"https://cdn.onlinewebfonts.com/svg/img_218090.png",
        "777222666");

    public static readonly UserEntity User3 = new(
        Guid.Parse("250c2ecc-802f-4e33-ad41-59a6e35191b8"),
        "Vít",
        "Janeček",
        @"https://cdn.onlinewebfonts.com/svg/img_218090.png",
        "777555666");

    static UserSeeds()
    {
        User2.Seats.Add(SeatReservationSeeds.PassengerSeat);
        User1.Seats.Add(SeatReservationSeeds.PassengerSeat1);
        User3.OwnedCars.Add(CarSeeds.Car1);
        User1.OwnedCars.Add(CarSeeds.Car2);
        User3.PlannedRoutesAsDriver.Add(RouteSeeds.Route1);
        User1.PlannedRoutesAsDriver.Add(RouteSeeds.Route2);
    }

    public static void Seed(this ModelBuilder modelBuilder) =>
        modelBuilder.Entity<UserEntity>().HasData(
            User1 with { Seats = Array.Empty<SeatReservationEntity>(), OwnedCars = Array.Empty<CarEntity>(), PlannedRoutesAsDriver = Array.Empty<RouteEntity>() },
            User2 with { Seats = Array.Empty<SeatReservationEntity>(), OwnedCars = Array.Empty<CarEntity>(), PlannedRoutesAsDriver = Array.Empty<RouteEntity>() },
            User3 with { Seats = Array.Empty<SeatReservationEntity>(), OwnedCars = Array.Empty<CarEntity>(), PlannedRoutesAsDriver = Array.Empty<RouteEntity>() }
        );
}
