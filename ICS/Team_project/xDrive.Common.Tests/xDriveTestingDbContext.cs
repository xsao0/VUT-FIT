using Microsoft.EntityFrameworkCore;
using xDrive.Common.Tests.Seeds;
using xDrive.DAL;
using xDrive.DAL.Entities;

namespace xDrive.Common.Tests;

public class xDriveTestingDbContext : xDriveDbContext
{
    private readonly bool _seedTestingData;

    public xDriveTestingDbContext(DbContextOptions contextOptions, bool seedTestingData = false) :
        base(contextOptions, seedDemoData: false)
    {
        _seedTestingData = seedTestingData;
    }

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        base.OnModelCreating(modelBuilder);

        if (_seedTestingData)
        {
            UserSeeds.Seed(modelBuilder);
            CarSeeds.Seed(modelBuilder);
            RouteSeeds.Seed(modelBuilder);
            SeatReservationSeeds.Seed(modelBuilder);
        }
    }
}
