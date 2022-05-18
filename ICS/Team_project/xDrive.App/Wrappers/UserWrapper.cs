using xDrive.BL.Models;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Runtime.CompilerServices;
using xDrive.App.Extensions;

namespace xDrive.App.Wrappers
{
    public class UserWrapper : ModelWrapper<UserDetailModel>
    {
        public UserWrapper(UserDetailModel model)
            : base(model)
        {
            InitializeCollectionProperties(model);
        }

        public string? FirstName
        {
            get => GetValue<string>();
            set => SetValue(value);
        }
        public string? SecondName
        {
            get => GetValue<string>();
            set => SetValue(value);
        }
        public string? PhoneNumber
        {
            get => GetValue<string>();
            set => SetValue(value);
        }
        public string? PictureUrl
        {
            get => GetValue<string>();
            set => SetValue(value);
        }

        private void InitializeCollectionProperties(UserDetailModel model)
        {
            if (model.OwnedCars == null)
            {
                throw new ArgumentException("OwnedCars cannot be null");
            }
            if (model.PlannedRoutesAsDriver == null)
            {
                throw new ArgumentException("PlannedRouteAsDriver cannot be null");
            }
            if (model.Seats == null)
            {
                throw new ArgumentException("Seats cannot be null");
            }
            OwnedCars.AddRange(model.OwnedCars.Select(e => new CarWrapper(e)));

            RegisterCollection(OwnedCars, model.OwnedCars);

            PlannedRoutesAsDriver.AddRange(model.PlannedRoutesAsDriver.Select(e => new RouteWrapper(e)));

            RegisterCollection(PlannedRoutesAsDriver, model.PlannedRoutesAsDriver);

            Seats.AddRange(model.Seats.Select(e => new SeatWrapper(e)));

            RegisterCollection(Seats, model.Seats);
        }

        public ObservableCollection<CarWrapper> OwnedCars { get; init; } = new();

        public ObservableCollection<RouteWrapper> PlannedRoutesAsDriver { get; init; } = new();

        public ObservableCollection<SeatWrapper> Seats { get; init; } = new();

        public override IEnumerable<ValidationResult> Validate(ValidationContext validationContext)
        {
            if (string.IsNullOrWhiteSpace(FirstName))
            {
                yield return new ValidationResult($"{nameof(FirstName)} is required", new[] { nameof(FirstName) });
            }

            if (string.IsNullOrWhiteSpace(SecondName))
            {
                yield return new ValidationResult($"{nameof(SecondName)} is required", new[] { nameof(SecondName) });
            }
            if (string.IsNullOrWhiteSpace(PhoneNumber))
            {
                yield return new ValidationResult($"{nameof(PhoneNumber)} is required", new[] { nameof(PhoneNumber) });
            }
        }

        public static implicit operator UserWrapper(UserDetailModel detailModel)
            => new(detailModel);

        public static implicit operator UserDetailModel(UserWrapper wrapper)
            => wrapper.Model;
    }
}
