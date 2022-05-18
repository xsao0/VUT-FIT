using xDrive.BL.Models;

namespace xDrive.App.Messages
{
    public record NewMessage<T> : Message<T>
        where T : IModel
    {
    }
}
