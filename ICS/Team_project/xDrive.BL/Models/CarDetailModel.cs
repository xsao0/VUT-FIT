using AutoMapper;
using xDrive.DAL.Entities;

namespace xDrive.BL.Models
{
    public record CarDetailModel(
        string NumberPlate,
        string Manufacturer,
        string Model,
        DateTime FirstDateRegistration,
        int NumberOfSeats,
        Guid OwnerId) : ModelBase
    {
        public string NumberPlate { get; set; } = NumberPlate;
        public string Manufacturer { get; set; } = Manufacturer;
        public string Model { get; set; } = Model;
        public DateTime FirstDateRegistration { get; set; } = FirstDateRegistration;
        public string? PictureUrl { get; set; }
        public int NumberOfSeats { get; set; } = NumberOfSeats;
        public Guid OwnerId { get; set; } = OwnerId;

        public class MapperProfile : Profile
        {
            public MapperProfile()
            {
                CreateMap<CarEntity, CarDetailModel>()
                    .ReverseMap();

            }
        }

        public static CarDetailModel Empty => new(string.Empty, string.Empty, string.Empty, default, default, Guid.Empty);
    }
}
