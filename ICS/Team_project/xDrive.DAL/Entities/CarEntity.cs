namespace xDrive.DAL.Entities;

public record CarEntity(
    Guid Id,
    string NumberPlate,
    string Manufacturer,
    string Model,
    DateTime FirstDateRegistration,
    string? PictureUrl,
    int NumberOfSeats,
    Guid OwnerId) : IEntity
{
    public ICollection<RouteEntity> PlannedRoutes { get; set; } = new List<RouteEntity>();
    public UserEntity? Owner { get; set; }

#nullable disable
    public CarEntity() : this(Guid.Empty, string.Empty, string.Empty, string.Empty, default, string.Empty, default, Guid.Empty) {}
#nullable enable
}
