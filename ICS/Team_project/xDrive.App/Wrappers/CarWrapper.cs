using xDrive.BL.Models;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel.DataAnnotations;

namespace xDrive.App.Wrappers
{
    public class CarWrapper : ModelWrapper<CarDetailModel>
    {
        public CarWrapper(CarDetailModel model)
            : base(model)
        {
        }

        public string? NumberPlate
        {
            get => GetValue<string>();
            set => SetValue(value);
        }
        public string? Manufacturer
        {
            get => GetValue<string>();
            set => SetValue(value);
        }
        public string? ModelName
        {
            get => GetValue<string>();
            set => SetValue(value);
        }

        public DateTime FirstDateRegistration
        {
            get => GetValue<DateTime>();
            set => SetValue(value);
        }

        public string? PictureUrl
        {
            get => GetValue<string>();
            set => SetValue(value);
        }

        public int NumberOfSeats
        {
            get => GetValue<int>();
            set => SetValue(value);
        }

        public static implicit operator CarWrapper(CarDetailModel detailModel)
            => new(detailModel);

        public static implicit operator CarDetailModel(CarWrapper wrapper)
            => wrapper.Model;
    }
}
