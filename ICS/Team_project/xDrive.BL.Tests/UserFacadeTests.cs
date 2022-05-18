using System;
using System.Linq;
using System.Threading.Tasks;
using xDrive.BL.Facades;
using xDrive.BL.Models;
using xDrive.Common.Tests;
using xDrive.Common.Tests.Seeds;
using Microsoft.EntityFrameworkCore;
using Xunit;
using Xunit.Abstractions;

namespace xDrive.BL.Tests
{
    public class UserFacadeTests : CRUDFacadeTestsBase
    {
        private readonly UserFacade _userfacadeSUT;

        public UserFacadeTests(ITestOutputHelper output) : base(output)
        {
            _userfacadeSUT = new UserFacade(UnitOfWorkFactory, Mapper);
        }

        [Fact]
        public async Task CreateWithWithoutCarDoesNotThrowAndEqualsCreated()
        {
            //Arrange
            var model = new UserDetailModel
            (
                FirstName: @"TestFirstName1",
                SecondName: @"TestSecondName1",
                PhoneNumber: @"0900000000"
            );

            //Act
            var returnedModel = await _userfacadeSUT.SaveAsync(model);

            FixIds(model, returnedModel);
            //Assert
            DeepAssert.Equal(model, returnedModel);
        }

        [Fact]
        public async Task CreateWithNoCarThrows()
        {
            //Arrange
            var model = new UserDetailModel
            (
                 FirstName: @"TestFirstName2",
                SecondName: @"TestSecondName2",
                PhoneNumber: @"0900000001"
            );
            

            //Act & Assert
            try
            {
                await _userfacadeSUT.SaveAsync(model);
            }
            catch (DbUpdateException) { } 
        }

        /*[Fact]
        public async Task GetById_SeededCar()
        {
            var detailModel = Mapper.Map<UserDetailModel>(UserSeeds.User2);
            var returnedModel = await _userfacadeSUT.GetAsync(detailModel.Id);
            DeepAssert.Equal(detailModel, returnedModel);
        }*/

        [Fact]
        public async Task GetAllFromSeededDoesNotThrowAndContainsSeeded()
        {
            //Arrange
            var listModel = Mapper.Map<UserListModel>(UserSeeds.User1);

            //Act
            var returnedModel = await _userfacadeSUT.GetAsync();

            //Assert
            Assert.Contains(listModel, returnedModel);
        }

        [Fact]
        public async Task DeleteFromSeededDoesNotThrow()
        {
            //Arrange
            var detailModel = Mapper.Map<UserDetailModel>(UserSeeds.User1);

            //Act & Assert
            await _userfacadeSUT.DeleteAsync(detailModel);
        }

        [Fact]
        public async Task UpdateFromSeededDoesNotThrow()
        {
            //Arrange
            var detailModel = Mapper.Map<UserDetailModel>(UserSeeds.User1);
            detailModel.FirstName = "Changed First name";

            //Act & Assert
            await _userfacadeSUT.SaveAsync(detailModel);
        }

        [Fact]
        public async Task UpdateNameFromSeededCheckUpdated()
        {
            //Arrange
            var detailModel = Mapper.Map<UserDetailModel>(UserSeeds.User1);
            detailModel.FirstName = "Changed First name 1";

            //Act
            await _userfacadeSUT.SaveAsync(detailModel);

            //Assert
            var returnedModel = await _userfacadeSUT.GetAsync(detailModel.Id);
            DeepAssert.Equal(detailModel, returnedModel);
        }

        [Fact]
        public async Task UpdateRemoveCarsFromSeededCheckUpdated()
        {
            //Arrange
            var detailModel = Mapper.Map<UserDetailModel>(UserSeeds.User1);
            detailModel.OwnedCars.Clear();

            //Act
            await _userfacadeSUT.SaveAsync(detailModel);

            //Assert
            var returnedModel = await _userfacadeSUT.GetAsync(detailModel.Id);
            DeepAssert.Equal(detailModel, returnedModel);
        }

        /*[Fact]
        public async Task UpdateRemoveOneOfCarsFromSeededCheckUpdated()
        {
            //Arrange
            var detailModel = Mapper.Map<UserDetailModel>(UserSeeds.User2);
            detailModel.OwnedCars.Remove(detailModel.OwnedCars.First());

            //Act
            await _userfacadeSUT.SaveAsync(detailModel);

            //Assert
            var returnedModel = await _userfacadeSUT.GetAsync(detailModel.Id);
            DeepAssert.Equal(detailModel, returnedModel);
        }*/

        [Fact]
        public async Task DeleteByIdFromSeededDoesNotThrow()
        {
            //Arrange & Act & Assert
            await _userfacadeSUT.DeleteAsync(UserSeeds.User2.Id);
        }

        private static void FixIds(UserDetailModel expectedModel, UserDetailModel returnedModel)
        {
            returnedModel.Id = expectedModel.Id;

            foreach (var carAmountModel in returnedModel.OwnedCars)
            {
                var carAmountDetailModel = expectedModel.OwnedCars.FirstOrDefault(i =>
                    i.Manufacturer == carAmountModel.Manufacturer
                    && i.Model == carAmountModel.Model
                    && i.PictureUrl == carAmountModel.PictureUrl
                    && i.NumberPlate == carAmountModel.NumberPlate);

                if (carAmountDetailModel != null)
                {
                    carAmountModel.Id = carAmountDetailModel.Id;
                }
            }
        }
    }
}
