using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using xDrive.Common.Tests;
using xDrive.Common.Tests.Seeds;
using xDrive.DAL.Entities;
using Xunit;
using Xunit.Abstractions;

namespace xDrive.DAL.Tests;

public class DbContextCarTests : DbContextTestsBase
{
    public DbContextCarTests(ITestOutputHelper output) : base(output)
    {
    }

    [Fact]
    public async Task AddNew_Car_Persisted()
    {
        CarEntity entity = CarSeeds.EmptyCarEntity with
        {
            NumberPlate = "4J2 4365", Manufacturer = "BMW", Model = "Q6", NumberOfSeats = 5, OwnerId = UserSeeds.User1.Id
        };

        xDriveDbContextSUT.Cars.Add(entity);
        await xDriveDbContextSUT.SaveChangesAsync();

        await using xDriveDbContext dbx = await DbContextFactory.CreateDbContextAsync();
        CarEntity? actualEntity = await dbx.Cars.SingleOrDefaultAsync(i => i.Id == entity.Id);
        DeepAssert.Equal(entity, actualEntity);
    }

    [Fact]
    public async Task AddNew_CarWithPlannedRoutes_Persisted()
    {
        CarEntity entity = CarSeeds.EmptyCarEntity with
        {
            NumberPlate = "123 4567",
            Manufacturer = "Tesla",
            Model = "Model S",
            NumberOfSeats = 5,
            OwnerId = UserSeeds.User1.Id,
            PlannedRoutes = new List<RouteEntity>
            {
                RouteSeeds.EmptyEntityRouteEntity with
                {
                    Start = "VUT FIT",
                    Finish = "Kolejni 2, Brno",
                    Beginning = new DateTime(2022, 5, 4, 12, 0, 0),
                    AssumedTimeToEnd = new DateTime(2022, 5, 4, 13, 0, 0),
                    UserId = UserSeeds.User1.Id
                },
                RouteSeeds.EmptyEntityRouteEntity with
                {
                    Start = "Prazsky hrad",
                    Finish = "Petrova 12, As",
                    Beginning = new DateTime(2022, 5, 5, 12, 0, 0),
                    AssumedTimeToEnd = new DateTime(2022, 5, 5, 15, 0, 0),
                    UserId = UserSeeds.User1.Id
                }
            }
        };

        xDriveDbContextSUT.Cars.Add(entity);
        await xDriveDbContextSUT.SaveChangesAsync();

        await using xDriveDbContext dbx = await DbContextFactory.CreateDbContextAsync();
        CarEntity actualEntity = await dbx.Cars
            .Include(i => i.PlannedRoutes)
            .SingleAsync(i => i.Id == entity.Id);
        DeepAssert.Equal(entity, actualEntity);
    }

    [Fact]
    public async Task GetById_Car()
    {
        CarEntity entity = await xDriveDbContextSUT.Cars.SingleAsync(i => i.Id == CarSeeds.Car1.Id);

        DeepAssert.Equal(CarSeeds.Car1 with {PlannedRoutes = Array.Empty<RouteEntity>(), Owner = null}, entity);
    }

    [Fact]
    public async Task Update_Car_Persisted()
    {
        CarEntity baseEntity = CarSeeds.CarEntityUpdate;
        CarEntity entity = baseEntity with
        {
            NumberPlate = baseEntity.NumberPlate + "Update",
            Manufacturer = baseEntity.Manufacturer + "Update",
            Model = baseEntity.Model + "Update",
            FirstDateRegistration = DateTime.Today,
            PictureUrl = baseEntity.PictureUrl + "Update",
            NumberOfSeats = baseEntity.NumberOfSeats + 1
        };

        xDriveDbContextSUT.Cars.Update(entity);
        await xDriveDbContextSUT.SaveChangesAsync();

        await using xDriveDbContext dbx = await DbContextFactory.CreateDbContextAsync();
        CarEntity actualEntity = await dbx.Cars.SingleAsync(i => i.Id == entity.Id);
        DeepAssert.Equal(entity, actualEntity);
    }

    [Fact]
    public async Task Delete_Car_Deleted()
    {
        CarEntity baseEntity = CarSeeds.CarEntityDelete;

        xDriveDbContextSUT.Cars.Remove(baseEntity);
        await xDriveDbContextSUT.SaveChangesAsync();

        Assert.False(await xDriveDbContextSUT.Cars.AnyAsync(i => i.Id == baseEntity.Id));
    }

    [Fact]
    public async Task DeleteById_Car_Deleted()
    {
        CarEntity baseEntity = CarSeeds.CarEntityDelete;

        xDriveDbContextSUT.Remove(xDriveDbContextSUT.Cars.Single(i => i.Id == baseEntity.Id));
        await xDriveDbContextSUT.SaveChangesAsync();

        Assert.False(await xDriveDbContextSUT.Cars.AnyAsync(i => i.Id == baseEntity.Id));
    }
}
