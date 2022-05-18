using System;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using xDrive.Common.Tests;
using xDrive.Common.Tests.Factories;
using Xunit;
using Xunit.Abstractions;

namespace xDrive.DAL.Tests;

public class DbContextTestsBase : IAsyncLifetime
{
    public DbContextTestsBase(ITestOutputHelper output)
    {
        XUnitTestOutputConverter converter = new(output);
        Console.SetOut(converter);

        // DbContextFactory = new DbContextTestingInMemoryFactory(GetType().FullName!, seedTestingData: true);
        DbContextFactory = new DbContextLocalDBTestingFactory(GetType().FullName!, true);

        xDriveDbContextSUT = DbContextFactory.CreateDbContext();
    }

    protected IDbContextFactory<xDriveDbContext> DbContextFactory { get; }
    protected xDriveDbContext xDriveDbContextSUT { get; }


    public async Task InitializeAsync()
    {
        await xDriveDbContextSUT.Database.EnsureDeletedAsync();
        await xDriveDbContextSUT.Database.EnsureCreatedAsync();
    }

    public async Task DisposeAsync()
    {
        await xDriveDbContextSUT.Database.EnsureDeletedAsync();
        await xDriveDbContextSUT.DisposeAsync();
    }
}
