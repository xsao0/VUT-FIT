using System;
using xDrive.BL.Models;

namespace xDrive.App.Wrappers
{
    public class SeatWrapper : ModelWrapper<SeatReservationDetailModel>
    {
        public SeatWrapper(SeatReservationDetailModel model) : base(model)
        {

        }

        public Guid RouteId
        {
            get => GetValue<Guid>();
            set => SetValue(value);
        }

        public Guid UserId
        {
            get => GetValue<Guid>();
            set => SetValue(value);
        }


        public static implicit operator SeatWrapper(SeatReservationDetailModel detailModel)
            => new(detailModel);

        public static implicit operator SeatReservationDetailModel(SeatWrapper wrapper)
            => wrapper.Model;
    }
}
