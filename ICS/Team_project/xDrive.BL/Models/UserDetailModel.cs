using AutoMapper;
using xDrive.DAL.Entities;

namespace xDrive.BL.Models
{
    public record UserDetailModel(
        string FirstName,
        string SecondName,
        string PhoneNumber) : ModelBase
    {
        public string FirstName { get; set; } = FirstName;
        public string SecondName { get; set; } = SecondName;
        public string PhoneNumber { get; set; } = PhoneNumber;
        public string? PictureUrl { get; set; }
        public List<CarDetailModel> OwnedCars { get; init; } = new();
        public List<RouteDetailModel> PlannedRoutesAsDriver { get; init; } = new();
        public List<SeatReservationDetailModel> Seats { get; init; } = new();

        public class MapperProfile : Profile
        {
            public MapperProfile()
            {
                CreateMap<UserEntity, UserDetailModel>()
                    .ReverseMap();
            }
        }

        public static UserDetailModel Empty => new(string.Empty, string.Empty, string.Empty);
    }
}
