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

public class DbContextSeatReservationTests : DbContextTestsBase
{
    public DbContextSeatReservationTests(ITestOutputHelper output) : base(output)
    {
    }

    [Fact]
    public async Task GetAll_SeatRegistration_ForPassenger()
    {
        SeatReservationEntity[] seatRegistration = await xDriveDbContextSUT.SeatReservations
            .Where(i => i.UserId == UserSeeds.User1.Id)
            .ToArrayAsync();

        Assert.Contains(SeatReservationSeeds.PassengerSeat with {Passenger = null, PlannedRoute = null},
            seatRegistration);
    }

    [Fact]
    public async Task AddNew_SeatReservationWithoutPassengerAndPlannedRoute_Persisted()
    {
        SeatReservationEntity entity = SeatReservationSeeds.EmptySeatReservationEntity with { Count = 5, UserId = UserSeeds.User1.Id, RouteId = RouteSeeds.Route1.Id };

        xDriveDbContextSUT.SeatReservations.Add(entity);
        await xDriveDbContextSUT.SaveChangesAsync();

        await using xDriveDbContext dbx = await DbContextFactory.CreateDbContextAsync();
        SeatReservationEntity actualEntities = await dbx.SeatReservations.SingleAsync(i => i.Id == entity.Id);

        DeepAssert.Equal(entity, actualEntities);
    }

    [Fact]
    public async Task GetById_SeatReservation()
    {
        SeatReservationEntity entity =
            await xDriveDbContextSUT.SeatReservations.SingleAsync(i => i.Id == SeatReservationSeeds.PassengerSeat.Id);

        DeepAssert.Equal(SeatReservationSeeds.PassengerSeat with {Passenger = null, PlannedRoute = null}, entity);
    }

    [Fact]
    public async Task Update_SeatRegistration_Persisted()
    {
        SeatReservationEntity baseEntity = SeatReservationSeeds.SeatReservationEntityUpdate;
        SeatReservationEntity entity = baseEntity with {Count = baseEntity.Count + 2};

        xDriveDbContextSUT.SeatReservations.Update(entity);
        await xDriveDbContextSUT.SaveChangesAsync();

        await using xDriveDbContext dbx = await DbContextFactory.CreateDbContextAsync();
        SeatReservationEntity actualEntity = await dbx.SeatReservations.SingleAsync(i => i.Id == entity.Id);
        DeepAssert.Equal(entity, actualEntity);
    }

    [Fact]
    public async Task Delete_SeatRegistration_Deleted()
    {
        SeatReservationEntity baseEntity = SeatReservationSeeds.SeatReservationEntityDelete;

        xDriveDbContextSUT.SeatReservations.Remove(baseEntity);
        await xDriveDbContextSUT.SaveChangesAsync();

        Assert.False(await xDriveDbContextSUT.SeatReservations.AnyAsync(i => i.Id == baseEntity.Id));
    }

    [Fact]
    public async Task DeleteById_SeatReservation_Deleted()
    {
        SeatReservationEntity baseEntity = SeatReservationSeeds.SeatReservationEntityDelete;

        xDriveDbContextSUT.Remove(xDriveDbContextSUT.SeatReservations.Single(i => i.Id == baseEntity.Id));
        await xDriveDbContextSUT.SaveChangesAsync();

        Assert.False(await xDriveDbContextSUT.SeatReservations.AnyAsync(i => i.Id == baseEntity.Id));
    }
}
