using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AutoMapper;
using xDrive.DAL.Entities;

namespace xDrive.BL.Models
{
    public record CarListModel(string NumberPlate, int NumberOfSeats) : ModelBase
    {
        public string NumberPlate { get; set; } = NumberPlate;
        public int NumberOfSeats { get; set; } = NumberOfSeats;
        public string? PictureUrl { get; set; }

        public class MapperProfile : Profile
        {
            public MapperProfile()
            {
                CreateMap<CarEntity, CarListModel>()
                    .ReverseMap();
            }
        }
    }
}
