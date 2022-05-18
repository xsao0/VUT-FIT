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

    public class MyTicketsViewModel : ViewModelBase, IRouteListViewModel
    {
        private readonly RouteFacade _routeFacade;
        private readonly IMediator _mediator;
        private readonly NavigationStore _navigationStore;
        private readonly IFactory<IUserDetailViewModel> _userDetailViewModelFactory;
        private readonly IFactory<IRouteDetailViewModel> _routeDetailViewModelFactory;

        public MyTicketsViewModel(RouteFacade routeFacade, IMediator mediator,
            NavigationStore navigationStore,
            IFactory<IRouteDetailViewModel> routeDetailViewModelFactory,
            IFactory<IUserDetailViewModel> userDetailViewModelFactory,
            IUserListViewModel userListViewModel)
        {
            _routeFacade = routeFacade;
            _mediator = mediator;
            _navigationStore = navigationStore;
            _navigationStore.CurrentViewModelChanged += OnCurrentViewModelChanged;

            _userDetailViewModelFactory = userDetailViewModelFactory;
            UserDetailViewModel = _userDetailViewModelFactory.Create();

            _mediator = mediator;

            _routeDetailViewModelFactory = routeDetailViewModelFactory;
            RouteDetailViewModel = _routeDetailViewModelFactory.Create();
        }

        public IUserDetailViewModel UserDetailViewModel { get; }
        public IRouteDetailViewModel RouteDetailViewModel { get; }
        public ObservableCollection<RouteListModel> Routes { get; } = new();
        public ObservableCollection<IUserDetailViewModel> UserDetailViewModels { get; } = new ObservableCollection<IUserDetailViewModel>();
        public IUserDetailViewModel? SelectedUserDetailViewModel { get; set; }

        private void OnUserSelected(SelectedMessage<UserWrapper> message)
        {
            SelectedUser(message.Id);
        }

        private void SelectedUser(Guid? id)
        {
            if (id is null)
            {
                SelectedUserDetailViewModel = null;
            }
            else
            {
                var userDetailViewModel =
                    UserDetailViewModels.SingleOrDefault(vm => vm.Model?.Id == id);
                if (userDetailViewModel == null)
                {
                    userDetailViewModel = _userDetailViewModelFactory.Create();
                    UserDetailViewModels.Add(userDetailViewModel);
                    userDetailViewModel.LoadAsync(id.Value);
                }
                SelectedUserDetailViewModel = userDetailViewModel;
            }
        }
        private void SelectedUserR(Guid? id)
        {
            if (id is null)
            {
                SelectedUserDetailViewModel = null;
            }
            else
            {
                var userDetailViewModel =
                    UserDetailViewModels.SingleOrDefault(vm => vm.Model?.Id == id);
                if (userDetailViewModel == null)
                {
                    userDetailViewModel = _userDetailViewModelFactory.Create();
                    UserDetailViewModels.Add(userDetailViewModel);
                    userDetailViewModel.LoadAsync(id.Value);
                }
                SelectedUserDetailViewModel = userDetailViewModel;
            }
        }

        public async Task LoadAsync()
        {
            Routes.Clear();
            var routes = await _routeFacade.GetAsync();
            Routes.AddRange(routes);
        }

        public bool? Visibility => _navigationStore.CurrentModel.MyTicketsView;
        private void OnCurrentViewModelChanged() => OnPropertyChanged(nameof(Visibility));
    }
}
