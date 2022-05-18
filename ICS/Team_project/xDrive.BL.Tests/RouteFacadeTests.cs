using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using xDrive.BL.Models;
using xDrive.Common.Tests;
using xDrive.Common.Tests.Seeds;
using xDrive.BL.Facades;
using Microsoft.EntityFrameworkCore;
using xDrive.DAL.Entities;
using xDrive.DAL.UnitOfWork;
using Xunit;
using Xunit.Abstractions;

namespace xDrive.BL.Tests
{
    public sealed class RouteFacadeTests : CRUDFacadeTestsBase
    {
        private readonly RouteFacade _routeFacadeSUT;

        public RouteFacadeTests(ITestOutputHelper output) : base(output)
        {
            _routeFacadeSUT = new RouteFacade(UnitOfWorkFactory, Mapper);
        }

        [Fact]
        public async Task CreateFirstItem()
        {
            var model = new RouteDetailModel
                (
                    Start: @"TestStart1",
                    Finish: @"TestFinish1",
                    Beginning: DateTime.Today,
                    AssumedTimeToEnd: DateTime.Today,
                    SeatCount: RouteSeeds.Route1.SeatCount,
                    UserId: UserSeeds.User1.Id
                );

            var _ = await _routeFacadeSUT.SaveAsync(model);
        }

        [Fact]
        public async Task GetAll_FromSeeded_DoesNotThrowAndEqualsSeeded()
        {
            var listModel = Mapper.Map<RouteListModel>(RouteSeeds.Route1);

            var returnedModel = await _routeFacadeSUT.GetAsync();

            Assert.Contains(listModel, returnedModel);
        }

        /*[Fact]
        public async Task GetByIdSeededRoute()
        {
            var route = await _routeFacadeSUT.GetAsync(RouteSeeds.Route2.Id);

            DeepAssert.Equal(Mapper.Map<RouteDetailModel>(RouteSeeds.Route2), route);
        }*/

        [Fact]
        public async Task GetAllByStart()
        {
            var listModel = Mapper.Map<RouteListModel>(RouteSeeds.Route2);

            var returnedModel = await _routeFacadeSUT.GetByStart(DateTime.MinValue, UserSeeds.User1.Id, RouteSeeds.Route2.Start);

            Assert.Contains(listModel, returnedModel);
        }

        [Fact]
        public async Task GetAllByStart_isOwner()
        {
            var returnedModel = await _routeFacadeSUT.GetByStart(DateTime.MinValue, UserSeeds.User2.Id, RouteSeeds.Route2.Start);

            Assert.Empty(returnedModel);
        }

        [Fact]
        public async Task? GetAllByStart_NonExistent()
        {
            var routes = await _routeFacadeSUT.GetByStart(DateTime.MaxValue, Guid.Empty, "non-existent place");

            Assert.Empty(routes);
        }

        [Fact]
        public async Task GetAllByFinish()
        {
            var listModel = Mapper.Map<RouteListModel>(RouteSeeds.Route1);

            var returnedModel = await _routeFacadeSUT.GetByFinish(DateTime.MinValue, UserSeeds.User2.Id, RouteSeeds.Route1.Finish);

            Assert.Contains(listModel, returnedModel);
        }

        [Fact]
        public async Task GetAllByFinish_isOwner()
        {
            var returnedModel = await _routeFacadeSUT.GetByFinish(DateTime.MinValue, UserSeeds.User2.Id, RouteSeeds.Route2.Start);

            Assert.Empty(returnedModel);
        }

        [Fact]
        public async Task GetAllByFinish_NonExistent()
        {
            var routes = await _routeFacadeSUT.GetByFinish(DateTime.MaxValue, Guid.Empty, "non-existent place");

            Assert.Empty(routes);
        }

        [Fact]
        public async Task GetAllByBeginig()
        {
            var listModel = Mapper.Map<RouteListModel>(RouteSeeds.Route1);

            var returnedModel = await _routeFacadeSUT.GetByBeginning(RouteSeeds.Route1.Beginning, Guid.Empty);

            Assert.Contains(listModel, returnedModel);
        }

        [Fact]
        public async Task GetAllByBeginning_NonExistent()
        {
            var routes = await _routeFacadeSUT.GetByBeginning(DateTime.MaxValue, Guid.Empty);

            Assert.Empty(routes);
        }

        [Fact]
        public async Task GetByIdNonExistent()
        {
            var Route = await _routeFacadeSUT.GetAsync(RouteSeeds.EmptyEntityRouteEntity.Id);

            Assert.Null(Route);
        }

        [Fact]
        public async Task SeededRouteDeleteById_Deleted()
        {
            await _routeFacadeSUT.DeleteAsync(RouteSeeds.Route1.Id);

            await using var dbxAssert = await DbContextFactory.CreateDbContextAsync();
            Assert.False(await dbxAssert.Routes.AnyAsync(i => i.Id == RouteSeeds.Route1.Id));
        }


        [Fact]
        public async Task NewRouteInsertOrUpdateRouteAdded()
        {
            //Arrange
            var route = new RouteDetailModel
                 (
                     Start: @"TestStart1",
                     Finish: @"TestFinish1",
                     Beginning: DateTime.Today,
                     AssumedTimeToEnd: DateTime.Today,
                     SeatCount: RouteSeeds.Route1.SeatCount,
                     UserId: UserSeeds.User1.Id
                 );

            //Act
            route = await _routeFacadeSUT.SaveAsync(route);

            //Assert
            await using var dbxAssert = await DbContextFactory.CreateDbContextAsync();
            var routeFromDb = await dbxAssert.Routes.SingleAsync(i => i.Id == route.Id);
            DeepAssert.Equal(route, Mapper.Map<RouteDetailModel>(routeFromDb));
        }

        [Fact]
        public async Task SeededRouteInsertOrUpdateRouteUpdated()
        {
            //Arrange
            var route = new RouteDetailModel
                 (
                     Start: RouteSeeds.Route1.Start,
                     Finish: RouteSeeds.Route1.Finish,
                     Beginning: RouteSeeds.Route1.Beginning,
                     AssumedTimeToEnd: RouteSeeds.Route1.AssumedTimeToEnd,
                     SeatCount: RouteSeeds.Route1.SeatCount,
                     UserId: UserSeeds.User2.Id
                 )
            {
                Id = Guid.Parse("96ab3671-1300-4f61-a2b6-4f4ba61fdd96")
            };

            //Act
            await _routeFacadeSUT.SaveAsync(route);

            //Assert
            await using var dbxAssert = await DbContextFactory.CreateDbContextAsync();
            var routeFromDb = await dbxAssert.Routes.SingleAsync(i => i.Id == route.Id);
            DeepAssert.Equal(route, Mapper.Map<RouteDetailModel>(routeFromDb));
        }
    }
}
