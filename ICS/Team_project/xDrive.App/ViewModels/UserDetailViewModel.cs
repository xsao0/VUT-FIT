using System;
using System.Collections.ObjectModel;
using System.Threading.Tasks;
using System.Windows.Input;
using Microsoft.Toolkit.Mvvm.Input;
using xDrive.App.Messages;
using xDrive.App.Services;
using xDrive.App.Stores;
using xDrive.App.Wrappers;
using xDrive.BL.Facades;
using xDrive.BL.Models;

namespace xDrive.App.ViewModels;

public class UserDetailViewModel : ViewModelBase, IUserDetailViewModel
{
    private readonly IMediator _mediator;
    private readonly UserFacade _userFacade;
    private readonly AccountStore _accountStore;

    public UserDetailViewModel(UserFacade userFacade, IMediator mediator, AccountStore accountStore)
    {
        _userFacade = userFacade;
        _mediator = mediator;
        _accountStore = accountStore;

        SaveCommand = new AsyncRelayCommand(SaveAsync, CanSave);
        CarSelectedCommand = new RelayCommand<CarWrapper>(CarSelected);
        DeleteRouteCommand = new RelayCommand<CarWrapper>(CarSelected);
        RouteSelectedCommand = new RelayCommand<RouteWrapper>(RouteSelected);

        mediator.UnRegister<SelectedMessage<UserWrapper>>(async message => await UserSelected(message));
        mediator.Register<SelectedMessage<UserWrapper>>(async message => await UserSelected(message));
        mediator.Register<DeleteMessage<RouteWrapper>>(async message => await RouteDeleted(message));
    }

    public UserWrapper? Model { get; private set; }

    public ICommand RouteSelectedCommand { get; }
    public ICommand CarSelectedCommand { get; }
    public ICommand SaveCommand { get; set; }
    public ICommand DeleteRouteCommand { get; }


    public async Task LoadAsync(Guid id)
    {
        Model = await _userFacade.GetAsync(id) ?? UserDetailModel.Empty;
    }

    private async Task UserSelected(SelectedMessage<UserWrapper> message)
    {
        if (message.Id is null)
        {
            Model = null;
        }
        else
        {
            var userDetail = await _userFacade.GetAsync(message.Id.Value);
            if (userDetail != null)
            {
                Model = userDetail;
            }

            SaveCommand = new AsyncRelayCommand(SaveAsync, CanSave);
        }
    }

    private void CarSelected(CarWrapper? carListModel)
    {
        if (carListModel is not null)
        {
            _mediator.Send(new SelectedMessage<CarWrapper> {Id = carListModel.Id});
        }
    }

    private void RouteSelected(RouteWrapper? routeListModel)
    {
        if (routeListModel is not null)
        {
            _mediator.Send(new SelectedMessage<RouteWrapper> { Id = routeListModel.Id });
        }
    }

    private async Task RouteDeleted(DeleteMessage<RouteWrapper> message)
    {
        if (message.Model != null)
        {
            await LoadAsync(message.Model.Model.UserId);
        }
    }

    public async Task SaveAsync()
    {
        if (Model == null)
        {
            throw new InvalidOperationException("Null model cannot be saved");
        }

        Model = await _userFacade.SaveAsync(Model.Model);
        _mediator.Send(new UpdateMessage<UserWrapper> {Model = Model});
    }

    private bool CanSave()
    {
        return _accountStore.Account != null;
    }

    public async Task DeleteAsync()
    {
        if (Model is null)
        {
            throw new InvalidOperationException("Null model cannot be deleted");
        }
    }
}
