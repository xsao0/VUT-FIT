using System;
using xDrive.App.Models;

namespace xDrive.App.Stores
{
    public class NavigationStore
    {
        private CurrentViewModel _currentViewModel = CurrentViewModel.Search;

        public CurrentViewModel CurrentModel
        {
            get => _currentViewModel;
            set
            {
                _currentViewModel = value;
                CurrentViewModelChanged?.Invoke();
            }
        }

        public event Action CurrentViewModelChanged;
    }
}
