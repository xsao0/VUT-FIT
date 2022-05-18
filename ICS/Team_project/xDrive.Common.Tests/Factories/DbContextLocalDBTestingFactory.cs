using Microsoft.EntityFrameworkCore;
using xDrive.DAL;

namespace xDrive.Common.Tests.Factories;

public class DbContextLocalDBTestingFactory : IDbContextFactory<xDriveDbContext>
{
    private readonly string _databaseName;
    private readonly bool _seedTestingData;

    public DbContextLocalDBTestingFactory(string databaseName, bool seedTestingData = false)
    {
        _databaseName = databaseName;
        _seedTestingData = seedTestingData;
    }

    public xDriveDbContext CreateDbContext()
    {
        DbContextOptionsBuilder<xDriveDbContext> builder = new();
        builder.UseSqlServer(
            $"Data Source=(LocalDB)\\MSSQLLocalDB;Initial Catalog = {_databaseName};MultipleActiveResultSets = True;Integrated Security = True; ");

        // builder.LogTo(System.Console.WriteLine); //Enable in case you want to see tests details, enabled may cause some inconsistencies in tests
        // builder.EnableSensitiveDataLogging();

        return new xDriveTestingDbContext(builder.Options, _seedTestingData);
    }
}
