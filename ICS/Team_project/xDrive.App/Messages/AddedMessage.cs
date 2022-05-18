using xDrive.BL.Models;

namespace xDrive.App.Messages
{
    public record AddedMessage<T> : Message<T>
        where T : IModel
    {
    }
}
