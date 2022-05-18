using xDrive.BL.Models;

namespace xDrive.App.Messages
{
    public record UpdateMessage<T> : Message<T>
        where T : IModel
    {
    }
}
