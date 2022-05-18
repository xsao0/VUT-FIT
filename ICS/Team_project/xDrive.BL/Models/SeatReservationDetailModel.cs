using AutoMapper;
using xDrive.DAL.Entities;

namespace xDrive.BL.Models
{
    public record SeatReservationDetailModel(
        Guid RouteId,
        Guid? UserId) : ModelBase
    {
        public Guid RouteId { get; set; } = RouteId;
        public Guid? UserId { get; set; } = UserId;

        public class MapperProfile : Profile
        {
            public MapperProfile()
            {
                CreateMap<SeatReservationEntity, SeatReservationDetailModel>()
                    .ReverseMap();
            }
        }

        public static SeatReservationDetailModel Empty => new(Guid.Empty, Guid.Empty);
    }
}
