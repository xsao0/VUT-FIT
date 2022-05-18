using System;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using xDrive.Common.Tests;
using xDrive.Common.Tests.Seeds;
using xDrive.DAL.Entities;
using Xunit;
using Xunit.Abstractions;

namespace xDrive.DAL.Tests;

public class DbContextRouteTests : DbContextTestsBase
{
    public DbContextRouteTests(ITestOutputHelper output) : base(output)
    {
    }

    [Fact]
    public async Task AddNew_Route_Persisted()
    {
        RouteEntity entity = RouteSeeds.EmptyEntityRouteEntity with
        {
            Start = "Jihlava",
            Finish = "Brno",
            Beginning = DateTime.Now,
            AssumedTimeToEnd = DateTime.Now.AddMinutes(90),
            UserId = UserSeeds.User2.Id
        };

        xDriveDbContextSUT.Routes.Add(entity);
        await xDriveDbContextSUT.SaveChangesAsync();

        await using xDriveDbContext dbx = await DbContextFactory.CreateDbContextAsync();
        RouteEntity? actualEntity = await dbx.Routes.SingleOrDefaultAsync(i => i.Id == entity.Id);
        DeepAssert.Equal(entity, actualEntity);
    }

    [Fact]
    public async Task DeleteById_Route_Deleted()
    {
        RouteEntity baseEntity = RouteSeeds.RouteEntityDelete;

        xDriveDbContextSUT.Remove(xDriveDbContextSUT.Routes.Single(i => i.Id == baseEntity.Id));
        await xDriveDbContextSUT.SaveChangesAsync();

        Assert.False(await xDriveDbContextSUT.Routes.AnyAsync(i => i.Id == baseEntity.Id));
    }

    [Fact]
    public async Task Delete_Route_Deleted()
    {
        RouteEntity baseEntity = RouteSeeds.RouteEntityDelete;

        xDriveDbContextSUT.Routes.Remove(baseEntity);
        await xDriveDbContextSUT.SaveChangesAsync();

        Assert.False(await xDriveDbContextSUT.Routes.AnyAsync(i => i.Id == baseEntity.Id));
    }

    [Fact]
    public async Task GetById_Route()
    {
        RouteEntity entity = await xDriveDbContextSUT.Routes.SingleAsync(i => i.Id == RouteSeeds.Route1.Id);

        DeepAssert.Equal(
            RouteSeeds.Route1 with {Passengers = Array.Empty<SeatReservationEntity>(), Driver = null, Car = null},
            entity);
    }

    [Fact]
    public async Task Update_Route_Persisted()
    {
        RouteEntity baseEntity = RouteSeeds.RouteEntityUpdate;
        RouteEntity entity = baseEntity with
        {
            Finish = "Ostrava", AssumedTimeToEnd = baseEntity.Beginning.AddMinutes(120)
        };

        xDriveDbContextSUT.Routes.Update(entity);
        await xDriveDbContextSUT.SaveChangesAsync();

        await using xDriveDbContext dbx = await DbContextFactory.CreateDbContextAsync();
        RouteEntity actualEntity = await dbx.Routes.SingleAsync(i => i.Id == entity.Id);
        DeepAssert.Equal(entity, actualEntity);
    }
}
