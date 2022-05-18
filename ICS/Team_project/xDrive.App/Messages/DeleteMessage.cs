using xDrive.BL.Models;

namespace xDrive.App.Messages
{
    public record DeleteMessage<T> : Message<T>
        where T : IModel
    {
    }
}
