using System.Collections.ObjectModel;
using xDrive.App.Extensions;
using System.Threading.Tasks;
using System.Windows.Input;
using xDrive.App.Stores;
using xDrive.App.Messages;
using xDrive.App.Services;
using xDrive.App.Wrappers;
using xDrive.BL.Facades;
using xDrive.BL.Models;

namespace xDrive.App.ViewModels
{

    public class RouteListViewModel : ViewModelBase, IRouteListViewModel
    {
        private readonly RouteFacade _routeFacade;
        private readonly IMediator _mediator;
        private readonly NavigationStore _navigationStore;
        
        public RouteListViewModel(RouteFacade routeFacade, IMediator mediator,
            NavigationStore navigationStore)
        {
            _routeFacade = routeFacade;
            _mediator = mediator;
            _navigationStore = navigationStore;
            _navigationStore.CurrentViewModelChanged += OnCurrentViewModelChanged;
        }

        public ObservableCollection<RouteListModel> Routes { get; } = new();

        public async Task LoadAsync()
        {
            Routes.Clear();
            var routes = await _routeFacade.GetAsync();
            Routes.AddRange(routes);
        }

        public bool? Visibility => _navigationStore.CurrentModel.CreateRouteView;
        private void OnCurrentViewModelChanged() => OnPropertyChanged(nameof(Visibility));
    }
}
