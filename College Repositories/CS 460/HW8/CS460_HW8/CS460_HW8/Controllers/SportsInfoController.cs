using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Diagnostics;
using System.Linq;
using System.Net;
using System.Web;
using System.Web.Helpers;
using System.Web.Mvc;
using CS460_HW8.DAL;
using CS460_HW8.Models;

namespace CS460_HW8.Controllers
{
    public class SportsInfoController : Controller
    {
        private SportsInfoContext db = new SportsInfoContext();

        

        //Main WebPage
        // GET: SportsInfo
        public ActionResult Index()
        {
            return View();
        }



        //actions for creating athletes
        // GET: Athletes/Create
        public ActionResult AddAthlete()
        {
            ViewBag.TeamID = new SelectList(db.Teams.OrderBy(b => b.Name), "ID", "Name");
           
            
            return View();
        }

        // POST: Athletes/Create
        // To protect from overposting attacks, please enable the specific properties you want to bind to, for 
        // more details see https://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult AddAthlete([Bind(Include = "ID,Name,TeamID,Gender")] Athlete athlete, string gender)
        {
            athlete.Gender = gender;

            if (ModelState.IsValid)
            {
                db.Athletes.Add(athlete);
                db.SaveChanges();
                return RedirectToAction("AddAthlete");
            }

            ViewBag.TeamID = new SelectList(db.Teams.OrderBy(b => b.Name), "ID", "Name", athlete.TeamID);
            return View(athlete);
        }




        //acitons for creating meets
        // GET: Meets/Create
        public ActionResult AddMeet()
        {
            return View();
        }

        // POST: Meets/Create
        // To protect from overposting attacks, please enable the specific properties you want to bind to, for 
        // more details see https://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult AddMeet([Bind(Include = "ID,Location,Date")] Meet meet)
        {
            if (ModelState.IsValid)
            {
                db.Meets.Add(meet);
                db.SaveChanges();
                return RedirectToAction("AddMeet");
            }

            return View(meet);
        }




        //actions for creating results
        // GET: Results/Create
        public ActionResult AddResult()
        {
            ViewBag.AthleteID = new SelectList(db.Athletes.OrderBy(b => b.Name), "ID", "Name");
            ViewBag.EventID = new SelectList(db.Events.OrderBy(b => b.Name), "ID", "Name");
            ViewBag.MeetID = new SelectList(db.Meets.OrderBy(b => b.Location), "ID", "Location");
            return View();
        }

        // POST: Results/Create
        // To protect from overposting attacks, please enable the specific properties you want to bind to, for 
        // more details see https://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult AddResult([Bind(Include = "ID,MeetID,EventID,AthleteID,RaceTime")] Result result)
        {
            if (ModelState.IsValid)
            {
                db.Results.Add(result);
                db.SaveChanges();
                return RedirectToAction("AddResult");
            }

            ViewBag.AthleteID = new SelectList(db.Athletes.OrderBy(b => b.Name), "ID", "Name", result.AthleteID);
            ViewBag.EventID = new SelectList(db.Events.OrderBy(b => b.Name), "ID", "Name", result.EventID);
            ViewBag.MeetID = new SelectList(db.Meets.OrderBy(b => b.Location), "ID", "Location", result.MeetID);
            return View(result);
        }


        //list the athletes
        public ActionResult AthleteList()
        {
            var athletes = db.Athletes.Include(a => a.Team).OrderBy(b => b.Name);
            return View(athletes.ToList());
        }


        //page to show the data for a specific athlete
        public ActionResult AthleteResults(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Athlete athlete = db.Athletes.Find(id);

            if (athlete == null)
            {
                return HttpNotFound();
            }

            ViewBag.name = athlete.Name;

            var records = db.Results.Where(x => x.AthleteID == athlete.ID).Select(n => new { n.Meet.Date, n.Event.Name, n.Meet.Location, n.RaceTime }).OrderBy(o => o.Name).ThenBy(o => o.Date).ToArray();

            int recordLength = records.Count();
            //int recordLength = 5;

            DateTime[] resultsDates = new DateTime[recordLength];
            String[] resultsEvents = new string[recordLength];
            String[] resultsLocations = new String[recordLength];
            float[] resultsRaceTimes = new float[recordLength];


            for(int i = 0;i < recordLength; i++)
            {
                resultsDates[i] = records[i].Date;
                resultsEvents[i] = records[i].Name;
                resultsLocations[i] = records[i].Location;
                resultsRaceTimes[i] = records[i].RaceTime;
            }

            ViewBag.test = resultsDates[0];


            ViewBag.dates = resultsDates;
            ViewBag.events = resultsEvents;
            ViewBag.locations = resultsLocations;
            ViewBag.racetimes = resultsRaceTimes;

            ViewBag.length = recordLength;

            //AthleteResultViewModel results = new AthleteResultViewModel();
                return View(athlete);
        }



        //page for looking a the graph of athlete results for an event
        public ActionResult AthleteData()
        {
            ViewBag.TeamID = new SelectList(db.Teams.OrderBy(b => b.Name), "ID", "Name");
            ViewBag.AthleteID = new SelectList(db.Athletes.Where(a => a.TeamID == 2).OrderBy(b => b.Name), "ID", "Name");
            ViewBag.EventID = new SelectList(db.Events.OrderBy(b => b.Name), "ID", "Name");
            return View();
        }

        //get the data for the graph
        public JsonResult GetAthleteData(int athleteID, int eventID)
        {
            Console.WriteLine(athleteID);
            Console.WriteLine(eventID);

            var athleteData = db.Results.Where(x => x.AthleteID == athleteID).Where(y => y.EventID == eventID).Select(n => new { n.Meet.Date, n.Event.Name, n.RaceTime }).OrderBy(o => o.Date).ToArray();

            List<string> dates = new List<string>();
            List<float> times = new List<float>();

            int length = athleteData.Count();

            for(int i=0; i<length; i++)
            {
                dates.Add(athleteData[i].Date.ToString());
                times.Add(athleteData[i].RaceTime);

            }


            var data = new
            {
                x = dates,
                y = times
            };

            return Json(data, JsonRequestBehavior.AllowGet);
        }



        //get the athletes for the team selected in athlete data
        public JsonResult GetTeamAthlete(int teamID)
        {
            Debug.WriteLine(teamID);

            var athleteData = db.Athletes.Where(a => a.TeamID == teamID).Select(c => new { c.ID, c.Name }).OrderBy(b => b.Name).ToArray();



            List<int> ids = new List<int>();
            List<string> names = new List<string>();

            int length = athleteData.Count();

            for (int i = 0; i < length; i++)
            {
                ids.Add(athleteData[i].ID);
                names.Add(athleteData[i].Name);

                Debug.WriteLine("id:" + ids[i] + "   name:" + names[i]);
                

            }


            var data = new
            {
                id = ids,
                name = names
            };
            
            return Json(data, JsonRequestBehavior.AllowGet);
        }



        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                db.Dispose();
            }
            base.Dispose(disposing);
        }
    }
}