using System.IO.Ports;
using OpenCvSharp;

namespace Camera
{
    public class SpresenseCamera : IDisposable
    {

        // ------ fields ------ //

        private readonly SerialPort _serial;


        // ------ constructors ------ //

        public SpresenseCamera(string port, int baudRate = 2000000)
        {
            _serial = new(port, baudRate);
            try
            {
                _serial.Open();
            }
            catch
            {
                Thread.Sleep(250);
                _serial.Open();
            }
        }


        // ------ public methods ------ //

        public void Dispose()
        {
            _serial.Close();
            _serial.Dispose();
        }

        public Mat Read()
        {
            _serial.Write(">");
            var size =
                _serial.ReadByte() |
                _serial.ReadByte() << 8 |
                _serial.ReadByte() << 16 |
                _serial.ReadByte() << 24;
            var buf = new byte[size];
            var progress = 0;
            while (progress < size)
                progress += _serial.Read(buf, progress, size - progress);
            return Cv2.ImDecode(buf, ImreadModes.Unchanged);
        }

    }
}
