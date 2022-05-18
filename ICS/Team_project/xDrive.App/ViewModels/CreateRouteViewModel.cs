using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Threading.Tasks;
using System.Windows.Input;
using xDrive.App.Commands;
using xDrive.App.Extensions;
using xDrive.App.Messages;
using xDrive.App.Services;
using xDrive.App.Stores;
using xDrive.App.Wrappers;
using xDrive.BL.Facades;
using xDrive.BL.Models;

namespace xDrive.App.ViewModels
{
    public class CreateRouteViewModel : ViewModelBase, IRouteDetailViewModel
    {
        private readonly NavigationStore _navigationStore;
        private readonly RouteFacade _routeFacade;
        private readonly UserFacade _userFacade;
        private readonly IMediator _mediator;
        private readonly AccountStore _accountStore;


        public bool? Visibility => _navigationStore.CurrentModel.CreateRouteView;

        public CreateRouteViewModel(NavigationStore navigationStore, RouteFacade routeFacade,
            IMediator mediator, AccountStore accountStore, UserFacade userFacade)
        {
            _routeFacade = routeFacade;
            _mediator = mediator;
            _accountStore = accountStore;
            _userFacade = userFacade;
            _navigationStore = navigationStore;
            _navigationStore.CurrentViewModelChanged += OnCurrentViewModelChanged;

            CreateRoute = new AsyncRelayCommand<CarDetailModel>(SaveAsync, CanSave);

            mediator.Register<SelectedMessage<UserWrapper>>(OnUserSelected);


            Model = RouteDetailModel.Empty;
            Model.Beginning = DateTime.Today;
        }

        private async void OnUserSelected(SelectedMessage<UserWrapper> message)
        {
            Model = RouteDetailModel.Empty;
            Model.Beginning = DateTime.Today;
            if (_accountStore.Account != null)
            {
                userModel = await _userFacade.GetAsync(_accountStore.Account.Id);
            }
            ownedCars = userModel.OwnedCars;
            LoadAsync();
        }

        public ICommand CreateRoute { get; set; }

        public UserDetailModel userModel { get; set; }

        public List<CarDetailModel> ownedCars { get; set; } = new List<CarDetailModel>();

        public ObservableCollection<CarDetailModel> Cars { get; } = new();

        public RouteWrapper? Model { get; private set; }

        public async Task LoadAsync(Guid id) => Model = await _routeFacade.GetAsync(id) ?? RouteDetailModel.Empty;

        public Task DeleteAsync() => throw new NotImplementedException();



        public async Task SaveAsync(CarDetailModel? carDetailModel)
        {
            if (Model == null)
            {
                throw new InvalidOperationException("Null model cannot be saved");
            }

            if (_accountStore.Account != null)
            {
                Model.Model.UserId = _accountStore.Account.Id;
                if (carDetailModel != null)
                {
                    Model.Model.SeatCount = carDetailModel.NumberOfSeats - 1;
                }
                Model = await _routeFacade.SaveAsync(Model.Model);
                _mediator.Send(new SelectedMessage<UserWrapper> { Id = _accountStore.Account?.Id });
            }
            Model = RouteDetailModel.Empty;
            Model.Beginning = DateTime.Today;
            LoadAsync();
        }

        private void OnCurrentViewModelChanged() => OnPropertyChanged(nameof(Visibility));

        private bool CanSave(CarDetailModel? _)
        {
            return _accountStore.Account != null;
        }

        public Task SaveAsync() => throw new NotImplementedException();

        public void LoadAsync()
        {
            Cars.Clear();
            foreach (var car in ownedCars)
            {
                Cars.Add(car);
            }
        }
    }
}
