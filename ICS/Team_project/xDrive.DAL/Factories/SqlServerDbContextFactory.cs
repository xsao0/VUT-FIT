using Microsoft.EntityFrameworkCore;

namespace xDrive.DAL.Factories;

public class SqlServerDbContextFactory : IDbContextFactory<xDriveDbContext>
{
    private readonly string _connectionString;
    private readonly bool _seedDemoData;

    public SqlServerDbContextFactory(string connectionString, bool seedDemoData = false)
    {
        _connectionString = connectionString;
        _seedDemoData = seedDemoData;
    }

    public xDriveDbContext CreateDbContext()
    {
        DbContextOptionsBuilder<xDriveDbContext> optionBuilder = new DbContextOptionsBuilder<xDriveDbContext>();
        optionBuilder.UseSqlServer(_connectionString);

        return new xDriveDbContext(optionBuilder.Options, _seedDemoData);
    }
}
