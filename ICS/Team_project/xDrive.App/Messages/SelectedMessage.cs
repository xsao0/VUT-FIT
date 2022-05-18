using xDrive.BL.Models;

namespace xDrive.App.Messages
{
    public record SelectedMessage<T> : Message<T>
        where T : IModel
    {
    }
}
