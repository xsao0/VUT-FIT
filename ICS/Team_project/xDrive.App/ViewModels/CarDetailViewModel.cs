using System;
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

public class CarDetailViewModel : ViewModelBase, ICarDetailViewModel
{
    private readonly IMediator _mediator;
    private readonly CarFacade _carFacade;
    private readonly IMessageDialogService _messageDialogService;
    private readonly AccountStore _accountStore;

    public CarDetailViewModel(
        CarFacade carFacade, IMediator mediator, IMessageDialogService messageDialogService, AccountStore accountStore)
    {
        _carFacade = carFacade;
        _messageDialogService = messageDialogService;
        _mediator = mediator;
        _accountStore = accountStore;

        mediator.UnRegister<SelectedMessage<CarWrapper>>(async message => await CarSelected(message));
        mediator.Register<SelectedMessage<CarWrapper>>(async message => await CarSelected(message));

        DeleteCommand = new AsyncRelayCommand(DeleteAsync,CanSave);
        SaveCommand = new AsyncRelayCommand(SaveAsync,CanSave);
        NewCarCommand = new AsyncRelayCommand(NewAsync,CanSave);
        EmptyCarCommand = new RelayCommand(EmptyAsync,CanSave);
    }

    public void EmptyAsync()
    {
        Model = CarDetailModel.Empty;
        if (_accountStore.Account != null)
        {
            Model.Model.OwnerId = _accountStore.Account.Id;
        }
    }

    public CarWrapper? Model { get; private set; }

    public ICommand DeleteCommand { get; set; }
    public ICommand SaveCommand { get; set; }
    public ICommand NewCarCommand { get; set; }
    public ICommand EmptyCarCommand { get; set; }

    private async Task CarSelected(Message<CarWrapper> message)
    {
        if (message.Id is null)
        {
            Model = null;
        }
        else
        {
            var carDetail = await _carFacade.GetAsync(message.Id.Value);
            if (carDetail != null)
            {
                Model = carDetail;
            }
            DeleteCommand = new AsyncRelayCommand(DeleteAsync,CanSave);
            SaveCommand = new AsyncRelayCommand(SaveAsync,CanSave);
            NewCarCommand = new AsyncRelayCommand(NewAsync,CanSave);
            EmptyCarCommand = new RelayCommand(EmptyAsync,CanSave);
        }
    }

    public async Task LoadAsync(Guid id)
    {
        Model = await _carFacade.GetAsync(id) ?? CarDetailModel.Empty;
    }

    public async Task NewAsync()
    {
        if (Model == null)
        {
            throw new InvalidOperationException("Null model cannot be saved");
        }
        Model.Id = Guid.Empty;
        Model = await _carFacade.SaveAsync(Model.Model);
        _mediator.Send(new SelectedMessage<UserWrapper> { Id = Model.Model.OwnerId });
    }

    public async Task SaveAsync()
    {
        if (Model == null)
        {
            throw new InvalidOperationException("Null model cannot be saved");
        }
        Model = await _carFacade.SaveAsync(Model.Model);
        _mediator.Send(new SelectedMessage<UserWrapper> { Id = Model.Model.OwnerId });
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
                $"Do you want to delete {Model?.NumberPlate}?.",
                MessageDialogButtonConfiguration.YesNo,
                MessageDialogResult.No);

            if (delete == MessageDialogResult.No) return;

            try
            {
                await _carFacade.DeleteAsync(Model!.Id);
            }
            catch
            {
                var _ = _messageDialogService.Show(
                    $"Deleting of {Model?.Manufacturer} failed!",
                    "Deleting failed",
                    MessageDialogButtonConfiguration.OK,
                    MessageDialogResult.OK);
            }

            _mediator.Send(new DeleteMessage<CarWrapper>
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
