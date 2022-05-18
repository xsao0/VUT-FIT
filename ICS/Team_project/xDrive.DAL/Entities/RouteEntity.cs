namespace xDrive.DAL.Entities;

public record RouteEntity(
    Guid Id,
    string Start,
    string Finish,
    DateTime Beginning,
    DateTime AssumedTimeToEnd,
    int SeatCount,
    Guid UserId) : IEntity

{
    public ICollection<SeatReservationEntity> Passengers { get; init; } = new List<SeatReservationEntity>();
    public UserEntity? Driver { get; init; }
    public CarEntity? Car { get; init; }

#nullable disable
    public RouteEntity() : this(Guid.Empty, string.Empty, string.Empty, default, default, default, Guid.Empty) { }
#nullable enable

}
