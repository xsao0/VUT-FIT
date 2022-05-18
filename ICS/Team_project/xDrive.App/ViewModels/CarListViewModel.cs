using xDrive.BL.Facades;
using xDrive.BL.Models;
using System.Collections.ObjectModel;
using System.Security.Principal;
using System.Threading.Tasks;
using System.Windows.Input;
using Microsoft.Toolkit.Mvvm.Input;
using xDrive.App.Extensions;
using xDrive.App.Messages;
using xDrive.App.Services;
using xDrive.App.Wrappers;

namespace xDrive.App.ViewModels
{
    public class CarListViewModel : ViewModelBase, ICarListViewModel
    {
        private readonly CarFacade _carFacade;

        public CarListViewModel(CarFacade carFacade)
        {
            _carFacade = carFacade;
        }

        public ObservableCollection<CarListModel> Cars { get; } = new();

        public async Task LoadAsync()
        {
            Cars.Clear();
            var cars = await _carFacade.GetAsync();
            Cars.AddRange(cars);
        }
    }
}
