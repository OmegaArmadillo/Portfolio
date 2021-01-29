using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Drawing;

namespace CS460_HW4.Controllers
{
    public class HomeController : Controller
    {
        public ActionResult Index()
        {
            return View();
        }

        public ActionResult About()
        {
            ViewBag.Message = "Your application description page.";

            return View();
        }

        public ActionResult Contact()
        {
            ViewBag.Message = "Your contact page.";

            return View();
        }

        public ActionResult RGBColor()
        {

            return View();
        }



        public ActionResult CreateColor()
        {
            //get the rgb values
            int red = int.Parse(Request.QueryString["Red"]);
            int green = int.Parse(Request.QueryString["Green"]);
            int blue = int.Parse(Request.QueryString["Blue"]);
            
            //create the color
            Color newColor = Color.FromArgb(red, green, blue);

            //get the hex value for the color
            string colorHtml = ColorTranslator.ToHtml(newColor);

            //set the viewbag color for the page
            ViewBag.Color = colorHtml;

            //return page
            return View("RGBColor");

        }

        public ActionResult ColorInterpolator()
        {
            ViewBag.colors = new string[1];
            ViewBag.colors[0] = "#AAAAAA";
            ViewBag.amount = 0;
            ViewBag.Finish = false;
            ViewBag.error = "";

            return View("ColorInterpolator");
        }

        [HttpPost]
        public ActionResult ColorInterpolator(string FirstColor, string SecondColor, int colorAmount)
        {
            //create the colors
            Color color1;
            Color color2;

            try
            {
                //set  the colors
                color1 = ColorTranslator.FromHtml(FirstColor);
            }

            catch
            {
                ViewBag.error = "Your first color is not in valid hex format.";
                return View("ColorInterpolator");
            }

            try
            {
                //set  the colors
                color2 = ColorTranslator.FromHtml(SecondColor);
            }

            catch
            {
                ViewBag.error = "Your second color is not in valid hex format.";
                return View("ColorInterpolator");
            }

            if(FirstColor.Length<7)
            {
                ViewBag.error = "Your first color is not in valid hex format.";
                return View("ColorInterpolator");
            }

            if (SecondColor.Length < 7)
            {
                ViewBag.error = "Your second color is not in valid hex format.";
                return View("ColorInterpolator");
            }



            //make an array to hold the values
            string[] colors = new string[colorAmount];

            //make the hsv values for the first color then find and set them
            double hue1;
            double sat1;
            double val1;
            ColorToHSV(color1, out hue1, out sat1, out val1);

            //make the hsv values for the second color then find and set them
            double hue2;
            double sat2;
            double val2;
            ColorToHSV(color2, out hue2, out sat2, out val2);

            //find the amount to incriment
            double hueInc = (hue2 - hue1) / (colorAmount - 1);
            double satInc = (sat2 - sat1) / (colorAmount - 1);
            double valInc = (val2 - val1) / (colorAmount - 1);

            //create values to be used in the loop
            double currentHue = hue1;
            double currentSat = sat1;
            double currentVal = val1;

            for (int i = 0; i < colors.Length; i++)
            {
                //make a color out of the hsv color
                Color currentColor = ColorFromHSV(currentHue, currentSat, currentVal);

                //find the hex value for the color and put it in the array
                colors[i] = ColorTranslator.ToHtml(currentColor);

                //incriment the values
                currentHue = currentHue + hueInc;
                currentSat = currentSat + satInc;
                currentVal = currentVal + valInc;
            }

            //set viewbag values
            ViewBag.colors = colors;
            ViewBag.amount = colorAmount;
            ViewBag.Finish = true;

            //return view
            return View();

        }

        // From Greg's answer: https://stackoverflow.com/questions/359612/how-to-change-rgb-color-to-hsv/1626175
        // And Wikipedia: https://en.wikipedia.org/wiki/HSL_and_HSV
        public static void ColorToHSV(Color color, out double hue, out double saturation, out double value)
        {
            int max = Math.Max(color.R, Math.Max(color.G, color.B));
            int min = Math.Min(color.R, Math.Min(color.G, color.B));

            hue = color.GetHue();
            saturation = (max == 0) ? 0 : 1d - (1d * min / max);
            value = max / 255d;
        }

        public static Color ColorFromHSV(double hue, double saturation, double value)
        {
            int hi = Convert.ToInt32(Math.Floor(hue / 60)) % 6;
            double f = hue / 60 - Math.Floor(hue / 60);

            value = value * 255;
            int v = Convert.ToInt32(value);
            int p = Convert.ToInt32(value * (1 - saturation));
            int q = Convert.ToInt32(value * (1 - f * saturation));
            int t = Convert.ToInt32(value * (1 - (1 - f) * saturation));

            if (hi == 0)
                return Color.FromArgb(255, v, t, p);
            else if (hi == 1)
                return Color.FromArgb(255, q, v, p);
            else if (hi == 2)
                return Color.FromArgb(255, p, v, t);
            else if (hi == 3)
                return Color.FromArgb(255, p, q, v);
            else if (hi == 4)
                return Color.FromArgb(255, t, p, v);
            else
                return Color.FromArgb(255, v, p, q);
        }


    }
}