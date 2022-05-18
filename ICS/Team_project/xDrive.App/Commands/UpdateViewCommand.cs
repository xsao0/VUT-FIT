using System;
using System.Windows.Input;
using xDrive.App.Models;
using xDrive.App.Stores;
using xDrive.App.ViewModels;

namespace xDrive.App.Commands
{
    public class UpdateViewCommand : ICommand
    {
        private MainViewModel viewModel;
        private readonly NavigationStore _navigationStore;

        public UpdateViewCommand(NavigationStore navigationStore)
        {
            _navigationStore = navigationStore;
        }

        public event EventHandler? CanExecuteChanged;

        bool ICommand.CanExecute(object? parameter)
        {
            return true;
        }

        void ICommand.Execute(object? parameter)
        {
            _navigationStore.CurrentModel = parameter.ToString() switch
            {
                "CreateRoute" => CurrentViewModel.CreateRoute,
                "CreateUser" => CurrentViewModel.CreateUser,
                "MyProfile" => CurrentViewModel.MyProfile,
                "MyGarage" => CurrentViewModel.MyGarage,
                "MySeatReservation" => CurrentViewModel.MySeatReservation,
                "MyTickets" => CurrentViewModel.MyTickets,
                _ => CurrentViewModel.Search
            };
        }
    }
}
