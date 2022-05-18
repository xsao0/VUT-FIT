using System;
using System.Collections.ObjectModel;
using System.Linq;
using xDrive.App.Factories;
using xDrive.App.Messages;
using xDrive.App.Services;
using xDrive.App.Stores;
using xDrive.App.Wrappers;

namespace xDrive.App.ViewModels
{
    public class MyProfileViewModel : ViewModelBase
    {
        public readonly NavigationStore _navigationStore;
        public bool? Visibility => _navigationStore.CurrentModel.MyProfileView;

        private readonly IFactory<IUserDetailViewModel> _userDetailViewModelFactory;

        public MyProfileViewModel(NavigationStore navigationStore,
            IFactory<IUserDetailViewModel> userDetailViewModelFactory,
            IUserListViewModel userListViewModel, IMediator mediator)
        {
            _navigationStore = navigationStore;
            _navigationStore.CurrentViewModelChanged += OnCurrentViewModelChanged;

            _userDetailViewModelFactory = userDetailViewModelFactory;
            UserDetailViewModel = _userDetailViewModelFactory.Create();
        }

        public IUserDetailViewModel UserDetailViewModel { get; }

        public ObservableCollection<IUserDetailViewModel> UserDetailViewModels { get; } = new ObservableCollection<IUserDetailViewModel>();

        public IUserDetailViewModel? SelectedUserDetailViewModel { get; set; }

        private void SelectUser(Guid? id)
        {
            if (id is null)
            {
                SelectedUserDetailViewModel = null;
            }

            else
            {
                var userDetailViewModel = UserDetailViewModels.SingleOrDefault(vm => vm.Model?.Id == id);
                if (userDetailViewModel == null)
                {
                    userDetailViewModel = _userDetailViewModelFactory.Create();
                    UserDetailViewModels.Add(userDetailViewModel);
                    userDetailViewModel.LoadAsync(id.Value);
                }

                SelectedUserDetailViewModel = userDetailViewModel;
            }
        }

        private void OnCurrentViewModelChanged()
        {
            OnPropertyChanged(nameof(Visibility));
        }
    }
}
