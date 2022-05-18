using System.Collections.ObjectModel;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Input;
using System.Windows.Media.Imaging;
using Microsoft.Toolkit.Mvvm.Input;
using xDrive.App.Extensions;
using xDrive.App.Messages;
using xDrive.App.Services;
using xDrive.App.Stores;
using xDrive.App.Wrappers;
using xDrive.BL.Facades;
using xDrive.BL.Models;

namespace xDrive.App.ViewModels
{
    public class UserListViewModel : ViewModelBase, IUserListViewModel
    {
        private readonly UserFacade _userFacade;
        private readonly IMediator _mediator;
        private readonly AccountStore _accountStore;

        public UserListViewModel(UserFacade userFacade,
            IMediator mediator, AccountStore accountStore)
        {
            _userFacade = userFacade;
            _mediator = mediator;
            _accountStore = accountStore;

            UserSelectedCommand = new RelayCommand<UserListModel>(UserSelected);

            mediator.Register<UpdateMessage<UserWrapper>>(UserUpdated);
            mediator.Register<DeleteMessage<CarWrapper>>(OnCarDeleted);

        }

        public ObservableCollection<UserListModel> Users { get; } = new();

        public ICommand UserSelectedCommand { get; }

        private async void UserUpdated(UpdateMessage<UserWrapper> _) => await LoadAsync();

        private void UserSelected(UserListModel? userListModel)
        {
            if (_accountStore.Account != null && _accountStore.Account.Id == userListModel?.Id) return;
            if (userListModel is not null)
            {
                _accountStore.Account = userListModel;
                _mediator.Send(new SelectedMessage<UserWrapper> { Id = userListModel?.Id });
                _mediator.Send(new SelectedMessage<CarWrapper>  { Id = null });
                _mediator.Send(new SelectedMessage<RouteWrapper> { Id = null });
            }
        }

        private void OnCarDeleted(DeleteMessage<CarWrapper> message)
        {
            _mediator.Send(new SelectedMessage<CarWrapper> { Id = null });
            _mediator.Send(new SelectedMessage<UserWrapper> { Id = message.Model?.Model.OwnerId });
        }

        public async Task LoadAsync()
        {
            Users.Clear();
            var users = await _userFacade.GetAsync();
            Users.AddRange(users);
        }
    }
}
