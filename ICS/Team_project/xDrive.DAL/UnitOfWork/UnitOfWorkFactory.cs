using Microsoft.EntityFrameworkCore;

namespace xDrive.DAL.UnitOfWork;

public class UnitOfWorkFactory : IUnitOfWorkFactory
{
    private readonly IDbContextFactory<xDriveDbContext> _dbContextFactory;

    public UnitOfWorkFactory(IDbContextFactory<xDriveDbContext> dbContextFactory)
    {
        _dbContextFactory = dbContextFactory;
    }
    public IUnitOfWork Create() => new UnitOfWork(_dbContextFactory.CreateDbContext());
}
