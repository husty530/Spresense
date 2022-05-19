using System.Diagnostics;
using OpenCvSharp;

namespace Camera
{
    internal class Program
    {
        static void Main(string[] args)
        {
            using var camera = new SpresenseCamera("COM4");
            var watch = new Stopwatch();
            while (!(Console.KeyAvailable && Console.ReadKey().Key is ConsoleKey.Escape))
            {
                watch.Restart();
                using var frame = camera.Read();
                Cv2.ImShow("FRAME", frame);
                Cv2.WaitKey(1);
                Console.WriteLine($"time: {watch.ElapsedMilliseconds}ms");
            }
        }
    }
}