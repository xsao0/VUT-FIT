namespace xDrive.DAL.Entities;

public record UserEntity(
    Guid Id,
    string FirstName,
    string SecondName,
    string? PictureUrl,
    string? PhoneNumber) : IEntity
{
    public ICollection<CarEntity> OwnedCars { get; init; } = new List<CarEntity>();
    public ICollection<RouteEntity> PlannedRoutesAsDriver { get; init; } = new List<RouteEntity>();
    public ICollection<SeatReservationEntity> Seats { get; init; } = new List<SeatReservationEntity>();
}
