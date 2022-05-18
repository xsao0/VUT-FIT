using Microsoft.EntityFrameworkCore;
using xDrive.DAL.Entities;

namespace xDrive.Common.Tests.Seeds;

public static class UserSeeds
{
    public static readonly UserEntity EmptyUserEntity = new(
        Id: default,
        FirstName: default!,
        SecondName: default!,
        PictureUrl: default,
        PhoneNumber: default);

    public static readonly UserEntity User1 = new(
        Id: Guid.Parse(input: "08299a5a-b3ef-4502-8244-90cf4325e552"),
        FirstName: "Josef",
        SecondName: "Kuba",
        PictureUrl: @"https://cdn.onlinewebfonts.com/svg/img_218090.png",
        PhoneNumber: "777888666");

    public static readonly UserEntity User2 = new(
        Id: Guid.Parse(input: "2ce98afd-036f-4117-a840-ade94b964902"),
        FirstName: "User2",
        SecondName: "Baláž",
        PictureUrl: @"https://cdn.onlinewebfonts.com/svg/img_218090.png",
        PhoneNumber: "777222666");

    public static readonly UserEntity UserEntityDelete = User1 with { Id = Guid.Parse("f8d04b22-ef41-4f4e-b38d-a8e144d03800"), OwnedCars = Array.Empty<CarEntity>(), PlannedRoutesAsDriver = Array.Empty<RouteEntity>(), Seats = Array.Empty<SeatReservationEntity>()};
    public static readonly UserEntity UserEntityUpdate = User1 with { Id = Guid.Parse("197ba00b-fb85-4a3a-9e21-42dbafecb855"), OwnedCars = Array.Empty<CarEntity>(), PlannedRoutesAsDriver = Array.Empty<RouteEntity>(), Seats = Array.Empty<SeatReservationEntity>()};

    static UserSeeds()
    {
        User2.Seats.Add(SeatReservationSeeds.PassengerSeat2);
        User2.OwnedCars.Add(CarSeeds.Car2);
        User2.PlannedRoutesAsDriver.Add(RouteSeeds.Route2);
    }

    public static void Seed(this ModelBuilder modelBuilder) =>
        modelBuilder.Entity<UserEntity>().HasData(
            User1 with { OwnedCars = Array.Empty<CarEntity>(), PlannedRoutesAsDriver = Array.Empty<RouteEntity>(), Seats = Array.Empty<SeatReservationEntity>() },
            User2 with { OwnedCars = Array.Empty<CarEntity>(), PlannedRoutesAsDriver = Array.Empty<RouteEntity>(), Seats = Array.Empty<SeatReservationEntity>() },
            UserEntityUpdate,
            UserEntityDelete
        );
}
