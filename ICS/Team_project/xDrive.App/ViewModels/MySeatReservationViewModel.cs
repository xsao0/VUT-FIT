using System;
using System.Collections.ObjectModel;
using System.Linq;
using xDrive.App.Extensions;
using System.Threading.Tasks;
using System.Windows.Input;
using xDrive.App.Stores;
using xDrive.App.Messages;
using xDrive.App.Factories;
using xDrive.App.Services;
using xDrive.App.Wrappers;
using xDrive.BL.Facades;
using xDrive.BL.Models;


namespace xDrive.App.ViewModels
{
    public class MySeatReservationViewModel : ViewModelBase
    {
        private readonly SeatReservationFacade _seatReservationFacade;
        private readonly UserFacade _userFacade;
        private readonly RouteFacade _routeFacade;
        private readonly NavigationStore _navigationStore;
        private readonly IFactory<IUserDetailViewModel> _userDetailViewModelFactory;
        private readonly AccountStore _accountStore;
        private readonly IFactory<IRouteDetailViewModel> _routeDetailViewModelFactory;

        public MySeatReservationViewModel(
            SeatReservationFacade seatReservationFacade,
            UserFacade userFacade,
            RouteFacade routeFacade,
            IMediator mediator,
            NavigationStore navigationStore,
            IFactory<IRouteDetailViewModel> routeDetailViewModelFactory,
            IFactory<IUserDetailViewModel> userDetailViewModelFactory,
            IUserListViewModel userListViewModel,
             AccountStore accountStore)
        {
            _seatReservationFacade = seatReservationFacade;
            _userFacade = userFacade;
            _routeFacade = routeFacade;

            _navigationStore = navigationStore;
            _navigationStore.CurrentViewModelChanged += OnCurrentViewModelChanged;

            _userDetailViewModelFactory = userDetailViewModelFactory;
            _accountStore = accountStore;
            UserDetailViewModel = _userDetailViewModelFactory.Create();

            mediator.Register<SelectedMessage<UserWrapper>>(OnUserSelected);
            _routeDetailViewModelFactory = routeDetailViewModelFactory;
            RouteDetailViewModel = _routeDetailViewModelFactory.Create();
        }

        public IUserDetailViewModel UserDetailViewModel { get; }
        public IRouteDetailViewModel RouteDetailViewModel { get; }
        
        public IUserDetailViewModel? SelectedUserDetailViewModel { get; set; }
        public ObservableCollection<SeatReservationListModel> Seats { get; } = new();
       
        public ObservableCollection<RouteDetailModel?> Routes { get; set; } = new();


 
        private void OnUserSelected(SelectedMessage<UserWrapper> message)
        {
            SelectedUser(message.Id);
        }

        private async Task SelectedUser(Guid? id)
        {
            Routes.Clear();
            if (id is null)
            {
                SelectedUserDetailViewModel = null;
            }
            else
            {
                if (_accountStore.Account != null)
                {
                    var userDetailViewModel = await _userFacade.GetAsync(_accountStore.Account.Id);

                    if (userDetailViewModel != null)
                    {
                        foreach (var seat in userDetailViewModel.Seats)
                        {
                            await AddRoute(seat);
                        }
                    }
                }
            }
        }

        private async Task AddRoute(SeatReservationDetailModel seat)
        {
            RouteDetailModel? route = await _routeFacade.GetAsync(seat.RouteId);
            Routes.Add(route);
        }

        public async Task LoadAsync()
        {
            Seats.Clear();
            var seats = await _seatReservationFacade.GetAsync();
            Seats.AddRange(seats);

        }

        public bool? Visibility => _navigationStore.CurrentModel.MySeatReservationView;
        private void OnCurrentViewModelChanged() => OnPropertyChanged(nameof(Visibility));
    }
}
