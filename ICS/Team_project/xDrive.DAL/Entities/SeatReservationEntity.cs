namespace xDrive.DAL.Entities;

public record SeatReservationEntity(
    Guid Id,
    Guid RouteId,
    Guid? UserId,
    int Count) : IEntity
{
    public UserEntity? Passenger { get; set; }
    public RouteEntity? PlannedRoute { get; set; }

#nullable disable
    public SeatReservationEntity() : this(Guid.Empty, Guid.Empty, Guid.Empty, default) { }
#nullable enable
}
