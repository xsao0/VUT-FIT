using AutoMapper;
using xDrive.DAL.Entities;

namespace xDrive.BL.Models
{
    public record OwnedCarsDetailModel(
        Guid CarId,
        string NumberPlate,
        string Manufacturer,
        string Model,
        DateTime FirstDateRegistration,
        int NumberOfSeats) : ModelBase
    {
        public Guid CarId { get; set; } = CarId;
        public string NumberPlate { get; set; } = NumberPlate;
        public string Manufacturer { get; set; } = Manufacturer;
        public string Model { get; set; } = Model;
        public DateTime FirstDateRegistration { get; set; } = FirstDateRegistration;
        public string? PictureUrl { get; set; }
        public int NumberOfSeats { get; set; } = NumberOfSeats;

        public class MapperProfile : Profile
        {
            public MapperProfile()
            {
                CreateMap<CarEntity, OwnedCarsDetailModel>()
                    .ForMember(e => e.CarId, opt => opt.Ignore())
                    .ReverseMap();
            }
        }

#nullable disable
        public OwnedCarsDetailModel() : this(default, string.Empty, string.Empty, string.Empty, default, default) { }
#nullable enable
    }
}
