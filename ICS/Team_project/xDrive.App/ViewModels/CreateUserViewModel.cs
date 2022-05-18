using System;
using System.Threading.Tasks;
using System.Windows.Input;
using Microsoft.Toolkit.Mvvm.Input;
using xDrive.App.Factories;
using xDrive.App.Messages;
using xDrive.App.Services;
using xDrive.App.Stores;
using xDrive.App.Wrappers;
using xDrive.BL.Facades;
using xDrive.BL.Models;

namespace xDrive.App.ViewModels
{
    public class CreateUserViewModel : ViewModelBase
    {
        public readonly NavigationStore _navigationStore;

        public bool? Visibility => _navigationStore.CurrentModel.CreateUserView;

        private readonly IMediator _mediator;
        private readonly UserFacade _userFacade;
        private readonly AccountStore _accountStore;

        private readonly IFactory<IUserDetailViewModel> _userDetailViewModelFactory;

        public CreateUserViewModel(NavigationStore navigationStore,
            IFactory<IUserDetailViewModel> userDetailViewModelFactory,
            IUserListViewModel userListViewModel, IMediator mediator,
            UserFacade userFacade, AccountStore accountStore)
        {
            _mediator = mediator;
            _userFacade = userFacade;
            _accountStore = accountStore;

            _navigationStore = navigationStore;
            _navigationStore.CurrentViewModelChanged += OnCurrentViewModelChanged;

            UserListViewModel = userListViewModel;
            mediator.Register<SelectedMessage<UserWrapper>>(OnUserUpdated);

            _userDetailViewModelFactory = userDetailViewModelFactory;
            UserDetailViewModel = _userDetailViewModelFactory.Create();

            CreateCommand = new AsyncRelayCommand(CreateAsync,CanSave);

            Model = new UserDetailModel(string.Empty, string.Empty, string.Empty);
        }
        public UserWrapper? Model { get; set; }

        private async Task CreateAsync()
        {
            if (Model != null)
            {
                var model = await _userFacade.SaveAsync(Model);
                _mediator.Send(new UpdateMessage<UserWrapper> { Model = model });
                Model = new UserDetailModel(string.Empty, string.Empty, string.Empty);
            }

        }

        private void OnUserUpdated(SelectedMessage<UserWrapper> message) => CreateCommand = new AsyncRelayCommand(CreateAsync,CanSave);


        public ICommand CreateCommand { get; set; }

        public IUserListViewModel UserListViewModel { get; }

        public IUserDetailViewModel UserDetailViewModel { get; }

        private void OnCurrentViewModelChanged()
        {
            OnPropertyChanged(nameof(Visibility));
        }

        private bool CanSave() => _accountStore.Account != null;
    }
}
