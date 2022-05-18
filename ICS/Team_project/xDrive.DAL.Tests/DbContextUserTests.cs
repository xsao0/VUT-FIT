using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using xDrive.Common.Tests;
using xDrive.Common.Tests.Seeds;
using xDrive.DAL.Entities;
using Xunit;
using Xunit.Abstractions;

namespace xDrive.DAL.Tests;

public class DbContextUserTests : DbContextTestsBase
{
    public DbContextUserTests(ITestOutputHelper output) : base(output)
    {
    }

    [Fact]
    public async Task AddNew_User_Persisted()
    {
        UserEntity entity = UserSeeds.EmptyUserEntity with
        {
            FirstName = "Radek",
            SecondName = "Šerejch",
            PictureUrl = @"https://cdn.onlinewebfonts.com/svg/img_218090.png",
            PhoneNumber = "777222666"
        };

        xDriveDbContextSUT.Users.Add(entity);
        await xDriveDbContextSUT.SaveChangesAsync();

        await using xDriveDbContext dbx = await DbContextFactory.CreateDbContextAsync();
        UserEntity actualEntities = await dbx.Users.SingleAsync(i => i.Id == entity.Id);

        DeepAssert.Equal(entity, actualEntities);
    }

    [Fact]
    public async Task AddNew_UserWithCar_Persisted()
    {
        UserEntity entity = UserSeeds.EmptyUserEntity with
        {
            FirstName = "David",
            SecondName = "Chocholatý",
            PhoneNumber = "100200300",
            OwnedCars = new List<CarEntity>
            {
                CarSeeds.EmptyCarEntity with {Manufacturer = "Fiat", Model = "Multipla", NumberPlate = "5A63240"}
            }
        };

        xDriveDbContextSUT.Users.Add(entity);
        await xDriveDbContextSUT.SaveChangesAsync();

        await using xDriveDbContext dbx = await DbContextFactory.CreateDbContextAsync();
        UserEntity actualEntity = await dbx.Users
            .Include(i => i.OwnedCars)
            .SingleAsync(i => i.Id == entity.Id);
        DeepAssert.Equal(entity, actualEntity);
    }

    [Fact]
    public async Task GetById_User()
    {
        UserEntity entity = await xDriveDbContextSUT.Users
            .SingleAsync(i => i.Id == UserSeeds.User1.Id);

        DeepAssert.Equal(
            UserSeeds.User1 with
            {
                OwnedCars = Array.Empty<CarEntity>(),
                PlannedRoutesAsDriver = Array.Empty<RouteEntity>(),
                Seats = Array.Empty<SeatReservationEntity>()
            }, entity);
    }

    [Fact]
    public async Task Update_User_Persisted()
    {
        UserEntity baseEntity = UserSeeds.UserEntityUpdate;
        UserEntity entity =
            baseEntity with
            {
                FirstName = baseEntity.FirstName + "Updated",
                SecondName = baseEntity.SecondName + "Updated",
                PictureUrl = baseEntity.PictureUrl,
                PhoneNumber = baseEntity.PhoneNumber + "Updated"
            };

        xDriveDbContextSUT.Users.Update(entity);
        await xDriveDbContextSUT.SaveChangesAsync();

        await using xDriveDbContext dbx = await DbContextFactory.CreateDbContextAsync();
        UserEntity actualEntity = await dbx.Users.SingleAsync(i => i.Id == entity.Id);
        DeepAssert.Equal(entity, actualEntity);
    }

    [Fact]
    public async Task Delete_User_Deleted()
    {
        UserEntity baseEntity = UserSeeds.UserEntityDelete;

        xDriveDbContextSUT.Users.Remove(baseEntity);
        await xDriveDbContextSUT.SaveChangesAsync();

        Assert.False(await xDriveDbContextSUT.Users.AnyAsync(i => i.Id == baseEntity.Id));
    }
}
