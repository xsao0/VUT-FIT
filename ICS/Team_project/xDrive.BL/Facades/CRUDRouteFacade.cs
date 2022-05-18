using AutoMapper;
using xDrive.DAL.Entities;
using xDrive.DAL.UnitOfWork;
using Microsoft.EntityFrameworkCore;

namespace xDrive.BL.Facades;

public class CRUDRouteFacade<TEntity, TListModel, TDetailModel> : CRUDFacade<TEntity, TListModel, TDetailModel>
    where TEntity : RouteEntity
    where TListModel : Models.IModel
    where TDetailModel : class, Models.IModel
{
    private readonly IMapper _mapper;
    private readonly IUnitOfWorkFactory _unitOfWorkFactory;

    protected CRUDRouteFacade(IUnitOfWorkFactory unitOfWorkFactory, IMapper mapper) : base(unitOfWorkFactory, mapper)
    {
        _unitOfWorkFactory = unitOfWorkFactory;
        _mapper = mapper;
    }

    public Task<IEnumerable<TListModel>> GetRoute(string start, string finish, DateTime dateTime, Guid id)
    {
        if (start is "" && finish is "")
        {
            return GetByBeginning(dateTime, id);
        }

        if (start is not "" && finish is "")
        {
            return GetByStart(dateTime, id, start);
        }

        if (start is "" && finish is not "")
        {
            return GetByFinish(dateTime, id, finish);
        }

        return GetByAll(dateTime, id, start, finish);
    }

    public async Task<IEnumerable<TListModel>> GetByBeginning(DateTime dateTime, Guid id)
    {
        await using var uow = _unitOfWorkFactory.Create();
        var query = uow.GetRepository<TEntity>().Get().Where(e => e.Beginning >= dateTime).Where(e => e.Driver!.Id != id);

        return await _mapper.ProjectTo<TListModel>(query).ToArrayAsync().ConfigureAwait(false);
    }

    public async Task<IEnumerable<TListModel>> GetByStart(DateTime dateTime, Guid id, string start)
    {
        await using var uow = _unitOfWorkFactory.Create();
        var query = uow.GetRepository<TEntity>().Get().Where(e => e.Beginning >= dateTime).Where(e => e.Driver!.Id != id).Where(e => e.Start == start);

        return await _mapper.ProjectTo<TListModel>(query).ToArrayAsync().ConfigureAwait(false);
    }

    public async Task<IEnumerable<TListModel>> GetByFinish(DateTime dateTime, Guid id, string finish)
    {
        await using var uow = _unitOfWorkFactory.Create();
        var query = uow.GetRepository<TEntity>().Get().Where(e => e.Beginning >= dateTime).Where(e => e.Driver!.Id != id).Where(e => e.Finish == finish);

        return await _mapper.ProjectTo<TListModel>(query).ToArrayAsync().ConfigureAwait(false);
    }

    public async Task<IEnumerable<TListModel>> GetByAll(DateTime dateTime, Guid id, string start, string finish)
    {
        await using var uow = _unitOfWorkFactory.Create();
        var query = uow.GetRepository<TEntity>().Get().Where(e => e.Beginning >= dateTime).Where(e => e.Driver!.Id != id).Where(e => e.Start == start).Where(e => e.Finish == finish);

        return await _mapper.ProjectTo<TListModel>(query).ToArrayAsync().ConfigureAwait(false);
    }
}

