using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AutoMapper;
using xDrive.DAL;
using xDrive.DAL.Entities;
using xDrive.DAL.UnitOfWork;
using xDrive.BL.Models;

namespace xDrive.BL.Facades
{
    public class RouteFacade : CRUDRouteFacade<RouteEntity, RouteListModel, RouteDetailModel>
    {
        public RouteFacade(IUnitOfWorkFactory unitOfWorkFactory, IMapper mapper) : base(unitOfWorkFactory, mapper)
        {

        }
    }
}
