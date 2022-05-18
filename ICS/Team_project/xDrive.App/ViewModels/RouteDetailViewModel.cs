using System;
using System.Collections.ObjectModel;
using System.Threading.Tasks;
using System.Windows.Input;
using xDrive.App.Commands;
using xDrive.App.Messages;
using xDrive.App.Services;
using xDrive.App.Services.MessageDialog;
using xDrive.App.Stores;
using xDrive.App.Wrappers;
using xDrive.BL.Facades;
using xDrive.BL.Models;

namespace xDrive.App.ViewModels;

public class RouteDetailViewModel : ViewModelBase, IRouteDetailViewModel
{
    private readonly IMediator _mediator;
    private readonly RouteFacade _routeFacade;
    private readonly UserFacade _userFacade;
    private readonly SeatReservationFacade _seatReservationFacade;
    private readonly IMessageDialogService _messageDialogService;
    private readonly AccountStore _accountStore;

    public RouteDetailViewModel(
        RouteFacade routeFacade, UserFacade userFacade, SeatReservationFacade seatReservationFacade, IMediator mediator, IMessageDialogService messageDialogService, AccountStore accountStore)
    {
        _routeFacade = routeFacade;
        _userFacade = userFacade;
        _seatReservationFacade = seatReservationFacade;
        _messageDialogService = messageDialogService;
        _mediator = mediator;
        _accountStore = accountStore;

        mediator.UnRegister<SelectedMessage<RouteWrapper>>(async message => await RouteSelected(message));
        mediator.Register<SelectedMessage<RouteWrapper>>(async message => await RouteSelected(message));
        mediator.Register<DeleteMessage<RouteWrapper>>(RouteDeleted);

        DeleteCommand = new AsyncRelayCommand(DeleteAsync, CanSave);
        PassengerSelectedCommand = new RelayCommand<UserWrapper>(OnPassengerSelected);

        SeatModel = SeatReservationDetailModel.Empty;
    }

    public ICommand DeleteCommand { get; set; }
    public ICommand PassengerSelectedCommand { get; }
    public RouteWrapper? Model { get; private set; }
    public UserWrapper? SelectedPassenger { get; private set; }
    public ObservableCollection<UserWrapper> Passengers { get;} = new ObservableCollection<UserWrapper>();
    public SeatReservationDetailModel SeatModel { get; private set; }

    private async void OnPassengerSelected(UserWrapper? userWrapper)
    {
        if (userWrapper == null)
            return;
        if (Model == null)
            return;

        var passenger = await _userFacade.GetAsync(userWrapper.Id);
        var route = await _routeFacade.GetAsync(Model.Id);

        if (route != null)
        {
            route.SeatCount += 1;
            await _routeFacade.SaveAsync(route);
            Model = route;

            foreach (var seat in route.Passengers)
            {
                if (passenger.Id == seat.UserId)
                {
                    SeatModel = seat;
                }
            }
        }

        await _seatReservationFacade.DeleteAsync(SeatModel.Id);
        Passengers.Clear();
        _mediator.Send(new SelectedMessage<RouteWrapper> { Model = Model });
        SeatModel = null;
    }
    
    private async Task RouteSelected(Message<RouteWrapper> message)
    {
        if (message.Id is null)
        {
            Model = null;
            SeatModel = null;
            Passengers.Clear();
        }
        else
        {
            var routeDetail = await _routeFacade.GetAsync(message.Id.Value);
            if (routeDetail != null)
            {
                Model = routeDetail;
                foreach (var passenger in routeDetail.Passengers)
                {
                    var user = await _userFacade.GetAsync( (Guid)passenger.UserId);
                    if (user != null)
                    {
                        Passengers.Add(user);
                    }
                }
            }
            DeleteCommand = new AsyncRelayCommand(DeleteAsync, CanSave);
        }
    }

    public Task SaveAsync() => throw new NotImplementedException();

    public async Task LoadAsync(Guid id)
    {
        Model = await _routeFacade.GetAsync(id) ?? RouteDetailModel.Empty;
        foreach (var passenger in Model.Passengers)
        {
            var user = await _userFacade.GetAsync(passenger.UserId) ?? UserDetailModel.Empty;
            if (user != null)
            {
                Passengers.Add(user);
            }
        }
    }

    private void RouteDeleted(DeleteMessage<RouteWrapper> obj)
    {
        Model = null;
        Passengers.Clear();
    }

    public async Task DeleteAsync()
    {
        if (Model is null)
        {
            throw new InvalidOperationException("Null model cannot be deleted");
        }

        if (Model.Id != Guid.Empty)
        {
            var delete = _messageDialogService.Show(
                $"Delete",
                $"Do you want to delete selected route?.",
                MessageDialogButtonConfiguration.YesNo,
                MessageDialogResult.No);

            if (delete == MessageDialogResult.No) return;

            try
            {
                await _routeFacade.DeleteAsync(Model!.Id);
            }
            catch
            {
                var _ = _messageDialogService.Show(
                    $"Deleting of selected route failed!",
                    "Deleting failed",
                    MessageDialogButtonConfiguration.OK,
                    MessageDialogResult.OK);
            }

            _mediator.Send(new DeleteMessage<RouteWrapper>
            {
                Model = Model
            });
        }
    }

    private bool CanSave()
    {
        return _accountStore.Account != null;
    }
}
