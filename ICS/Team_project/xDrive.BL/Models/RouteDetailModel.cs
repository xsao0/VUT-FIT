using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using AutoMapper;
using xDrive.DAL.Entities;

namespace xDrive.BL.Models
{
    public record RouteDetailModel(
        string Start,
        string Finish,
        DateTime Beginning,
        DateTime AssumedTimeToEnd,
        int SeatCount,
        Guid UserId) : ModelBase
    {
        public Guid UserId { get; set; } = UserId;
        public string Start { get; set; } = Start;
        public string Finish { get; set; } = Finish;
        public DateTime Beginning { get; set; } = Beginning;
        public DateTime AssumedTimeToEnd { get; set; } = AssumedTimeToEnd;
        public int SeatCount { get; set; } = SeatCount;
        public List<SeatReservationDetailModel> Passengers { get; init; } = new();

        public class MapperProfile : Profile
        {
            public MapperProfile()
            {
                CreateMap<RouteDetailModel, RouteEntity>()
                    .ForMember(entity => entity.Car, expression => expression.Ignore())
                    .ForMember(entity => entity.Driver, expression => expression.Ignore())
                    .ReverseMap();
            }
        }

        public static RouteDetailModel Empty => new(string.Empty, string.Empty, default, default, default, Guid.Empty);
    }
}
