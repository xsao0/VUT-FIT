using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AutoMapper;
using xDrive.DAL.Entities;

namespace xDrive.BL.Models
{
    public record RouteListModel(
        string Start,
        string Finish,
        int SeatCount,
        DateTime Beginning) : ModelBase
    {
        public string Start { get; set; } = Start;
        public string Finish { get; set; } = Finish;
        public DateTime Beginning { get; set; } = Beginning;

        public class MapperProfile : Profile
        {
            public MapperProfile()
            {
                CreateMap<RouteEntity, RouteListModel>();
            }
        }
    }
}
