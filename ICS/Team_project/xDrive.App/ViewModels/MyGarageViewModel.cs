using System;
using System.Collections.ObjectModel;
using System.Linq;
using Microsoft.EntityFrameworkCore.Query.Internal;
using xDrive.App.Factories;
using xDrive.App.Messages;
using xDrive.App.Services;
using xDrive.App.Stores;
using xDrive.App.Wrappers;

namespace xDrive.App.ViewModels
{
    public class MyGarageViewModel : ViewModelBase
    {
        public readonly NavigationStore _navigationStore;
        public bool? Visibility => _navigationStore.CurrentModel.MyGarageView;

        private readonly IFactory<ICarDetailViewModel> _carDetailViewModelFactory;
        private readonly IFactory<IUserDetailViewModel> _userDetailViewModelFactory;

        public MyGarageViewModel(NavigationStore navigationStore,
            IFactory<ICarDetailViewModel> carDetailViewModelFactory,
            IFactory<IUserDetailViewModel> userDetailViewModelFactory,
            ICarListViewModel carListViewModel, IMediator mediator,
            IUserListViewModel userListViewModel)
        {
            _navigationStore = navigationStore;
            _navigationStore.CurrentViewModelChanged += OnCurrentViewModelChanged;

            UserListViewModel = userListViewModel;
            CarListViewModel = carListViewModel;

            _carDetailViewModelFactory = carDetailViewModelFactory;
            CarDetailViewModel = _carDetailViewModelFactory.Create();

            _userDetailViewModelFactory = userDetailViewModelFactory;
            UserDetailViewModel = _userDetailViewModelFactory.Create();

            //mediator.Register<SelectedMessage<UserWrapper>>(OnUserSelected);
            mediator.Register<DeleteMessage<CarWrapper>>(OnCarDeleted);
        }

        public IUserListViewModel UserListViewModel { get; }
        public IUserDetailViewModel UserDetailViewModel { get; }
        public ICarDetailViewModel CarDetailViewModel { get; }
        public ObservableCollection<ICarDetailViewModel> CarDetailViewModels { get; } = new ObservableCollection<ICarDetailViewModel>();
        public ObservableCollection<IUserDetailViewModel> UserDetailViewModels { get; } = new ObservableCollection<IUserDetailViewModel>();
        public IUserDetailViewModel? SelectedUserDetailViewModel { get; set; }


        public ICarListViewModel CarListViewModel { get; }

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

        private void OnCarDeleted(DeleteMessage<CarWrapper> message)
        {
            var car = CarDetailViewModels.SingleOrDefault(i => i.Model?.Id == message.Id);
            if (car != null)
            {
                CarDetailViewModels.Remove(car);
            }
        }

        private void OnCurrentViewModelChanged()
        {
            OnPropertyChanged(nameof(Visibility));
        }
    }
}
