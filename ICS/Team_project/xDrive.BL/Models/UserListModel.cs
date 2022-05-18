using AutoMapper;
using xDrive.DAL.Entities;

namespace xDrive.BL.Models
{
    public record UserListModel(
        string FirstName,
        string SecondName,
        string PhoneNumber) : ModelBase
    {
        public string FirstName { get; set; } = FirstName;
        public string SecondName { get; set; } = SecondName;
        public string PhoneNumber { get; set; } = PhoneNumber;

        public class MapperProfile : Profile
        {
            public MapperProfile()
            {
                CreateMap<UserEntity, UserListModel>();
            }
        }
    }
}
