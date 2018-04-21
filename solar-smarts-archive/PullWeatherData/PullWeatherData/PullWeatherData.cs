using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Http;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace SolarSmarts
{
    class DataRetrieval   
    {
        public static readonly string API_KEY = "23cb6a46ff972a4647744da94959240b";
        public static string API_URL = "https://api.darksky.net/forecast/[key]/[latitude],[longitude],[time]";
        
        public static void Main(string[] args)
        {
            /*
            WriteLine("SolarSmarts Data Retrieval - Select data to retrieve:" +
                "\n\t1. DarkSky API" +
                "\n\t2. Noveda", 
                MethodBase.GetCurrentMethod());

            ConsoleKeyInfo userInput = Console.ReadKey();

            if (userInput.Key == ConsoleKey.D1)
                GetWeatherData();
            else if (userInput.Key == ConsoleKey.D2)
                GetNovedaData();

            Console.WriteLine("\n");
            */

            GetWeatherData();
        }

        private static void GetWeatherData()
        {
            IDictionary<DateTime, DateTime> dateRanges = new Dictionary<DateTime, DateTime>()
            {
                { new DateTime(2013, 6, 1, 0, 0, 0), new DateTime(2013, 6, 30, 23, 59, 59) },
                { new DateTime(2014, 6, 1, 0, 0, 0), new DateTime(2014, 6, 30, 23, 59, 59) },
                { new DateTime(2015, 6, 1, 0, 0, 0), new DateTime(2015, 6, 30, 23, 59, 59) },
                { new DateTime(2016, 6, 1, 0, 0, 0), new DateTime(2016, 6, 30, 23, 59, 59) },
                { new DateTime(2017, 6, 1, 0, 0, 0), new DateTime(2017, 6, 30, 23, 59, 59) },

                { new DateTime(2013, 7, 1, 0, 0, 0), new DateTime(2013, 7, 31, 23, 59, 59) },
                { new DateTime(2014, 7, 1, 0, 0, 0), new DateTime(2014, 7, 31, 23, 59, 59) },
                { new DateTime(2015, 7, 1, 0, 0, 0), new DateTime(2015, 7, 31, 23, 59, 59) },
                { new DateTime(2016, 7, 1, 0, 0, 0), new DateTime(2016, 7, 31, 23, 59, 59) },
                { new DateTime(2017, 7, 1, 0, 0, 0), new DateTime(2017, 7, 31, 23, 59, 59) },

                { new DateTime(2013, 8, 1, 0, 0, 0), new DateTime(2013, 8, 31, 23, 59, 59) },
                { new DateTime(2014, 8, 1, 0, 0, 0), new DateTime(2014, 8, 31, 23, 59, 59) },
                { new DateTime(2015, 8, 1, 0, 0, 0), new DateTime(2015, 8, 31, 23, 59, 59) },
                { new DateTime(2016, 8, 1, 0, 0, 0), new DateTime(2016, 8, 31, 23, 59, 59) },
                { new DateTime(2017, 8, 1, 0, 0, 0), new DateTime(2017, 8, 31, 23, 59, 59) },

                { new DateTime(2013, 9, 1, 0, 0, 0), new DateTime(2013, 9, 30, 23, 59, 59) },
                { new DateTime(2014, 9, 1, 0, 0, 0), new DateTime(2014, 9, 30, 23, 59, 59) },
                { new DateTime(2015, 9, 1, 0, 0, 0), new DateTime(2015, 9, 30, 23, 59, 59) },
                { new DateTime(2016, 9, 1, 0, 0, 0), new DateTime(2016, 9, 30, 23, 59, 59) },
                { new DateTime(2017, 9, 1, 0, 0, 0), new DateTime(2017, 9, 30, 23, 59, 59) },
            };

            foreach (KeyValuePair<DateTime, DateTime> date in dateRanges)
            {
                DateTime currentDate = date.Key;
                string fileName = date.Key.Year.ToString() + "_" + date.Key.Month + ".csv";
                using (StreamWriter Writer = new StreamWriter(fileName, append: true)) { Writer.Write("["); }

                while (currentDate <= date.Value)
                {
                    Console.WriteLine("Pulling data from " + currentDate.ToString() + "...");
                    long unixTime = ((DateTimeOffset)currentDate).ToUnixTimeSeconds();

                    var result = GetTimeMachineObj(API_KEY, "40.526044", "-74.435656", unixTime.ToString()).Result;

                    using (StreamWriter Writer = new StreamWriter(fileName, append: true))
                    {
                        Writer.Write(result);
                        if (date.Key.Day != date.Value.Day) { Writer.Write(","); }
                    }
                    currentDate = currentDate.AddDays(1);
                }

                using (StreamWriter Writer = new StreamWriter(fileName, append: true)) { Writer.Write("]"); }
            }
        }
        
        private static void GetNovedaData()
        {

        }

        private static void WriteLine(string line, MethodBase methodBase)
        {
            Console.WriteLine("[" + methodBase.Name + "] " + line);
        }

        public static async Task<string> GetTimeMachineObj(string apiKey, string latitude, string longitude, string time)
        {
            string responseUrl = API_URL.Replace("[key]", apiKey).Replace("[latitude]", latitude).Replace("[longitude]", longitude).Replace("[time]", time);
            using (var client = new HttpClient())
            {
                HttpResponseMessage response = await client.GetAsync(responseUrl);
                if (response.IsSuccessStatusCode)
                {
                    return await response.Content.ReadAsStringAsync().ContinueWith((task) => task.Result);        
                }
                return null;
            }
        }
    }
}
