using xDrive.BL.Models;
using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Runtime.CompilerServices;
using xDrive.App.Extensions;

namespace xDrive.App.Wrappers
{
    public class RouteWrapper : ModelWrapper<RouteDetailModel>
    {
        public RouteWrapper(RouteDetailModel model)
            : base(model)
        {
        }

        public string? Start
        {
            get => GetValue<string>();
            set => SetValue(value);
        }

        public string? Finish
        {
            get => GetValue<string>();
            set => SetValue(value);
        }

        public DateTime Beginning
        {
            get => GetValue<DateTime>();
            set => SetValue(value);
        }

        public DateTime AssumedTimeToEnd
        {
            get => GetValue<DateTime>();
            set => SetValue(value);
        }

        public int SeatCount
        {
            get => GetValue<int>();
            set => SetValue(value);
        }

        private void InitializeCollectionProperties(RouteDetailModel model)
        {
            if (model.Passengers == null)
            {
                throw new ArgumentException("Passengers cannot be null");
            }

            Passengers.AddRange(model.Passengers.Select(e => new SeatWrapper(e)));

            RegisterCollection(Passengers, model.Passengers);

        }

        public ObservableCollection<SeatWrapper> Passengers { get; init; } = new();

        public static implicit operator RouteWrapper(RouteDetailModel detailModel)
            => new(detailModel);

        public static implicit operator RouteDetailModel(RouteWrapper wrapper)
            => wrapper.Model;
    }
}
