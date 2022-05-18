using xDrive.App.Services;
using xDrive.App.Services.MessageDialog;
using xDrive.App.ViewModels;
using xDrive.App.Views;
using xDrive.DAL;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using System;
using System.Windows;
using xDrive.App.Settings;
using xDrive.BL;
using xDrive.DAL.Factories;
using Microsoft.Extensions.Options;
using xDrive.App.Extensions;
using xDrive.App.Stores;

namespace xDrive.App
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        private readonly IHost _host;

        public App()
        {
            _host = Host.CreateDefaultBuilder()
                .ConfigureAppConfiguration(ConfigureAppConfiguration)
                .ConfigureServices((context, services) => { ConfigureServices(context.Configuration, services); })
                .Build();
        }

        private static void ConfigureAppConfiguration(HostBuilderContext context, IConfigurationBuilder builder)
        {
            builder.AddJsonFile(@"AppSettings.json", false, false);
        }

        private static void ConfigureServices(IConfiguration configuration,
            IServiceCollection services)
        {
            services.AddBLServices();

            services.Configure<DALSettings>(configuration.GetSection("xDrive:DAL"));

            services.AddSingleton<IDbContextFactory<xDriveDbContext>>(provider =>
            {
                var dalSettings = provider.GetRequiredService<IOptions<DALSettings>>().Value;
                return new SqlServerDbContextFactory(dalSettings.ConnectionString!, dalSettings.SkipMigrationAndSeedDemoData);
            });

            services.AddSingleton<MainWindow>();

            services.AddSingleton<IMessageDialogService, MessageDialogService>();
            services.AddSingleton<IMediator, Mediator>();
            services.AddSingleton<NavigationStore>();
            services.AddSingleton<AccountStore>();

            services.AddSingleton<MainViewModel>();
            services.AddSingleton<SearchViewModel>();
            services.AddSingleton<CreateUserViewModel>();
            services.AddSingleton<MyProfileViewModel>();
            services.AddSingleton<MyGarageViewModel>();
            services.AddSingleton<UserDetailViewModel>();
            services.AddSingleton<CreateRouteViewModel>();
            services.AddSingleton<MyTicketsViewModel>();
            services.AddSingleton<MySeatReservationViewModel>();

            services.AddSingleton<IUserListViewModel, UserListViewModel>();
            services.AddSingleton<IRouteListViewModel, RouteListViewModel>();
            services.AddSingleton<ICarListViewModel, CarListViewModel>();

            services.AddFactory<ICarDetailViewModel, CarDetailViewModel>();
            services.AddFactory<IUserDetailViewModel, UserDetailViewModel>();
            services.AddFactory<IRouteDetailViewModel, RouteDetailViewModel>();
        }

        protected override async void OnStartup(StartupEventArgs e)
        {
            await _host.StartAsync();

            var dbContextFactory = _host.Services.GetRequiredService<IDbContextFactory<xDriveDbContext>>();

            var dalSettings = _host.Services.GetRequiredService<IOptions<DALSettings>>().Value;

            await using (var dbx = await dbContextFactory.CreateDbContextAsync())
            {
                if (dalSettings.SkipMigrationAndSeedDemoData)
                {
                    await dbx.Database.EnsureDeletedAsync();
                    await dbx.Database.EnsureCreatedAsync();
                }
                else
                {
                    await dbx.Database.MigrateAsync();
                }
            }

            var mainWindow = _host.Services.GetRequiredService<MainWindow>();
            mainWindow.Show();

            base.OnStartup(e);
        }

        protected override async void OnExit(ExitEventArgs e)
        {
            using (_host)
            {
                await _host.StopAsync(TimeSpan.FromSeconds(5));
            }

            base.OnExit(e);
        }
    }
}
