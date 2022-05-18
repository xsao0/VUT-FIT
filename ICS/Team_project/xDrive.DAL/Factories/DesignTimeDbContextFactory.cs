using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Design;

namespace xDrive.DAL.Factories;

public class DesignTimeDbContextFactory : IDesignTimeDbContextFactory<xDriveDbContext>
{
    public xDriveDbContext CreateDbContext(string[] args)
    {
        DbContextOptionsBuilder<xDriveDbContext> builder = new();
        builder.UseSqlServer(
            @"Data Source=(LocalDB)\MSSQLLocalDB; Initial Catalog = xDrive; MultipleActiveResultSets = True;
                Integrated Security = True; ");

        return new xDriveDbContext(builder.Options);
    }
}
