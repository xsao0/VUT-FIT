using Microsoft.EntityFrameworkCore;
using xDrive.DAL.Entities;
using xDrive.DAL.Seeds;

namespace xDrive.DAL;

public class xDriveDbContext : DbContext
{
    private readonly bool _seedDemoData;

    public xDriveDbContext(DbContextOptions contextOptions, bool seedDemoData = false)
        : base(contextOptions)
    {
        _seedDemoData = seedDemoData;
    }

    public DbSet<CarEntity> Cars => Set<CarEntity>();
    public DbSet<RouteEntity> Routes => Set<RouteEntity>();
    public DbSet<UserEntity> Users => Set<UserEntity>();
    public DbSet<SeatReservationEntity> SeatReservations => Set<SeatReservationEntity>();

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        base.OnModelCreating(modelBuilder);


        modelBuilder.Entity<UserEntity>()
            .HasMany(i => i.OwnedCars).WithOne(i => i.Owner).HasForeignKey(k => k.OwnerId);

        modelBuilder.Entity<UserEntity>()
            .HasMany(i => i.PlannedRoutesAsDriver).WithOne(i => i.Driver).HasForeignKey(k => k.UserId);

        modelBuilder.Entity<UserEntity>()
            .HasMany(i => i.Seats).WithOne(i => i.Passenger).HasForeignKey(k => k.UserId).OnDelete(DeleteBehavior.NoAction);

        modelBuilder.Entity<RouteEntity>()
            .HasMany(e => e.Passengers).WithOne(i => i.PlannedRoute).HasForeignKey(k => k.RouteId);

        if (_seedDemoData)
        {
            UserSeeds.Seed(modelBuilder);
            CarSeeds.Seed(modelBuilder);
            RouteSeeds.Seed(modelBuilder);
            SeatReservationSeeds.Seed(modelBuilder);
        }
    }
}
