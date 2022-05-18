 using System.Windows.Input;
 using xDrive.App.Commands;
 using xDrive.App.Stores;

 namespace xDrive.App.ViewModels
{
    public class MainViewModel : ViewModelBase
    {
        public MainViewModel(
            IUserListViewModel userListViewModel,
            NavigationStore navigationStore,
            SearchViewModel searchViewModel,
            CreateRouteViewModel createRouteViewModel,
            CreateUserViewModel createUserViewModel,
            MyProfileViewModel myProfileViewModel,
            MyGarageViewModel myGarageViewModel,
            MyTicketsViewModel myTicketsViewModel,
            MySeatReservationViewModel mySeatReservationView)
        {
            UserListViewModel = userListViewModel;
            SearchViewModel = searchViewModel;
            CreateRouteViewModel = createRouteViewModel;
            CreateUserViewModel = createUserViewModel;
            MyProfileViewModel = myProfileViewModel;
            MyGarageViewModel = myGarageViewModel;
            MyTicketsViewModel = myTicketsViewModel;
            MySeatReservationViewModel = mySeatReservationView;

            UpdateViewCommand = new UpdateViewCommand(navigationStore);
        }

        public IUserListViewModel UserListViewModel { get; }

        public ICommand UpdateViewCommand { get; set; }
        public SearchViewModel SearchViewModel { get; }
        public CreateRouteViewModel CreateRouteViewModel { get; }
        public CreateUserViewModel CreateUserViewModel { get; }
        public MyProfileViewModel MyProfileViewModel { get; }
        public MyGarageViewModel MyGarageViewModel { get; }
        public MySeatReservationViewModel MySeatReservationViewModel { get; }
        public MyTicketsViewModel MyTicketsViewModel { get; }
    }
}
