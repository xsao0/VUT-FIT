using xDrive.BL.Models;

namespace xDrive.App.Models
{
    public record CurrentViewModel(
        bool? SearchView,
        bool? CreateRouteView,
        bool? CreateUserView,
        bool? MyProfileView,
        bool? MyGarageView,
        bool? MySeatReservationView,
        bool? MyTicketsView) : ModelBase
    {
        public bool? SearchView { get; set; } = SearchView;
        public bool? CreateRouteView { get; set; } = CreateRouteView;
        public bool? CreateUserView { get; set; } = CreateUserView;
        public bool? MyProfileView { get; set; } = MyProfileView;
        public bool? MyGarageView { get; set; } = MyGarageView;
        public bool? MySeatReservationView { get; set; } = MySeatReservationView;
        public bool? MyTicketsView { get; set; } = MyTicketsView;

        public static CurrentViewModel Search => new(
            true,
            false,
            false,
            false,
            false,
            false,
            false
        );

        public static CurrentViewModel CreateRoute => new(
            false,
            true,
            false,
            false,
            false,
            false,
            false
        );

        public static CurrentViewModel CreateUser => new(
            false,
            false,
            true,
            false,
            false,
            false,
            false
            );

        public static CurrentViewModel MyProfile => new(
            false,
            false,
            false,
            true,
            false,
            false,
            false
        );

        public static CurrentViewModel MyGarage => new(
            false,
            false,
            false,
            false,
            true,
            false,
            false
        );
        public static CurrentViewModel MySeatReservation => new(
           false,
           false,
           false,
           false,
           false,
           true,
           false
       );
        public static CurrentViewModel MyTickets => new(
            false,
            false,
            false,
            false,
            false,
            false,
            true
        );
    }
}
