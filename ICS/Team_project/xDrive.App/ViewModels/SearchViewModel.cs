using System;
using System.Windows.Controls;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.Windows.Input;
using Xceed.Wpf.Toolkit;
using xDrive.App.Commands;
using xDrive.App.Factories;
using xDrive.App.Messages;
using xDrive.App.Services;
using xDrive.App.Stores;
using xDrive.App.Wrappers;
using xDrive.BL.Facades;
using xDrive.BL.Models;

namespace xDrive.App.ViewModels
{
    public class SearchViewModel : ViewModelBase
    {
        public readonly NavigationStore _navigationStore;
        public bool? Visibility => _navigationStore.CurrentModel.SearchView;
        private readonly RouteFacade _routeFacade;
        private readonly SeatReservationFacade _seatReservationFacade;
        private readonly UserFacade _userFacade;
        private readonly AccountStore _accountStore;
        private readonly IMediator _mediator;

        public SearchViewModel(
            NavigationStore navigationStore,
            RouteFacade routeFacade,
            SeatReservationFacade _seatReservationFacade,
            UserFacade userFacade,
            AccountStore accountStore,
            IMediator mediator)
        {
            _navigationStore = navigationStore;
            _navigationStore.CurrentViewModelChanged += OnCurrentViewModelChanged;
            _routeFacade = routeFacade;
            this._seatReservationFacade = _seatReservationFacade;
            _userFacade = userFacade;
            _accountStore = accountStore;
            _mediator = mediator;


            mediator.Register<SelectedMessage<UserWrapper>>(OnUserUpdated);


            SearchCommand = new AsyncRelayCommand(SearchRoute, CanSave);
            RouteSelectedCommand = new RelayCommand<RouteListModel>(OnRouteSelected);

            Beginning = string.Empty;
            Start = string.Empty;
            Finish = string.Empty;

            SeatModel = SeatReservationDetailModel.Empty;

        }

        public UserDetailModel? UserModel { get; private set; }
        public RouteWrapper Model { get; set; }
        public SeatReservationDetailModel SeatModel { get; private set; }

        private async void OnRouteSelected(RouteListModel? message)
        {
            if (message == null)
                return;

            var route = await _routeFacade.GetAsync(message.Id);
            if (route is { SeatCount: <= 0 })
                return;

            if (route != null)
            {
                route.SeatCount -= 1;
                await _routeFacade.SaveAsync(route);
                Model = route;
            }

            await RouteSelected();
        }

        private async Task RouteSelected()
        {
            if (_accountStore.Account != null)
            {
                SeatModel.UserId = _accountStore.Account.Id;
                SeatModel.RouteId = Model.Id;
                await _seatReservationFacade.SaveAsync(SeatModel);
                _mediator.Send(new SelectedMessage<UserWrapper> { Id = _accountStore.Account?.Id });
            }
            await SearchRoute();
        }

        private void OnUserUpdated(SelectedMessage<UserWrapper> message) => RouteListViewModels = null;

        private async Task SearchRoute()
        {
            DateTime dateTime = Convert.ToDateTime(Beginning) ;
            if (_accountStore.Account != null)
            {
                RouteListViewModels = await _routeFacade.GetRoute(Start, Finish, dateTime, _accountStore.Account.Id);
                SearchCommand = new AsyncRelayCommand(SearchRoute, CanSave);
            }
        }

        public string Beginning { get; set; }
        public string Start { get; set; }
        public string Finish { get; set; }

        public IEnumerable<RouteListModel>? RouteListViewModels { get; set; }
        public ICommand SearchCommand { get; set; }
        public ICommand RouteSelectedCommand { get; }

        private void OnCurrentViewModelChanged()
        {
            OnPropertyChanged(nameof(Visibility));
        }

        private bool CanSave() => _accountStore.Account != null;
    }
}
