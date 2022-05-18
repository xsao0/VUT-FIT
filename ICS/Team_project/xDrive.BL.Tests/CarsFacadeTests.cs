using System;
using System.Linq;
using System.Threading.Tasks;
using xDrive.BL.Models;
using xDrive.Common.Tests;
using xDrive.Common.Tests.Seeds;
using xDrive.BL.Facades;
using Microsoft.EntityFrameworkCore;
using Xunit;
using Xunit.Abstractions;

namespace xDrive.BL.Tests
{
    public sealed class CarFacadeTests : CRUDFacadeTestsBase
    {
        private readonly CarFacade _carFacadeSUT;

        public CarFacadeTests(ITestOutputHelper output) : base(output)
        {
            _carFacadeSUT = new CarFacade(UnitOfWorkFactory, Mapper);
        }

        [Fact]
        public async Task CreateFirstItem()
        {
            var model = new CarDetailModel
            (
                NumberPlate: @"TestPlate1",
                Manufacturer: @"TestManufacturer1",
                Model: @"TestModel1",
                FirstDateRegistration: DateTime.Today,
                NumberOfSeats: 4,
                OwnerId: UserSeeds.User1.Id
            );

            var _ = await _carFacadeSUT.SaveAsync(model);
        }

        [Fact]
        public async Task GetAllSingleSeededCar()
        {
            var cars = await _carFacadeSUT.GetAsync();
            var car = cars.Single(i => i.Id == CarSeeds.Car1.Id);
            DeepAssert.Equal(Mapper.Map<CarListModel>(CarSeeds.Car1), car);
        }

        [Fact]
        public async Task GetByIdSeededCar()
        {
            var detailModel = Mapper.Map<CarDetailModel>(CarSeeds.Car1);
            var returnedModel = await _carFacadeSUT.GetAsync(detailModel.Id);
            DeepAssert.Equal(detailModel, returnedModel);
        }

        [Fact]
        public async Task GetByIdNonExistent()
        {
            var car = await _carFacadeSUT.GetAsync(CarSeeds.EmptyCarEntity.Id);

            Assert.Null(car);
        }

        [Fact]
        public async Task SeededCarDeleteById_Deleted()
        {
            await _carFacadeSUT.DeleteAsync(CarSeeds.Car1.Id);

            await using var dbxAssert = await DbContextFactory.CreateDbContextAsync();
            Assert.False(await dbxAssert.Cars.AnyAsync(i => i.Id == CarSeeds.Car1.Id));
        }


        [Fact]
        public async Task NewCarInsertOrUpdateCarAdded()
        {
            //Arrange
            var car = new CarDetailModel(
                NumberPlate: @"CZ1 PLATE",
                Manufacturer: @"Ford",
                Model: @"Mustang",
                FirstDateRegistration: DateTime.Today,
                NumberOfSeats: 4,
                OwnerId: UserSeeds.User1.Id);

        //Act
            car = await _carFacadeSUT.SaveAsync(car);

            //Assert
            await using var dbxAssert = await DbContextFactory.CreateDbContextAsync();
            var carFromDb = await dbxAssert.Cars.SingleAsync(i => i.Id == car.Id);
            DeepAssert.Equal(car, Mapper.Map<CarDetailModel>(carFromDb));
        }

        [Fact]
        public async Task SeededCarInsertOrUpdateCarUpdated()
        {
            //Arrange
            var car = new CarDetailModel
            (
                NumberPlate: CarSeeds.Car1.NumberPlate,
                Manufacturer: CarSeeds.Car1.Manufacturer,
                Model: CarSeeds.Car1.Model,
                FirstDateRegistration: CarSeeds.Car1.FirstDateRegistration,
                NumberOfSeats: CarSeeds.Car1.NumberOfSeats,
                OwnerId: UserSeeds.User1.Id
            )
            {
                Id = CarSeeds.Car1.Id
            };
            car.NumberPlate += "updated";
            car.Manufacturer += "updated";
            car.Model += "updated";
            car.PictureUrl += "updated";

            //Act
            await _carFacadeSUT.SaveAsync(car);

            //Assert
            await using var dbxAssert = await DbContextFactory.CreateDbContextAsync();
            var carFromDb = await dbxAssert.Cars.SingleAsync(i => i.Id == car.Id);
            DeepAssert.Equal(car, Mapper.Map<CarDetailModel>(carFromDb));
        }
    }
}
